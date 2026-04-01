class V30_Json_BasicSerializer : V30_Json_Serializer {
	override void SerializeNull() {
		SerializeRaw("null");
	};

	override void SerializeBool(bool value) {
		SerializeRaw(value.ToString(numerical: false));
	};

	override void SerializeInt(int value) {
		SerializeRaw(value.ToString());
	};

	override void SerializeFloat(float value) {
		SerializeRaw(value.ToString());
	};

	override void SerializeString(string value) {
		SerializeRaw("\"");
		auto n = value.Length();
		auto from = 0;
		for (int i = 0; i < n; i++) {
			auto c = value.ToAscii(i); // Signed!
			switch (c) {
				// "
				case 0x22:
					SerializeSubstring(value, from, i - from);
					from = i + 1;
					SerializeRaw("\\"); // Combining escape sequence results in parser error
					SerializeRaw("\""); // Combining escape sequence results in parser error
					break;
				// \
				case 0x5C:
					SerializeSubstring(value, from, i - from);
					from = i + 1;
					SerializeRaw("\\"); // Combining escape sequence results in parser error
					SerializeRaw("\\"); // Combining escape sequence results in parser error
					break;
				// // /
				// case 0x2F:
				// 	SerializeSubstring(value, from, i - from);
				// 	from = i + 1;
				// 	SerializeRaw("\\/");
				// 	break;
				// BS
				case 0x08:
					SerializeSubstring(value, from, i - from);
					from = i + 1;
					SerializeRaw("\\b");
					break;
				// FF
				case 0x0C:
					SerializeSubstring(value, from, i - from);
					from = i + 1;
					SerializeRaw("\\f");
					break;
				// LF
				case 0x0A:
					SerializeSubstring(value, from, i - from);
					from = i + 1;
					SerializeRaw("\\n");
					break;
				// CR
				case 0x0D:
					SerializeSubstring(value, from, i - from);
					from = i + 1;
					SerializeRaw("\\r");
					break;
				// HT
				case 0x09:
					SerializeSubstring(value, from, i - from);
					from = i + 1;
					SerializeRaw("\\t");
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
					SerializeSubstring(value, from, i - from);
					from = i + 1;
                    SerializeRaw(c.ToString(len: 4, hex: true, prefix: "\\u"));
					break;
			};
		};
		SerializeSubstring(value, from, n - from);
		SerializeRaw("\"");
	};

	override void SerializeArrayBegin() {
		SerializeRaw("[");
	};

	override void SerializeArrayEnd() {
		SerializeRaw("]");
	};

	override void SerializeObjectBegin() {
		SerializeRaw("{");
	};

	override void SerializeObjectEnd() {
		SerializeRaw("}");
	};

	override void SerializeComma() {
		SerializeRaw(",");
	};

	override void SerializeColon() {
		SerializeRaw(":");
	};

    protected void SerializeRaw(string data);

	protected void SerializeSubstring(string src, int from, int count) {
		// enfusion://ScriptEditor/scripts/Core/generated/Types/string.c;88
		// (Maximum output of string.Substring is limited to 8191 characters)
		auto to = from + count;
		for (auto i = from; i < to; i += 8192) {
			string str;
			if (i + 8192 > to)
				str = src.Substring(i, to - i);
			else
				str = src.Substring(i, 8192);
			SerializeRaw(str);
		};
	};
};
