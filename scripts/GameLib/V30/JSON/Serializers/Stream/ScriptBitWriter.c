class V30_JSON_ScriptBitWriterSerializer : V30_JSON_StreamSerializer {
    protected ScriptBitWriter writer;

    void V30_JSON_ScriptBitWriterSerializer(notnull ScriptBitWriter newWriter) {
        SetWriter(newWriter);
    };

    ScriptBitWriter GetWriter() {
        return writer;
    };

    void SetWriter(notnull ScriptBitWriter newWriter) {
        writer = newWriter;
    };



    override protected void SerializeNull() {
        WriteType(V30_JSON_ScriptBitWriterSerializer_Value.Null);
    };

    override void Serialize(bool value) {
        WriteType(V30_JSON_ScriptBitWriterSerializer_Value.Bool);
        writer.WriteBool(value);
    };

    override void Serialize(int value) {
        WriteType(V30_JSON_ScriptBitWriterSerializer_Value.Int);
        writer.WriteInt(value);
    };

    override void Serialize(float value) {
        WriteType(V30_JSON_ScriptBitWriterSerializer_Value.Float);
        writer.WriteFloat(value);
    };

    override void Serialize(string value) {
        WriteType(V30_JSON_ScriptBitWriterSerializer_Value.String);
        writer.WriteString(value);
    };

    override void BeginArraySerialization() {
        WriteType(V30_JSON_ScriptBitWriterSerializer_Value.ArrayBegin);
    };

    override void EndArraySerialization() {
        WriteType(V30_JSON_ScriptBitWriterSerializer_Value.ArrayEnd);
    };

    override void BeginObjectSerialization() {
        WriteType(V30_JSON_ScriptBitWriterSerializer_Value.ObjectBegin);
    };

	override void SerializeKey(string key) {
        writer.WriteString(key);
    };

    override void EndObjectSerialization() {
        WriteType(V30_JSON_ScriptBitWriterSerializer_Value.ObjectEnd);
    };

    void WriteType(V30_JSON_ScriptBitWriterSerializer_Value type) {
        writer.WriteIntRange(type, V30_JSON_ScriptBitWriterSerializer_Value.Null, V30_JSON_ScriptBitWriterSerializer_Value.ObjectEnd);
    };
};

enum V30_JSON_ScriptBitWriterSerializer_Value {
    Null,
    Bool,
    Int,
    Float,
    String,
    ArrayBegin,
    ArrayEnd,
    ObjectBegin,
    ObjectEnd
};
