[V30_JSON_NullSerializerAttribute()]
class V30_JSON_Null : V30_JSON_Value {
    protected static ref V30_JSON_Null s_Instance = new V30_JSON_Null();

    void V30_JSON_Null();

    Class GetValue() {
        return null;
    };

    static V30_JSON_Null GetInstance() {
        return s_Instance;
    };

    override bool IsEqualTo(V30_JSON_Value other) {
        return IsEqualTo(V30_JSON_Null.Cast(other));
    };

    bool IsEqualTo(V30_JSON_Null other) {
        return !!other;
    };

    override string DebugString() {
        return "null";
    };
};

class V30_JSON_NullSerializerAttribute : V30_JSON_StreamSerializerAttribute {
    override void StreamSerialize(notnull V30_JSON_StreamSerializer serializer, Class instance) {
        serializer.Serialize(null);
    };

    override void SerializeArray(notnull V30_JSON_Serializer serializer, notnull Managed arr) {
        V30_JSON_SerializerAttributeHelperT<V30_JSON_Null>.SerializeArray(serializer, arr);
    };

    override void SerializeArrayRef(notnull V30_JSON_Serializer serializer, notnull Managed arr) {
        V30_JSON_SerializerAttributeHelperRefT<V30_JSON_Null>.SerializeArray(serializer, arr);
    };

    override void SerializeObject(notnull V30_JSON_Serializer serializer, notnull Managed obj) {
        V30_JSON_SerializerAttributeHelperT<V30_JSON_Null>.SerializeObject(serializer, obj);
    };

    override void SerializeObjectRef(notnull V30_JSON_Serializer serializer, notnull Managed obj) {
        V30_JSON_SerializerAttributeHelperRefT<V30_JSON_Null>.SerializeObject(serializer, obj);
    };
};
