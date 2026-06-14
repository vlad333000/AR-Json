#ifdef WORKBENCH

[BaseContainerProps(category: "Autotest/V30/JSON")]
class V30_JSON_TEST_FileDeserializerSuite : V30_JSON_TEST_Suite {
	override ResourceName GetWorldFile() {
		return SCR_AutotestHelper.WORLD_EMPTY;
	};
};

class V30_JSON_TEST_FileDeserializerCase : V30_JSON_TEST_Case {
    protected ref V30_JSON_FileDeserializer m_Deserializer;

    protected FileHandle m_OwnedFileHandle;

    protected string m_FilePath;

    [Step(EStage.Setup)]
    void Setup() {
        m_Deserializer = new V30_JSON_FileDeserializer();
        m_FilePath = "$profile:V30_JSON_TEST_FileDeserializer.json";
    };

    [Step(EStage.Main)]
    void Execute() {
        auto data = GetData();
        if (!WriteData(data))
            return;

        if (!m_Deserializer.BeginDeserialization(m_FilePath)) {
            if (!GetResult() || !GetResult().Failure())
                SetResult(SCR_AutotestResult.AsFailure("Failed to begin deserialization for file: %1", m_FilePath));
            return;
        };
        m_OwnedFileHandle = m_Deserializer.GetFileHandle();

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
        FileIO.DeleteFile(m_FilePath);
        m_OwnedFileHandle = null;
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

    string GetData();

    bool Deserialize(notnull V30_JSON_FileDeserializer deserializer);

    bool AfterDeserialization() {
        return m_OwnedFileHandle && !m_OwnedFileHandle.IsOpen() && !m_Deserializer.IsFileOpen();
    };
};

[Test(suite: V30_JSON_TEST_FileDeserializerSuite)]
class V30_JSON_TEST_FileDeserializerSuite_Null : V30_JSON_TEST_FileDeserializerCase {
    override string GetData() {
        return "null";
    };

    override bool Deserialize(notnull V30_JSON_FileDeserializer deserializer) {
        return deserializer.DeserializeNull();
    };
};

[Test(suite: V30_JSON_TEST_FileDeserializerSuite)]
class V30_JSON_TEST_FileDeserializerSuite_Bool : V30_JSON_TEST_FileDeserializerCase {
    override string GetData() {
        return "false";
    };

    override bool Deserialize(notnull V30_JSON_FileDeserializer deserializer) {
        bool value;
        return deserializer.DeserializeBool(value) && !value;
    };
};

[Test(suite: V30_JSON_TEST_FileDeserializerSuite)]
class V30_JSON_TEST_FileDeserializerSuite_Int : V30_JSON_TEST_FileDeserializerCase {
    override string GetData() {
        return "42";
    };

    override bool Deserialize(notnull V30_JSON_FileDeserializer deserializer) {
        int value;
        return deserializer.DeserializeInt(value) && value == 42;
    };
};

[Test(suite: V30_JSON_TEST_FileDeserializerSuite)]
class V30_JSON_TEST_FileDeserializerSuite_Float : V30_JSON_TEST_FileDeserializerCase {
    override string GetData() {
        return "-1.25";
    };

    override bool Deserialize(notnull V30_JSON_FileDeserializer deserializer) {
        float value;
        return deserializer.DeserializeFloat(value) && value == -1.25;
    };
};

[Test(suite: V30_JSON_TEST_FileDeserializerSuite)]
class V30_JSON_TEST_FileDeserializerSuite_StringEscapes : V30_JSON_TEST_FileDeserializerCase {
    override string GetData() {
        return "\"hello\\nworld\"";
    };

    override bool Deserialize(notnull V30_JSON_FileDeserializer deserializer) {
        string value;
        return deserializer.DeserializeString(value) && value == "hello\nworld";
    };
};

[Test(suite: V30_JSON_TEST_FileDeserializerSuite)]
class V30_JSON_TEST_FileDeserializerSuite_ArrayManual : V30_JSON_TEST_FileDeserializerCase {
    override string GetData() {
        return "[1,2,3]";
    };

    override bool Deserialize(notnull V30_JSON_FileDeserializer deserializer) {
        if (!deserializer.BeginArrayDeserialization())
            return false;
        int value;
        if (!deserializer.DeserializeInt(value) || value != 1)
            return false;
        if (!deserializer.DeserializeInt(value) || value != 2)
            return false;
        if (!deserializer.DeserializeInt(value) || value != 3)
            return false;
        return deserializer.EndArrayDeserialization();
    };
};

[Test(suite: V30_JSON_TEST_FileDeserializerSuite)]
class V30_JSON_TEST_FileDeserializerSuite_Object : V30_JSON_TEST_FileDeserializerCase {
    override string GetData() {
        return "{\"a\":1,\"b\":true,\"c\":[2,3]}";
    };

    override bool Deserialize(notnull V30_JSON_FileDeserializer deserializer) {
        V30_JSON_Object value;
        if (!deserializer.DeserializeObject(value))
            return false;
        auto a = V30_JSON_Int.Cast(value.Get("a"));
        auto b = V30_JSON_Bool.Cast(value.Get("b"));
        auto c = V30_JSON_Array.Cast(value.Get("c"));
        return a && a.GetValue() == 1 && b && b.GetValue() && c && c.Count() == 2;
    };
};

[Test(suite: V30_JSON_TEST_FileDeserializerSuite)]
class V30_JSON_TEST_FileDeserializerSuite_Visit : V30_JSON_TEST_FileDeserializerCase {
    override string GetData() {
        return "{\"n\":null,\"s\":\"hello\",\"a\":[1,2]}";
    };

    override bool Deserialize(notnull V30_JSON_FileDeserializer deserializer) {
        V30_JSON_Value value;
        if (!deserializer.Deserialize(value))
            return false;
        auto objectValue = V30_JSON_Object.Cast(value);
        if (!objectValue || objectValue.Count() != 3)
            return false;
        auto stringValue = V30_JSON_String.Cast(objectValue.Get("s"));
        auto arrayValue = V30_JSON_Array.Cast(objectValue.Get("a"));
        return stringValue && stringValue.GetValue() == "hello" && arrayValue && arrayValue.Count() == 2;
    };
};

[Test(suite: V30_JSON_TEST_FileDeserializerSuite)]
class V30_JSON_TEST_FileDeserializerSuite_LineColumnAndFilePos : V30_JSON_TEST_FileDeserializerCase {
    override string GetData() {
        return "[\n 1,\n 2\n]";
    };

    override bool Deserialize(notnull V30_JSON_FileDeserializer deserializer) {
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
        return super.AfterDeserialization() && m_Deserializer.TellLine() == 4 && m_Deserializer.TellColumn() == 2 && m_Deserializer.TellFilePos() == GetData().Length();
    };
};

[Test(suite: V30_JSON_TEST_FileDeserializerSuite)]
class V30_JSON_TEST_FileDeserializerSuite_WriteLineInput : V30_JSON_TEST_FileDeserializerCase {
    override string GetData() {
        return "[\n 1,\n 2\n]";
    };

    override bool UseWriteLine() {
        return true;
    };

    override bool Deserialize(notnull V30_JSON_FileDeserializer deserializer) {
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
        return super.AfterDeserialization() && m_Deserializer.TellLine() == 5 && m_Deserializer.TellColumn() == 1;
    };
};

#endif
