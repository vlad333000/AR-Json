class V30_JSON_FileDeserializer: V30_JSON_Deserializer {
    protected ref FileHandle m_FileHandle;

    protected ref V30_JSON_FileHandleDeserializer m_Deserializer;

    void V30_JSON_FileDeserializer() {
        m_Deserializer = new V30_JSON_FileHandleDeserializer();
    };

    void ~V30_JSON_FileDeserializer() {
        if (IsDeserializationInProcess()) {
            EndDeserialization();
            return;
        };

        CloseFile();
    };

    bool BeginDeserialization(string filePath) {
        if (IsDeserializationInProcess())
            if (!EndDeserialization())
                return Error("failed begin deserialization, because previous deserialization not ended properly");
        CloseFile();

        m_FileHandle = FileIO.OpenFile(filePath, FileMode.READ);
        if (!m_FileHandle || !m_FileHandle.IsOpen())
            return ErrorFormat("failed to open file for reading: %1", filePath);

        if (!m_Deserializer.BeginDeserialization(m_FileHandle)) {
            CloseFile();
            return false;
        };

        return super.BeginDeserialization();
    };

    override bool EndDeserialization() {
        if (!IsDeserializationInProcess())
            return super.EndDeserialization();

        if (!m_Deserializer.EndDeserialization()) {
            CloseFile();
            super.EndDeserialization();
            return false;
        };

        CloseFile();
        return super.EndDeserialization();
    };

    FileHandle GetFileHandle() {
        return m_FileHandle;
    };

    bool IsFileOpen() {
        return m_FileHandle && m_FileHandle.IsOpen();
    };

    V30_JSON_FileHandleDeserializer GetDeserializer() {
        return m_Deserializer;
    };

    void TellPos(out int line, out int column) {
        m_Deserializer.TellPos(line, column);
    };

    int TellLine() {
        return m_Deserializer.TellLine();
    };

    int TellColumn() {
        return m_Deserializer.TellColumn();
    };

    int TellFilePos() {
        return m_Deserializer.TellFilePos();
    };

    protected void CloseFile() {
        if (m_FileHandle && m_FileHandle.IsOpen())
            m_FileHandle.Close();
        m_FileHandle = null;
    };

    bool IsEnd() {
        return m_Deserializer.IsEnd();
    };

    bool IsContainerEnd() {
        return m_Deserializer.IsContainerEnd();
    };

    bool IsArrayEnd() {
        return m_Deserializer.IsArrayEnd();
    };

    bool IsObjectEnd() {
        return m_Deserializer.IsObjectEnd();
    };

    override bool IsNull() {
        return m_Deserializer.IsNull();
    };

    override bool IsBool() {
        return m_Deserializer.IsBool();
    };

    override bool IsNumber() {
        return m_Deserializer.IsNumber();
    };

    override bool IsInt() {
        return m_Deserializer.IsInt();
    };

    override bool IsFloat() {
        return m_Deserializer.IsFloat();
    };

    override bool IsString() {
        return m_Deserializer.IsString();
    };

    override bool IsContainer() {
        return m_Deserializer.IsContainer();
    };

    override bool IsArray() {
        return m_Deserializer.IsArray();
    };

    override bool IsObject() {
        return m_Deserializer.IsObject();
    };

    override bool IsKey() {
        return m_Deserializer.IsKey();
    };

    override typename GetJsonType() {
        return m_Deserializer.GetJsonType();
    };

    override bool DeserializeNull() {
        return m_Deserializer.DeserializeNull();
    };

    override bool DeserializeBool(out bool value) {
        return m_Deserializer.DeserializeBool(value);
    };

    override bool DeserializeInt(out int value) {
        return m_Deserializer.DeserializeInt(value);
    };

    override bool DeserializeFloat(out float value) {
        return m_Deserializer.DeserializeFloat(value);
    };

    override bool DeserializeString(out string value) {
        return m_Deserializer.DeserializeString(value);
    };

    override bool DeserializeKey(out string key) {
        return m_Deserializer.DeserializeKey(key);
    };

    bool BeginArrayDeserialization() {
        return m_Deserializer.BeginArrayDeserialization();
    };

    bool EndArrayDeserialization() {
        return m_Deserializer.EndArrayDeserialization();
    };

    bool BeginObjectDeserialization() {
        return m_Deserializer.BeginObjectDeserialization();
    };

    bool EndObjectDeserialization() {
        return m_Deserializer.EndObjectDeserialization();
    };

    override bool ForEachArray(notnull V30_JSON_DeserializerArrayVisitor visitor) {
        if (!BeginArrayDeserialization())
            return false;
        if (!visitor.OnBegin(this))
            return false;
        while (!IsArrayEnd())
            if (!visitor.OnElement(this))
                return false;
        if (!EndArrayDeserialization())
            return false;
        return visitor.OnEnd(this);
    };

    override bool ForEachObject(notnull V30_JSON_DeserializerObjectVisitor visitor) {
        if (!BeginObjectDeserialization())
            return false;
        if (!visitor.OnBegin(this))
            return false;
        string key;
        while (!IsObjectEnd()) {
            if (!DeserializeKey(key))
                return false;
            if (!visitor.OnElement(this, key))
                return false;
        };
        if (!EndObjectDeserialization())
            return false;
        return visitor.OnEnd(this);
    };
};
