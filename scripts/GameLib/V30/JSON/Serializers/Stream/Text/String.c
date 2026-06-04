class V30_JSON_StringSerializer : V30_JSON_TextSerializer {
    protected string m_Data;

    void V30_JSON_StringSerializer();

    string GetString() {
        return m_Data;
    };

    void ClearString() {
        m_Data = "";
    };

    override void Write(string data) {
        m_Data += data;
    };
};
