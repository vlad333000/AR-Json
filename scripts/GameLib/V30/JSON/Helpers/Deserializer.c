class V30_Json_DeserializerHelper {
	static bool Take(notnull V30_Json_Deserializer deserializer, out bool value, out string error) {
		return deserializer.TakeBool(value, error);
	};

	static bool Take(notnull V30_Json_Deserializer deserializer, out int value, out string error) {
		return deserializer.TakeInt(value, error);
	};

	static bool Take(notnull V30_Json_Deserializer deserializer, out float value, out string error) {
		return deserializer.TakeFloat(value, error);
	};

	static bool Take(notnull V30_Json_Deserializer deserializer, out string value, out string error) {
		return deserializer.TakeString(value, error);
	};

	static bool Take(notnull V30_Json_Deserializer deserializer, out Class instance, out string error);
};

class V30_Json_DeserializerHelperT<Class T> {
	static bool Take(notnull V30_Json_Deserializer deserializer, out array<T> arr, out string error) {
		if (!deserializer.BeginArray(error))
			return false;
		if (!arr)
			arr = new array<T>();
		while (!deserializer.IsArrayEnd()) {
			T value;
			if (!V30_Json_DeserializerHelper.Take(value, error))
				return false;
			arr.Insert(value);
		};
		if (!deserializer.EndArray(error))
			return false;
	};

	static bool Take(notnull V30_Json_Deserializer deserializer, out map<string, T> obj, out string error) {
		if (!deserializer.BeginObject(error))
			return false;
		if (!obj)
			obj = new map<string, T>();
		while (!deserializer.IsObjectEnd()) {
			string key;
			if (!deserializer.TakeKey(key, error))
				return false;
			T value;
			if (!V30_Json_DeserializerHelper.Take(value, error))
				return false;
			obj.Insert(key, value);
		};
		if (!deserializer.EndObject(error))
			return false;
	};
};

class V30_Json_DeserializerHelperRefT<Managed T> {
	static bool Take(notnull V30_Json_Deserializer deserializer, out array<ref T> arr, out string error) {
		if (!deserializer.BeginArray(error))
			return false;
		if (!arr)
			arr = new array<ref T>();
		while (!deserializer.IsArrayEnd()) {
			T value;
			if (!V30_Json_DeserializerHelper.Take(value, error))
				return false;
			arr.Insert(value);
		};
		if (!deserializer.EndArray(error))
			return false;
	};

	static bool Take(notnull V30_Json_Deserializer deserializer, out map<string, ref T> obj, out string error) {
		if (!deserializer.BeginObject(error))
			return false;
		if (!obj)
			obj = new map<string, ref T>();
		while (!deserializer.IsObjectEnd()) {
			string key;
			if (!deserializer.TakeKey(key, error))
				return false;
			T value;
			if (!V30_Json_DeserializerHelper.Take(value, error))
				return false;
			obj.Insert(key, value);
		};
		if (!deserializer.EndObject(error))
			return false;
	};
};
