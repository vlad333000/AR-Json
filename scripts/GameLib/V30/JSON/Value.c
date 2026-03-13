class V30_Json_Value : Managed {
	protected void V30_Json_Value();

	bool IsNull() {
		return V30_Json_Null.Cast(this) != null;
	};

	V30_Json_Null AsNull() {
		return V30_Json_Null.Cast(this);
	};

	bool IsBool() {
		return V30_Json_bool.Cast(this) != null;
	};

	V30_Json_bool AsBool() {
		return V30_Json_bool.Cast(this);
	};

	bool IsNumber() {
		return V30_Json_Number.Cast(this) != null;
	};

	V30_Json_Number AsNumber() {
		return V30_Json_Number.Cast(this);
	};

	bool IsInt() {
		return V30_Json_Int.Cast(this) != null;
	};

	V30_Json_Int AsInt() {
		return V30_Json_Int.Cast(this);
	};

	bool IsFloat() {
		return V30_Json_Float.Cast(this) != null;
	};

	V30_Json_Float AsFloat() {
		return V30_Json_Float.Cast(this);
	};

	bool IsString() {
		return V30_Json_String.Cast(this) != null;
	};

	V30_Json_String AsString() {
		return V30_Json_String.Cast(this);
	};

	bool IsArray() {
		return V30_Json_Array.Cast(this) != null;
	};

	V30_Json_Array AsArray() {
		return V30_Json_Array.Cast(this);
	};

	bool IsObject() {
		return V30_Json_Object.Cast(this) != null;
	};

	V30_Json_Object AsObject() {
		return V30_Json_Object.Cast(this);
	};

	// static V30_Json_Value New(Class value) {
	// 	if (!value)
	// 		return V30_Json_Null();
	// 	auto valueJson = V30_Json_Object();
	// 	auto valueJsonRaw = valueJson.Get();
	// 	auto type = value.Type();
	// 	auto n = type.GetVariableCount();
	// 	for (auto i = 0; i < n; i++) {
	// 		auto varName = type.GetVariableName(i);
	// 		auto varType = type.GetVariableType(i);
	// 		V30_Json_Value varValueJson;
	// 		if (varType.IsInherited(bool)) {
	// 			if (!V30_Json_ValueHelperT<bool>.New(value, type, i, varValueJson))
	// 				continue;
	// 		}
	// 		else if (varType.IsInherited(int)) {
	// 			if (!V30_Json_ValueHelperT<int>.New(value, type, i, varValueJson))
	// 				continue;
	// 		}
	// 		else if (varType.IsInherited(float)) {
	// 			if (!V30_Json_ValueHelperT<float>.New(value, type, i, varValueJson))
	// 				continue;
	// 		}
	// 		else if (varType.IsInherited(string)) {
	// 			if (!V30_Json_ValueHelperT<string>.New(value, type, i, varValueJson))
	// 				continue;
	// 		}
	// 		else if (varType.IsInherited(Class)) {
	// 			auto varJsonAttribute = GetTypeJsonAttribute(varType);
	// 			if (varJsonAttribute) {
	// 				//varValueJson = varJsonAttribute.SerializeInstance(value, type, i);
	// 			}
	// 			else if (varType.IsInherited(array)) {
	// 				auto varSubType = GetArraySubType(varType);
	// 				switch (varSubType) {
	// 					case bool : {
	// 						if (!V30_Json_ValueHelperT<bool>.NewArray(value, type, i, varValueJson))
	// 							continue;
	// 						break;
	// 					};
	// 					case int : {
	// 						if (!V30_Json_ValueHelperT<int>.NewArray(value, type, i, varValueJson))
	// 							continue;
	// 						break;
	// 					};
	// 					case float : {
	// 						if (!V30_Json_ValueHelperT<float>.NewArray(value, type, i, varValueJson))
	// 							continue;
	// 						break;
	// 					};
	// 					case string : {
	// 						if (!V30_Json_ValueHelperT<string>.NewArray(value, type, i, varValueJson))
	// 							continue;
	// 						break;
	// 					};
	// 					default : {
	// 						if (varSubType.IsInherited(Class)) {
	// 							auto varSubJsonAttribute = GetTypeJsonAttribute(varSubType);
	// 							if (varSubJsonAttribute) {
	// 								//varValueJson = varSubJsonAttribute.SerializeInstanceArray(value, type, i);
	// 							}
	// 							else if (varSubType.IsInherited(array)) {
	// 								PrintFormat("[V30][JSON] Multidimensional array/map are not supported %1.", varType, level: LogLevel.ERROR);
	// 								continue;
	// 							}
	// 							else if (varSubType.IsInherited(map)) {
	// 								PrintFormat("[V30][JSON] Multidimensional array/map are not supported %1.", varType, level: LogLevel.ERROR);
	// 								continue;
	// 							}
	// 							else {
	// 								PrintFormat("[V30][JSON] Unsupported array sub type of class %1, define `V30_Json_SerializerAttribute` for it.", varSubType, level: LogLevel.ERROR);
	// 								continue;
	// 							};
	// 						}
	// 						else {
	// 							PrintFormat("[V30][JSON] Unsupported array sub type %1.", varSubType, level: LogLevel.ERROR);
	// 							continue;
	// 						};
	// 						break;
	// 					};
	// 				};
	// 			}
	// 			else if (varType.IsInherited(map)) {
	// 				auto varSubType = GetObjectSubType(varType);
	// 				switch (varSubType) {
	// 					case bool : {
	// 						if (!V30_Json_ValueHelperT<bool>.NewObject(value, type, i, varValueJson))
	// 							continue;
	// 						break;
	// 					};
	// 					case int : {
	// 						if (!V30_Json_ValueHelperT<int>.NewObject(value, type, i, varValueJson))
	// 							continue;
	// 						break;
	// 					};
	// 					case float : {
	// 						if (!V30_Json_ValueHelperT<float>.NewObject(value, type, i, varValueJson))
	// 							continue;
	// 						break;
	// 					};
	// 					case string : {
	// 						if (!V30_Json_ValueHelperT<string>.NewObject(value, type, i, varValueJson))
	// 							continue;
	// 						break;
	// 					};
	// 					default : {
	// 						if (varSubType.IsInherited(Class)) {
	// 							auto varSubJsonAttribute = GetTypeJsonAttribute(varSubType);
	// 							if (varSubJsonAttribute) {
	// 								//varValueJson = varSubJsonAttribute.SerializeInstanceObject(value, type, i);
	// 							}
	// 							else if (varSubType.IsInherited(array)) {
	// 								PrintFormat("[V30][JSON] Multidimensional array/map are not supported %1.", varType, level: LogLevel.ERROR);
	// 								continue;
	// 							}
	// 							else if (varSubType.IsInherited(map)) {
	// 								PrintFormat("[V30][JSON] Multidimensional array/map are not supported %1.", varType, level: LogLevel.ERROR);
	// 								continue;
	// 							}
	// 							else {
	// 								PrintFormat("[V30][JSON] Unsupported map sub type of class %1, define `V30_Json_SerializerAttribute` for it.", varSubType, level: LogLevel.ERROR);
	// 								continue;
	// 							};
	// 						}
	// 						else {
	// 							PrintFormat("[V30][JSON] Unsupported map sub type %1.", varSubType, level: LogLevel.ERROR);
	// 							continue;
	// 						};
	// 						break;
	// 					};
	// 				};
	// 			}
	// 			else {
	// 				if (!V30_Json_ValueHelperT<Class>.New(value, type, i, varValueJson))
	// 					continue;
	// 			};
	// 		}
	// 		else {
	// 			PrintFormat("[V30][JSON] Unsupported type %1.", varType, level: LogLevel.ERROR);
	// 			continue;
	// 		};
	// 		if (varValueJson)
	// 			valueJsonRaw.Insert(varName, varValueJson);
	// 	};
	// 	return valueJson;
	// };

	// static typename GetArraySubType(typename type) {
	// 	if (!type.IsInherited(array))
	// 		return void;
	// 	auto typeString = type.ToString();
	// 	auto typeStringLength = typeString.Length();
	// 	if (typeString.StartsWith("@")) {
	// 		typeStringLength = typeStringLength - 1;
	// 		typeString = typeString.Substring(1, typeStringLength);
	// 	};
	// 	if (!typeString.StartsWith("array<"))
	// 		return void;
	// 	auto subTypeStringPrefixLength = "array<".Length();
	// 	auto subTypeStringPostfixLength = ">".Length();
	// 	auto subTypeStringLength = typeStringLength - subTypeStringPrefixLength - subTypeStringPostfixLength;
	// 	auto subTypeString = typeString.Substring(subTypeStringPrefixLength, subTypeStringLength);
	// 	if (subTypeString.StartsWith("@")) {
	// 		subTypeStringLength = subTypeStringLength - 1;
	// 		subTypeString = subTypeString.Substring(1, subTypeStringLength);
	// 	};
	// 	return subTypeString.ToType();
	// };

	// static typename GetObjectSubType(typename type) {
	// 	if (!type.IsInherited(map))
	// 		return void;
	// 	auto typeString = type.ToString();
	// 	auto typeStringLength = typeString.Length();
	// 	if (typeString.StartsWith("@")) {
	// 		typeStringLength = typeStringLength - 1;
	// 		typeString = typeString.Substring(1, typeStringLength);
	// 	};
	// 	if (!typeString.StartsWith("map<string,"))
	// 		return void;
	// 	auto subTypeStringPrefixLength = "map<string,".Length();
	// 	auto subTypeStringPostfixLength = ">".Length();
	// 	auto subTypeStringLength = typeStringLength - subTypeStringPrefixLength - subTypeStringPostfixLength;
	// 	auto subTypeString = typeString.Substring(subTypeStringPrefixLength, subTypeStringLength);
	// 	if (subTypeString.StartsWith("@")) {
	// 		subTypeStringLength = subTypeStringLength - 1;
	// 		subTypeString = subTypeString.Substring(1, subTypeStringLength);
	// 	};
	// 	return subTypeString.ToType();
	// };

	// static V30_Json_SerializerAttribute GetTypeJsonAttribute(typename type) {
	// 	auto varAttributes = new array<Class>();
	// 	type.GetAttributes(varAttributes);
	// 	foreach (auto varAttribute : varAttributes)
	// 		if (varAttribute.IsInherited(V30_Json_SerializerAttribute))
	// 			return V30_Json_SerializerAttribute.Cast(varAttribute);
	// 	return null;
	// };
};

// class V30_Json_ValueHelperT<Class T> {
// 	static V30_Json_Value New(array<T> arr) {
// 		if (!arr)
// 			return V30_Json_Null();
// 		auto arrJson = V30_Json_Array();
// 		auto arrJsonRaw = arrJson.Get();
// 		auto arrN = arr.Count();
// 		arrJsonRaw.Reserve(arrN);
// 		foreach (auto val : arr) {
// 			auto valJson = V30_Json_Value.New(val);
// 			arrJsonRaw.Insert(valJson);
// 		};
// 		return arrJson;
// 	};

// 	static bool New(Class instance, typename type, int i, out V30_Json_Value outValue) {
// 		T value;
// 		if (!type.GetVariableValue(instance, i, value))
// 			return false;
// 		outValue = V30_Json_Value.New(value);
// 		return true;
// 	};

// 	static bool NewArray(Class instance, typename type, int i, out V30_Json_Value outValues) {
// 		array<T> values;
// 		if (!type.GetVariableValue(instance, i, values))
// 			return false;
// 		auto outValuesRaw = new array<ref V30_Json_Value>();
// 		foreach (auto value : values) {
// 			auto outValue = V30_Json_Value.New(value);
// 			outValuesRaw.Insert(outValue);
// 		};
// 		outValues = V30_Json_Array(outValuesRaw);
// 		return true;
// 	};

// 	static bool NewObject(Class instance, typename type, int i, out V30_Json_Value outValues) {
// 		map<string, T> values;
// 		if (!type.GetVariableValue(instance, i, values))
// 			return false;
// 		auto outValuesRaw = new map<string, ref V30_Json_Value>();
// 		foreach (auto key, auto value : values) {
// 			auto outValue = V30_Json_Value.New(value);
// 			outValuesRaw.Insert(key, outValue);
// 		};
// 		outValues = V30_Json_Object(outValuesRaw);
// 		return true;
// 	};
// };

// class V30_Json_ValueHelperClassT<Class T> {
// 	static bool NewAttr(Class instance, typename type, int i, out V30_Json_Value outValue, V30_Json_SerializerAttribute serializer) {
// 		T value;
// 		if (!type.GetVariableValue(instance, i, value))
// 			return false;
// 		outValue = serializer.Serialize(value);
// 		return true;
// 	};
// };

// class V30_Json_ValueHelperRefT<Class T> {
// 	static V30_Json_Value New(array<ref T> arr) {
// 		if (!arr)
// 			return V30_Json_Null();
// 		auto arrJson = V30_Json_Array();
// 		auto arrJsonRaw = arrJson.Get();
// 		auto arrN = arr.Count();
// 		arrJsonRaw.Reserve(arrN);
// 		foreach (auto val : arr) {
// 			auto valJson = V30_Json_Value.New(val);
// 			arrJsonRaw.Insert(valJson);
// 		};
// 		return arrJson;
// 	};
// };

// class V30_Json_Attribute_HelperT<Class T> {
// 	static T Get(Class instance) {
// 		if (!instance)
// 			return null;
// 		if (!instance.IsInherited(T))
// 			return null;
// 		return T.Cast(instance);
// 	};

// 	static V30_Json_Value SerializeArray(notnull V30_Json_SerializerAttribute serializer, Managed arr) {
// 		if (!arr)
// 			return new V30_Json_Null();
// 		auto jsonRaw = new array<ref V30_Json_Value>();
// 		if (array<T>.Cast(arr))
// 			foreach (auto instance : array<T>.Cast(arr))
// 				jsonRaw.Insert(serializer.Serialize(instance));
// 		else
// 			return null;
// 		return new V30_Json_Array(jsonRaw);
// 	};

// 	static V30_Json_Value SerializeObject(notnull V30_Json_SerializerAttribute serializer, Managed obj) {
// 		if (!obj)
// 			return new V30_Json_Null();
// 		auto jsonRaw = new map<string, ref V30_Json_Value>();
// 		if (map<string, T>.Cast(obj))
// 			foreach (auto key, auto instance : map<string, T>.Cast(obj))
// 				jsonRaw.Insert(key, serializer.Serialize(instance));
// 		else
// 			return null;
// 		return new V30_Json_Object(jsonRaw);
// 	};
// };

// class V30_Json_Attribute_HelperRefT<Class T> {
// 	static T Get(Class instance) {
// 		if (!instance)
// 			return null;
// 		if (!instance.IsInherited(T))
// 			return null;
// 		return T.Cast(instance);
// 	};

// 	static V30_Json_Value SerializeArray(notnull V30_Json_SerializerAttribute serializer, Managed arr) {
// 		if (!arr)
// 			return new V30_Json_Null();
// 		auto jsonRaw = new array<ref V30_Json_Value>();
// 		if (array<ref T>.Cast(arr))
// 			foreach (auto instance : array<ref T>.Cast(arr))
// 				jsonRaw.Insert(serializer.Serialize(instance));
// 		else if (array<T>.Cast(arr))
// 			foreach (auto instance : array<T>.Cast(arr))
// 				jsonRaw.Insert(serializer.Serialize(instance));
// 		else
// 			return null;
// 		return new V30_Json_Array(jsonRaw);
// 	};

// 	static V30_Json_Value SerializeObject(notnull V30_Json_SerializerAttribute serializer, Managed obj) {
// 		if (!obj)
// 			return new V30_Json_Null();
// 		auto jsonRaw = new map<string, ref V30_Json_Value>();
// 		if (map<string, ref T>.Cast(obj))
// 			foreach (auto key, auto instance : map<string, ref T>.Cast(obj))
// 				jsonRaw.Insert(key, serializer.Serialize(instance));
// 		else if (map<string, T>.Cast(obj))
// 			foreach (auto key, auto instance : map<string, T>.Cast(obj))
// 				jsonRaw.Insert(key, serializer.Serialize(instance));
// 		else
// 			return null;
// 		return new V30_Json_Object(jsonRaw);
// 	};
// };
