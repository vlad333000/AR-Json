class V30_JSON_WrapperSerializerAttribute : V30_JSON_SerializerAttribute {
    override void Serialize(notnull V30_JSON_Serializer serializer, Class instance) {
        auto instanceSerializer = V30_JSON_SerializerHelper.GetSerializerAttribute(instance);
        instanceSerializer.Serialize(serializer, instance);
    };
};

class V30_JSON_WrapperSerializerAttributeHelperT<Class T> {
	static void SerializeArray(notnull V30_JSON_Serializer serializer, notnull Managed arr, notnull V30_JSON_WrapperSerializerAttribute arrSerializer) {
		V30_JSON_SerializerHelperT<T>.SerializeArray(serializer, array<T>.Cast(arr));
	};

	static void SerializeObject(notnull V30_JSON_Serializer serializer, notnull Managed obj, notnull V30_JSON_WrapperSerializerAttribute objSerializer) {
		V30_JSON_SerializerHelperT<T>.SerializeObject(serializer, map<string, T>.Cast(obj));
	};
};

class V30_JSON_WrapperSerializerAttributeHelperRefT<Class T> {
	static void SerializeArray(notnull V30_JSON_Serializer serializer, notnull Managed arr, notnull V30_JSON_WrapperSerializerAttribute arrSerializer) {
		V30_JSON_SerializerHelperRefT<T>.SerializeArray(serializer, array<ref T>.Cast(arr));
	};

	static void SerializeObject(notnull V30_JSON_Serializer serializer, notnull Managed obj, notnull V30_JSON_WrapperSerializerAttribute objSerializer) {
		V30_JSON_SerializerHelperRefT<T>.SerializeObject(serializer, map<string, ref T>.Cast(obj));
	};
};
