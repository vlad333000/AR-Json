class V30_JSON_Serializer {
    protected void V30_JSON_Serializer();

    void Serialize(notnull V30_JSON_Value value) {
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
                SerializeArray(V30_JSON_Array.Cast(value));
                break;
            case V30_JSON_Object:
                SerializeObject(V30_JSON_Object.Cast(value));
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

    void SerializeArray(notnull V30_JSON_Array value) {
        foreach (auto element : value.GetValue())
            Serialize(element);
    };

    void SerializeObject(notnull V30_JSON_Object value) {
        foreach (auto key, auto element : value.GetValue()) {
            SerializeKey(key);
            Serialize(element);
        };
    };

    void SerializeClass(Class instance) {
        if (!instance) {
            SerializeNull();
            return;
        };
        V30_JSON_SerializerHelper.Serialize(this, instance);
    };

    void SerializeKey(string key) {
        SerializeString(key);
    };
};

class V30_JSON_SerializerHelper {
    protected void V30_JSON_SerializerHelper();



    static void Serialize(notnull V30_JSON_Serializer serializer, bool value) {
        serializer.SerializeBool(value);
    };

    static void Serialize(notnull V30_JSON_Serializer serializer, int value) {
        serializer.SerializeInt(value);
    };

    static void Serialize(notnull V30_JSON_Serializer serializer, float value) {
        serializer.SerializeFloat(value);
    };

    static void Serialize(notnull V30_JSON_Serializer serializer, string value) {
        serializer.SerializeString(value);
    };

    static void SerializePair(notnull V30_JSON_Serializer serializer, string key, bool value) {
        SerializeBoolPair(serializer, key, value);
    };

    static void SerializePair(notnull V30_JSON_Serializer serializer, string key, int value) {
        SerializeIntPair(serializer, key, value);
    };

    static void SerializePair(notnull V30_JSON_Serializer serializer, string key, float value) {
        SerializeFloatPair(serializer, key, value);
    };

    static void SerializePair(notnull V30_JSON_Serializer serializer, string key, string value) {
        SerializeStringPair(serializer, key, value);
    };

    static void SerializePair(notnull V30_JSON_Serializer serializer, string key, Class value) {
        SerializeClassPair(serializer, key, value);
    };



    static void SerializeNullPair(notnull V30_JSON_Serializer serializer, string key) {
        serializer.SerializeKey(key);
        serializer.SerializeNull();
    }

    static void SerializeBoolPair(notnull V30_JSON_Serializer serializer, string key, bool value) {
        serializer.SerializeKey(key);
        serializer.SerializeBool(value);
    };

    static void SerializeIntPair(notnull V30_JSON_Serializer serializer, string key, int value) {
        serializer.SerializeKey(key);
        serializer.SerializeInt(value);
    };

    static void SerializeFloatPair(notnull V30_JSON_Serializer serializer, string key, float value) {
        serializer.SerializeKey(key);
        serializer.SerializeFloat(value);
    };

    static void SerializeStringPair(notnull V30_JSON_Serializer serializer, string key, string value) {
        serializer.SerializeKey(key);
        serializer.SerializeString(value);
    };

    static void SerializeArrayPair(notnull V30_JSON_Serializer serializer, string key, notnull V30_JSON_Array value) {
        serializer.SerializeKey(key);
        serializer.SerializeArray(value);
    };

    static void SerializeObjectPair(notnull V30_JSON_Serializer serializer, string key, notnull V30_JSON_Object value) {
        serializer.SerializeKey(key);
        serializer.SerializeObject(value);
    };

    static void SerializeClassPair(notnull V30_JSON_Serializer serializer, string key, Class instance) {
        serializer.SerializeKey(key);
        serializer.SerializeClass(instance);
    };



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
            V30_JSON_SerializerHelper.Serialize(valueSerializer, value);
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
            V30_JSON_SerializerHelper.Serialize(valueSerializer, value);
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
            V30_JSON_SerializerHelper.Serialize(valueSerializer, value);
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
            V30_JSON_SerializerHelper.Serialize(valueSerializer, value);
            auto valueJson = valueSerializer.GetValue();
            arrJson.Insert(key, valueJson);
            valueSerializer.ClearValue();
        };
        serializer.Serialize(arrJson);
    };
};
