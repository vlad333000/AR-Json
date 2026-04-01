class V30_Json_FileHandleSerializer : V30_Json_BasicSerializer {
	protected FileHandle fileHandle;

	void V30_Json_FileHandleSerializer(notnull FileHandle fileHandle) {
		this.fileHandle = fileHandle;
	};

	FileHandle GetFileHandle() {
		return this.fileHandle;
	};

    void SetFileHandle(notnull FileHandle fileHandle) {
        this.fileHandle = fileHandle;
    };

    override protected void Write(string data) {
        #ifdef ENABLE_DIAG
		if (!this.fileHandle)
            Debug.Error(string.Format("[V30][JSON][FileHandleSerializer] Write(string): File handle is null."));
		if (!this.fileHandle.IsOpen())
            Debug.Error(string.Format("[V30][JSON][FileHandleSerializer] Write(string): File handle is closed."));
        #endif
        this.fileHandle.Write(data);
    };
};
