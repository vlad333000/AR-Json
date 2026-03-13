class V30_Json_Object : V30_Json_Value {
	protected ref map<string, ref V30_Json_Value> m_mValue;

	void V30_Json_Object(map<string, ref V30_Json_Value> value = null) {
		if (!value)
			m_mValue = new map<string, ref V30_Json_Value>();
		else
			m_mValue = value;
	};

	map<string, ref V30_Json_Value> Get() {
		return m_mValue;
	};

	int Count() {
		return m_mValue.Count();
	};

	V30_Json_Value GetAt(string key) {
		V30_Json_Value value;
		if (!m_mValue.Find(key, value)) return new V30_Json_Null();
		return value;
	};

	bool ContainsAt(string key) {
		return m_mValue.Contains(key);
	};

	bool FindAt(string key, out V30_Json_Value value) {
		return m_mValue.Find(key, value);
	};
};