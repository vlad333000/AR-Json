#ifdef WORKBENCH

[BaseContainerProps(category: "Autotest/V30/JSON")]
class V30_JSON_TEST_FileSerializerSuite : V30_JSON_TEST_Suite {
	override ResourceName GetWorldFile() {
		return SCR_AutotestHelper.WORLD_EMPTY;
	};
};

class V30_JSON_TEST_FileSerializerCase : V30_JSON_TEST_Case {
    protected ref V30_JSON_FileSerializer m_Serializer;

    protected string m_FilePath;

    [Step(EStage.Setup)]
    void Setup() {
        m_FilePath = "$profile:V30_JSON_TEST_FileSerializer.json";
        FileIO.DeleteFile(m_FilePath);
    };

    [Step(EStage.Main)]
    void Execute() {
        m_Serializer = new V30_JSON_FileSerializer(m_FilePath);
        if (!m_Serializer.IsFileOpen()) {
            SetResult(SCR_AutotestResult.AsFailure("Failed to open test file for serialization: %1", m_FilePath));
            return;
        };

        Serialize(m_Serializer);
        m_Serializer.CloseFile();

        if (m_Serializer.IsFileOpen()) {
            SetResult(SCR_AutotestResult.AsFailure("Serializer-owned file handle stayed open: %1", m_FilePath));
            return;
        };

        string result;
        if (!ReadData(result))
            return;

        auto expect = GetExpected();
        Print("\tResult: " + result);
        Print("\tExpect: " + expect);
        if (result != expect) {
            SetResult(SCR_AutotestResult.AsFailure("Serialized file content isn't equal to expected"));
            return;
        };

        SetResult(SCR_AutotestResult.AsSuccess());
    };

    [Step(EStage.TearDown)]
    void TearDown() {
        if (m_Serializer && m_Serializer.IsFileOpen())
            m_Serializer.CloseFile();
        FileIO.DeleteFile(m_FilePath);
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

    void Serialize(notnull V30_JSON_FileSerializer serializer);

    string GetExpected();
};

[Test(suite: V30_JSON_TEST_FileSerializerSuite)]
class V30_JSON_TEST_FileSerializerSuite_Null : V30_JSON_TEST_FileSerializerCase {
    override void Serialize(notnull V30_JSON_FileSerializer serializer) {
        serializer.Serialize(null);
    };

    override string GetExpected() {
        return "null";
    };
};

[Test(suite: V30_JSON_TEST_FileSerializerSuite)]
class V30_JSON_TEST_FileSerializerSuite_Bool : V30_JSON_TEST_FileSerializerCase {
    override void Serialize(notnull V30_JSON_FileSerializer serializer) {
        serializer.Serialize(true);
    };

    override string GetExpected() {
        return "true";
    };
};

[Test(suite: V30_JSON_TEST_FileSerializerSuite)]
class V30_JSON_TEST_FileSerializerSuite_Int : V30_JSON_TEST_FileSerializerCase {
    override void Serialize(notnull V30_JSON_FileSerializer serializer) {
        serializer.Serialize(-42);
    };

    override string GetExpected() {
        return "-42";
    };
};

[Test(suite: V30_JSON_TEST_FileSerializerSuite)]
class V30_JSON_TEST_FileSerializerSuite_Float : V30_JSON_TEST_FileSerializerCase {
    override void Serialize(notnull V30_JSON_FileSerializer serializer) {
        serializer.Serialize(123.456);
    };

    override string GetExpected() {
        return "123.456";
    };
};

[Test(suite: V30_JSON_TEST_FileSerializerSuite)]
class V30_JSON_TEST_FileSerializerSuite_StringEscapes : V30_JSON_TEST_FileSerializerCase {
    override void Serialize(notnull V30_JSON_FileSerializer serializer) {
        serializer.Serialize(string.Format("line1%1line2%2%3%4", "\n", "\t", "\\", "\""));
    };

    override string GetExpected() {
        return string.Format("\"line1%1line2%2%3%4\"", "\\n", "\\t", "\\\\", "\\\"");
    };
};

[Test(suite: V30_JSON_TEST_FileSerializerSuite)]
class V30_JSON_TEST_FileSerializerSuite_ArrayManual : V30_JSON_TEST_FileSerializerCase {
    override void Serialize(notnull V30_JSON_FileSerializer serializer) {
        serializer.BeginArraySerialization();
            serializer.Serialize(null);
            serializer.Serialize(true);
            serializer.Serialize(42);
            serializer.Serialize(3.14);
            serializer.Serialize("hello");
        serializer.EndArraySerialization();
    };

    override string GetExpected() {
        return "[null,true,42,3.14,\"hello\"]";
    };
};

[Test(suite: V30_JSON_TEST_FileSerializerSuite)]
class V30_JSON_TEST_FileSerializerSuite_Object : V30_JSON_TEST_FileSerializerCase {
    override void Serialize(notnull V30_JSON_FileSerializer serializer) {
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

[Test(suite: V30_JSON_TEST_FileSerializerSuite)]
class V30_JSON_TEST_FileSerializerSuite_Visit : V30_JSON_TEST_FileSerializerCase {
    override void Serialize(notnull V30_JSON_FileSerializer serializer) {
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

