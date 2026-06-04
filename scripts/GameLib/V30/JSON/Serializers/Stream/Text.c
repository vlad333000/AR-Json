class V30_JSON_TextSerializer : V30_JSON_StreamSerializer {
	protected bool isCommaNeeded;

    protected void V30_JSON_TextSerializer();



    override protected void SerializeNull() {
		TryWriteComma();
        Write("null");
    };

    override void Serialize(bool value) {
		TryWriteComma();
        auto data = value.ToString(false);
        Write(data);
    };

    override void Serialize(int value) {
		TryWriteComma();
        auto data = value.ToString();
        Write(data);
    };

    override void Serialize(float value) {
		TryWriteComma();
        auto data = value.ToString();
        Write(data);
    };

    override void Serialize(string value) {
		TryWriteComma();
        Write("\"");
		auto n = value.Length();
		auto from = 0;
		for (int i = 0; i < n; i++) {
			auto c = value.ToAscii(i); // Signed!
			switch (c) {
				// "
				case 0x22:
					WriteSubstring(value, from, i - from);
					from = i + 1;
					Write("\\"); // Combining escape sequence results in parser error
					Write("\""); // Combining escape sequence results in parser error
					break;
				// \
				case 0x5C:
					WriteSubstring(value, from, i - from);
					from = i + 1;
					Write("\\"); // Combining escape sequence results in parser error
					Write("\\"); // Combining escape sequence results in parser error
					break;
				// // /
				// case 0x2F:
				// 	WriteSubstring(value, from, i - from);
				// 	from = i + 1;
				// 	Write("\\/");
				// 	break;
				// BS
				case 0x08:
					WriteSubstring(value, from, i - from);
					from = i + 1;
					Write("\\b");
					break;
				// FF
				case 0x0C:
					WriteSubstring(value, from, i - from);
					from = i + 1;
					Write("\\f");
					break;
				// LF
				case 0x0A:
					WriteSubstring(value, from, i - from);
					from = i + 1;
					Write("\\n");
					break;
				// CR
				case 0x0D:
					WriteSubstring(value, from, i - from);
					from = i + 1;
					Write("\\r");
					break;
				// HT
				case 0x09:
					WriteSubstring(value, from, i - from);
					from = i + 1;
					Write("\\t");
					break;
				// 0x00..0x1F
				case 0x00:
				case 0x01:
				case 0x02:
				case 0x03:
				case 0x04:
				case 0x05:
				case 0x06:
				case 0x07:
				case 0x08:
				// case 0x09:
				// case 0x0A:
				case 0x0B:
				case 0x0C:
				// case 0x0D:
				case 0x0E:
				case 0x0F:
				case 0x10:
				case 0x11:
				case 0x12:
				case 0x13:
				case 0x14:
				case 0x15:
				case 0x16:
				case 0x17:
				case 0x18:
				case 0x19:
				case 0x1A:
				case 0x1B:
				case 0x1C:
				case 0x1D:
				case 0x1E:
				case 0x1F:
					WriteSubstring(value, from, i - from);
					from = i + 1;
                    Write(c.ToString(len: 4, hex: true, prefix: "\\u"));
					break;
			};
		};
		WriteSubstring(value, from, n - from);
		Write("\"");
    };

    override void BeginArraySerialization() {
		TryWriteComma();
        Write("[");
		isCommaNeeded = false;
    };

    override void EndArraySerialization() {
        Write("]");
		isCommaNeeded = true;
    };

    override void BeginObjectSerialization() {
		TryWriteComma();
        Write("{");
		isCommaNeeded = false;
    };

	override void SerializeKey(string key) {
		TryWriteComma();
		isCommaNeeded = false; // Prevent string serialization to put comma.
		Serialize(key);
		WriteColon();
		isCommaNeeded = false; // Prevent any value serialization to put comma (After any value is serialized, this will automatically set to `true` inside `TryWriteComma` that exists at the beginning of any value serialization).
	};

    override void EndObjectSerialization() {
        Write("}");
		isCommaNeeded = true;
    };

    void WriteComma() {
        Write(",");
    };

    void WriteColon() {
        Write(":");
    };

	bool TryWriteComma() {
		if (isCommaNeeded) {
			WriteComma();
			return true;
		}
		else {
			isCommaNeeded = true;
			return false;
		};
	};



    /*modded*/ void Write(string data);

    protected void WriteSubstring(string data, int from, int count) {
		// enfusion://ScriptEditor/scripts/Core/generated/Types/string.c;88
		// (Maximum output of string.Substring is limited to 8191 characters)
		auto to = from + count;
		for (auto i = from; i < to; i += 8192) {
			string str;
			if (i + 8192 > to)
				str = data.Substring(i, to - i);
			else
				str = data.Substring(i, 8192);
			Write(str);
		};
    };
};
