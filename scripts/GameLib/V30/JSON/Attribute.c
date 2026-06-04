class V30_JSON_SerializerAttribute {
    /*modded*/ void Serialize(notnull V30_JSON_Serializer serializer, Class instance);

    /*modded*/ void SerializeArray(notnull V30_JSON_Serializer serializer, notnull Managed arr);

    /*modded*/ void SerializeArrayRef(notnull V30_JSON_Serializer serializer, notnull Managed arr);

    /*modded*/ void SerializeObject(notnull V30_JSON_Serializer serializer, notnull Managed obj);

    /*modded*/ void SerializeObjectRef(notnull V30_JSON_Serializer serializer, notnull Managed obj);

    /*modded*/ void Deserialize(out Class instance, notnull V30_JSON_Deserializer deserializer);
};

class V30_JSON_SerializerAttributeHelperT<Class T> {
    protected void V30_JSON_SerializerAttributeHelperT();

    static void SerializeArray(notnull V30_JSON_Serializer serializer, notnull Managed arr) {
        foreach (auto instance : array<T>.Cast(arr))
            serializer.Serialize(instance);
    };

    static void SerializeObject(notnull V30_JSON_Serializer serializer, notnull Managed arr) {
        foreach (auto key, auto instance : map<string, T>.Cast(arr)) {
            serializer.SerializeKey(key);
            serializer.Serialize(instance);
        };
    };
};

class V30_JSON_SerializerAttributeHelperRefT<Managed T> {
    protected void V30_JSON_SerializerAttributeHelperRefT();

    static void SerializeArray(notnull V30_JSON_Serializer serializer, notnull Managed arr) {
        foreach (auto instance : array<ref T>.Cast(arr))
            serializer.Serialize(instance);
    };

    static void SerializeObject(notnull V30_JSON_Serializer serializer, notnull Managed arr) {
        foreach (auto key, auto instance : map<string, ref T>.Cast(arr)) {
            serializer.SerializeKey(key);
            serializer.Serialize(instance);
        };
    };
};
