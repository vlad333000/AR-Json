// Implements serialization.
class V30_Json_Serializer : Managed {
	// State of serialization.
	protected ref array<V30_Json_ESerializerState> state;

	protected void V30_Json_Serializer() {
		this.state = new array<V30_Json_ESerializerState>();
		PushState(V30_Json_ESerializerState.ROOT);
		PushState(V30_Json_ESerializerState.VALUE);
	};

	void ~V30_Json_Serializer() {
		#ifdef ENABLE_DIAG
		if (!IsEnded())
			Debug.Error(string.Format("[V30][Json][Serializer] ~V30_Json_Serializer(): serialization is not finished."));
		#endif
	};



	// Put `null` to serializer.
	void PutNull() {
		#ifdef ENABLE_DIAG
		if (!PopState(V30_Json_ESerializerState.VALUE))
			Debug.Error(string.Format("[V30][Json][Serializer] PutNull(): serializer in wrong state! Expected to be in %1 state, but it's in %2.", V30_Json_ESerializerStateName(V30_Json_ESerializerState.VALUE), V30_Json_ESerializerStateName(GetState())));
		#else
		PopState(); // V30_Json_ESerializerState.VALUE
		#endif
		EndValue();
	};

	// Put boolean value to serializer.
	void PutBool(bool value) {
		#ifdef ENABLE_DIAG
		if (!PopState(V30_Json_ESerializerState.VALUE))
			Debug.Error(string.Format("[V30][Json][Serializer] PutBool(bool): serializer in wrong state! Expected to be in %1 state, but it's in %2.", V30_Json_ESerializerStateName(V30_Json_ESerializerState.VALUE), V30_Json_ESerializerStateName(GetState())));
		#else
		PopState(); // V30_Json_ESerializerState.VALUE
		#endif
		EndValue();
	};

	// Put integer value to serializer.
	void PutInt(int value) {
		#ifdef ENABLE_DIAG
		if (!PopState(V30_Json_ESerializerState.VALUE))
			Debug.Error(string.Format("[V30][Json][Serializer] PutInt(int): serializer in wrong state! Expected to be in %1 state, but it's in %2.", V30_Json_ESerializerStateName(V30_Json_ESerializerState.VALUE), V30_Json_ESerializerStateName(GetState())));
		#else
		PopState(); // V30_Json_ESerializerState.VALUE
		#endif
		EndValue();
	};

	// Put float value to serializer.
	void PutFloat(float value) {
		#ifdef ENABLE_DIAG
		if (!PopState(V30_Json_ESerializerState.VALUE))
			Debug.Error(string.Format("[V30][Json][Serializer] PutFloat(float): serializer in wrong state! Expected to be in %1 state, but it's in %2.", V30_Json_ESerializerStateName(V30_Json_ESerializerState.VALUE), V30_Json_ESerializerStateName(GetState())));
		#else
		PopState(); // V30_Json_ESerializerState.VALUE
		#endif
		EndValue();
	};

	// Put string value to serializer.
	void PutString(string value) {
		#ifdef ENABLE_DIAG
		if (!PopState(V30_Json_ESerializerState.VALUE))
			Debug.Error(string.Format("[V30][Json][Serializer] PutString(string): serializer in wrong state! Expected to be in %1 state, but it's in %2.", V30_Json_ESerializerStateName(V30_Json_ESerializerState.VALUE), V30_Json_ESerializerStateName(GetState())));
		#else
		PopState(); // V30_Json_ESerializerState.VALUE
		#endif
		EndValue();
	};

	// Begins serialization of array.
	void BeginArray() {
		#ifdef ENABLE_DIAG
		if (!PopState(V30_Json_ESerializerState.VALUE))
			Debug.Error(string.Format("[V30][Json][Serializer] BeginArray(): serializer in wrong state! Expected to be in %1 state, but it's in %2.", V30_Json_ESerializerStateName(V30_Json_ESerializerState.VALUE), V30_Json_ESerializerStateName(GetState())));
		#else
		PopState(); // V30_Json_ESerializerState.VALUE
		#endif
		PushState(V30_Json_ESerializerState.ARRAY);
		PushState(V30_Json_ESerializerState.VALUE);
	};

	// Ends serialization of array.
	void EndArray() {
		PopState(V30_Json_ESerializerState.COMMA);
		PopState(V30_Json_ESerializerState.VALUE);
		#ifdef ENABLE_DIAG
		if (!PopState(V30_Json_ESerializerState.ARRAY))
			Debug.Error(string.Format("[V30][Json][Serializer] EndArray(): serializer in wrong state! Expected to be in %1 state, but it's in %2.", V30_Json_ESerializerStateName(V30_Json_ESerializerState.ARRAY), V30_Json_ESerializerStateName(GetState())));
		#else
		PopState(); // V30_Json_ESerializerState.ARRAY
		#endif
		EndValue();
	};

	// Begins serialization of object.
	void BeginObject() {
		#ifdef ENABLE_DIAG
		if (!PopState(V30_Json_ESerializerState.VALUE))
			Debug.Error(string.Format("[V30][Json][Serializer] BeginObject(): serializer in wrong state! Expected to be in %1 state, but it's in %2.", V30_Json_ESerializerStateName(V30_Json_ESerializerState.VALUE), V30_Json_ESerializerStateName(GetState())));
		#else
		PopState(); // V30_Json_ESerializerState.VALUE
		#endif
		PushState(V30_Json_ESerializerState.OBJECT);
		PushState(V30_Json_ESerializerState.KEY);
	};

	// Ends serialization of object.
	void EndObject() {
		PopState(V30_Json_ESerializerState.COMMA);
		PopState(V30_Json_ESerializerState.KEY);
		#ifdef ENABLE_DIAG
		if (!PopState(V30_Json_ESerializerState.OBJECT))
			Debug.Error(string.Format("[V30][Json][Serializer] EndObject(): serializer in wrong state! Expected to be in %1 state, but it's in %2.", V30_Json_ESerializerStateName(V30_Json_ESerializerState.OBJECT), V30_Json_ESerializerStateName(GetState())));
		#else
		PopState(); // V30_Json_ESerializerState.OBJECT
		#endif
		EndValue();
	};

	// Put key for object to serializer.
	void PutKey(string key) {
		#ifdef ENABLE_DIAG
		if (!PopState(V30_Json_ESerializerState.KEY))
			Debug.Error(string.Format("[V30][Json][Serializer] PutKey(string): serializer in wrong state! Expected to be in %1 state, but it's in %2.", V30_Json_ESerializerStateName(V30_Json_ESerializerState.KEY), V30_Json_ESerializerStateName(GetState())));
		#else
		PopState(); // V30_Json_ESerializerState.KEY
		#endif
		PushState(V30_Json_ESerializerState.VALUE);
	};

	// Puts comma to serializer.
	void PutComma() {
		#ifdef ENABLE_DIAG
		if (!PopState(V30_Json_ESerializerState.COMMA))
			Debug.Error(string.Format("[V30][Json][Serializer] PutComma(): serializer in wrong state! Expected to be in %1 state, but it's in %2.", V30_Json_ESerializerStateName(V30_Json_ESerializerState.COMMA), V30_Json_ESerializerStateName(GetState())));
		#else
		PopState(); // V30_Json_ESerializerState.COMMA
		#endif
		if (IsArray())
			PushState(V30_Json_ESerializerState.VALUE);
		else if (IsObject())
			PushState(V30_Json_ESerializerState.KEY);
	};

	// Puts comma to serializer if serializer is expected comma.
	bool TryPutComma() {
		if (GetState() != V30_Json_ESerializerState.COMMA)
			return false;
		PutComma();
		return true;
	};



	// Returns `true` if serializing root value.
	bool IsRoot() {
		return GetContainerState() == V30_Json_ESerializerState.ROOT;
	};

	// Returns `true` if serializing array.
	bool IsArray() {
		return GetContainerState() == V30_Json_ESerializerState.ARRAY;
	};

	// Returns `true` if serializing object.
	bool IsObject() {
		return GetContainerState() == V30_Json_ESerializerState.OBJECT;
	};

	// Returns `true` if `IsArray()` or `IsObject()` returns `true`.
	bool IsContainer() {
		return IsArray() || IsObject();
	};

	// Returns `true` if expecting comma.
	bool IsComma() {
		return GetState() == V30_Json_ESerializerState.COMMA;
	};

	// Returns `true` if expecting object's entry key (Next call must be `PutKey`).
	bool IsKey() {
		return GetState() == V30_Json_ESerializerState.KEY;
	};

	// Returns `true` if expecting any value (Always `true` except when `IsKey` is `true`).
	bool IsValue() {
		return GetState() == V30_Json_ESerializerState.VALUE;
	};

	// Returns `true` if serialization is ended (Root values is putted and last required `End*` call is performed).
	bool IsEnded() {
		return GetState() == V30_Json_ESerializerState.ENDED;
	};



	// Returns current state of serializer.
	protected V30_Json_ESerializerState GetState() {
		auto i = this.state.Count() - 1;
		return this.state.Get(i);
	};

	// Returns container state (root value, array or object).
	protected V30_Json_ESerializerState GetContainerState() {
		auto n = this.state.Count();
		for (auto i = n - 1; i >= 0; i--) {
			auto state = this.state.Get(i);
			switch (state) {
				case V30_Json_ESerializerState.ROOT:
				case V30_Json_ESerializerState.ARRAY:
				case V30_Json_ESerializerState.OBJECT:
					return state;
				case V30_Json_ESerializerState.KEY:
					return V30_Json_ESerializerState.OBJECT;
			};
		};
		#ifdef ENABLE_DIAG
		Debug.Error("[V30][JSON][Serializer] GetContainerState(): unrechable code reached.");
		#endif
		return V30_Json_ESerializerState.UNKNOWN;
	};

	// Pushes new state of serializer to stack.
	protected void PushState(V30_Json_ESerializerState state) {
		this.state.Insert(state);
	};

	// Pop current state of serializer from stack.
	protected V30_Json_ESerializerState PopState() {
		auto i = this.state.Count() - 1;
		auto state = this.state.Get(i);
		this.state.RemoveOrdered(i);
		return state;
	};

	// Pop current state of serializer from stack only if it's equal to `expected`.
	protected bool PopState(V30_Json_ESerializerState expected) {
		auto i = this.state.Count() - 1;
		auto state = this.state.Get(i);
		if (state != expected)
			return false;
		this.state.RemoveOrdered(i);
		return true;
	};

	// Resets state of serializer.
	protected void ResetState() {
		#ifdef ENABLE_DIAG
		if (!IsEnded() && !IsRoot())
			Debug.Error(string.Format("[V30][Json][Serializer] ResetState(): trying to reset in the middle of serialization."));
		#endif
		this.state.Clear();
		PushState(V30_Json_ESerializerState.ROOT);
		PushState(V30_Json_ESerializerState.VALUE);
	};

	// Finishes value, putting ENDED or COMMA state depending on the current state.
	protected void EndValue() {
		if (!PopState(V30_Json_ESerializerState.ROOT))
			PushState(V30_Json_ESerializerState.COMMA);
		else
			PushState(V30_Json_ESerializerState.ENDED);
	};
};

// Serialization state for V30_Json_Serializer class.
enum V30_Json_ESerializerState {
	UNKNOWN,
	ENDED,
	ROOT,
	ARRAY,
	OBJECT,
	COMMA,
	KEY,
	VALUE
};

// Returns human readable name for V30_Json_ESerializerState.
string V30_Json_ESerializerStateName(V30_Json_ESerializerState state) {
	auto name = typename.EnumToString(V30_Json_ESerializerState, state);
	if (name.IsEmpty())
		return string.Format("%1 (<UNKNOWN>)", state);
	return string.Format("%1 (%2)", state, name);
};
