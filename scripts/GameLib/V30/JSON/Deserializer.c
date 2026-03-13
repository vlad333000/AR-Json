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



	bool TakeNull(out string error) {
		// TODO
	};

	bool TakeBool(out bool value, out string error) {
		// TODO
	};

	bool TakeInt(out int value, out string error) {
		// TODO
	};

	bool TakeFloat(out int value, out string error) {
		// TODO
	};

	bool TakeString(out string value, out string error) {
		// TODO
	};

	bool BeginArray(out string error) {
		// TODO
	};

	// param `skip` - skips all values until end of the array.
	bool EndArray(out string error, bool skip = true) {
		// TODO
	};

	bool BeginObject(out string error) {
		// TODO
	};

	// param `skip` - skips all keys and values until end of the object.
	bool EndObject(out string error, bool skip = true) {
		// TODO
	};

	bool TakeKey(out string key, out string error) {
		// TODO
	};

	// Skips one value.
	bool Skip(out string error) {
		// TODO
	};



	// Returns `true` if in process of deserializing of array.
	bool IsArray() {
		// TODO
	};

	// Returns `true` if in process of deserializing of object.
	bool IsObject() {
		// TODO
	};

	// Returns `true` if in process of deserializing of root value.
	bool IsRoot() {
		// TODO
	};

	// Returns `true` if in process of deserializing value (root value, array element or object value part).
	bool IsValue() {
		// TODO
	};

	// Returns `true` if in process of deserializing key (object key part).
	bool IsKey() {
		// TODO
	};

	// Returns `true` if process of deserialization is ended.
	bool IsEnded() {
		return GetState() == V30_Json_EDeserializerState.ENDED;
	};




	// Returns `true` if next value is a `null`.
	bool IsNull() {
		// TODO
	};

	// Returns `true` if next value is a boolean.
	bool IsBool() {
		// TODO
	};

	// Returns `true` if next value is a integer.
	bool IsInt() {
		// TODO
	};

	// Returns `true` if next value is a float.
	bool IsFloat() {
		// TODO
	};

	// Returns `true` if next value is a string.
	bool IsString() {
		// TODO
	};

	// Returns `true` if next value is an array.
	bool IsArrayBegin() {
		// TODO
	};

	// Returns `true` if array is ended.
	bool IsArrayEnd() {
		// TODO
	};

	// Returns `true` if next value is an object.
	bool IsObjectBegin() {
		// TODO
	};

	// Returns `true` if object is ended.
	bool IsObjectEnd() {
		// TODO
	};

	protected V30_Json_EDeserializerState GetState() {
		if (this.state.IsEmpty())
			return V30_Json_EDeserializerState.ENDED;
		auto i = this.state.Count() - 1;
		return this.state.Get(i);
	};

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
};

enum V30_Json_EDeserializerState {
	ENDED,
	ROOT,
	ARRAY,
	OBJECT,
	OBJECT_KEY
};

// Returns human readable name for V30_Json_EDeserializerState.
string V30_Json_EDeserializerStateName(V30_Json_EDeserializerState state) {
	auto name = typename.EnumToString(V30_Json_EDeserializerState, state);
	if (name.IsEmpty())
		return string.Format("%1 (<UNKNOWN>)", state);
	return string.Format("%1 (%2)", state, name);
};
