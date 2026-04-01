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
};
