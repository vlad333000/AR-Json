class V30_JSON_StreamDeserializer : V30_JSON_Deserializer {
    // Begins array deserialization.
    bool BeginArrayDeserialization();

    // Ends array deserialization.
    bool EndArrayDeserialization();

    // Begins object (key-value pairs) deserialization.
    bool BeginObjectDeserialization();

    // Deserialize key for object (key-value pairs) element deserialization.
    protected bool DeserializeKey(out string key) {
        return DeserializeString(key);
    };

    // Ends object (key-value pairs) deserialization.
    bool EndObjectDeserialization();

    override bool EndDeserialization() {
        auto isEnded = IsEnd();
        if (!super.EndDeserialization())
            return false;
        if (!isEnded)
            return Error("some data after end of deserialization");
        return true;
    };



    // Checks if stream is at the end.
	bool IsEnd();

    // Checks if next value in stream is container (array or object (key-value pairs)) end.
    bool IsContainerEnd();

    // Checks if next value in stream is array end.
    bool IsArrayEnd();

    // Checks if next value in stream is object (key-value pairs) end.
    bool IsObjectEnd();



    override bool ForEachArray(notnull V30_JSON_DeserializerArrayVisitor visitor) {
        if (!BeginArrayDeserialization())
            return false;
        if (!visitor.OnBegin(this))
            return false;
        while (!IsArrayEnd())
            if (!visitor.OnElement(this))
                return false;
        if (!EndArrayDeserialization())
            return false;
        return visitor.OnEnd(this);
    };

    override bool ForEachObject(notnull V30_JSON_DeserializerObjectVisitor visitor) {
        if (!BeginObjectDeserialization())
            return false;
        if (!visitor.OnBegin(this))
            return false;
        string key;
        while (!IsObjectEnd()) {
            if (!DeserializeKey(key))
                return false;
            if (!visitor.OnElement(this, key))
                return false;
        };
        if (!EndObjectDeserialization())
            return false;
        return visitor.OnEnd(this);
    };
};

