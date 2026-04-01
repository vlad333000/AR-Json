class V30_Json_FileHandlePrettySerializer : V30_Json_BasicPrettySerializer {
	protected FileHandle fileHandle;

	void V30_Json_FileHandlePrettySerializer(int tabSpaceCount = -1, FileHandle fileHandle = null) {
		#ifdef ENABLE_DIAG
		if (!fileHandle)
            Debug.Error(string.Format("[V30][JSON][FileHandlePrettySerializer] V30_Json_FileHandlePrettySerializer(int, FileHandle): File handle is null."));
		#endif
		this.fileHandle = fileHandle;
	};

	FileHandle GetFileHandle() {
		return this.fileHandle;
	};

    void SetFileHandle(notnull FileHandle fileHandle) {
        this.fileHandle = fileHandle;
    };

    override protected void SerializeRaw(string data) {
        #ifdef ENABLE_DIAG
        if (!this.fileHandle)
            Debug.Error(string.Format("[V30][JSON][FileHandlePrettySerializer] SerializeRaw(string): File handle is null."));
        if (!this.fileHandle.IsOpen())
            Debug.Error(string.Format("[V30][JSON][FileHandlePrettySerializer] SerializeRaw(string): File handle is closed."));
        #endif
        this.fileHandle.Write(data);
    };
};
