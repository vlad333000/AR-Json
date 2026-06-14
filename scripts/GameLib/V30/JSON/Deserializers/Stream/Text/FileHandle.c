class V30_JSON_FileHandleDeserializer: V30_JSON_TextDeserializer {
    protected ref FileHandle m_FileHandle;

    protected string m_Data;

    protected int m_Cursor;

    protected int m_FileStartPos;

    protected ref array<int> m_FilePosByCursor;

    void V30_JSON_FileHandleDeserializer() {
        m_Data = "";
        m_Cursor = 0;
        m_FileStartPos = 0;
        m_FilePosByCursor = new array<int>();
    };

    bool BeginDeserialization(notnull FileHandle fileHandle) {
        m_FileHandle = fileHandle;
        m_Data = "";
        m_Cursor = 0;
        m_FileStartPos = 0;
        m_FilePosByCursor.Clear();

        if (!m_FileHandle.IsOpen())
            return Error("file is not open");

        m_FileStartPos = m_FileHandle.GetPos();
        ReadData();
        m_FileHandle.Seek(m_FileStartPos);

        return BeginDeserialization();
    };

    protected void ReadData() {
        m_FilePosByCursor.Insert(m_FileStartPos);

        string line;
        while (true) {
            auto lineStartPos = m_FileHandle.GetPos();
            auto length = m_FileHandle.ReadLine(line);
            if (length < 0)
                break;

            m_Data += line;
            for (int i = 1; i <= line.Length(); i++)
                m_FilePosByCursor.Insert(lineStartPos + i);

            auto lineEndPos = m_FileHandle.GetPos();
            if (lineEndPos > lineStartPos + line.Length()) {
                m_Data += "\n";
                m_FilePosByCursor.Insert(lineEndPos);
            };
        };

        if (m_FilePosByCursor.Count() <= m_Data.Length())
            m_FilePosByCursor.Insert(m_FileHandle.GetPos());
    };

    FileHandle GetFileHandle() {
        return m_FileHandle;
    };

    override bool DeserializeKey(out string key) {
        return super.DeserializeKey(key);
    };

    int TellFilePos() {
        if (m_Cursor < m_FilePosByCursor.Count())
            return m_FilePosByCursor[m_Cursor];
        return m_FileHandle.GetPos();
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

    override protected bool ReadChar(out string char) {
        if (!PeakChar(char))
            return false;
        Next();
        return true;
    };

    override protected bool ReadCharAt(out string char, int at) {
        #ifdef ENABLE_DIAG
        if (at < 0)
            return Error("in `ReadCharAt` method `at` argument can't be lower then `0`");
        #endif
        auto advanced = Advance(at);
        if (advanced < at)
            return false;
        return ReadChar(char);
    };

    override protected bool ReadAscii(out int ascii) {
        string char;
        if (!ReadChar(char))
            return false;
        ascii = char.ToAscii();
        return true;
    };

    override protected bool ReadAsciiAt(out int ascii, int at) {
        #ifdef ENABLE_DIAG
        if (at < 0)
            return Error("in `ReadAsciiAt` method `at` argument can't be lower then `0`");
        #endif
        auto advanced = Advance(at);
        if (advanced < at)
            return false;
        return ReadAscii(ascii);
    };

    override protected int ReadString(out string outData, int count) {
        auto peaked = PeakString(outData, count);
        Advance(peaked);
        return peaked;
    };

    override protected int ReadStringFrom(out string outData, int from, int count) {
        #ifdef ENABLE_DIAG
        if (from < 0)
            return Error("in `ReadStringFrom` method `from` argument can't be lower then `0`");
        #endif
        auto advanced = Advance(from);
        if (advanced < from)
            return 0;
        return ReadString(outData, count);
    };

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
        m_FileHandle.Seek(TellFilePos());
        return true;
    };

    override protected int Advance(int count) {
        auto n = m_Data.Length();
        auto advanced = 0;
        while (advanced < count && m_Cursor < n) {
            auto char = m_Data.Get(m_Cursor);
            if (char != "\n")
                NextColumn();
            else
                NextLine();
            m_Cursor++;
            advanced++;
        };
        m_FileHandle.Seek(TellFilePos());
        return advanced;
    };
};

/*
sealed class FileHandle: Managed
{
	private void FileHandle();

	/*!
	Read raw data.
	\param data supported types: int, float, string
	\param length number of bytes to read. For int type is clamped [0,4]. For float its not used (always 4). For string it's not limited.
	\return the total number of bytes successfully read.
	proto int Read(out void data, int length);
	/*!
	Get line from file, every next call of this function returns next line.
	\return Count of characters or -1 if there is nothing to read
	proto int ReadLine(out string data);
	/*!
	Read raw data.
	\param dataArray supported types: array<int>, array<float> (array content will be overwritten)
	\param elementLength number of bytes from each array element to read (e.g. for reading array of bytes use 1, for shorts use 2, for int-s use 4). For int type its clamped [0,4] For float its not used (always 4).
	\param numElements number of array elements to read.
	\return the total number of bytes successfully read.
	proto int ReadArray(out notnull Managed dataArray, int elementLength, int numElements);
	/*!
	Write raw data.
	\param data supported types: int, float, string
	\param length number of bytes to write. For int type its clamped [0,4] For float its not used. For string its clamped [0, size of string]. If -1 value is used, the whole content of data is written.
	\return the total number of bytes successfully written.
	proto int Write(void data, int length = -1);
	/*!
	Write to file and add newline (CARRIAGE RETURN + LINE FEED).
	\param data Value to write
	proto void WriteLine(string data);
	/*!
	Write raw data.
	\param dataArray supported types: array<int>, array<float>
	\param elementLength number of bytes from each array element to write. For int type its clamped [0,4] For float its not used (always 4).
	\param numElements number of array elements to write. If -1 value is used, all elements from array are written.
	\return the total number of bytes successfully written.
	proto int WriteArray(out notnull Managed dataArray, int elementLength = 4, int numElements = -1);
	/*!
	Set current position in file.
	\param pos offset from the file beginning
	proto void Seek(int pos);
	/*!
	Get current position in file.
	\return offset from the file beginning
	proto int GetPos();
	/*!
	Get file size.
	\return file size in bytes
	proto int GetLength();
	//! Close the File.
	proto void Close();
	proto bool IsOpen();
	//! Indicate that the End-of-File has been reached
	proto bool IsEOF();
}
*/
