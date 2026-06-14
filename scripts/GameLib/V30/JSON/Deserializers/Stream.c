enum V30_JSON_EDeserializerContext {
    ROOT,
    ROOT_VALUE,
    ARRAY,
    ARRAY_VALUE,
    OBJECT,
    OBJECT_KEY,
    OBJECT_VALUE,
    END
};

class V30_JSON_StreamDeserializer : V30_JSON_Deserializer {
    protected ref array<V30_JSON_EDeserializerContext> m_DeserializationContexts;

    void V30_JSON_StreamDeserializer() {
        m_DeserializationContexts = new array<V30_JSON_EDeserializerContext>();
    };

    bool IsDeserializingValue() {
        auto context = GetDeserializationContext();
        return context == V30_JSON_EDeserializerContext.ROOT_VALUE || context == V30_JSON_EDeserializerContext.ARRAY_VALUE || context == V30_JSON_EDeserializerContext.OBJECT_VALUE;
    };

    bool IsDeserializingRoot() {
        auto context = GetDeserializationContext();
        return context == V30_JSON_EDeserializerContext.ROOT || context == V30_JSON_EDeserializerContext.ROOT_VALUE;
    };

    bool IsDeserializingArray() {
        auto context = GetDeserializationContext();
        return context == V30_JSON_EDeserializerContext.ARRAY || context == V30_JSON_EDeserializerContext.ARRAY_VALUE;
    };

    bool IsDeserializingArrayValue() {
        return GetDeserializationContext() == V30_JSON_EDeserializerContext.ARRAY_VALUE;
    };

    bool IsDeserializingObject() {
        auto context = GetDeserializationContext();
        return context == V30_JSON_EDeserializerContext.OBJECT || context == V30_JSON_EDeserializerContext.OBJECT_KEY || context == V30_JSON_EDeserializerContext.OBJECT_VALUE;
    };

    bool IsDeserializingObjectKey() {
        return GetDeserializationContext() == V30_JSON_EDeserializerContext.OBJECT_KEY;
    };

    bool IsDeserializingObjectValue() {
        return GetDeserializationContext() == V30_JSON_EDeserializerContext.OBJECT_VALUE;
    };

    bool IsDeserializingEnd() {
        return GetDeserializationContext() == V30_JSON_EDeserializerContext.END;
    };

    protected bool BeginValueDeserialization() {
        if (!IsDeserializingValue())
            return Error("expected value deserialization context");
        PopDeserializationContext();
        return true;
    };

    protected bool EndValueDeserialization() {
        auto context = GetDeserializationContext();
        switch (context) {
            case V30_JSON_EDeserializerContext.ROOT:
                return true;
            case V30_JSON_EDeserializerContext.ARRAY:
                PushDeserializationContext(V30_JSON_EDeserializerContext.ARRAY_VALUE);
                return true;
            case V30_JSON_EDeserializerContext.OBJECT:
                PushDeserializationContext(V30_JSON_EDeserializerContext.OBJECT_KEY);
                return true;
            default:
                return Error("Unexpected deserialization context");
        };
        return Error("Unreached code reached");
    };

    // Begins array deserialization.
    bool BeginArrayDeserialization() {
        if (!BeginValueDeserialization())
            return Error("expected value deserialization context");
        PushDeserializationContext(V30_JSON_EDeserializerContext.ARRAY);
        PushDeserializationContext(V30_JSON_EDeserializerContext.ARRAY_VALUE);
        return true;
    };

    // Ends array deserialization.
    bool EndArrayDeserialization() {
        if (!PopDeserializationContext(V30_JSON_EDeserializerContext.ARRAY_VALUE))
            return Error("expected array's value deserialization context");
        if (!PopDeserializationContext(V30_JSON_EDeserializerContext.ARRAY))
            return Error("expected array deserialization context");
        return EndValueDeserialization();
    };

    // Begins object (key-value pairs) deserialization.
    bool BeginObjectDeserialization() {
        if (!BeginValueDeserialization())
            return Error("expected value deserialization context");
        PushDeserializationContext(V30_JSON_EDeserializerContext.OBJECT);
        PushDeserializationContext(V30_JSON_EDeserializerContext.OBJECT_KEY);
        return true;
    };

    // Ends object (key-value pairs) deserialization.
    bool EndObjectDeserialization() {
        if (!PopDeserializationContext(V30_JSON_EDeserializerContext.OBJECT_KEY))
            return Error("expected object's key deserialization context");
        if (!PopDeserializationContext(V30_JSON_EDeserializerContext.OBJECT))
            return Error("expected object deserialization context");
        return EndValueDeserialization();
    };

    // Checks if stream is at the end.
	bool IsEnd();

    // Checks if next value in stream is container (array or object (key-value pairs)) end.
    bool IsContainerEnd();

    // Checks if next value in stream is array end.
    bool IsArrayEnd();

    // Checks if next value in stream is object (key-value pairs) end.
    bool IsObjectEnd();



    V30_JSON_EDeserializerContext GetDeserializationContext() {
        auto n = m_DeserializationContexts.Count();
        auto last = n - 1;
        return m_DeserializationContexts[last];
    };

    protected void PushDeserializationContext(V30_JSON_EDeserializerContext context) {
        m_DeserializationContexts.Insert(context);
    };

    protected bool PopDeserializationContext(V30_JSON_EDeserializerContext expectedContext) {
        if (GetDeserializationContext() != expectedContext)
            return ErrorFormat("expected %1 context end, actual context is %2", expectedContext.ToString(), GetDeserializationContext().ToString());
        PopDeserializationContext();
        return true;
    };

    protected void PopDeserializationContext() {
        auto n = m_DeserializationContexts.Count();
        auto last = n - 1;
        m_DeserializationContexts.RemoveOrdered(last);
    };



    override protected bool BeginDeserialization() {
        if (!super.BeginDeserialization())
            return false;
        m_DeserializationContexts.Clear();
        PushDeserializationContext(V30_JSON_EDeserializerContext.ROOT);
        PushDeserializationContext(V30_JSON_EDeserializerContext.ROOT_VALUE);
        return true;
    };

    override bool EndDeserialization() {
        auto isEnded = IsEnd();
        auto isRoot = IsDeserializingRoot();
        if (!super.EndDeserialization())
            return false;
        if (!isRoot)
            return Error("container deserialization is not ended");
        if (!isEnded)
            return Error("some data after end of deserialization");
        return true;
    };

    override bool DeserializeKey(out string key) {
        if (!IsDeserializingObjectKey())
            return Error("expected object's key deserialization context");
        if (!DeserializeString(key))
            return Error("faield to deserialize object's key");
        PopDeserializationContext();
        PushDeserializationContext(V30_JSON_EDeserializerContext.OBJECT_VALUE);
        return true;
    };

    override bool IsKey() {
        return IsDeserializingObjectKey();
    };

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
