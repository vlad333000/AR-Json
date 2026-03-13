class V30_Json_String : V30_Json_Value {
	protected string m_sValue;

	void V30_Json_String(string value = "") {
		m_sValue = value;
	};

	string Get() {
		return m_sValue;
	};

	int Length() {
		return m_sValue.Length();
	};
};