class V30_JSON_StreamSerializer : V30_JSON_Serializer {
    protected void V30_JSON_StreamSerializer();

    override void Serialize(notnull V30_JSON_Value value) {
        switch (value.Type()) {
            case V30_JSON_Null:
                SerializeNull();
                break;
            case V30_JSON_Bool:
                SerializeBool(V30_JSON_Bool.Cast(value).GetValue());
                break;
            case V30_JSON_Int:
                SerializeInt(V30_JSON_Int.Cast(value).GetValue());
                break;
            case V30_JSON_Float:
                SerializeFloat(V30_JSON_Float.Cast(value).GetValue());
                break;
            case V30_JSON_String:
                SerializeString(V30_JSON_String.Cast(value).GetValue());
                break;
            case V30_JSON_Array:
                BeginArraySerialization();
                foreach(auto element : V30_JSON_Array.Cast(value).GetValue()) {
                    Serialize(element);
                };
                EndArraySerialization();
                break;
            case V30_JSON_Object:
                BeginObjectSerialization();
                foreach(auto key, auto element : V30_JSON_Object.Cast(value).GetValue()) {
                    SerializeKey(key);
                    Serialize(element);
                };
                EndObjectSerialization();
                break;
            default:
                Debug.Error(string.Format("Unknown JSON type: %1", value.Type()));
                break;
        };
    };

    void SerializeNull();

    void SerializeBool(bool value);

    void SerializeInt(int value);

    void SerializeFloat(float value);

    void SerializeString(string value);

    void BeginArraySerialization();

    void EndArraySerialization();

    void BeginObjectSerialization();

    void EndObjectSerialization();

    void SerializeKey(string key) {
        SerializeString(key);
    };
};

class V30_JSON_StreamSerializerHelper {
    protected void V30_JSON_StreamSerializerHelper();

    static void Serialize(notnull V30_JSON_StreamSerializer serializer, bool value) {
        serializer.SerializeBool(value);
    };

    static void Serialize(notnull V30_JSON_StreamSerializer serializer, notnull array<bool> arr) {
		V30_JSON_StreamSerializerHelperT<bool>.SerializeArray(serializer, arr);
    };

    static void Serialize(notnull V30_JSON_StreamSerializer serializer, notnull map<string, bool> obj) {
		V30_JSON_StreamSerializerHelperT<bool>.SerializeObject(serializer, obj);
    };

    static void Serialize(notnull V30_JSON_StreamSerializer serializer, int value) {
        serializer.SerializeInt(value);
    };

    static void Serialize(notnull V30_JSON_StreamSerializer serializer, notnull array<int> arr) {
		V30_JSON_StreamSerializerHelperT<int>.SerializeArray(serializer, arr);
    };

    static void Serialize(notnull V30_JSON_StreamSerializer serializer, notnull map<string, int> obj) {
		V30_JSON_StreamSerializerHelperT<int>.SerializeObject(serializer, obj);
    };

    static void Serialize(notnull V30_JSON_StreamSerializer serializer, float value) {
        serializer.SerializeFloat(value);
    };

    static void Serialize(notnull V30_JSON_StreamSerializer serializer, notnull array<float> arr) {
		V30_JSON_StreamSerializerHelperT<float>.SerializeArray(serializer, arr);
    };

    static void Serialize(notnull V30_JSON_StreamSerializer serializer, notnull map<string, float> obj) {
		V30_JSON_StreamSerializerHelperT<float>.SerializeObject(serializer, obj);
    };

    static void Serialize(notnull V30_JSON_StreamSerializer serializer, string value) {
        serializer.SerializeString(value);
    };

    static void Serialize(notnull V30_JSON_StreamSerializer serializer, notnull array<string> arr) {
		V30_JSON_StreamSerializerHelperT<string>.SerializeArray(serializer, arr);
    };

    static void Serialize(notnull V30_JSON_StreamSerializer serializer, notnull map<string, string> obj) {
		V30_JSON_StreamSerializerHelperT<string>.SerializeObject(serializer, obj);
    };

    static void Serialize(notnull V30_JSON_StreamSerializer serializer, Class value) {
        if (!value) {
            serializer.SerializeNull();
            return;
        };
        auto valueType = value.Type();
        if (valueType.IsInherited(array)) {
			bool arrSubTypeIsStrongRef;
			auto arrSubType = V30_JSON_SerializerHelper.GetArraySubType(valueType, arrSubTypeIsStrongRef);
			auto arrSubTypeAttr = V30_JSON_SerializerHelper.GetSerializerAttribute(arrSubType);
			if (arrSubTypeIsStrongRef)
				arrSubTypeAttr.SerializeArrayRef(serializer, Managed.Cast(value));
			else
				arrSubTypeAttr.SerializeArray(serializer, Managed.Cast(value));
		}
        else if (valueType.IsInherited(map)) {
			bool objSubTypeIsStrongRef;
			auto objSubType = V30_JSON_SerializerHelper.GetArraySubType(valueType, objSubTypeIsStrongRef);
			auto objSubTypeAttr = V30_JSON_SerializerHelper.GetSerializerAttribute(objSubType);
			if (objSubTypeIsStrongRef)
				objSubTypeAttr.SerializeObjectRef(serializer, Managed.Cast(value));
			else
				objSubTypeAttr.SerializeObject(serializer, Managed.Cast(value));
		}
        else
            serializer.SerializeClass(value);
    };

    static void Serialize(notnull V30_JSON_StreamSerializer serializer, notnull array<ref V30_JSON_Value> arr) {
        V30_JSON_StreamSerializerHelperRefT<V30_JSON_Value>.SerializeArray(serializer, arr);
    };

    static void Serialize(notnull V30_JSON_StreamSerializer serializer, notnull array<V30_JSON_Value> arr) {
        V30_JSON_StreamSerializerHelperT<V30_JSON_Value>.SerializeArray(serializer, arr);
    };

    static void Serialize(notnull V30_JSON_StreamSerializer serializer, notnull map<string, ref V30_JSON_Value> obj) {
        V30_JSON_StreamSerializerHelperRefT<V30_JSON_Value>.SerializeObject(serializer, obj);
    };

    static void Serialize(notnull V30_JSON_StreamSerializer serializer, notnull map<string, V30_JSON_Value> obj) {
        V30_JSON_StreamSerializerHelperT<V30_JSON_Value>.SerializeObject(serializer, obj);
    };

    static void Serialize(notnull V30_JSON_StreamSerializer serializer, notnull V30_JSON_Value value) {
        serializer.Serialize(value);
    };

    static void Serialize(notnull V30_JSON_StreamSerializer serializer, notnull V30_JSON_Null value) {
        serializer.SerializeNull();
    };

    static void Serialize(notnull V30_JSON_StreamSerializer serializer, notnull V30_JSON_Bool value) {
        serializer.SerializeBool(value.GetValue());
    };

    static void Serialize(notnull V30_JSON_StreamSerializer serializer, notnull V30_JSON_Number value) {
        switch (value.Type()) {
            case V30_JSON_Int:
        		serializer.SerializeInt(V30_JSON_Int.Cast(value).GetValue());
                break;
            case V30_JSON_Float:
        		serializer.SerializeFloat(V30_JSON_Float.Cast(value).GetValue());
                break;
            default:
                Debug.Error(string.Format("unknown json number type: %1", value.Type().ToString()));
                return;
        };
    };

    static void Serialize(notnull V30_JSON_StreamSerializer serializer, notnull V30_JSON_Int value) {
        serializer.SerializeInt(value.GetValue());
    };

    static void Serialize(notnull V30_JSON_StreamSerializer serializer, notnull V30_JSON_Float value) {
        serializer.SerializeFloat(value.GetValue());
    };

    static void Serialize(notnull V30_JSON_StreamSerializer serializer, notnull V30_JSON_String value) {
        serializer.SerializeString(value.GetValue());
    };

    static void Serialize(notnull V30_JSON_StreamSerializer serializer, notnull V30_JSON_Container value) {
        switch (value.Type()) {
            case V30_JSON_Array:
                V30_JSON_StreamSerializerHelperRefT<V30_JSON_Value>.SerializeArray(serializer, V30_JSON_Array.Cast(value).GetValue());
                break;
            case V30_JSON_Object:
                V30_JSON_StreamSerializerHelperRefT<V30_JSON_Value>.SerializeObject(serializer, V30_JSON_Object.Cast(value).GetValue());
                break;
            default:
                Debug.Error(string.Format("unknown json container type: %1", value.Type().ToString()));
                return;
        };
    };

    static void Serialize(notnull V30_JSON_StreamSerializer serializer, notnull V30_JSON_Array value) {
        V30_JSON_StreamSerializerHelperRefT<V30_JSON_Value>.SerializeArray(serializer, V30_JSON_Array.Cast(value).GetValue());
    };

    static void Serialize(notnull V30_JSON_StreamSerializer serializer, notnull V30_JSON_Object value) {
        V30_JSON_StreamSerializerHelperRefT<V30_JSON_Value>.SerializeObject(serializer, V30_JSON_Object.Cast(value).GetValue());
    };
};

class V30_JSON_StreamSerializerHelperT<Class T> {
    static void SerializeArray(notnull V30_JSON_StreamSerializer serializer, notnull array<T> arr) {
		serializer.BeginArraySerialization();
        foreach (auto el : arr)
			V30_JSON_StreamSerializerHelper.Serialize(serializer, el);
		serializer.EndArraySerialization();
    };

    static void SerializeObject(notnull V30_JSON_StreamSerializer serializer, notnull map<string, T> obj) {
		serializer.BeginObjectSerialization();
        foreach (auto key, auto el : obj) {
			serializer.SerializeKey(key);
			V30_JSON_StreamSerializerHelper.Serialize(serializer, el);
		};
		serializer.EndObjectSerialization();
    };
};

class V30_JSON_StreamSerializerHelperRefT<Managed T> {
    static void SerializeArray(notnull V30_JSON_StreamSerializer serializer, notnull array<ref T> arr) {
		serializer.BeginArraySerialization();
        foreach (auto el : arr)
			V30_JSON_StreamSerializerHelper.Serialize(serializer, el);
		serializer.EndArraySerialization();
    };

    static void SerializeObject(notnull V30_JSON_StreamSerializer serializer, notnull map<string, ref T> obj) {
		serializer.BeginObjectSerialization();
        foreach (auto key, auto el : obj) {
			serializer.SerializeKey(key);
			V30_JSON_StreamSerializerHelper.Serialize(serializer, el);
		};
		serializer.EndObjectSerialization();
    };
};
