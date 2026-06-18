[V30_JSON_IntSerializerAttribute()]
class V30_JSON_Int : V30_JSON_Number {
    protected int value;

    void V30_JSON_Int(int newValue = 0) {
        SetValue(newValue);
    };

    int GetValue() {
        return value;
    };

    void SetValue(int newValue) {
        value = newValue;
    };

    override bool IsEqualTo(V30_JSON_Value other) {
        return IsEqualTo(V30_JSON_Int.Cast(other));
    };

    bool IsEqualTo(V30_JSON_Int other) {
        return this == other || (other && value == other.value);
    };

    override string DebugString() {
        return value.ToString();
    };
};

class V30_JSON_IntSerializerAttribute : V30_JSON_StreamSerializerAttribute {
    override void StreamSerialize(notnull V30_JSON_StreamSerializer serializer, Class instance) {
        serializer.SerializeInt(V30_JSON_Int.Cast(instance).GetValue());
    };

    override void SerializeArray(notnull V30_JSON_Serializer serializer, notnull Managed arr) {
        V30_JSON_SerializerAttributeHelperT<V30_JSON_Int>.SerializeArray(serializer, arr);
    };

    override void SerializeArrayRef(notnull V30_JSON_Serializer serializer, notnull Managed arr) {
        V30_JSON_SerializerAttributeHelperRefT<V30_JSON_Int>.SerializeArray(serializer, arr);
    };

    override void SerializeObject(notnull V30_JSON_Serializer serializer, notnull Managed obj) {
        V30_JSON_SerializerAttributeHelperT<V30_JSON_Int>.SerializeObject(serializer, obj);
    };

    override void SerializeObjectRef(notnull V30_JSON_Serializer serializer, notnull Managed obj) {
        V30_JSON_SerializerAttributeHelperRefT<V30_JSON_Int>.SerializeObject(serializer, obj);
    };
};
