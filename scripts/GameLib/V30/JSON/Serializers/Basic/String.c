class V30_Json_StringSerializer : V30_Json_BasicSerializer {
	protected string data;

	void V30_Json_StringSerializer() {
		this.data = "";
	};

	string GetString() {
		return this.data;
	};

	void ClearString() {
		this.data = "";
	};

    override protected void Write(string data) {
        this.data += data;
    };
};
