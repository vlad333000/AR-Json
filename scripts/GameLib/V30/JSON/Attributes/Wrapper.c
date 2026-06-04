class V30_JSON_WrapperSerializerAttribute : V30_JSON_SerializerAttribute {
    override void Serialize(notnull V30_JSON_Serializer serializer, Class instance) {
        auto instanceSerializer = V30_JSON_SerializerHelper.GetSerializerAttribute(instance);
        instanceSerializer.Serialize(serializer, instance);
    };
};

class V30_JSON_WrapperSerializerAttributeHelperT<Class T> {
	static void SerializeArray(notnull V30_JSON_Serializer serializer, notnull Managed arr, notnull V30_JSON_WrapperSerializerAttribute arrSerializer) {
		foreach (auto element : array<T>.Cast(arr))
			arrSerializer.Serialize(serializer, element);
	};
	
	static void SerializeObject(notnull V30_JSON_Serializer serializer, notnull Managed obj, notnull V30_JSON_WrapperSerializerAttribute objSerializer) {
		foreach (auto key, auto element : map<string, T>.Cast(obj)) {
			serializer.SerializeKey(key);
			objSerializer.Serialize(serializer, element);
		};
	};
};

class V30_JSON_WrapperSerializerAttributeHelperRefT<Class T> {
	static void SerializeArray(notnull V30_JSON_Serializer serializer, notnull Managed arr, notnull V30_JSON_WrapperSerializerAttribute arrSerializer) {
		foreach (auto element : array<ref T>.Cast(arr))
			arrSerializer.Serialize(serializer, element);
	};
	
	static void SerializeObject(notnull V30_JSON_Serializer serializer, notnull Managed obj, notnull V30_JSON_WrapperSerializerAttribute objSerializer) {
		foreach (auto key, auto element : map<string, ref T>.Cast(obj)) {
			serializer.SerializeKey(key);
			objSerializer.Serialize(serializer, element);
		};
	};
};
