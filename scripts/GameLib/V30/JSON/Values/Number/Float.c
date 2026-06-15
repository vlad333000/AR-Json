[V30_JSON_FloatSerializerAttribute()]
class V30_JSON_Float : V30_JSON_Number {
    protected float value;

    void V30_JSON_Float(float newValue = 0.0) {
        SetValue(newValue);
    };

    float GetValue() {
        return value;
    };

    void SetValue(float newValue) {
        value = newValue;
    };
};

class V30_JSON_FloatSerializerAttribute : V30_JSON_StreamSerializerAttribute {
    override void StreamSerialize(notnull V30_JSON_StreamSerializer serializer, Class instance) {
        serializer.SerializeFloat(V30_JSON_Float.Cast(instance).GetValue());
    };

    override void SerializeArray(notnull V30_JSON_Serializer serializer, notnull Managed arr) {
        V30_JSON_SerializerAttributeHelperT<V30_JSON_Float>.SerializeArray(serializer, arr);
    };

    override void SerializeArrayRef(notnull V30_JSON_Serializer serializer, notnull Managed arr) {
        V30_JSON_SerializerAttributeHelperRefT<V30_JSON_Float>.SerializeArray(serializer, arr);
    };

    override void SerializeObject(notnull V30_JSON_Serializer serializer, notnull Managed obj) {
        V30_JSON_SerializerAttributeHelperT<V30_JSON_Float>.SerializeObject(serializer, obj);
    };

    override void SerializeObjectRef(notnull V30_JSON_Serializer serializer, notnull Managed obj) {
        V30_JSON_SerializerAttributeHelperRefT<V30_JSON_Float>.SerializeObject(serializer, obj);
    };
};
