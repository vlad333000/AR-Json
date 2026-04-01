class V30_Json_StringPrettySerializer : V30_Json_BasicPrettySerializer {
	protected string data;

	void V30_Json_StringPrettySerializer(int tabSpaceCount = -1) {
		this.data = "";
	};

	string GetString() {
		return this.data;
	};

    override protected void SerializeRaw(string data) {
        this.data += data;
    };
};
