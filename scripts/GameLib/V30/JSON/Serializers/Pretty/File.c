class V30_Json_FilePrettySerializer : V30_Json_BasicPrettySerializer {
	protected ref FileHandle fileHandle;

	void V30_Json_FilePrettySerializer(int tabSpaceCount = -1, string path = "", FileMode mode = FileMode.WRITE) {
		this.fileHandle = null;
        if (!path.IsEmpty())
            Open(path, mode);
	};

    void ~V30_Json_FilePrettySerializer() {
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
            PrintFormat("[V30][JSON][FilePrettySerializer] Open(string, FileMode): Faield to open file \"%1\" with mode %2 (%3).", path, mode, typename.EnumToString(FileMode, mode));
    };

    bool IsOpen() {
        return this.fileHandle && this.fileHandle.IsOpen();
    };

    void Close() {
        #ifdef ENABLE_DIAG
        if (!IsOpen())
            Debug.Error("[V30][JSON][FilePrettySerializer] Close(): File handle is null or isn't open.");
        #endif
        this.fileHandle.Close();
        this.fileHandle = null;
    };

    override protected void SerializeRaw(string data) {
        #ifdef ENABLE_DIAG
        if (!IsOpen())
            Debug.Error(string.Format("[V30][JSON][FilePrettySerializer] SerializeRaw(string): File handle is null or isn't open."));
        #endif
        this.fileHandle.Write(data);
    };
};
