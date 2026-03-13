class V30_Json_FileHandleSerializer : V30_Json_BasicSerializer {
	protected ref FileHandle fileHandle;

	protected int filePos;

	void V30_Json_FileHandleSerializer(FileHandle fileHandle = null) {
		this.fileHandle = fileHandle;
		if (fileHandle)
			this.filePos = fileHandle.GetPos();
		else
			this.filePos = 0;
	};

	FileHandle GetFileHandle() {
		return this.fileHandle;
	};

    void SetFileHandle(notnull FileHandle fileHandle) {
        this.fileHandle = fileHandle;
		this.filePos = fileHandle.GetPos();
        ResetState();
    };

	void ClearFileHandle() {
		this.fileHandle = null;
		this.filePos = 0;
        ResetState();
	};

    bool IsOpen() {
        return this.fileHandle && this.fileHandle.IsOpen();
    };

    override protected void Write(string data) {
        #ifdef ENABLE_DIAG
        if (!IsOpen())
            Debug.Error(string.Format("[V30][JSON][FileHandleSerializer] Write(string): File handle is null or isn't open."));
        #endif
        this.fileHandle.Write(data);
    };

	override protected void ResetState() {
		super.ResetState();
		if (this.fileHandle)
			this.fileHandle.Seek(this.filePos);
	};
};
