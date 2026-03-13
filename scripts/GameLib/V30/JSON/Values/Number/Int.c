class V30_Json_Int : V30_Json_Number {
	protected int m_iValue;

	void V30_Json_Int(int value = 0) {
		m_iValue = value;
	};

	int Get() {
		return m_iValue;
	};
};