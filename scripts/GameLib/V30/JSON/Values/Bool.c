class V30_Json_bool : V30_Json_Value {
	protected bool m_bValue;

	void V30_Json_bool(bool value = false) {
		m_bValue = value;
	};

	bool Get() {
		return m_bValue;
	};
};