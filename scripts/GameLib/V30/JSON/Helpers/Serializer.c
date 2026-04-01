// Helps with serialization.
class V30_Json_SerializerHelper {
	protected void V30_Json_SerializerHelper();

	// Overload for putting `null` value to serializer `serializer`.
	static void Write(notnull V30_Json_Serializer serializer) {
		serializer.WriteNull();
	};

	static void Write(notnull V30_Json_Serializer serializer, void value) {
		serializer.WriteNull();
	};

	// Overload for putting boolean value to serializer `serializer`.
	static void Write(notnull V30_Json_Serializer serializer, bool value) {
		serializer.WriteBool(value);
	};

	// Overload for putting integer value to serializer `serializer`.
	static void Write(notnull V30_Json_Serializer serializer, int value) {
		serializer.WriteInt(value);
	};

	// Overload for putting floating point value to serializer `serializer`.
	static void Write(notnull V30_Json_Serializer serializer, float value) {
		serializer.WriteFloat(value);
	};

	// Overload for putting string value to serializer `serializer`.
	static void Write(notnull V30_Json_Serializer serializer, string value) {
		serializer.WriteString(value);
	};

	// Overload for putting `array<T>`, `map<string, T>` or `Class` value to serializer `serializer`.
	static void Write(notnull V30_Json_Serializer serializer, notnull Class instance) {
		auto type = instance.Type();
		auto typeAttribute = GetSerializerAttribute(type);
		if (typeAttribute)
			typeAttribute.Serialize(serializer, instance);
		else if (type.IsInherited(array))
			WriteArray(serializer, Managed.Cast(instance));
		else if (type.IsInherited(map))
			WriteObject(serializer, Managed.Cast(instance));
		else
			WriteClass(serializer, instance);
	};

	static void Write(notnull V30_Json_Serializer serializer, typename type, notnull Class instance, int i) {
		auto variableAttribute = GetSerializerVariableAttribute(type, i);
		if (variableAttribute) {
			Class variable;
			if (!type.GetVariableValue(instance, i, variable))
				return;
			variableAttribute.Serialize(serializer, variable);
			return;
		};

		auto variableType = type.GetVariableType(i);
		switch (variableType) {
			case bool:
				V30_Json_SerializerHelperT<bool>.Write(serializer, type, instance, i);
				break;
			case int:
				V30_Json_SerializerHelperT<int>.Write(serializer, type, instance, i);
				break;
			case float:
				V30_Json_SerializerHelperT<float>.Write(serializer, type, instance, i);
				break;
			case string:
				V30_Json_SerializerHelperT<string>.Write(serializer, type, instance, i);
				break;
			default: {
				#ifdef ENABLE_DIAG
				if (!variableType.IsInherited(Class))
					Debug.Error(string.Format("[V30][JSON][SerializerHelper] Put(V30_Json_Serializer, typename, Class, int): Unsupported type %1 for serialization in type %2 at %3 (%4)", variableType, type, i, type.GetVariableName(i)));
				#endif
				Class variable;
				type.GetVariableValue(instance, i, variable);
				Write(serializer, variable);
				break;
			};
		};
	};

	static void WriteArray(notnull V30_Json_Serializer serializer, notnull Managed arr) {
		auto type = arr.Type();
		bool subTypeIsRef;
		auto subType = GetArraySubType(type, subTypeIsRef);
		WriteArray(serializer, arr, subType, subTypeIsRef);
	};

	static void WriteArray(notnull V30_Json_Serializer serializer, notnull Managed arr, typename subType, bool subTypeIsRef = true) {
		switch (subType) {
			case bool:
				V30_Json_SerializerHelperT<bool>.Write(serializer, array<bool>.Cast(arr));
				break;
			case int:
				V30_Json_SerializerHelperT<int>.Write(serializer, array<int>.Cast(arr));
				break;
			case float:
				V30_Json_SerializerHelperT<float>.Write(serializer, array<float>.Cast(arr));
				break;
			case string:
				V30_Json_SerializerHelperT<string>.Write(serializer, array<string>.Cast(arr));
				break;
			default:
				#ifdef ENABLE_DIAG
				if (!subType.IsInherited(Class) || !GetSerializerAttribute(subType))
					Debug.Error(string.Format("[V30][JSON][SerializerHelper] PutArray(V30_Json_Serializer, Managed): Unsupported type %1 for serialization in array.", subType));
				#endif
				WriteArray(serializer, arr, GetSerializerAttribute(subType), subTypeIsRef);
				break;
		};
	};

	static void WriteArray(notnull V30_Json_Serializer serializer, notnull Managed arr, notnull V30_Json_SerializerAttribute attribute, bool isRef = true) {
		if (isRef)
			attribute.SerializeArrayRef(serializer, arr);
		else
			attribute.SerializeArray(serializer, arr);
	};

	static void WriteObject(notnull V30_Json_Serializer serializer, notnull Managed obj) {
		auto type = obj.Type();
		bool subTypeIsRef;
		auto subType = GetObjectSubType(type, subTypeIsRef);
		WriteObject(serializer, obj, subType, subTypeIsRef);
	};

	static void WriteObject(notnull V30_Json_Serializer serializer, notnull Managed obj, typename subType, bool subTypeIsRef = true) {
		switch (subType) {
			case bool:
				V30_Json_SerializerHelperT<bool>.Write(serializer, map<string, bool>.Cast(obj));
				break;
			case int:
				V30_Json_SerializerHelperT<int>.Write(serializer, map<string, int>.Cast(obj));
				break;
			case float:
				V30_Json_SerializerHelperT<float>.Write(serializer, map<string, float>.Cast(obj));
				break;
			case string:
				V30_Json_SerializerHelperT<string>.Write(serializer, map<string, string>.Cast(obj));
				break;
			default:
				#ifdef ENABLE_DIAG
				if (!subType.IsInherited(Class) || !GetSerializerAttribute(subType))
					Debug.Error(string.Format("[V30][JSON][SerializerHelper] PutObject(V30_Json_Serializer, Managed): Unsupported type %1 for serialization in object.", subType));
				#endif
				WriteObject(serializer, obj, GetSerializerAttribute(subType), subTypeIsRef);
				break;
		};
	};

	static void WriteObject(notnull V30_Json_Serializer serializer, notnull Managed obj, notnull V30_Json_SerializerAttribute attribute, bool isRef = true) {
		if (isRef)
			attribute.SerializeObjectRef(serializer, obj);
		else
			attribute.SerializeObject(serializer, obj);
	};

	static void WriteClass(notnull V30_Json_Serializer serializer, notnull Class instance) {
		serializer.WriteObjectBegin();
		auto type = instance.Type();
		auto n = type.GetVariableCount();
		for (auto i = 0; i < n; i++) {
			if (i > 0)
				serializer.WriteComma();
			auto variableName = type.GetVariableName(i);
			serializer.WriteString(variableName);
			auto variableType = type.GetVariableType(i);
			switch (variableType) {
				case bool:
					V30_Json_SerializerHelperT<bool>.Write(serializer, type, instance, i);
					break;
				case int:
					V30_Json_SerializerHelperT<int>.Write(serializer, type, instance, i);
					break;
				case float:
					V30_Json_SerializerHelperT<float>.Write(serializer, type, instance, i);
					break;
				case string:
					V30_Json_SerializerHelperT<string>.Write(serializer, type, instance, i);
					break;
				default: {
					break;
				};
			};
		};
		serializer.WriteObjectEnd();
	};

    static void Write(notnull V30_Json_Serializer serializer, notnull V30_Json_SerializerAttribute serializerAttr, Class instance) {
        serializerAttr.Serialize(serializer, instance);
    };

	static string SanitizeString(string src) {
		auto dst = "";
		auto n = src.Length();
		auto from = 0;
		for (int i = 0; i < n; i++) {
			auto c = src.ToAscii(i); // Signed!
			switch (c) {
				// "
				case 0x22:
					WriteSubstring(dst, src, from, i - from);
					from = i + 1;
					dst += "\\"; // Combining escape sequence results in parser error
					dst += "\""; // Combining escape sequence results in parser error
					break;
				// \
				case 0x5C:
					WriteSubstring(dst, src, from, i - from);
					from = i + 1;
					dst += "\\"; // Combining escape sequence results in parser error
					dst += "\\"; // Combining escape sequence results in parser error
					break;
				// // /
				// case 0x2F:
				// 	WriteSubstring(dst, src, from, i - from);
				// 	from = i + 1;
				// 	dst += "\\/";
				// 	break;
				// BS
				case 0x08:
					WriteSubstring(dst, src, from, i - from);
					from = i + 1;
					dst += "\\b";
					break;
				// FF
				case 0x0C:
					WriteSubstring(dst, src, from, i - from);
					from = i + 1;
					dst += "\\f";
					break;
				// LF
				case 0x0A:
					WriteSubstring(dst, src, from, i - from);
					from = i + 1;
					dst += "\\n";
					break;
				// CR
				case 0x0D:
					WriteSubstring(dst, src, from, i - from);
					from = i + 1;
					dst += "\\r";
					break;
				// HT
				case 0x09:
					WriteSubstring(dst, src, from, i - from);
					from = i + 1;
					dst += "\\t";
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
					WriteSubstring(dst, src, from, i - from);
					from = i + 1;
					dst += "\\u";
                    dst += c.ToString(len: 4, hex: true);
					break;
			};
		};
		WriteSubstring(dst, src, from, n - from);
		return dst;
	};

	protected static void WriteSubstring(out string dst, string src, int from, int count) {
		// enfusion://ScriptEditor/scripts/Core/generated/Types/string.c;88
		// (Maximum output of string.Substring is limited to 8191 characters)
		while (count > 0) {
			int n;
			if (count <= 8191)
				n = count;
			else
				n = 8191;
			dst += src.Substring(from, n);
			from += n;
			count -= n;
		};
	};

	protected static typename GetArraySubType(typename type, out bool isRef) {
		if (!type.IsInherited(array))
			return void;
		auto typeString = type.ToString();
		if (!typeString.StartsWith("array<"))
			return void;
		auto typeStringLength = typeString.Length();
		auto subTypeStringPrefixLength = "array<".Length();
		auto subTypeStringPostfixLength = ">".Length();
		auto subTypeStringLength = typeStringLength - subTypeStringPrefixLength - subTypeStringPostfixLength;
		auto subTypeString = typeString.Substring(subTypeStringPrefixLength, subTypeStringLength);
		if (subTypeString.StartsWith("@")) {
			isRef = true;
			subTypeStringLength = subTypeStringLength - 1;
			subTypeString = subTypeString.Substring(1, subTypeStringLength);
		}
		else
			isRef = false;
		return subTypeString.ToType();
	};

	protected static typename GetObjectSubType(typename type, out bool isRef) {
		if (!type.IsInherited(map))
			return void;
		auto typeString = type.ToString();
		if (!typeString.StartsWith("map<string"))
			return void;
		auto typeStringLength = typeString.Length();
		auto subTypeStringPrefixLength = "map<string".Length();
		auto subTypeStringPostfixLength = ">".Length();
		auto subTypeStringLength = typeStringLength - subTypeStringPrefixLength - subTypeStringPostfixLength;
		auto subTypeString = typeString.Substring(subTypeStringPrefixLength, subTypeStringLength);
		if (subTypeString.StartsWith("@")) {
			isRef = true;
			subTypeStringLength = subTypeStringLength - 1;
			subTypeString = subTypeString.Substring(1, subTypeStringLength);
		}
		else
			isRef = false;
		return subTypeString.ToType();
	};

	static V30_Json_SerializerAttribute GetSerializerAttribute(typename type) {
		auto attributes = new array<Class>();
		type.GetAttributes(attributes);
		foreach (auto attribute : attributes)
			if (attribute.IsInherited(V30_Json_SerializerAttribute))
				return V30_Json_SerializerAttribute.Cast(attribute);
		return null;
	};

	protected static V30_Json_SerializerAttribute GetSerializerVariableAttribute(typename type, int i) {
		auto variableAttributes = new array<Class>();
		type.GetVariableAttributes(i, variableAttributes);
		foreach (auto variableAttribute : variableAttributes)
			if (variableAttribute.IsInherited(V30_Json_SerializerAttribute))
				return V30_Json_SerializerAttribute.Cast(variableAttribute);
		return null;
	};
};

// Helps with serialization.
class V30_Json_SerializerHelperT<Class T> {
	protected void V30_Json_SerializerHelperT();

	static void Write(notnull V30_Json_Serializer serializer, notnull array<T> arr) {
		serializer.WriteArrayBegin();
		foreach (auto i, auto val : arr) {
			if (i > 0)
				serializer.WriteComma();
			V30_Json_SerializerHelper.Write(serializer, val);
		};
		serializer.WriteArrayEnd();
	};

	static void Write(notnull V30_Json_Serializer serializer, notnull map<string, T> obj) {
		serializer.WriteObjectBegin();
		auto comma = false;
		foreach (auto key, auto val : obj) {
			if (comma)
				serializer.WriteComma();
			else
				comma = true;
			serializer.WriteString(key);
			serializer.WriteColon();
			V30_Json_SerializerHelper.Write(serializer, val);
		};
		serializer.WriteObjectEnd();
	};

	static void Write(notnull V30_Json_Serializer serializer, typename type, notnull Class instance, int i) {
		T value;
		if (!type.GetVariableValue(instance, i, value))
			return;
		V30_Json_SerializerHelper.Write(serializer, value);
	};
};

// Helps with serialization.
class V30_Json_SerializerHelperRefT<Managed t> {
	protected void V30_Json_SerializerHelperRefT();

	static void Put(notnull V30_Json_Serializer serializer, notnull array<ref T> arr) {
		serializer.BeginArray();
		foreach (auto val : arr) {
			serializer.TryPutComma();
			V30_Json_SerializerHelper.Put(serializer, val);
		};
		serializer.EndArray();
	};

	static void Put(notnull V30_Json_Serializer serializer, notnull V30_Json_SerializeAttribute instanceSerializer, notnull array<ref T> arr) {
		serializer.BeginArray();
		foreach (auto val : arr) {
			serializer.TryPutComma();
			V30_Json_SerializerHelper.Put(serializer, instanceSerializer, val);
		};
		serializer.EndArray();
	};

	static void Put(notnull V30_Json_Serializer serializer, notnull map<string, ref T> obj) {
		serializer.BeginObject();
		foreach (auto key, auto val : obj) {
			serializer.TryPutComma();
			serializer.PutKey(key);
			V30_Json_SerializerHelper.Put(serializer, val);
		};
		serializer.EndObject();
	};

	static void Put(notnull V30_Json_Serializer serializer, notnull V30_Json_SerializeAttribute instanceSerializer, notnull map<string, ref T> obj) {
		serializer.BeginObject();
		foreach (auto key, auto val : obj) {
			serializer.TryPutComma();
			serializer.PutKey(key);
			V30_Json_SerializerHelper.Put(serializer, instanceSerializer, val);
		};
		serializer.EndObject();
	};
};
