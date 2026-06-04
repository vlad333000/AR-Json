class V30_JSON_StreamSerializer : V30_JSON_Serializer {
    protected void V30_JSON_StreamSerializer();

    override void Serialize(notnull V30_JSON_Null value) {
        Serialize(value.GetValue());
    };

    override void Serialize(notnull V30_JSON_Bool value) {
        Serialize(value.GetValue());
    };

    override void Serialize(notnull V30_JSON_Int value) {
        Serialize(value.GetValue());
    };

    override void Serialize(notnull V30_JSON_Float value) {
        Serialize(value.GetValue());
    };

    override void Serialize(notnull V30_JSON_String value) {
        Serialize(value.GetValue());
    };

    override void Serialize(notnull V30_JSON_Array value) {
        Serialize(value.GetValue());
    };

    override void Serialize(notnull V30_JSON_Object value) {
        Serialize(value.GetValue());
    };

    void Serialize(string key, notnull V30_JSON_Value value) {
        if (value.IsInherited(V30_JSON_Null))
            Serialize(key, V30_JSON_Null.Cast(value));
        else if (value.IsInherited(V30_JSON_Bool))
            Serialize(key, V30_JSON_Bool.Cast(value));
        else if (value.IsInherited(V30_JSON_Number))
            Serialize(key, V30_JSON_Number.Cast(value));
        else if (value.IsInherited(V30_JSON_String))
            Serialize(key, V30_JSON_String.Cast(value));
        else if (value.IsInherited(V30_JSON_Container))
            Serialize(key, V30_JSON_Container.Cast(value));
    };

    void Serialize(string key, notnull V30_JSON_Null value) {
        Serialize(key, value.GetValue());
    };

    void Serialize(string key, notnull V30_JSON_Bool value) {
        Serialize(key, value.GetValue());
    };

    void Serialize(string key, notnull V30_JSON_Number value) {
        if (value.IsInherited(V30_JSON_Int))
            Serialize(key, V30_JSON_Int.Cast(value));
        else if (value.IsInherited(V30_JSON_Float))
            Serialize(key, V30_JSON_Float.Cast(value));
    };

    void Serialize(string key, notnull V30_JSON_Int value) {
        Serialize(key, value.GetValue());
    };

    void Serialize(string key, notnull V30_JSON_Float value) {
        Serialize(key, value.GetValue());
    };

    void Serialize(string key, notnull V30_JSON_String value) {
        Serialize(key, value.GetValue());
    };

    void Serialize(string key, notnull V30_JSON_Container value) {
        if (value.IsInherited(V30_JSON_Array))
            Serialize(key, V30_JSON_Array.Cast(value));
        else if (value.IsInherited(V30_JSON_Object))
            Serialize(key, V30_JSON_Object.Cast(value));
    };

    void Serialize(string key, notnull V30_JSON_Array value) {
        Serialize(key, value.GetValue());
    };

    void Serialize(string key, notnull V30_JSON_Object value) {
        Serialize(key, value.GetValue());
    };

    /*modded*/ void BeginArraySerialization();

    /*modded*/ void BeginArraySerialization(string key) {
        SerializeKey(key);
        BeginArraySerialization();
    };

    /*modded*/ void EndArraySerialization();

    /*modded*/ void BeginObjectSerialization();

    /*modded*/ void BeginObjectSerialization(string key) {
        SerializeKey(key);
        BeginObjectSerialization();
    };

    /*modded*/ void EndObjectSerialization();



    protected void SerializeNull();

    protected void SerializeNull(string key) {
        SerializeKey(key);
        SerializeNull();
    };

    void Serialize(string key, bool value) {
        SerializeKey(key);
        Serialize(value);
    };

    void Serialize(string key, int value) {
        SerializeKey(key);
        Serialize(value);
    };

    void Serialize(string key, float value) {
        SerializeKey(key);
        Serialize(value);
    };

    void Serialize(string key, string value) {
        SerializeKey(key);
        Serialize(value);
    };

    override void Serialize(Class instance) {
        if (!instance) {
            SerializeNull();
            return;
        };
        V30_JSON_StreamSerializerHelper.Serialize(this, instance);
    };

    void Serialize(string key, Class instance) {
        SerializeKey(key);
        Serialize(instance);
    };
};

class V30_JSON_StreamSerializerHelper {
    protected void V30_JSON_StreamSerializerHelper();

    static void Serialize(notnull V30_JSON_StreamSerializer serializer, notnull Class instance) {
        auto type = instance.Type();
        Serialize(serializer, instance, type);
    };

    static void Serialize(notnull V30_JSON_StreamSerializer serializer, notnull Class instance, typename type) {
        if (type.IsInherited(array))
            SerializeArray(serializer, Managed.Cast(instance), type);
        else if (type.IsInherited(map))
            SerializeObject(serializer, Managed.Cast(instance), type);
        else
            SerializeClass(serializer, instance, type);
    };

    static void SerializeArray(notnull V30_JSON_StreamSerializer serializer, notnull Managed arr) {
        auto arrType = arr.Type();
        SerializeArray(serializer, arr, arrType);
    };

    static void SerializeArray(notnull V30_JSON_StreamSerializer serializer, notnull Managed arr, typename arrType) {
        bool arrSubTypeIsRef;
        auto arrSubType = V30_JSON_SerializerHelper.GetArraySubType(arrType, arrSubTypeIsRef);
        SerializeArray(serializer, arr, arrSubType, arrSubTypeIsRef);
    };

    static void SerializeArray(notnull V30_JSON_StreamSerializer serializer, notnull Managed arr, typename arrSubType, bool arrSubTypeIsRef) {
        switch (arrSubType) {
            case bool:
                V30_JSON_StreamSerializerHelperT<bool>.SerializeArray(serializer, arr);
                break;
            case int:
                V30_JSON_StreamSerializerHelperT<int>.SerializeArray(serializer, arr);
                break;
            case float:
                V30_JSON_StreamSerializerHelperT<float>.SerializeArray(serializer, arr);
                break;
            case string:
                V30_JSON_StreamSerializerHelperT<string>.SerializeArray(serializer, arr);
                break;
            default:
                if (arrSubType.IsInherited(Class)) {
                    auto arrSubTypeSerializer = V30_JSON_SerializerHelper.GetSerializerAttribute(arrSubType);
                    SerializeArray(serializer, arr, arrSubTypeSerializer, arrSubTypeIsRef);
                };
                break;
        };
    };

    static void SerializeArray(notnull V30_JSON_StreamSerializer serializer, notnull Managed arr, notnull V30_JSON_SerializerAttribute arrSubTypeSerializer, bool arrSubTypeIsRef) {
        if (arrSubTypeIsRef)
            SerializeArrayRef(serializer, arr, arrSubTypeSerializer);
        else
            SerializeArray(serializer, arr, arrSubTypeSerializer);
    };

    static void SerializeArray(notnull V30_JSON_StreamSerializer serializer, notnull Managed arr, notnull V30_JSON_SerializerAttribute arrSubTypeSerializer) {
        serializer.BeginArraySerialization();
        arrSubTypeSerializer.SerializeArray(serializer, arr);
        serializer.EndArraySerialization();
    };

    static void SerializeArrayRef(notnull V30_JSON_StreamSerializer serializer, notnull Managed arr, notnull V30_JSON_SerializerAttribute arrSubTypeSerializer) {
        serializer.BeginArraySerialization();
        arrSubTypeSerializer.SerializeArrayRef(serializer, arr);
        serializer.EndArraySerialization();
    };

    static void SerializeObject(notnull V30_JSON_StreamSerializer serializer, notnull Managed obj) {
        auto objType = obj.Type();
        SerializeObject(serializer, obj, objType);
    };

    static void SerializeObject(notnull V30_JSON_StreamSerializer serializer, notnull Managed obj, typename objType) {
        bool objSubTypeIsRef;
        auto objSubType = V30_JSON_SerializerHelper.GetObjectSubType(objType, objSubTypeIsRef);
        SerializeObject(serializer, obj, objSubType, objSubTypeIsRef);
    };

    static void SerializeObject(notnull V30_JSON_StreamSerializer serializer, notnull Managed obj, typename objSubType, bool objSubTypeIsRef) {
        switch (objSubType) {
            case bool:
                V30_JSON_StreamSerializerHelperT<bool>.SerializeObject(serializer, obj);
                break;
            case int:
                V30_JSON_StreamSerializerHelperT<int>.SerializeObject(serializer, obj);
                break;
            case float:
                V30_JSON_StreamSerializerHelperT<float>.SerializeObject(serializer, obj);
                break;
            case string:
                V30_JSON_StreamSerializerHelperT<string>.SerializeObject(serializer, obj);
                break;
            default:
                if (objSubType.IsInherited(Class)) {
                    auto objSubTypeSerializer = V30_JSON_SerializerHelper.GetSerializerAttribute(objSubType);
                    SerializeObject(serializer, obj, objSubTypeSerializer, objSubTypeIsRef);
                };
                break;
        };
    };

    static void SerializeObject(notnull V30_JSON_StreamSerializer serializer, notnull Managed obj, notnull V30_JSON_SerializerAttribute objSubTypeSerializer, bool objSubTypeIsRef) {
        if (objSubTypeIsRef)
            SerializeObjectRef(serializer, obj, objSubTypeSerializer);
        else
            SerializeObject(serializer, obj, objSubTypeSerializer);
    };

    static void SerializeObject(notnull V30_JSON_StreamSerializer serializer, notnull Managed obj, notnull V30_JSON_SerializerAttribute objSubTypeSerializer) {
        serializer.BeginObjectSerialization();
        objSubTypeSerializer.SerializeObject(serializer, obj);
        serializer.EndObjectSerialization();
    };

    static void SerializeObjectRef(notnull V30_JSON_StreamSerializer serializer, notnull Managed obj, notnull V30_JSON_SerializerAttribute objSubTypeSerializer) {
        serializer.BeginObjectSerialization();
        objSubTypeSerializer.SerializeObjectRef(serializer, obj);
        serializer.EndObjectSerialization();
    };

    static void SerializeClass(notnull V30_JSON_StreamSerializer serializer, notnull Class instance) {
        auto type = instance.Type();
        SerializeClass(serializer, instance, type);
    };

    static void SerializeClass(notnull V30_JSON_StreamSerializer serializer, notnull Class instance, typename type) {
        auto instanceSerializer = V30_JSON_SerializerHelper.GetSerializerAttribute(type);
        SerializeClass(serializer, instance, instanceSerializer);
    };

    static void SerializeClass(notnull V30_JSON_StreamSerializer serializer, notnull Class instance, notnull V30_JSON_SerializerAttribute instanceSerializer) {
        instanceSerializer.Serialize(serializer, instance);
    };
};

class V30_JSON_StreamSerializerHelperT<Class T> {
    protected void V30_JSON_StreamSerializerHelperT();

    static void SerializeArray(notnull V30_JSON_StreamSerializer serializer, notnull Managed arr) {
        serializer.BeginArraySerialization();
        foreach (auto value : array<T>.Cast(arr))
            serializer.Serialize(value);
        serializer.EndArraySerialization();
    };

    static void SerializeObject(notnull V30_JSON_StreamSerializer serializer, notnull Managed obj) {
        serializer.BeginObjectSerialization();
        foreach (auto key, auto value : map<string, T>.Cast(obj))
            serializer.Serialize(key, value);
        serializer.EndObjectSerialization();
    };
};

class V30_JSON_StreamSerializerHelperRefT<Managed T> {
    protected void V30_JSON_StreamSerializerHelperRefT();

    static void SerializeArray(notnull V30_JSON_StreamSerializer serializer, notnull Managed arr) {
        serializer.BeginArraySerialization();
        foreach (auto value : array<ref T>.Cast(arr))
            serializer.Serialize(value);
        serializer.EndArraySerialization();
    };

    static void SerializeObject(notnull V30_JSON_StreamSerializer serializer, notnull Managed obj) {
        serializer.BeginObjectSerialization();
        foreach (auto key, auto value : map<string, ref T>.Cast(obj))
            serializer.Serialize(key, value);
        serializer.EndObjectSerialization();
    };
};
