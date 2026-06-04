class V30_JSON_StringDeserializer : V30_JSON_TextDeserializer {
    protected string m_Data;

    protected int m_Cursor;

    void V30_JSON_StringDeserializer() {
        m_Data = "";
        m_Cursor = 0;
    };

    override protected bool BeginDeserialization() {
        if (!super.BeginDeserialization())
            return false;
        m_Cursor = 0;
        return true;
    };

    bool BeginDeserialization(string data) {
        m_Data = data;
        return BeginDeserialization();
    };



    string GetString() {
        return m_Data;
    };

    int TellStringPos() {
        return m_Cursor;
    };

    protected int Length() {
        return m_Data.Length();
    };

    override bool IsEnd() {
        return m_Cursor == m_Data.Length();
    };

    override protected bool IsEndAt(int at) {
        auto pos = m_Cursor + at;
        auto len = m_Data.Length();
        return pos >= len;
    };

    override protected bool PeakChar(out string char) {
        if (m_Cursor == m_Data.Length())
            return false;
        char = m_Data.Get(m_Cursor);
        return true;
    };

    override protected bool PeakCharAt(out string char, int at) {
        auto i = m_Cursor + at;
        if (i >= m_Data.Length())
            return false;
        char = m_Data.Get(i);
        return true;
    };

    override protected bool PeakAscii(out int ascii) {
        if (m_Cursor == m_Data.Length())
            return false;
        ascii = m_Data.ToAscii(m_Cursor);
        return true;
    };

    override protected bool PeakAsciiAt(out int ascii, int at) {
        auto i = m_Cursor + at;
        if (i >= m_Data.Length())
            return false;
        ascii = m_Data.ToAscii(i);
        return true;
    };

    override protected int PeakString(out string outData, int count) {
        auto n = m_Data.Length();
        if (m_Cursor == n)
            return 0;
        auto c = count;
        if (m_Cursor + count > n)
            c = n - m_Cursor;
        outData = m_Data.Substring(m_Cursor, c);
        return outData.Length();
    };

    override protected int PeakStringFrom(out string outData, int from, int count) {
        auto i = from + m_Cursor;
        auto n = m_Data.Length();
        if (i >= n)
            return 0;
        auto c = count;
        if (i + count > n)
            c = n - i;
        outData = m_Data.Substring(i, c);
        return outData.Length();
    };

    // override protected bool ReadChar(out string char) {
    //     if (m_Cursor >= m_Data.Length())
    //         return false;
    //     char = m_Data.Get(m_Cursor);
    //     m_Cursor++;
    //     return true;
    // };

    // override protected bool ReadCharAt(out string char, int at) {
    //     m_Cursor += at;
    //     auto n = m_Data.Length();
    //     if (m_Cursor >= n) {
    //         m_Cursor = n;
    //         return false;
    //     };
    //     char = m_Data.Get(m_Cursor);
    //     m_Cursor++;
    //     return true;
    // };

    // override protected bool ReadAscii(out int ascii) {
    //     if (m_Cursor >= m_Data.Length())
    //         return false;
    //     ascii = m_Data.ToAscii(m_Cursor);
    //     m_Cursor++;
    //     return true;
    // };

    // override protected bool ReadAsciiAt(out int ascii, int at) {
    //     m_Cursor += at;
    //     auto n = m_Data.Length();
    //     if (m_Cursor >= n) {
    //         m_Cursor = n;
    //         return false;
    //     };
    //     ascii = m_Data.ToAscii(m_Cursor);
    //     m_Cursor++;
    //     return true;
    // };

    // override protected bool ReadString(out string outData, int count) {
    //     auto n = m_Data.Length();
    //     if (m_Cursor == n)
    //         return false;
    //     if (m_Cursor + count > n)
    //         count = n - m_Cursor;
    //     outData = m_Data.Substring(m_Cursor, count);
    //     m_Cursor += outData.Length();
    //     return true;
    // };

    // override protected bool ReadStringFrom(out string outData, int from, int count) {
    //     from += m_Cursor;
    //     auto n = m_Data.Length();
    //     if (from >= n)
    //         return false;
    //     if (from + count > n)
    //         count = n - from;
    //     outData = m_Data.Substring(from, count);
    //     m_Cursor += from + outData.Length();
    //     return true;
    // };

    override bool Next() {
        auto n = m_Data.Length();
        if (m_Cursor == n)
            return false;
        auto char = m_Data.Get(m_Cursor);
        if (char != "\n")
            NextColumn();
        else
            NextLine();
        m_Cursor++;
        return true;
    };

    // override int Advance(int count) {
    //     auto n = m_Data.Length();
    //     if (m_Cursor + count > n) {
    //         m_Cursor = n;
    //         count = n - m_Cursor;
    //     }
    //     else
    //         m_Cursor += count;
    //     return count;
    // };
};
