class V30_Json_BasicSerializer : V30_Json_Serializer {
	override void WriteNull() {
		Write("null");
	};

	override void WriteBool(bool value) {
		Write(value.ToString(numerical: false));
	};

	override void WriteInt(int value) {
		Write(value.ToString());
	};

	override void WriteFloat(float value) {
		Write(value.ToString());
	};

	override void WriteString(string value) {
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

	override void WriteArrayBegin() {
		Write("[");
	};

	override void WriteArrayEnd() {
		Write("]");
	};

	override void WriteObjectBegin() {
		Write("{");
	};

	override void WriteObjectEnd() {
		Write("}");
	};

	override void WriteComma() {
		Write(",");
	};

	override void WriteColon() {
		Write(":");
	};

    protected void Write(string data);

	protected void WriteSubstring(string src, int from, int count) {
		// enfusion://ScriptEditor/scripts/Core/generated/Types/string.c;88
		// (Maximum output of string.Substring is limited to 8191 characters)
		auto to = from + count;
		for (auto i = from; i < to; i += 8192) {
			string str;
			if (i + 8192 > to)
				str = src.Substring(i, to - i);
			else
				str = src.Substring(i, 8192);
			Write(str);
		};
	};
};
