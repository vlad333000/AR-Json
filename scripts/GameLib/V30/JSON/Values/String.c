[V30_JSON_StringSerializerAttribute()]
class V30_JSON_String : V30_JSON_Value {
    protected string m_Value;

    void V30_JSON_String(string value = "") {
        SetValue(value);
    };

    int Length() {
        return m_Value.Length();
    };

    string GetValue() {
        return m_Value;
    };

    void SetValue(string newValue) {
        m_Value = newValue;
    };

    override bool IsEqualTo(V30_JSON_Value other) {
        return IsEqualTo(V30_JSON_String.Cast(other));
    };

    bool IsEqualTo(V30_JSON_String other) {
        return this == other || (other && m_Value == other.m_Value);
    };

    override string DebugString() {
        if (m_Value.Length() < 256)
            return "\"" + m_Value + "\"";
        else
            return "\"" + m_Value.Substring(0, 254) + "...";
    };
};

class V30_JSON_StringSerializerAttribute : V30_JSON_StreamSerializerAttribute {
    override void StreamSerialize(notnull V30_JSON_StreamSerializer serializer, Class instance) {
        serializer.SerializeString(V30_JSON_String.Cast(instance).GetValue());
    };

    override void SerializeArray(notnull V30_JSON_Serializer serializer, notnull Managed arr) {
        V30_JSON_SerializerAttributeHelperT<V30_JSON_String>.SerializeArray(serializer, arr);
    };

    override void SerializeArrayRef(notnull V30_JSON_Serializer serializer, notnull Managed arr) {
        V30_JSON_SerializerAttributeHelperRefT<V30_JSON_String>.SerializeArray(serializer, arr);
    };

    override void SerializeObject(notnull V30_JSON_Serializer serializer, notnull Managed obj) {
        V30_JSON_SerializerAttributeHelperT<V30_JSON_String>.SerializeObject(serializer, obj);
    };

    override void SerializeObjectRef(notnull V30_JSON_Serializer serializer, notnull Managed obj) {
        V30_JSON_SerializerAttributeHelperRefT<V30_JSON_String>.SerializeObject(serializer, obj);
    };
};

