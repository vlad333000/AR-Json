class V30_JSON_DefaultSerializerAttribute : V30_JSON_StreamSerializerAttribute {
    protected static ref V30_JSON_DefaultSerializerAttribute s_Instance = new V30_JSON_DefaultSerializerAttribute();

    protected void V30_JSON_DefaultSerializerAttribute();

    override void StreamSerialize(notnull V30_JSON_StreamSerializer serializer, Class instance) {
        if (!instance) {
            serializer.Serialize(null);
            return;
        };
        serializer.BeginObjectSerialization();
            auto instanceType = instance.Type();
            auto variablesCount = instanceType.GetVariableCount();
            for (auto variableIndex = 0; variableIndex < variablesCount; variableIndex++)
                SerializeVariable(serializer, instance, variableIndex);
        serializer.EndObjectSerialization();
    };

    void SerializeVariable(notnull V30_JSON_StreamSerializer serializer, notnull Class instance, int variableIndex) {
        auto variableType = instance.Type().GetVariableType(variableIndex);
        SerializeVariable(serializer, instance, variableIndex, variableType);
    };

    protected void SerializeVariable(notnull V30_JSON_StreamSerializer serializer, notnull Class instance, int variableIndex, typename variableType) {
        switch (variableType) {
            case bool:
                V30_JSON_DefaultSerializerAttribute_HelperT<bool>.Serialize(serializer, instance, variableIndex);
                break;
            case int:
                V30_JSON_DefaultSerializerAttribute_HelperT<int>.Serialize(serializer, instance, variableIndex);
                break;
            case float:
                V30_JSON_DefaultSerializerAttribute_HelperT<float>.Serialize(serializer, instance, variableIndex);
                break;
            case string:
                V30_JSON_DefaultSerializerAttribute_HelperT<string>.Serialize(serializer, instance, variableIndex);
                break;
            default:
                if (variableType.IsInherited(Class))
                    V30_JSON_DefaultSerializerAttribute_Helper.Serialize(serializer, instance, variableIndex);
                break;
        };
    };

    static V30_JSON_DefaultSerializerAttribute GetInstance() {
        return s_Instance;
    };
};

class V30_JSON_DefaultSerializerAttribute_Helper {
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

    static void Serialize(notnull V30_JSON_StreamSerializer serializer, notnull Class instance, int i) {
        auto instanceType = instance.Type();
        Class value;
        instanceType.GetVariableValue(instance, i, value);
        auto key = instanceType.GetVariableName(i);
        V30_JSON_SerializerHelper.SerializePair(serializer, key, value);
    };
};

class V30_JSON_DefaultSerializerAttribute_HelperT<Class T> {
    protected void V30_JSON_DefaultSerializerAttribute_HelperT();

    static void Serialize(notnull V30_JSON_StreamSerializer serializer, notnull Class instance, int i) {
        auto instanceType = instance.Type();
        T value;
        instanceType.GetVariableValue(instance, i, value);
        auto key = instanceType.GetVariableName(i);
        V30_JSON_SerializerHelper.SerializePair(serializer, key, value);
    };
};
