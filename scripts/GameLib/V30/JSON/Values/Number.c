//[V30_JSON_NumberSerializerAttribute()]
class V30_JSON_Number : V30_JSON_Value {
    protected void V30_JSON_Number();
};

class V30_JSON_NumberSerializerAttribute : V30_JSON_WrapperSerializerAttribute {
    override void SerializeArray(notnull V30_JSON_Serializer serializer, notnull Managed arr) {
        V30_JSON_WrapperSerializerAttributeHelperT<V30_JSON_Number>.SerializeArray(serializer, arr, this);
    };

    override void SerializeArrayRef(notnull V30_JSON_Serializer serializer, notnull Managed arr) {
        V30_JSON_WrapperSerializerAttributeHelperRefT<V30_JSON_Number>.SerializeArray(serializer, arr, this);
    };

    override void SerializeObject(notnull V30_JSON_Serializer serializer, notnull Managed obj) {
        V30_JSON_WrapperSerializerAttributeHelperT<V30_JSON_Number>.SerializeObject(serializer, obj, this);

    };

    override void SerializeObjectRef(notnull V30_JSON_Serializer serializer, notnull Managed obj) {
        V30_JSON_WrapperSerializerAttributeHelperRefT<V30_JSON_Number>.SerializeObject(serializer, obj, this);
    };
};
