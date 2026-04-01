// Helps with serialization.
class V30_Json_SerializerHelper {
	protected void V30_Json_SerializerHelper();

	// Overload for putting `null` value to serializer `serializer`.
	static void Serialize(notnull V30_Json_Serializer serializer) {
		serializer.SerializeNull();
	};

	static void Serialize(notnull V30_Json_Serializer serializer, void value) {
		serializer.SerializeNull();
	};

	// Overload for putting boolean value to serializer `serializer`.
	static void Serialize(notnull V30_Json_Serializer serializer, bool value) {
		serializer.SerializeBool(value);
	};

	// Overload for putting integer value to serializer `serializer`.
	static void Serialize(notnull V30_Json_Serializer serializer, int value) {
		serializer.SerializeInt(value);
	};

	// Overload for putting floating point value to serializer `serializer`.
	static void Serialize(notnull V30_Json_Serializer serializer, float value) {
		serializer.SerializeFloat(value);
	};

	// Overload for putting string value to serializer `serializer`.
	static void Serialize(notnull V30_Json_Serializer serializer, string value) {
		serializer.SerializeString(value);
	};

	// Overload for putting `array<T>`, `map<string, T>` or `Class` value to serializer `serializer`.
	static void Serialize(notnull V30_Json_Serializer serializer, notnull Class instance) {
		auto type = instance.Type();
		auto typeAttribute = GetSerializerAttribute(type);
		if (typeAttribute)
			typeAttribute.SerializeClass(serializer, instance);
		else if (type.IsInherited(array))
			SerializeArray(serializer, Managed.Cast(instance));
		else if (type.IsInherited(map))
			SerializeObject(serializer, Managed.Cast(instance));
		else
			SerializeClass(serializer, instance);
	};

	static void Serialize(notnull V30_Json_Serializer serializer, typename type, notnull Class instance, int i) {
		auto variableAttribute = GetSerializerVariableAttribute(type, i);
		if (variableAttribute) {
			Class variable;
			if (!type.GetVariableValue(instance, i, variable))
				return;
			variableAttribute.SerializeClass(serializer, variable);
			return;
		};

		auto variableType = type.GetVariableType(i);
		switch (variableType) {
			case bool:
				V30_Json_SerializerHelperT<bool>.Serialize(serializer, type, instance, i);
				break;
			case int:
				V30_Json_SerializerHelperT<int>.Serialize(serializer, type, instance, i);
				break;
			case float:
				V30_Json_SerializerHelperT<float>.Serialize(serializer, type, instance, i);
				break;
			case string:
				V30_Json_SerializerHelperT<string>.Serialize(serializer, type, instance, i);
				break;
			default: {
				#ifdef ENABLE_DIAG
				if (!variableType.IsInherited(Class))
					Debug.Error(string.Format("[V30][JSON][SerializerHelper] Put(V30_Json_Serializer, typename, Class, int): Unsupported type %1 for serialization in type %2 at %3 (%4)", variableType, type, i, type.GetVariableName(i)));
				#endif
				Class variable;
				type.GetVariableValue(instance, i, variable);
				Serialize(serializer, variable);
				break;
			};
		};
	};

	static void SerializeArray(notnull V30_Json_Serializer serializer, notnull Managed arr) {
		auto type = arr.Type();
		bool subTypeIsRef;
		auto subType = GetArraySubType(type, subTypeIsRef);
		SerializeArray(serializer, arr, subType, subTypeIsRef);
	};

	static void SerializeArray(notnull V30_Json_Serializer serializer, notnull Managed arr, typename subType, bool subTypeIsRef = true) {
		switch (subType) {
			case bool:
				V30_Json_SerializerHelperT<bool>.Serialize(serializer, array<bool>.Cast(arr));
				break;
			case int:
				V30_Json_SerializerHelperT<int>.Serialize(serializer, array<int>.Cast(arr));
				break;
			case float:
				V30_Json_SerializerHelperT<float>.Serialize(serializer, array<float>.Cast(arr));
				break;
			case string:
				V30_Json_SerializerHelperT<string>.Serialize(serializer, array<string>.Cast(arr));
				break;
			default:
				#ifdef ENABLE_DIAG
				if (!subType.IsInherited(Class) || !GetSerializerAttribute(subType))
					Debug.Error(string.Format("[V30][JSON][SerializerHelper] PutArray(V30_Json_Serializer, Managed): Unsupported type %1 for serialization in array.", subType));
				#endif
				SerializeArray(serializer, arr, GetSerializerAttribute(subType), subTypeIsRef);
				break;
		};
	};

	static void SerializeArray(notnull V30_Json_Serializer serializer, notnull Managed arr, notnull V30_Json_SerializerAttribute attribute, bool isRef = true) {
		if (isRef)
			attribute.SerializeArrayRef(serializer, arr);
		else
			attribute.SerializeArray(serializer, arr);
	};

	static void SerializeObject(notnull V30_Json_Serializer serializer, notnull Managed obj) {
		auto type = obj.Type();
		bool subTypeIsRef;
		auto subType = GetObjectSubType(type, subTypeIsRef);
		SerializeObject(serializer, obj, subType, subTypeIsRef);
	};

	static void SerializeObject(notnull V30_Json_Serializer serializer, notnull Managed obj, typename subType, bool subTypeIsRef = true) {
		switch (subType) {
			case bool:
				V30_Json_SerializerHelperT<bool>.Serialize(serializer, map<string, bool>.Cast(obj));
				break;
			case int:
				V30_Json_SerializerHelperT<int>.Serialize(serializer, map<string, int>.Cast(obj));
				break;
			case float:
				V30_Json_SerializerHelperT<float>.Serialize(serializer, map<string, float>.Cast(obj));
				break;
			case string:
				V30_Json_SerializerHelperT<string>.Serialize(serializer, map<string, string>.Cast(obj));
				break;
			default:
				#ifdef ENABLE_DIAG
				if (!subType.IsInherited(Class) || !GetSerializerAttribute(subType))
					Debug.Error(string.Format("[V30][JSON][SerializerHelper] PutObject(V30_Json_Serializer, Managed): Unsupported type %1 for serialization in object.", subType));
				#endif
				SerializeObject(serializer, obj, GetSerializerAttribute(subType), subTypeIsRef);
				break;
		};
	};

	static void SerializeObject(notnull V30_Json_Serializer serializer, notnull Managed obj, notnull V30_Json_SerializerAttribute attribute, bool isRef = true) {
		if (isRef)
			attribute.SerializeObjectRef(serializer, obj);
		else
			attribute.SerializeObject(serializer, obj);
	};

	static void SerializeClass(notnull V30_Json_Serializer serializer, notnull Class instance) {
		serializer.SerializeObjectBegin();
		auto type = instance.Type();
		auto n = type.GetVariableCount();
		for (auto i = 0; i < n; i++) {
			if (i > 0)
				serializer.SerializeComma();
			auto variableName = type.GetVariableName(i);
			serializer.SerializeString(variableName);
			auto variableType = type.GetVariableType(i);
			switch (variableType) {
				case bool:
					V30_Json_SerializerHelperT<bool>.Serialize(serializer, type, instance, i);
					break;
				case int:
					V30_Json_SerializerHelperT<int>.Serialize(serializer, type, instance, i);
					break;
				case float:
					V30_Json_SerializerHelperT<float>.Serialize(serializer, type, instance, i);
					break;
				case string:
					V30_Json_SerializerHelperT<string>.Serialize(serializer, type, instance, i);
					break;
				default: {
					break;
				};
			};
		};
		serializer.SerializeObjectEnd();
	};

    static void Serialize(notnull V30_Json_Serializer serializer, notnull V30_Json_SerializerAttribute serializerAttr, Class instance) {
        serializerAttr.SerializeClass(serializer, instance);
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
					SerializeSubstring(dst, src, from, i - from);
					from = i + 1;
					dst += "\\"; // Combining escape sequence results in parser error
					dst += "\""; // Combining escape sequence results in parser error
					break;
				// \
				case 0x5C:
					SerializeSubstring(dst, src, from, i - from);
					from = i + 1;
					dst += "\\"; // Combining escape sequence results in parser error
					dst += "\\"; // Combining escape sequence results in parser error
					break;
				// // /
				// case 0x2F:
				// 	SerializeSubstring(dst, src, from, i - from);
				// 	from = i + 1;
				// 	dst += "\\/";
				// 	break;
				// BS
				case 0x08:
					SerializeSubstring(dst, src, from, i - from);
					from = i + 1;
					dst += "\\b";
					break;
				// FF
				case 0x0C:
					SerializeSubstring(dst, src, from, i - from);
					from = i + 1;
					dst += "\\f";
					break;
				// LF
				case 0x0A:
					SerializeSubstring(dst, src, from, i - from);
					from = i + 1;
					dst += "\\n";
					break;
				// CR
				case 0x0D:
					SerializeSubstring(dst, src, from, i - from);
					from = i + 1;
					dst += "\\r";
					break;
				// HT
				case 0x09:
					SerializeSubstring(dst, src, from, i - from);
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
					SerializeSubstring(dst, src, from, i - from);
					from = i + 1;
					dst += "\\u";
                    dst += c.ToString(len: 4, hex: true);
					break;
			};
		};
		SerializeSubstring(dst, src, from, n - from);
		return dst;
	};

	protected static void SerializeSubstring(out string dst, string src, int from, int count) {
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
		auto subTypeStringPrefixLength = "map<string,".Length();
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

	static void Serialize(notnull V30_Json_Serializer serializer, notnull array<T> arr) {
		serializer.SerializeArrayBegin();
		foreach (auto i, auto val : arr) {
			if (i > 0)
				serializer.SerializeComma();
			V30_Json_SerializerHelper.Serialize(serializer, val);
		};
		serializer.SerializeArrayEnd();
	};

	static void Serialize(notnull V30_Json_Serializer serializer, notnull map<string, T> obj) {
		serializer.SerializeObjectBegin();
		auto comma = false;
		foreach (auto key, auto val : obj) {
			if (comma)
				serializer.SerializeComma();
			else
				comma = true;
			serializer.SerializeString(key);
			serializer.SerializeColon();
			V30_Json_SerializerHelper.Serialize(serializer, val);
		};
		serializer.SerializeObjectEnd();
	};

	static void Serialize(notnull V30_Json_Serializer serializer, typename type, notnull Class instance, int i) {
		T value;
		if (!type.GetVariableValue(instance, i, value))
			return;
		V30_Json_SerializerHelper.Serialize(serializer, value);
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
