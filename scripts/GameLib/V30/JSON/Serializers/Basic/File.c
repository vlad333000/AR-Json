class V30_Json_FileSerializer : V30_Json_BasicSerializer {
	protected ref FileHandle fileHandle;

	void V30_Json_FileSerializer(string path = "", FileMode mode = FileMode.WRITE) {
		this.fileHandle = null;
        if (!path.IsEmpty())
            Open(path, mode);
	};

    void ~V30_Json_FileSerializer() {
        if (IsOpen())
            Close();
    };

	FileHandle GetFileHandle() {
		return this.fileHandle;
	};

    void Open(string path, FileMode mode = FileMode.WRITE) {
        if (IsOpen())
            Close();
        this.fileHandle = FileIO.OpenFile(path, mode);
        if (!IsOpen())
            PrintFormat("[V30][JSON][FileSerializer] Open(string, FileMode): Faield to open file \"%1\" with mode %2 (%3).", path, mode, typename.EnumToString(FileMode, mode));
    };

    bool IsOpen() {
        return this.fileHandle && this.fileHandle.IsOpen();
    };

    void Close() {
        #ifdef ENABLE_DIAG
        if (!IsOpen())
            Debug.Error("[V30][JSON][FileSerializer] Close(): File handle is null or isn't open.");
        #endif
        this.fileHandle.Close();
        this.fileHandle = null;
    };

    override protected void Write(string data) {
        #ifdef ENABLE_DIAG
        if (!IsOpen())
            Debug.Error(string.Format("[V30][JSON][FileSerializer] Write(string): File handle is null or isn't open."));
        #endif
        this.fileHandle.Write(data);
    };
};
