//[V30_JSON_ValueSerializerAttribute()]
class V30_JSON_Value : Managed {
    protected void V30_JSON_Value();

    string DebugString();
};

class V30_JSON_ValueSerializerAttribute : V30_JSON_WrapperSerializerAttribute {
    override void SerializeArray(notnull V30_JSON_Serializer serializer, notnull Managed arr) {
        V30_JSON_WrapperSerializerAttributeHelperT<V30_JSON_Value>.SerializeArray(serializer, arr, this);
    };

    override void SerializeArrayRef(notnull V30_JSON_Serializer serializer, notnull Managed arr) {
        V30_JSON_WrapperSerializerAttributeHelperRefT<V30_JSON_Value>.SerializeArray(serializer, arr, this);
    };

    override void SerializeObject(notnull V30_JSON_Serializer serializer, notnull Managed obj) {
        V30_JSON_WrapperSerializerAttributeHelperT<V30_JSON_Value>.SerializeObject(serializer, obj, this);

    };

    override void SerializeObjectRef(notnull V30_JSON_Serializer serializer, notnull Managed obj) {
        V30_JSON_WrapperSerializerAttributeHelperRefT<V30_JSON_Value>.SerializeObject(serializer, obj, this);
    };
};

class V30_JSON_ValueHelper {
    protected void V30_JSON_ValueHelper();

    static V30_JSON_Bool New(bool value) {
        return new V30_JSON_Bool(value);
    };

    static V30_JSON_Int New(int value) {
        return new V30_JSON_Int(value);
    };

    static V30_JSON_Float New(float value) {
        return new V30_JSON_Float(value);
    };

    static V30_JSON_String New(string value) {
        return new V30_JSON_String(value);
    };

    static V30_JSON_Array New(notnull array<ref V30_JSON_Value> value) {
        return new V30_JSON_Array(value);
    };

    static V30_JSON_Object New(notnull map<string, ref V30_JSON_Value> value) {
        return new V30_JSON_Object(value);
    };

    static V30_JSON_Value New(Class value) {
        if (!value)
            return new V30_JSON_Null();
        auto serializer = new V30_JSON_ValueSerializer();
        serializer.SerializeClass(value);
        return serializer.GetValue();
    };
};

class V30_JSON_ValueHelperT<Class T> {
    static V30_JSON_Array New(notnull array<T> values) {
        auto arr = new V30_JSON_Array();
        arr.GetValue().Reserve(values.Count());
        foreach (auto value : values)
            arr.Insert(V30_JSON_ValueHelper.New(value));
        return arr;
    };

    static V30_JSON_Object New(notnull map<string, T> values) {
        auto obj = new V30_JSON_Object();
        obj.GetValue().Reserve(values.Count());
        foreach (auto key, auto value : values)
            obj.Insert(key, V30_JSON_ValueHelper.New(value));
        return obj;
    };
};

class V30_JSON_ValueHelperRefT<Managed T> {
    static V30_JSON_Array New(notnull array<ref T> values) {
        auto arr = new V30_JSON_Array();
        arr.GetValue().Reserve(values.Count());
        foreach (auto value : values)
            arr.Insert(V30_JSON_ValueHelper.New(value));
        return arr;
    };

    static V30_JSON_Object New(notnull map<string, ref T> values) {
        auto obj = new V30_JSON_Object();
        obj.GetValue().Reserve(values.Count());
        foreach (auto key, auto value : values)
            obj.Insert(key, V30_JSON_ValueHelper.New(value));
        return obj;
    };
};
