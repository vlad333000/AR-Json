class V30_Json_Array : V30_Json_Value {
	protected ref array<ref V30_Json_Value> m_aValue;

	void V30_Json_Array(array<ref V30_Json_Value> value = null) {
		if (!value)
			m_aValue = new array<ref V30_Json_Value>();
		else
			m_aValue = value;
	};

	array<ref V30_Json_Value> Get() {
		return m_aValue;
	};

	V30_Json_Value GetAt(int i) {
		if (!m_aValue.IsIndexValid(i)) return new V30_Json_Null();
		return m_aValue.Get(i);
	};

	int Count() {
		return m_aValue.Count();
	};
};