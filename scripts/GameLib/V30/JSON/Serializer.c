// JSON serializer.
class V30_Json_Serializer : Managed {
	protected void V30_Json_Serializer();

	void WriteNull();

	void WriteBool(bool value);

	void WriteInt(int value);

	void WriteFloat(float value);

	void WriteString(string value);

	void WriteArrayBegin();

	void WriteArrayEnd();

	void WriteObjectBegin();

	void WriteObjectEnd();

	void WriteComma();

	void WriteColon();

	void WriteClass(Class instance) {
		if (!instance) {
			WriteNull();
			return;
		};
		auto type = instance.Type();
		WriteClass(instance, type);
	};

	void WriteClass(Class instance, typename type) {
		auto serializerAttribute = V30_Json_SerializerHelper.GetSerializerAttribute(type);
		#ifdef ENABLE_DIAG
		if (!serializerAttribute)
			Debug.Error(string.Format("[V30][JSON][Serializer] WriteClass(Class, typename): No serializer for type `%1`.", type));
		#endif
		serializerAttribute.Serialize(this, instance);
	};
};
