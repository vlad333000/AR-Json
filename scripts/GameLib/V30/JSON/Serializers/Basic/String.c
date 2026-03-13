class V30_Json_StringSerializer : V30_Json_BasicSerializer {
	protected string data;

	void V30_Json_StringSerializer() {
		this.data = "";
	};

	string GetString() {
		#ifdef ENABLE_DIAG
		if (!IsEnded())
			Debug.Error(string.Format("[V30][JSON][StringSerializer] GetString(): Trying to get string in the middle of serialization."));
		#endif
		return this.data;
	};

    override protected void Write(string data) {
        this.data += data;
    };

	override void ResetState() {
		super.ResetState();
		this.data = "";
	};
};
