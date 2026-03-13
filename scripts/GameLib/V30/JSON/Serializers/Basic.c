class V30_Json_BasicSerializer : V30_Json_Serializer {
	override void PutNull() {
		super.PutNull();
		Write("null");
	};

	override void PutBool(bool value) {
		super.PutBool(value);
        auto s = value.ToString(numerical: false); // Converts to "true" or "false" string
		Write(s);
	};

	override void PutInt(int value) {
		super.PutInt(value);
        auto s = value.ToString();
		Write(s);
	};

	override void PutFloat(float value) {
		super.PutFloat(value);
        auto s = value.ToString();
		Write(s);
	};

	override void PutString(string value) {
		super.PutString(value);
		WriteString(value);
	};

	override void BeginArray() {
		super.BeginArray();
		Write("[");
	};

	override void EndArray() {
		super.EndArray();
		Write("]");
	};

	override void BeginObject() {
		super.BeginObject();
		Write("{");
	};

	override void EndObject() {
		super.EndObject();
		Write("}");
	};

	override void PutKey(string key) {
		super.PutKey(key);
		WriteString(key);
		Write(":");
	};

	void PutComment(string comment) {
		Write("/*");
		Write(comment);
		Write("*/");
	};

	override void PutComma() {
		super.PutComma();
		Write(",");
	};

    protected void Write(string data);

	protected void WriteString(string str) {
		Write("\"");
		auto s = V30_Json_SerializerHelper.SanitizeString(str);
        Write(s);
		Write("\"");
	};
};
