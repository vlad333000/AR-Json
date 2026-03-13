// Describes serialization for your class.
class V30_Json_SerializerAttribute {
	// Cast `instance` to your type and call methods on `serializer` (Like `PutInt`, `PutString`, `BeginArray`, `BeginObject` and etc.).
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
