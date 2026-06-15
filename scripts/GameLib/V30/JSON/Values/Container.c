[V30_JSON_ContainerSerializerAttribute()]
class V30_JSON_Container : V30_JSON_Value {
    protected void V30_JSON_Container();

    bool IsEmpty();

    int Count();
};

class V30_JSON_ContainerSerializerAttribute : V30_JSON_WrapperSerializerAttribute {
    override void SerializeArray(notnull V30_JSON_Serializer serializer, notnull Managed arr) {
        V30_JSON_WrapperSerializerAttributeHelperT<V30_JSON_Container>.SerializeArray(serializer, arr, this);
    };

    override void SerializeArrayRef(notnull V30_JSON_Serializer serializer, notnull Managed arr) {
        V30_JSON_WrapperSerializerAttributeHelperRefT<V30_JSON_Container>.SerializeArray(serializer, arr, this);
    };

    override void SerializeObject(notnull V30_JSON_Serializer serializer, notnull Managed obj) {
        V30_JSON_WrapperSerializerAttributeHelperT<V30_JSON_Container>.SerializeObject(serializer, obj, this);

    };

    override void SerializeObjectRef(notnull V30_JSON_Serializer serializer, notnull Managed obj) {
        V30_JSON_WrapperSerializerAttributeHelperRefT<V30_JSON_Container>.SerializeObject(serializer, obj, this);
    };
};

