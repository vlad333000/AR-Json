class V30_JSON_Serializer {
    protected void V30_JSON_Serializer();

    void Serialize(notnull V30_JSON_Value value);

    void SerializeClass(Class inst) {
        if (!inst) {
            Serialize(new V30_JSON_Null());
            return;
        };
        auto instAttr = V30_JSON_SerializerHelper.GetSerializerAttribute(inst);
		#ifdef ENABLE_DIAG
		if (!instAttr)
            Debug.Error(string.Format("unsupported custom type %1 for serialization", inst.Type()));
		#endif
        instAttr.Serialize(this, inst);
    };
};

class V30_JSON_SerializerHelper {
    protected void V30_JSON_SerializerHelper();



    static void Serialize(notnull V30_JSON_Serializer serializer, bool value) {
        serializer.Serialize(new V30_JSON_Bool(value));
    };

    static void Serialize(notnull V30_JSON_Serializer serializer, notnull array<bool> arr) {
		V30_JSON_SerializerHelperT<bool>.SerializeArray(serializer, arr);
    };

    static void Serialize(notnull V30_JSON_Serializer serializer, notnull map<string, bool> obj) {
		V30_JSON_SerializerHelperT<bool>.SerializeObject(serializer, obj);
    };

    static void Serialize(notnull V30_JSON_Serializer serializer, int value) {
        serializer.Serialize(new V30_JSON_Int(value));
    };

    static void Serialize(notnull V30_JSON_Serializer serializer, notnull array<int> arr) {
		V30_JSON_SerializerHelperT<int>.SerializeArray(serializer, arr);
    };

    static void Serialize(notnull V30_JSON_Serializer serializer, notnull map<string, int> obj) {
		V30_JSON_SerializerHelperT<int>.SerializeObject(serializer, obj);
    };

    static void Serialize(notnull V30_JSON_Serializer serializer, float value) {
        serializer.Serialize(new V30_JSON_Float(value));
    };

    static void Serialize(notnull V30_JSON_Serializer serializer, notnull array<float> arr) {
		V30_JSON_SerializerHelperT<float>.SerializeArray(serializer, arr);
    };

    static void Serialize(notnull V30_JSON_Serializer serializer, notnull map<string, float> obj) {
		V30_JSON_SerializerHelperT<float>.SerializeObject(serializer, obj);
    };

    static void Serialize(notnull V30_JSON_Serializer serializer, string value) {
        serializer.Serialize(new V30_JSON_String(value));
    };

    static void Serialize(notnull V30_JSON_Serializer serializer, notnull array<string> arr) {
		V30_JSON_SerializerHelperT<string>.SerializeArray(serializer, arr);
    };

    static void Serialize(notnull V30_JSON_Serializer serializer, notnull map<string, string> obj) {
		V30_JSON_SerializerHelperT<string>.SerializeObject(serializer, obj);
    };

    static void Serialize(notnull V30_JSON_Serializer serializer, Class value) {
        if (!value) {
            serializer.Serialize(new V30_JSON_Null());
            return;
        };
        auto valueType = value.Type();
        if (valueType.IsInherited(array)) {
			bool arrSubTypeIsStrongRef;
			auto arrSubType = GetArraySubType(valueType, arrSubTypeIsStrongRef);
			auto arrSubTypeAttr = GetSerializerAttribute(arrSubType);
			if (arrSubTypeIsStrongRef)
				arrSubTypeAttr.SerializeArrayRef(serializer, Managed.Cast(value));
			else
				arrSubTypeAttr.SerializeArray(serializer, Managed.Cast(value));
		}
        else if (valueType.IsInherited(map)) {
			bool objSubTypeIsStrongRef;
			auto objSubType = GetArraySubType(valueType, objSubTypeIsStrongRef);
			auto objSubTypeAttr = GetSerializerAttribute(objSubType);
			if (objSubTypeIsStrongRef)
				objSubTypeAttr.SerializeObjectRef(serializer, Managed.Cast(value));
			else
				objSubTypeAttr.SerializeObject(serializer, Managed.Cast(value));
		}
        else
            serializer.SerializeClass(value);
    };

    static void Serialize(notnull V30_JSON_Serializer serializer, notnull array<ref V30_JSON_Value> arr) {
        V30_JSON_SerializerHelperRefT<V30_JSON_Value>.SerializeArray(serializer, arr);
    };

    static void Serialize(notnull V30_JSON_Serializer serializer, notnull array<V30_JSON_Value> arr) {
        V30_JSON_SerializerHelperT<V30_JSON_Value>.SerializeArray(serializer, arr);
    };

    static void Serialize(notnull V30_JSON_Serializer serializer, notnull map<string, ref V30_JSON_Value> obj) {
        V30_JSON_SerializerHelperRefT<V30_JSON_Value>.SerializeObject(serializer, obj);
    };

    static void Serialize(notnull V30_JSON_Serializer serializer, notnull map<string, V30_JSON_Value> obj) {
        V30_JSON_SerializerHelperT<V30_JSON_Value>.SerializeObject(serializer, obj);
    };

    static void Serialize(notnull V30_JSON_Serializer serializer, notnull V30_JSON_Value value) {
        serializer.Serialize(value);
    };



	static typename GetArraySubType(notnull Class inst, out bool isStrongRef) {
		return GetArraySubType(inst.Type(), isStrongRef);
	};

	static typename GetArraySubType(typename type, out bool isStrongRef) {
		isStrongRef = type.ToString().StartsWith("array<@");
		if (isStrongRef)
			return GetArraySubTypeStrongRef(type);
		else
			return GetArraySubTypeWeakRef(type);
	};

	static typename GetObjectSubType(notnull Class inst, out bool isStrongRef) {
		return GetObjectSubType(inst.Type(), isStrongRef);
	};

	static typename GetObjectSubType(typename type) {
		auto isStrongRef = type.ToString().StartsWith("map<string,@");
		if (isStrongRef)
			return GetObjectSubTypeStrongRef(type);
		else
			return GetObjectSubTypeWeakRef(type);
	};

	static typename GetObjectSubType(typename type, out bool isStrongRef) {
		isStrongRef = type.ToString().StartsWith("map<string,@");
		if (isStrongRef)
			return GetObjectSubTypeStrongRef(type);
		else
			return GetObjectSubTypeWeakRef(type);
	};

	static typename GetArraySubTypeStrongRef(typename type) {
		#ifdef ENABLE_DIAG
		if (!type.IsInherited(array))
			Debug.Error(string.Format("type %1 isn't array", type));
		if (!type.ToString().StartsWith("array<@"))
			Debug.Error(string.Format("sub-type of array type %1 isn't strong reference", type));
		#endif
		auto typeName = type.ToString();
		return typeName.Substring("array<@".Length(), typeName.Length() - "array<@".Length() - ">".Length()).ToType();
	};

	static typename GetArraySubTypeWeakRef(typename type) {
		#ifdef ENABLE_DIAG
		if (!type.IsInherited(array))
			Debug.Error(string.Format("type %1 isn't array", type));
		if (type.ToString().StartsWith("array<@"))
			Debug.Error(string.Format("sub-type of array type %1 is strong reference", type));
		#endif
		auto typeName = type.ToString();
		return typeName.Substring("array<".Length(), typeName.Length() - "array<".Length() - ">".Length()).ToType();
	};

	static typename GetObjectSubTypeStrongRef(typename type) {
		#ifdef ENABLE_DIAG
		if (!type.IsInherited(map))
			Debug.Error(string.Format("type %1 isn't map", type));
		if (!type.ToString().StartsWith("map<string"))
			Debug.Error(string.Format("key type of map type %1 isn't string", type));
		if (!type.ToString().StartsWith("map<string,@"))
			Debug.Error(string.Format("value type of map type %1 isn't strong reference", type));
		#endif
		auto typeName = type.ToString();
		return typeName.Substring("map<string,@".Length(), typeName.Length() - "map<string,@".Length() - ">".Length()).ToType();
	};

	static typename GetObjectSubTypeWeakRef(typename type) {
		#ifdef ENABLE_DIAG
		if (!type.IsInherited(map))
			Debug.Error(string.Format("type %1 isn't map", type));
		if (!type.ToString().StartsWith("map<string"))
			Debug.Error(string.Format("key type of map type %1 isn't string", type));
		if (type.ToString().StartsWith("map<string,@"))
			Debug.Error(string.Format("value type of map type %1 is strong reference", type));
		#endif
		auto typeName = type.ToString();
		return typeName.Substring("map<string,".Length(), typeName.Length() - "map<string,".Length() - ">".Length()).ToType();
	};

    static V30_JSON_SerializerAttribute GetSerializerAttribute(notnull Class inst) {
        return GetSerializerAttribute(inst.Type());
    };

	protected static ref map<typename, V30_JSON_SerializerAttribute> s_SerializerAttributes = new map<typename, V30_JSON_SerializerAttribute>();

	static V30_JSON_SerializerAttribute GetSerializerAttribute(typename type) {
		V30_JSON_SerializerAttribute typeSerializerAttr;
		if (!s_SerializerAttributes.Find(type, typeSerializerAttr)) {
			auto typeAttrs = new array<Class>();
			type.GetAttributes(typeAttrs);
			foreach (auto typeAttr : typeAttrs)
				if (typeAttr.IsInherited(V30_JSON_SerializerAttribute)) {
					typeSerializerAttr = V30_JSON_SerializerAttribute.Cast(typeAttr);
					s_SerializerAttributes.Insert(type, typeSerializerAttr);
					return typeSerializerAttr;
				};
			s_SerializerAttributes.Insert(type, null);
			return null;
		};
		return typeSerializerAttr;
	};

	static void SetSerializerAttribute(typename type, V30_JSON_SerializerAttribute typeSerializerAttr) {
		s_SerializerAttributes.Set(type, typeSerializerAttr);
	};
};

class V30_JSON_SerializerHelperT<Class T> {
    static void SerializeArray(notnull V30_JSON_Serializer serializer, notnull array<T> arr) {
		auto jsonSerializer = new V30_JSON_ValueSerializer();
		jsonSerializer.BeginArraySerialization();
        foreach (auto el : arr) {
			V30_JSON_SerializerHelper.Serialize(jsonSerializer, el);
		};
		jsonSerializer.EndArraySerialization();
		auto jsonValue = jsonSerializer.GetValue();
		serializer.Serialize(jsonValue);
    };

    static void SerializeObject(notnull V30_JSON_Serializer serializer, notnull map<string, T> obj) {
		auto jsonSerializer = new V30_JSON_ValueSerializer();
		jsonSerializer.BeginObjectSerialization();
        foreach (auto key, auto el : obj) {
			jsonSerializer.SerializeKey(key);
			V30_JSON_SerializerHelper.Serialize(jsonSerializer, el);
		};
		jsonSerializer.EndObjectSerialization();
		auto jsonValue = jsonSerializer.GetValue();
		serializer.Serialize(jsonValue);
    };
};

class V30_JSON_SerializerHelperRefT<Managed T> {
    static void SerializeArray(notnull V30_JSON_Serializer serializer, notnull array<ref T> arr) {
		auto jsonSerializer = new V30_JSON_ValueSerializer();
		jsonSerializer.BeginArraySerialization();
        foreach (auto el : arr) {
			V30_JSON_SerializerHelper.Serialize(jsonSerializer, el);
		};
		jsonSerializer.EndArraySerialization();
		auto jsonValue = jsonSerializer.GetValue();
		serializer.Serialize(jsonValue);
    };

    static void SerializeObject(notnull V30_JSON_Serializer serializer, notnull map<string, ref T> obj) {
		auto jsonSerializer = new V30_JSON_ValueSerializer();
		jsonSerializer.BeginObjectSerialization();
        foreach (auto key, auto el : obj) {
			jsonSerializer.SerializeKey(key);
			V30_JSON_SerializerHelper.Serialize(jsonSerializer, el);
		};
		jsonSerializer.EndObjectSerialization();
		auto jsonValue = jsonSerializer.GetValue();
		serializer.Serialize(jsonValue);
    };
};
