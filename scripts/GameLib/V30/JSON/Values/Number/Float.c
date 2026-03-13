class V30_Json_Float : V30_Json_Number {
	protected float m_fValue;

	void V30_Json_Float(float value = 0.0) {
		m_fValue = value;
	};

	float Get() {
		return m_fValue;
	};
};