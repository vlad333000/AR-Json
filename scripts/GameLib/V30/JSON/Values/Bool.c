[V30_JSON_BoolSerializerAttribute()]
class V30_JSON_Bool : V30_JSON_Value {
    protected bool m_Value;

    void V30_JSON_Bool(bool value = false) {
        SetValue(value);
    };

    bool GetValue() {
        return m_Value;
    };

    void SetValue(bool newValue) {
        m_Value = newValue;
    };

    override bool IsEqualTo(V30_JSON_Value other) {
        return IsEqualTo(V30_JSON_Bool.Cast(other));
    };

    bool IsEqualTo(V30_JSON_Bool other) {
        return this == other || (other && m_Value == other.m_Value);
    };

    override string DebugString() {
        return m_Value.ToString();
    };
};

class V30_JSON_BoolSerializerAttribute : V30_JSON_StreamSerializerAttribute {
    override void StreamSerialize(notnull V30_JSON_StreamSerializer serializer, Class instance) {
        serializer.SerializeBool(V30_JSON_Bool.Cast(instance).GetValue());
    };

    override void SerializeArray(notnull V30_JSON_Serializer serializer, notnull Managed arr) {
        V30_JSON_SerializerAttributeHelperT<V30_JSON_Bool>.SerializeArray(serializer, arr);
    };

    override void SerializeArrayRef(notnull V30_JSON_Serializer serializer, notnull Managed arr) {
        V30_JSON_SerializerAttributeHelperRefT<V30_JSON_Bool>.SerializeArray(serializer, arr);
    };

    override void SerializeObject(notnull V30_JSON_Serializer serializer, notnull Managed obj) {
        V30_JSON_SerializerAttributeHelperT<V30_JSON_Bool>.SerializeObject(serializer, obj);
    };

    override void SerializeObjectRef(notnull V30_JSON_Serializer serializer, notnull Managed obj) {
        V30_JSON_SerializerAttributeHelperRefT<V30_JSON_Bool>.SerializeObject(serializer, obj);
    };
};
