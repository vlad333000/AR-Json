// Describes serialization for your class.
class V30_Json_SerializerAttribute {
	// Cast `instance` to your type and call methods on `serializer` (Like `WriteInt`, `WriteString`, `WriteArrayBegin`, `WriteArrayEnd` and etc.).
	void Serialize(notnull V30_Json_Serializer serializer, Class instance);

	// Cast `arr` to `array<T>` where `T` is your type and call `Serialize` method for each element in this array.
	void SerializeArray(notnull V30_Json_Serializer serializer, notnull Managed arr);

	// Cast `arr` to `array<ref T>` where `T` is your type and call `Serialize` method for each element in this array.
	void SerializeArrayRef(notnull V30_Json_Serializer serializer, notnull Managed arr);

	// Cast `obj` to `map<string, T>` where `T` is your type and call `Serialize` method for each element in this map.
	void SerializeObject(notnull V30_Json_Serializer serializer, notnull Managed obj);

	// Cast `obj` to `map<string, ref T>` where `T` is your type and call `Serialize` method for each element in this map.
	void SerializeObjectRef(notnull V30_Json_Serializer serializer, notnull Managed obj);



	// Call methods on `deserializer` (Like `TakeInt`, `TakeString`, `BeginArray`, `BeginObject` and etc.), create instance of your type and output it to `instance`.
	// Return `true` if deserialization was successfull, otherwise return `false` and set error message to `error`.
	bool Deserialize(notnull V30_Json_Deserializer deserializer, out Class instance, out string error);

	// Cast `arr` to `array<T>` where `T` is your type and call `Deserialize` method for each element in this array.
	bool DeserializeArray(notnull V30_Json_Deserializer deserializer, out Managed arr, out string error);

	// Cast `arr` to `array<ref T>` where `T` is your type and call `Deserialize` method for each element in this array.
	bool DeserializeArrayRef(notnull V30_Json_Deserializer deserializer, out Managed arr, out string error);

	// Cast `obj` to `map<string, T>` where `T` is your type and call `Deserialize` method for each element in this map.
	bool DeserializeObject(notnull V30_Json_Deserializer deserializer, out Managed obj, out string error);

	// Cast `obj` to `map<string, ref T>` where `T` is your type and call `Deserialize` method for each element in this map.
	bool DeserializeObjectRef(notnull V30_Json_Deserializer deserializer, out Managed obj, out string error);
};

// Helper for `V30_Json_SerializerAttribute`
class V30_Json_SerializerAttributeHelperT<Class T> {
	static void SerializeArray(notnull V30_Json_Serializer serializer, notnull Managed arr, notnull V30_Json_SerializerAttribute attribute) {
		serializer.WriteArrayBegin();
		foreach (auto i, auto el : array<T>.Cast(arr)) {
			if (i > 0)
				serializer.WriteComma();
			attribute.Serialize(serializer, el);
		};
		serializer.WriteArrayEnd();
	};

	static void SerializeObject(notnull V30_Json_Serializer serializer, notnull Managed obj, notnull V30_Json_SerializerAttribute attribute) {
		serializer.WriteObjectBegin();
		auto comma = false;
		foreach (auto key, auto el : map<string, T>.Cast(obj)) {
			if (comma)
				serializer.WriteComma();
			else
				comma = true;
			serializer.WriteString(key);
			serializer.WriteColon();
			attribute.Serialize(serializer, el);
		};
		serializer.WriteObjectEnd();
	};
};

// Strong reference version of helper for `V30_Json_SerializerAttribute`
class V30_Json_SerializerAttributeHelperRefT<Managed T> {
	static void SerializeArray(notnull V30_Json_Serializer serializer, notnull Managed arr, notnull V30_Json_SerializerAttribute attribute) {
		serializer.WriteArrayBegin();
		foreach (auto i, auto el : array<ref T>.Cast(arr)) {
			if (i > 0)
				serializer.WriteComma();
			attribute.Serialize(serializer, el);
		};
		serializer.WriteArrayEnd();
	};

	static void SerializeObject(notnull V30_Json_Serializer serializer, notnull Managed obj, notnull V30_Json_SerializerAttribute attribute) {
		serializer.WriteObjectBegin();
		auto comma = false;
		foreach (auto key, auto el : map<string, ref T>.Cast(obj)) {
			if (comma)
				serializer.WriteComma();
			else
				comma = true;
			serializer.WriteString(key);
			serializer.WriteColon();
			attribute.Serialize(serializer, el);
		};
		serializer.WriteObjectEnd();
	};
};
