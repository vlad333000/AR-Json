class V30_Json_Deserializer : Managed {
	protected ref array<V30_Json_EDeserializerState> state;

	protected void V30_Json_Deserializer() {
		this.state = new array<V30_Json_EDeserializerState>();
		PushState(V30_Json_EDeserializerState.ROOT);
	};

	protected void ~V30_Json_Deserializer() {
		#ifdef ENABLE_DIAG
		if (!IsEnded())
			Debug.Error("[V30][Json][Deserializer] ~V30_Json_Deserializer(): deserialization is not ended.")
		#endif
	};


	protected bool DeserializeNull(out string error);

	protected bool DeserializeBool(out bool value, out string error);

	protected bool DeserializeInt(out int value, out string error);

	protected bool DeserializeFloat(out float value, out string error);

	protected bool DeserializeString(out string value, out string error);

	protected bool DeserializeArrayBegin(out string error);

	protected bool DeserializeArrayEnd(out string error);

	protected bool DeserializeObjectBegin(out string error);

	protected bool DeserializeObjectEnd(out string error);

	protected bool DeserializeComma(out string error);

	protected bool DeserializeColon(out string error);



	protected bool Success() {
		return true;
	};

	protected bool Error(out string error, string message) {
		error = message;
		return false;
	};

	protected bool ErrorFormat(out string error, string format, string param1 = "", string param2 = "", string param3 = "", string param4 = "", string param5 = "", string param6 = "", string param7 = "", string param8 = "", string param9 = "") {
		return Error(error, string.Format(format, param1, param2, param3, param4, param5, param6, param7, param8, param9));
	};

	protected bool DebugError(out string error, string message) {
		#ifdef ENABLE_DIAG
		Debug.Error(message);
		#endif
		error = message;
		return false;
	};

	protected bool DebugErrorFormat(out string error, string format, string param1 = "", string param2 = "", string param3 = "", string param4 = "", string param5 = "", string param6 = "", string param7 = "", string param8 = "", string param9 = "") {
		return DebugError(error, string.Format(format, param1, param2, param3, param4, param5, param6, param7, param8, param9));
	};

	protected bool InternalError(out string error, string message) {
		Debug.Error(message);
		error = "Internal error.";
		return false;
	};

	protected bool InternalErrorFormat(out string error, string format, string param1 = "", string param2 = "", string param3 = "", string param4 = "", string param5 = "", string param6 = "", string param7 = "", string param8 = "", string param9 = "") {
		return InternalError(error, string.Format(format, param1, param2, param3, param4, param5, param6, param7, param8, param9));
	};

	protected bool TakeComma(out string error) {
		#ifdef ENABLE_DIAG
		if (!IsComma())
			return DebugError(error, "Comma isn't expected.");
		#endif
		if (!DeserializeComma(error))
			return Error(error, "Failed to take comma. " + error);
		#ifdef ENABLE_DIAG
		if (!PopState(V30_Json_EDeserializerState.COMMA))
			return InternalError(error, "[V30][JSON][Deserializer] TakeComma(out string): failed to pop COMMA state.");
		#else
		PopState();
		#endif
		return Success();
	};

	protected bool TakeColon(out string error) {
		#ifdef ENABLE_DIAG
		if (!IsComma())
			return DebugError(error, "Colon isn't expected.");
		#endif
		if (!DeserializeColon(error))
			return Error(error, "Failed to take colon. " + error);
		#ifdef ENABLE_DIAG
		if (!PopState(V30_Json_EDeserializerState.COLON))
			return InternalError(error, "[V30][JSON][Deserializer] TakeComma(out string): failed to pop COLON state.");
		#else
		PopState();
		#endif
		return Success();
	};

	protected bool BeginValue(out string error) {
		if (IsComma()) {
			if (!TakeComma(error))
				return Error(error, "Failed to begin value. " + error);
		}
		else if (IsColon()) {
			if (!TakeColon(error))
				return Error(error, "Failed to begin value. " + error);
		};
		#ifdef ENABLE_DIAG
		switch (GetState()) {
			case V30_Json_EDeserializerState.ROOT:
			case V30_Json_EDeserializerState.ARRAY:
			case V30_Json_EDeserializerState.OBJECT:
				break;
			default:
				return InternalError(error, "Invalid state for value begin.");
		};
		#endif
		PushState(V30_Json_EDeserializerState.VALUE);
		return Success();
	};

	protected bool EndValue(out string error) {
		#ifdef ENABLE_DIAG
		if (!PopState(V30_Json_EDeserializerState.VALUE))
			return InternalError(error, "Expected VALUE state for value end.");
		#else
		PopState();
		#endif
		if (IsContainer())
			PushState(V30_Json_EDeserializerState.COMMA);
		#ifdef ENABLE_DIAG
		else if (!PopState(V30_Json_EDeserializerState.ROOT))
			return InternalError(error, "Expected ROOT state for ending root value.");
		#else
		else
			PopState();
		#endif
		PushState(V30_Json_EDeserializerState.ENDED);
		return true;
	};

	protected bool SkipValue(out string error);

	protected bool SkipAllValues(out string error);

	// Begins deserialization.
	bool Begin();

	// Deserialize `null`.
	bool TakeNull(out string error);

	// Deserialize boolean value (`true` or `false`).
	bool TakeBool(out bool value, out string error);

	// Deserialize integer value.
	bool TakeInt(out int value, out string error);

	// Deserialize floating point value.
	bool TakeFloat(out float value, out string error);

	// Deserialize string value.
	bool TakeString(out string value, out string error);

	// Deserialize key part of object's value.
	bool TakeKey(out string key, out string error);

	// Begins deserialization of array.
	bool BeginArray(out string error);

	// Ends deserialization of array.
	// param `skip` - skips all values until the end of array.
	bool EndArray(out string error, bool skip = false);

	// Begins deserialization of object.
	bool BeginObject(out string error);

	// Ends deserialization of object.
	// param `skip` - skips all values until the end of object.
	bool EndObject(out string error, bool skip = false);

	// Ends deserialization of array or object.
	bool EndContainer();

	// Ends deserialization.
	bool End();



	// Deserialize logical value (bool or int != 0).
	bool TakeLogic(out bool value, out string error) {
		if (IsNextBool()) {
			if (!TakeBool(value, error)) {
				error = string.Format("Failed to parse logic as bool. ") + error;
				return false;
			};

			return true;
		}
		else if (IsNextInt()) {
			int intValue;
			if (!TakeInt(intValue, error)) {
				error = string.Format("Failed to parse logic as int. ") + error;
				return false;
			};

			value = intValue != 0;
			return true;
		}
		else {
			error = string.Format("Expected bool or int.");
			return false;
		};
	};

	// Returns `true` if next token can be a logical value.
	bool IsNextLogic() {
		return IsNextBool() || IsNextInt();
	};

	// Deserialize number (int or float).
	bool TakeNumber(out int intValue, out float floatValue, out bool isFloat, out string error) {
		if (IsNextInt()) {
			if (!TakeInt(intValue, error)) {
				error = string.Format("Failed to parse number as int. ") + error;
				return false;
			};

			isFloat = false;
			return true;
		}
		else if (IsNextFloat()) {
			if (!TakeFloat(floatValue, error)) {
				error = string.Format("Failed to parse number as float. ") + error;
				return false;
			};

			isFloat = true;
			return true;
		}
		else {
			error = string.Format("Expected int or float.");
			return false;
		};
	};

	// Returns `true` if next token can be a number value.
	bool IsNextNumber() {
		return IsNextInt() || IsNextFloat();
	};

	// Deserialize enum.
	bool TakeEnum(out int value, typename enumType, out string error) {
		array<int> enumValues = {};
		//SCR_Enum.GetEnumValues(enumType, enumValues);

		if (IsNextInt()) {
			// Parse as int
			int intValue;
			if (!TakeInt(intValue, error)) {
				error = string.Format("Failed to parse enum as int. ") + error;
				return false;
			};

			// Validate
			if (!enumValues.Contains(intValue)) {
				auto enumValuesString = "";
				foreach (auto i, auto enumValue : enumValues) {
					if (i != 0)
						enumValuesString += ", ";
					//enumValuesString += string.Format("%1 (\"%2\")", enumValue, SCR_Enum.GetEnumName(enumType, enumValue));
				};
				error = string.Format("Invalid enum value %1, must be one of: ", intValue) + enumValuesString;
				return false;
			};

			value = intValue;
			return true;
		}
		else if (IsNextString()) {
			// Parse as string
			string stringValue;
			if (!TakeString(stringValue, error)) {
				error = string.Format("Failed to parse enum as string. ") + error;
				return false;
			};

			// Validate
			array<string> enumNames = {};
			//SCR_Enum.GetEnumNames(enumType, enumNames);
			auto enumIndex = enumNames.Find(stringValue);
			if (enumIndex == -1) {
				auto enumNamesString = "";
				foreach (auto i, auto enumName : enumNames) {
					if (i != 0)
						enumNamesString += ", ";
					enumNamesString += string.Format("\"%2\"", enumName);
				};
				error = string.Format("Invalid enum value \"%1\", must be one of: ", stringValue) + enumNamesString;
				return false;
			};

			// Get value
			value = enumValues.Get(enumIndex);
			return true;
		}
		else {
			error = string.Format("Expected int or string.");
			return false;
		};
	};

	// Returns `true` if next token can be a enum value.
	bool IsNextEnum() {
		return IsNextInt() || IsNextString();
	};

	bool For(notnull V30_Json_DeserializerCallback callback, out string error);

	bool ForEachArray(notnull V30_Json_DeserializerArrayCallback callback, out string error);

	bool ForEachObject(notnull V30_Json_DeserializerObjectCallback callback, out string error);




	// Returns `true` if next token is a `null`.
	bool IsNextNull();

	// Returns `true` if next token is a boolean value.
	bool IsNextBool();

	// Returns `true` if next token is a integer value.
	bool IsNextInt();

	// Returns `true` if next token is a floating point value.
	bool IsNextFloat();

	// Returns `true` if next token is integer or float value.
	//bool IsNextNumber();

	// Returns `true` if next token is a string value.
	bool IsNextString();

	// Alias for `IsNextArrayBegin()`.
	bool IsNextArray();

	// Returns `true` if next token is a array begin.
	bool IsNextArrayBegin();

	// Returns `true` if next token is array end.
	bool IsNextArrayEnd();

	// Alias for `IsNextObjectBegin()`.
	bool IsNextObject();

	// Returns `true` if next token is object.
	bool IsNextObjectBegin();

	// Returns `true` if next token is object end.
	bool IsNextObjectEnd();

	// Returns `true` if next token is begin or array or object.
	bool IsNextContainerBegin();

	// Returns `true` if next token is end of array or object.
	bool IsNextContainerEnd();

	// Returns `true` if next token is comma.
	bool IsNextComma();

	// Returns `true` if next token is colon.
	bool IsNextColon();



	protected V30_Json_EDeserializerState GetState() {
		if (this.state.IsEmpty())
			return V30_Json_EDeserializerState.ENDED;
		auto i = this.state.Count() - 1;
		return this.state.Get(i);
	};

	protected V30_Json_EDeserializerState GetContainerState();

	protected void PushState(V30_Json_EDeserializerState state) {
		#ifdef ENABLE_DIAG
		if (IsEnded())
			Debug.Error("[V30][JSON][Deserializer] PushState(V30_Json_EDeserializerState): deserializer is already finished.");
		#endif
		this.state.Insert(state);
	};

	protected V30_Json_EDeserializerState PopState() {
		#ifdef ENABLE_DIAG
		if (IsEnded())
			Debug.Error("[V30][JSON][Deserializer] PopState(): deserializer is already finished.");
		#endif
		auto i = this.state.Count() - 1;
		auto state = this.state.Get(i);
		this.state.RemoveOrdered(i);
		return state;
	};

	protected bool PopState(V30_Json_EDeserializerState expected) {
		if (this.state.IsEmpty())
			return false;
		auto i = this.state.Count() - 1;
		auto state = this.state.Get(i);
		if (state != expected)
			return false;
		this.state.RemoveOrdered(i);
		return true;
	};

	// Returns `true` if deserialization of deserializing of root value in progress.
	bool IsRoot();

	// Returns `true` if deserialization of array in progress.
	bool IsArray();

	// Returns `true` if deserialization of object in progress.
	bool IsObject();

	// Returns `true` if deserialization of array or object in progress.
	bool IsContainer();

	// Returns `true` if deserialization of key part of object's value in progress.
	bool IsKey();

	// Returns `true` if deserialization of root value, array element or value part of object's value in progress.
	bool IsValue();

	// Returns `true` if deserialization is ended.
	bool IsEnded();

	// Returns `true` if deserialization of comma in progress.
	bool IsComma();

	// Returns `true` if deserialization of colon in progress.
	bool IsColon();
};

enum V30_Json_EDeserializerState {
	ROOT,
	ARRAY,
	OBJECT,
	KEY,
	COMMA,
	COLON,
	VALUE,
	ENDED
};

enum V30_Json_EType {
	Null,
	Bool,
	Int,
	Float,
	String,
	Array,
	Object
};

enum V30_Json_EValueType {
	Null,
	Bool,
	Int,
	Float,
	String,
	Array,
	Object
};

enum V30_Json_EContainer {
	Root,
	Array,
	Object
};

// Returns human readable name for V30_Json_EDeserializerState.
string V30_Json_EDeserializerStateName(V30_Json_EDeserializerState state) {
	auto name = typename.EnumToString(V30_Json_EDeserializerState, state);
	if (name.IsEmpty())
		return string.Format("%1 (<UNKNOWN>)", state);
	return string.Format("%1 (%2)", state, name);
};

class V30_Json_DeserializerCallback {
	bool OnNull(notnull V30_Json_Deserializer deserializer, out string error);

	bool OnBool(notnull V30_Json_Deserializer deserializer, out string error);

	bool OnInt(notnull V30_Json_Deserializer deserializer, out string error);

	bool OnFloat(notnull V30_Json_Deserializer deserializer, out string error);

	bool OnString(notnull V30_Json_Deserializer deserializer, out string error);

	bool OnArray(notnull V30_Json_Deserializer deserializer, out string error);

	bool OnObject(notnull V30_Json_Deserializer deserializer, out string error);
};

class V30_Json_DeserializerArrayCallback {
	bool OnNull(notnull V30_Json_Deserializer deserializer, int i, out string error);

	bool OnBool(notnull V30_Json_Deserializer deserializer, int i, out string error);

	bool OnInt(notnull V30_Json_Deserializer deserializer, int i, out string error);

	bool OnFloat(notnull V30_Json_Deserializer deserializer, int i, out string error);

	bool OnString(notnull V30_Json_Deserializer deserializer, int i, out string error);

	bool OnArray(notnull V30_Json_Deserializer deserializer, int i, out string error);

	bool OnObject(notnull V30_Json_Deserializer deserializer, int i, out string error);
};

class V30_Json_DeserializerObjectCallback {
	bool OnNull(notnull V30_Json_Deserializer deserializer, string key, out string error);

	bool OnBool(notnull V30_Json_Deserializer deserializer, string key, out string error);

	bool OnInt(notnull V30_Json_Deserializer deserializer, string key, out string error);

	bool OnFloat(notnull V30_Json_Deserializer deserializer, string key, out string error);

	bool OnString(notnull V30_Json_Deserializer deserializer, string key, out string error);

	bool OnArray(notnull V30_Json_Deserializer deserializer, string key, out string error);

	bool OnObject(notnull V30_Json_Deserializer deserializer, string key, out string error);
};
