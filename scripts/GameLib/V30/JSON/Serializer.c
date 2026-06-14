class V30_JSON_Serializer {
    protected void V30_JSON_Serializer();

    void Serialize(notnull V30_JSON_Value value) {
        switch (value.Type()) {
            case V30_JSON_Null:
                Serialize(V30_JSON_Null.Cast(value));
                break;
            case V30_JSON_Bool:
                Serialize(V30_JSON_Bool.Cast(value));
                break;
            case V30_JSON_Int:
                Serialize(V30_JSON_Int.Cast(value));
                break;
            case V30_JSON_Float:
                Serialize(V30_JSON_Float.Cast(value));
                break;
            case V30_JSON_String:
                Serialize(V30_JSON_String.Cast(value));
                break;
            case V30_JSON_Array:
                Serialize(V30_JSON_Array.Cast(value));
                break;
            case V30_JSON_Object:
                Serialize(V30_JSON_Object.Cast(value));
                break;
            default:
                Debug.Error(string.Format("Unknown JSON type: %1", value.Type()));
                break;
        };
    };

    void Serialize(notnull V30_JSON_Null value) {
        SerializeNull();
    };

    void Serialize(notnull V30_JSON_Bool value) {
        Serialize(value.GetValue());
    };

    void Serialize(notnull V30_JSON_Number value) {
        switch (value.Type()) {
            case V30_JSON_Int:
                Serialize(V30_JSON_Int.Cast(value));
                break;
            case V30_JSON_Float:
                Serialize(V30_JSON_Float.Cast(value));
                break;
            default:
                Debug.Error(string.Format("Unknown JSON number type: %1", value.Type()));
                break;
        };
    };

    void Serialize(notnull V30_JSON_Int value) {
        Serialize(value.GetValue());
    };

    void Serialize(notnull V30_JSON_Float value) {
        Serialize(value.GetValue());
    };

    void Serialize(notnull V30_JSON_String value) {
        Serialize(value.GetValue());
    };

    void Serialize(notnull V30_JSON_Container value) {
        switch (value.Type()) {
            case V30_JSON_Array:
                Serialize(V30_JSON_Array.Cast(value));
                break;
            case V30_JSON_Object:
                Serialize(V30_JSON_Object.Cast(value));
                break;
            default:
                Debug.Error(string.Format("Unknown JSON container type: %1", value.Type()));
                break;
        };
    };

    void Serialize(notnull V30_JSON_Array value) {
        foreach (auto element : value.GetValue())
            Serialize(element);
    };

    void Serialize(notnull V30_JSON_Object value) {
        foreach (auto key, auto element : value.GetValue()) {
			SerializeKey(key);
            Serialize(element);
		};
    };

    void SerializeNull();

    void Serialize(bool value);

    void Serialize(int value);

    void Serialize(float value);

    void Serialize(string value);

    void Serialize(Class instance) {
        if (!instance) {
            SerializeNull();
            return;
        };
        V30_JSON_SerializerHelper.Serialize(this, instance);
    };

    void SerializeKey(string key) {
        Serialize(key);
    };
};

class V30_JSON_SerializerHelper {
    protected void V30_JSON_SerializerHelper();

	static typename GetArraySubType(typename type, out bool isRef) {
		if (!type.IsInherited(array))
			return typename.Empty;
		auto typeString = type.ToString();
		if (!typeString.StartsWith("array<"))
			return typename.Empty;
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

	static typename GetObjectSubType(typename type, out bool isRef) {
		if (!type.IsInherited(map))
			return typename.Empty;
		auto typeString = type.ToString();
		if (!typeString.StartsWith("map<string"))
			return typename.Empty;
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

    static V30_JSON_SerializerAttribute GetSerializerAttribute(Class instance) {
        if (!instance)
            return V30_JSON_DefaultSerializerAttribute.GetInstance();
        return GetSerializerAttribute(instance.Type());
    };

	static V30_JSON_SerializerAttribute GetSerializerAttribute(typename type) {
        if (!type.IsInherited(Class))
            return null;
		auto attributes = new array<Class>();
		type.GetAttributes(attributes);
		foreach (auto attribute : attributes) {
            auto instanceSerializer = V30_JSON_SerializerAttribute.Cast(attribute);
			if (instanceSerializer)
				return instanceSerializer;
        };
		return V30_JSON_DefaultSerializerAttribute.GetInstance();
	};

    static void Serialize(notnull V30_JSON_Serializer serializer, notnull Class instance) {
        auto type = instance.Type();
        Serialize(serializer, instance, type);
    };

    static void Serialize(notnull V30_JSON_Serializer serializer, notnull Class instance, typename type) {
        if (type.IsInherited(array))
            SerializeArray(serializer, Managed.Cast(instance), type);
        else if (type.IsInherited(map))
            SerializeObject(serializer, Managed.Cast(instance), type);
        else
            SerializeClass(serializer, instance, type);
    };

    static void SerializeArray(notnull V30_JSON_Serializer serializer, notnull Managed arr) {
        auto arrType = arr.Type();
        SerializeArray(serializer, arr, arrType);
    };

    static void SerializeArray(notnull V30_JSON_Serializer serializer, notnull Managed arr, typename arrType) {
        bool arrSubTypeIsRef;
        auto arrSubType = V30_JSON_SerializerHelper.GetArraySubType(arrType, arrSubTypeIsRef);
        SerializeArray(serializer, arr, arrSubType, arrSubTypeIsRef);
    };

    static void SerializeArray(notnull V30_JSON_Serializer serializer, notnull Managed arr, typename arrSubType, bool arrSubTypeIsRef) {
        switch (arrSubType) {
            case bool:
                V30_JSON_SerializerHelperT<bool>.SerializeArray(serializer, arr);
                break;
            case int:
                V30_JSON_SerializerHelperT<int>.SerializeArray(serializer, arr);
                break;
            case float:
                V30_JSON_SerializerHelperT<float>.SerializeArray(serializer, arr);
                break;
            case string:
                V30_JSON_SerializerHelperT<string>.SerializeArray(serializer, arr);
                break;
            default:
                if (arrSubType.IsInherited(Class)) {
                    auto arrSubTypeSerializer = V30_JSON_SerializerHelper.GetSerializerAttribute(arrSubType);
                    SerializeArray(serializer, arr, arrSubTypeSerializer, arrSubTypeIsRef);
                };
                break;
        };
    };

    static void SerializeArray(notnull V30_JSON_Serializer serializer, notnull Managed arr, notnull V30_JSON_SerializerAttribute arrSubTypeSerializer, bool arrSubTypeIsRef) {
        if (arrSubTypeIsRef)
            SerializeArrayRef(serializer, arr, arrSubTypeSerializer);
        else
            SerializeArray(serializer, arr, arrSubTypeSerializer);
    };

    static void SerializeArray(notnull V30_JSON_Serializer serializer, notnull Managed arr, notnull V30_JSON_SerializerAttribute arrSubTypeSerializer) {
        arrSubTypeSerializer.SerializeArray(serializer, arr);
    };

    static void SerializeArrayRef(notnull V30_JSON_Serializer serializer, notnull Managed arr, notnull V30_JSON_SerializerAttribute arrSubTypeSerializer) {
        arrSubTypeSerializer.SerializeArrayRef(serializer, arr);
    };

    static void SerializeObject(notnull V30_JSON_Serializer serializer, notnull Managed obj) {
        auto objType = obj.Type();
        SerializeObject(serializer, obj, objType);
    };

    static void SerializeObject(notnull V30_JSON_Serializer serializer, notnull Managed obj, typename objType) {
        bool objSubTypeIsRef;
        auto objSubType = V30_JSON_SerializerHelper.GetObjectSubType(objType, objSubTypeIsRef);
        SerializeObject(serializer, obj, objSubType, objSubTypeIsRef);
    };

    static void SerializeObject(notnull V30_JSON_Serializer serializer, notnull Managed obj, typename objSubType, bool objSubTypeIsRef) {
        switch (objSubType) {
            case bool:
                V30_JSON_SerializerHelperT<bool>.SerializeObject(serializer, obj);
                break;
            case int:
                V30_JSON_SerializerHelperT<int>.SerializeObject(serializer, obj);
                break;
            case float:
                V30_JSON_SerializerHelperT<float>.SerializeObject(serializer, obj);
                break;
            case string:
                V30_JSON_SerializerHelperT<string>.SerializeObject(serializer, obj);
                break;
            default:
                if (objSubType.IsInherited(Class)) {
                    auto objSubTypeSerializer = V30_JSON_SerializerHelper.GetSerializerAttribute(objSubType);
                    SerializeObject(serializer, obj, objSubTypeSerializer, objSubTypeIsRef);
                };
                break;
        };
    };

    static void SerializeObject(notnull V30_JSON_Serializer serializer, notnull Managed obj, notnull V30_JSON_SerializerAttribute objSubTypeSerializer, bool objSubTypeIsRef) {
        if (objSubTypeIsRef)
            SerializeObjectRef(serializer, obj, objSubTypeSerializer);
        else
            SerializeObject(serializer, obj, objSubTypeSerializer);
    };

    static void SerializeObject(notnull V30_JSON_Serializer serializer, notnull Managed obj, notnull V30_JSON_SerializerAttribute objSubTypeSerializer) {
        objSubTypeSerializer.SerializeObject(serializer, obj);
    };

    static void SerializeObjectRef(notnull V30_JSON_Serializer serializer, notnull Managed obj, notnull V30_JSON_SerializerAttribute objSubTypeSerializer) {
        objSubTypeSerializer.SerializeObjectRef(serializer, obj);
    };

    static void SerializeClass(notnull V30_JSON_Serializer serializer, notnull Class instance) {
        auto type = instance.Type();
        SerializeClass(serializer, instance, type);
    };

    static void SerializeClass(notnull V30_JSON_Serializer serializer, notnull Class instance, typename type) {
        auto instanceSerializer = GetSerializerAttribute(type);
        SerializeClass(serializer, instance, instanceSerializer);
    };

    static void SerializeClass(notnull V30_JSON_Serializer serializer, notnull Class instance, notnull V30_JSON_SerializerAttribute instanceSerializer) {
        instanceSerializer.Serialize(serializer, instance);
    };
};

class V30_JSON_SerializerHelperT<Class T> {
    static void SerializeArray(notnull V30_JSON_Serializer serializer, notnull Managed arr) {
        auto valueSerializer = new V30_JSON_ValueSerializer();
        auto arrJson = new V30_JSON_Array();
        foreach (auto value : array<T>.Cast(arr)) {
            valueSerializer.Serialize(value);
            auto valueJson = valueSerializer.GetValue();
            arrJson.Insert(valueJson);
            valueSerializer.ClearValue();
        };
        serializer.Serialize(arrJson);
    };

    static void SerializeObject(notnull V30_JSON_Serializer serializer, notnull Managed obj) {
        auto valueSerializer = new V30_JSON_ValueSerializer();
        auto arrJson = new V30_JSON_Object();
        foreach (auto key, auto value : map<string, T>.Cast(obj)) {
            valueSerializer.Serialize(value);
            auto valueJson = valueSerializer.GetValue();
            arrJson.Insert(key, valueJson);
            valueSerializer.ClearValue();
        };
        serializer.Serialize(arrJson);
    };
};

class V30_JSON_SerializerHelperRefT<Managed T> {
    static void SerializeArray(notnull V30_JSON_Serializer serializer, notnull Managed arr) {
        auto valueSerializer = new V30_JSON_ValueSerializer();
        auto arrJson = new V30_JSON_Array();
        foreach (auto value : array<ref T>.Cast(arr)) {
            valueSerializer.Serialize(value);
            auto valueJson = valueSerializer.GetValue();
            arrJson.Insert(valueJson);
            valueSerializer.ClearValue();
        };
        serializer.Serialize(arrJson);
    };

    static void SerializeObject(notnull V30_JSON_Serializer serializer, notnull Managed obj) {
        auto valueSerializer = new V30_JSON_ValueSerializer();
        auto arrJson = new V30_JSON_Object();
        foreach (auto key, auto value : map<string, ref T>.Cast(obj)) {
            valueSerializer.Serialize(value);
            auto valueJson = valueSerializer.GetValue();
            arrJson.Insert(key, valueJson);
            valueSerializer.ClearValue();
        };
        serializer.Serialize(arrJson);
    };
};
