#ifdef WORKBENCH

[BaseContainerProps(category: "Autotest/V30/JSON")]
class V30_JSON_TEST_FileHandleSerializerSuite : V30_JSON_TEST_Suite {
	override ResourceName GetWorldFile() {
		return SCR_AutotestHelper.WORLD_EMPTY;
	};
};

class V30_JSON_TEST_FileHandleSerializerCase : V30_JSON_TEST_Case {
    protected ref V30_JSON_FileHandleSerializer m_Serializer;

    protected ref FileHandle m_FileHandle;

    protected string m_FilePath;

    [Step(EStage.Setup)]
    void Setup() {
        m_FilePath = "$profile:V30_JSON_TEST_FileHandleSerializer.json";
        FileIO.DeleteFile(m_FilePath);
    };

    [Step(EStage.Main)]
    void Execute() {
        m_FileHandle = FileIO.OpenFile(m_FilePath, FileMode.WRITE);
        if (!m_FileHandle || !m_FileHandle.IsOpen()) {
            SetResult(SCR_AutotestResult.AsFailure("Failed to open test file for serialization: %1", m_FilePath));
            return;
        };

        auto prefix = GetPrefix();
        if (prefix != "")
            m_FileHandle.Write(prefix);

        m_Serializer = new V30_JSON_FileHandleSerializer(m_FileHandle);
        Serialize(m_Serializer);

        if (!AfterSerialization()) {
            if (!GetResult() || !GetResult().Failure())
                SetResult(SCR_AutotestResult.AsFailure("Post serialization assertion failed for: %1", m_FilePath));
            return;
        };

        m_FileHandle.Close();

        string result;
        if (!ReadData(result))
            return;

        auto expect = GetExpected();
        Print("\tResult: " + result);
        Print("\tExpect: " + expect);
        if (result != expect) {
            SetResult(SCR_AutotestResult.AsFailure("Serialized file handle content isn't equal to expected"));
            return;
        };

        SetResult(SCR_AutotestResult.AsSuccess());
    };

    [Step(EStage.TearDown)]
    void TearDown() {
        if (m_FileHandle && m_FileHandle.IsOpen())
            m_FileHandle.Close();
        FileIO.DeleteFile(m_FilePath);
        m_FileHandle = null;
        m_Serializer = null;
    };

    protected bool ReadData(out string data) {
        data = "";
        auto file = FileIO.OpenFile(m_FilePath, FileMode.READ);
        if (!file || !file.IsOpen()) {
            SetResult(SCR_AutotestResult.AsFailure("Failed to open serialized file for reading: %1", m_FilePath));
            return false;
        };

        string line;
        while (file.ReadLine(line) >= 0) {
            if (data != "")
                data += "\n";
            data += line;
        };
        file.Close();
        return true;
    };

    string GetPrefix() {
        return "";
    };

    void Serialize(notnull V30_JSON_FileHandleSerializer serializer);

    string GetExpected();

    bool AfterSerialization() {
        return m_FileHandle && m_FileHandle.IsOpen() && m_FileHandle.GetPos() == GetExpected().Length();
    };
};

[Test(suite: V30_JSON_TEST_FileHandleSerializerSuite)]
class V30_JSON_TEST_FileHandleSerializerSuite_Null : V30_JSON_TEST_FileHandleSerializerCase {
    override void Serialize(notnull V30_JSON_FileHandleSerializer serializer) {
        serializer.Serialize(null);
    };

    override string GetExpected() {
        return "null";
    };
};

[Test(suite: V30_JSON_TEST_FileHandleSerializerSuite)]
class V30_JSON_TEST_FileHandleSerializerSuite_Bool : V30_JSON_TEST_FileHandleSerializerCase {
    override void Serialize(notnull V30_JSON_FileHandleSerializer serializer) {
        serializer.Serialize(false);
    };

    override string GetExpected() {
        return "false";
    };
};

[Test(suite: V30_JSON_TEST_FileHandleSerializerSuite)]
class V30_JSON_TEST_FileHandleSerializerSuite_Int : V30_JSON_TEST_FileHandleSerializerCase {
    override void Serialize(notnull V30_JSON_FileHandleSerializer serializer) {
        serializer.Serialize(42);
    };

    override string GetExpected() {
        return "42";
    };
};

[Test(suite: V30_JSON_TEST_FileHandleSerializerSuite)]
class V30_JSON_TEST_FileHandleSerializerSuite_Float : V30_JSON_TEST_FileHandleSerializerCase {
    override void Serialize(notnull V30_JSON_FileHandleSerializer serializer) {
        serializer.Serialize(-1.25);
    };

    override string GetExpected() {
        return "-1.25";
    };
};

[Test(suite: V30_JSON_TEST_FileHandleSerializerSuite)]
class V30_JSON_TEST_FileHandleSerializerSuite_StringEscapes : V30_JSON_TEST_FileHandleSerializerCase {
    override void Serialize(notnull V30_JSON_FileHandleSerializer serializer) {
        serializer.Serialize(string.Format("hello%1world", "\n"));
    };

    override string GetExpected() {
        return "\"hello\\nworld\"";
    };
};

[Test(suite: V30_JSON_TEST_FileHandleSerializerSuite)]
class V30_JSON_TEST_FileHandleSerializerSuite_ArrayManual : V30_JSON_TEST_FileHandleSerializerCase {
    override void Serialize(notnull V30_JSON_FileHandleSerializer serializer) {
        serializer.BeginArraySerialization();
            serializer.Serialize(1);
            serializer.Serialize(2);
            serializer.Serialize(3);
        serializer.EndArraySerialization();
    };

    override string GetExpected() {
        return "[1,2,3]";
    };
};

[Test(suite: V30_JSON_TEST_FileHandleSerializerSuite)]
class V30_JSON_TEST_FileHandleSerializerSuite_Object : V30_JSON_TEST_FileHandleSerializerCase {
    override void Serialize(notnull V30_JSON_FileHandleSerializer serializer) {
        serializer.BeginObjectSerialization();
            serializer.Serialize("a", 1);
            serializer.Serialize("b", true);
            serializer.BeginArraySerialization("c");
                serializer.Serialize(2);
                serializer.Serialize(3);
            serializer.EndArraySerialization();
        serializer.EndObjectSerialization();
    };

    override string GetExpected() {
        return "{\"a\":1,\"b\":true,\"c\":[2,3]}";
    };
};

[Test(suite: V30_JSON_TEST_FileHandleSerializerSuite)]
class V30_JSON_TEST_FileHandleSerializerSuite_Offset : V30_JSON_TEST_FileHandleSerializerCase {
    override string GetPrefix() {
        return "xx";
    };

    override void Serialize(notnull V30_JSON_FileHandleSerializer serializer) {
        serializer.BeginObjectSerialization();
            serializer.Serialize("a", 1);
        serializer.EndObjectSerialization();
    };

    override string GetExpected() {
        return "xx{\"a\":1}";
    };
};

[Test(suite: V30_JSON_TEST_FileHandleSerializerSuite)]
class V30_JSON_TEST_FileHandleSerializerSuite_Visit : V30_JSON_TEST_FileHandleSerializerCase {
    override void Serialize(notnull V30_JSON_FileHandleSerializer serializer) {
        auto value = new V30_JSON_Object();
        value.Insert("n", V30_JSON_Null.GetInstance());
        value.Insert("s", new V30_JSON_String("hello"));

        auto arrayValue = new V30_JSON_Array();
        arrayValue.Insert(new V30_JSON_Int(1));
        arrayValue.Insert(new V30_JSON_Int(2));
        value.Insert("a", arrayValue);

        serializer.Serialize(value);
    };

    override string GetExpected() {
        return "{\"n\":null,\"s\":\"hello\",\"a\":[1,2]}";
    };
};

#endif

