class V30_JSON_StreamSerializer : V30_JSON_Serializer {
    protected void V30_JSON_StreamSerializer();

    /*modded*/ void BeginArraySerialization();

    /*modded*/ void EndArraySerialization();

    /*modded*/ void BeginObjectSerialization();

    /*modded*/ void EndObjectSerialization();

    override void SerializeArray(notnull V30_JSON_Array value) {
        BeginArraySerialization();
        super.SerializeArray(value);
        EndArraySerialization();
    };

    override void SerializeObject(notnull V30_JSON_Object value) {
        BeginObjectSerialization();
        super.SerializeObject(value);
        EndObjectSerialization();
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
            V30_JSON_SerializerHelper.Serialize(serializer, value);
        serializer.EndArraySerialization();
    };

    static void SerializeObject(notnull V30_JSON_StreamSerializer serializer, notnull Managed obj) {
        serializer.BeginObjectSerialization();
        foreach (auto key, auto value : map<string, T>.Cast(obj))
            V30_JSON_SerializerHelper.SerializePair(serializer, key, value);
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
