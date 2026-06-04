class V30_JSON_FileHandleSerializer : V30_JSON_TextSerializer {
    protected FileHandle m_FileHandle;

    void V30_JSON_FileHandleSerializer(notnull FileHandle fileHandle) {
        SetFileHandle(fileHandle);
    };

    void SetFileHandle(FileHandle newFileHandle) {
        m_FileHandle = newFileHandle;
    };

    FileHandle GetFileHandle() {
        return m_FileHandle;
    };

    override void Write(string data) {
        m_FileHandle.Write(data);
    };
};
