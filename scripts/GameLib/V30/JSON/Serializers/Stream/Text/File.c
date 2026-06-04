class V30_JSON_FileSerializer : V30_JSON_TextSerializer {
    protected ref FileHandle fileHandle;

    protected int pos;

    void V30_JSON_FileSerializer(string path, FileMode fileMode = FileMode.WRITE) {
        OpenFile(path, fileMode);
    };

    void ~V30_JSON_FileSerializer() {
        if (IsFileOpen())
            CloseFile();
    };

    void OpenFile(string path, FileMode fileMode = FileMode.WRITE) {
        fileHandle = FileIO.OpenFile(path, fileMode);
    };

    bool IsFileOpen() {
        return fileHandle && fileHandle.IsOpen();
    };

    void CloseFile() {
        fileHandle.Close();
    };

    protected FileHandle GetFileHandle() {
        return fileHandle;
    };

    override void Write(string data) {
        fileHandle.Write(data);
    };
};
