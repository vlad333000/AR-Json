#ifdef WORKBENCH

[BaseContainerProps(category: "Autotest/V30/JSON")]
class V30_JSON_TEST_FileHandleDeserializerSuite : V30_JSON_TEST_Suite {
	override ResourceName GetWorldFile() {
		return SCR_AutotestHelper.WORLD_EMPTY;
	};
};

class V30_JSON_TEST_FileHandleDeserializerCase : V30_JSON_TEST_Case {
    protected ref V30_JSON_FileHandleDeserializer m_Deserializer;

    protected ref FileHandle m_FileHandle;

    protected string m_FilePath;

    [Step(EStage.Setup)]
    void Setup() {
        m_Deserializer = new V30_JSON_FileHandleDeserializer();
        m_FilePath = "$profile:V30_JSON_TEST_FileHandleDeserializer.json";
    };

    [Step(EStage.Main)]
    void Execute() {
        auto data = GetData();
        if (!WriteData(data))
            return;

        m_FileHandle = FileIO.OpenFile(m_FilePath, FileMode.READ);
        if (!m_FileHandle || !m_FileHandle.IsOpen()) {
            SetResult(SCR_AutotestResult.AsFailure("Failed to open test file for reading: %1", m_FilePath));
            return;
        };

        auto seek = GetFileSeek();
        if (seek > 0)
            m_FileHandle.Seek(seek);

        if (!m_Deserializer.BeginDeserialization(m_FileHandle)) {
            if (!GetResult() || !GetResult().Failure())
                SetResult(SCR_AutotestResult.AsFailure("Failed to begin deserialization for: \"%1\"", data));
            return;
        };
        if (!Deserialize(m_Deserializer)) {
            if (!GetResult() || !GetResult().Failure())
                SetResult(SCR_AutotestResult.AsFailure("Failed to deserialize: \"%1\"", data));
            return;
        };
        if (!m_Deserializer.EndDeserialization()) {
            if (!GetResult() || !GetResult().Failure())
                SetResult(SCR_AutotestResult.AsFailure("Failed to end deserialization for: \"%1\"", data));
            return;
        };
        if (!AfterDeserialization()) {
            if (!GetResult() || !GetResult().Failure())
                SetResult(SCR_AutotestResult.AsFailure("Post deserialization assertion failed for: \"%1\"", data));
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
        m_Deserializer = null;
    };

    protected bool WriteData(string data) {
        auto file = FileIO.OpenFile(m_FilePath, FileMode.WRITE);
        if (!file || !file.IsOpen()) {
            SetResult(SCR_AutotestResult.AsFailure("Failed to open test file for writing: %1", m_FilePath));
            return false;
        };
        if (UseWriteLine()) {
            array<string> lines = {};
            data.Split("\n", lines, false);
            foreach (auto line : lines)
                file.WriteLine(line);
        }
        else {
            file.Write(data);
        };
        file.Close();
        return true;
    };

    bool UseWriteLine() {
        return false;
    };

    int GetFileSeek() {
        return 0;
    };

    string GetData();

    bool Deserialize(notnull V30_JSON_FileHandleDeserializer deserializer);

    bool AfterDeserialization() {
        return m_FileHandle && m_FileHandle.IsOpen();
    };
};

[Test(suite: V30_JSON_TEST_FileHandleDeserializerSuite)]
class V30_JSON_TEST_FileHandleDeserializerSuite_Null : V30_JSON_TEST_FileHandleDeserializerCase {
    override string GetData() {
        return "null";
    };

    override bool Deserialize(notnull V30_JSON_FileHandleDeserializer deserializer) {
        return deserializer.DeserializeNull();
    };
};

[Test(suite: V30_JSON_TEST_FileHandleDeserializerSuite)]
class V30_JSON_TEST_FileHandleDeserializerSuite_Bool : V30_JSON_TEST_FileHandleDeserializerCase {
    override string GetData() {
        return "true";
    };

    override bool Deserialize(notnull V30_JSON_FileHandleDeserializer deserializer) {
        bool value;
        return deserializer.DeserializeBool(value) && value;
    };
};

[Test(suite: V30_JSON_TEST_FileHandleDeserializerSuite)]
class V30_JSON_TEST_FileHandleDeserializerSuite_Int : V30_JSON_TEST_FileHandleDeserializerCase {
    override string GetData() {
        return "-42";
    };

    override bool Deserialize(notnull V30_JSON_FileHandleDeserializer deserializer) {
        int value;
        return deserializer.DeserializeInt(value) && value == -42;
    };
};

[Test(suite: V30_JSON_TEST_FileHandleDeserializerSuite)]
class V30_JSON_TEST_FileHandleDeserializerSuite_Float : V30_JSON_TEST_FileHandleDeserializerCase {
    override string GetData() {
        return "123.456";
    };

    override bool Deserialize(notnull V30_JSON_FileHandleDeserializer deserializer) {
        float value;
        return deserializer.DeserializeFloat(value) && value == 123.456;
    };
};

[Test(suite: V30_JSON_TEST_FileHandleDeserializerSuite)]
class V30_JSON_TEST_FileHandleDeserializerSuite_StringEscapes : V30_JSON_TEST_FileHandleDeserializerCase {
    override string GetData() {
        return "\"line1\\nline2\\t\\\\\\\"\"";
    };

    override bool Deserialize(notnull V30_JSON_FileHandleDeserializer deserializer) {
        string value;
        return deserializer.DeserializeString(value) && value == "line1\nline2\t\\\"";
    };
};

[Test(suite: V30_JSON_TEST_FileHandleDeserializerSuite)]
class V30_JSON_TEST_FileHandleDeserializerSuite_ArrayManual : V30_JSON_TEST_FileHandleDeserializerCase {
    override string GetData() {
        return "[null,true,42,3.14,\"hello\"]";
    };

    override bool Deserialize(notnull V30_JSON_FileHandleDeserializer deserializer) {
        if (!deserializer.BeginArrayDeserialization())
            return false;
        if (!deserializer.DeserializeNull())
            return false;
        bool boolValue;
        if (!deserializer.DeserializeBool(boolValue) || !boolValue)
            return false;
        int intValue;
        if (!deserializer.DeserializeInt(intValue) || intValue != 42)
            return false;
        float floatValue;
        if (!deserializer.DeserializeFloat(floatValue) || floatValue != 3.14)
            return false;
        string stringValue;
        if (!deserializer.DeserializeString(stringValue) || stringValue != "hello")
            return false;
        return deserializer.EndArrayDeserialization();
    };
};

[Test(suite: V30_JSON_TEST_FileHandleDeserializerSuite)]
class V30_JSON_TEST_FileHandleDeserializerSuite_Object : V30_JSON_TEST_FileHandleDeserializerCase {
    override string GetData() {
        return "{\"a\":1,\"b\":true,\"c\":[2,3]}";
    };

    override bool Deserialize(notnull V30_JSON_FileHandleDeserializer deserializer) {
        V30_JSON_Object value;
        if (!deserializer.DeserializeObject(value))
            return false;
        auto a = V30_JSON_Int.Cast(value.Get("a"));
        auto b = V30_JSON_Bool.Cast(value.Get("b"));
        auto c = V30_JSON_Array.Cast(value.Get("c"));
        return a && a.GetValue() == 1 && b && b.GetValue() && c && c.Count() == 2;
    };
};

[Test(suite: V30_JSON_TEST_FileHandleDeserializerSuite)]
class V30_JSON_TEST_FileHandleDeserializerSuite_Offset : V30_JSON_TEST_FileHandleDeserializerCase {
    override string GetData() {
        return "xx{\"a\":1}";
    };

    override int GetFileSeek() {
        return 2;
    };

    override bool Deserialize(notnull V30_JSON_FileHandleDeserializer deserializer) {
        V30_JSON_Object value;
        if (!deserializer.DeserializeObject(value))
            return false;
        auto a = V30_JSON_Int.Cast(value.Get("a"));
        return a && a.GetValue() == 1;
    };

    override bool AfterDeserialization() {
        return m_FileHandle && m_FileHandle.IsOpen() && m_FileHandle.GetPos() == GetData().Length();
    };
};

[Test(suite: V30_JSON_TEST_FileHandleDeserializerSuite)]
class V30_JSON_TEST_FileHandleDeserializerSuite_LineColumnAndFilePos : V30_JSON_TEST_FileHandleDeserializerCase {
    override string GetData() {
        return "[\n 1,\n 2\n]";
    };

    override bool Deserialize(notnull V30_JSON_FileHandleDeserializer deserializer) {
        if (!deserializer.BeginArrayDeserialization())
            return false;
        int value;
        if (!deserializer.DeserializeInt(value) || value != 1)
            return false;
        if (!deserializer.DeserializeInt(value) || value != 2)
            return false;
        return deserializer.EndArrayDeserialization();
    };

    override bool AfterDeserialization() {
        return m_FileHandle && m_FileHandle.IsOpen() && m_Deserializer.TellLine() == 4 && m_Deserializer.TellColumn() == 2 && m_Deserializer.TellFilePos() == GetData().Length();
    };
};

[Test(suite: V30_JSON_TEST_FileHandleDeserializerSuite)]
class V30_JSON_TEST_FileHandleDeserializerSuite_WriteLineInput : V30_JSON_TEST_FileHandleDeserializerCase {
    override string GetData() {
        return "[\n 1,\n 2\n]";
    };

    override bool UseWriteLine() {
        return true;
    };

    override bool Deserialize(notnull V30_JSON_FileHandleDeserializer deserializer) {
        if (!deserializer.BeginArrayDeserialization())
            return false;
        int value;
        if (!deserializer.DeserializeInt(value) || value != 1)
            return false;
        if (!deserializer.DeserializeInt(value) || value != 2)
            return false;
        return deserializer.EndArrayDeserialization();
    };

    override bool AfterDeserialization() {
        return m_FileHandle && m_FileHandle.IsOpen() && m_Deserializer.TellLine() == 5 && m_Deserializer.TellColumn() == 1 && m_FileHandle.GetPos() == m_FileHandle.GetLength();
    };
};

#endif
