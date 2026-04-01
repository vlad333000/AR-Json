class V30_Json_FileSerializer : V30_Json_BasicSerializer {
	protected ref FileHandle fileHandle;

	void V30_Json_FileSerializer(string path, FileMode mode = FileMode.WRITE) {
        OpenFile(path, mode);
	};

    void ~V30_Json_FileSerializer() {
        if (IsFileOpen())
            CloseFile();
    };

    void OpenFile(string path, FileMode mode = FileMode.WRITE) {
        if (IsFileOpen())
            CloseFile();
        this.fileHandle = FileIO.OpenFile(path, mode);
        if (!this.fileHandle)
            PrintFormat("[V30][JSON][FileSerializer] OpenFile(string, FileMode): Failed to open file \"%1\" with mode %2 (%3).", path, mode, typename.EnumToString(FileMode, mode));
    };

    bool IsFileOpen() {
        return this.fileHandle && this.fileHandle.IsOpen();
    };

    void CloseFile() {
        #ifdef ENABLE_DIAG
        if (!IsFileOpen())
            Debug.Error(string.Format("[V30][JSON][FileSerializer] CloseFile(): Trying to close closed file."));
        #endif
        this.fileHandle.Close();
    };

    override protected void SerializeRaw(string data) {
        #ifdef ENABLE_DIAG
        if (!IsFileOpen())
            Debug.Error(string.Format("[V30][JSON][FileSerializer] SerializeRaw(string): File handle is null or isn't open."));
        #endif
        this.fileHandle.Write(data);
    };

	protected FileHandle GetFileHandle() {
		return this.fileHandle;
	};
};
