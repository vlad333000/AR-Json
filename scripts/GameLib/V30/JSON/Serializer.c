// JSON serializer.
class V30_Json_Serializer : Managed {
	protected void V30_Json_Serializer();

	// Serialize `null`.
	void WriteNull();

	// Serialize boolean value (`true` or `false`).
	void WriteBool(bool value);

	// Serialize integer value.
	void WriteInt(int value);

	// Serialize floating point value.
	void WriteFloat(float value);

	// Serialize string (includes sanitization).
	void WriteString(string value);

	// Starts serialization of array.
	void WriteArrayBegin();

	// Ends serialization of array.
	void WriteArrayEnd();

	// Starts serialization of object (key-value pairs).
	void WriteObjectBegin();

	// Ends serialization of object (key-value pairs).
	void WriteObjectEnd();

	// Serialize separator for array or object elements.
	void WriteComma();

	// Serialize separator for key and value of object element.
	void WriteColon();

	// Serialize custom class. If `instance` is `null` then serialize `null`.
	// `instance` must be of type that defines `V30_Json_SerializerAttribute`.
	void WriteClass(Class instance) {
		if (!instance) {
			WriteNull();
			return;
		};
		auto type = instance.Type();
		WriteClassT(instance, type);
	};

	// Finds `V30_Json_SerializerAttribute` for `type` and calls it for `instance`.
	// `type` must define `V30_Json_SerializerAttribute`.
	void WriteClassT(Class instance, typename type) {
		auto serializerAttribute = V30_Json_SerializerHelper.GetSerializerAttribute(type);
		#ifdef ENABLE_DIAG
		if (!serializerAttribute)
			Debug.Error(string.Format("[V30][JSON][Serializer] WriteClassT(Class, typename): No serializer for type `%1`.", type));
		#endif
		serializerAttribute.Serialize(this, instance);
	};
};
