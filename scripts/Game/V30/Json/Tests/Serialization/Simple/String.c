#ifdef WORKBENCH

[BaseContainerProps(category: "Autotest/V30/JSON")]
class V30_JSON_TEST_StringSerializerSuite : V30_JSON_TEST_Suite {};

[Test("V30_JSON_TEST_StringSerializerSuite")]
class V30_JSON_TEST_StringSerialization_NullSerialization : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto serializer = new V30_Json_StringSerializer();
        serializer.WriteNull();
        AssertEqual(serializer.GetString(), "null");
    };
};

[Test("V30_JSON_TEST_StringSerializerSuite")]
class V30_JSON_TEST_StringSerialization_TrueBoolSerialization : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto serializer = new V30_Json_StringSerializer();
        serializer.WriteBool(true);
        AssertEqual(serializer.GetString(), "true");
    };
};

[Test("V30_JSON_TEST_StringSerializerSuite")]
class V30_JSON_TEST_StringSerialization_FalseBoolSerialization : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto serializer = new V30_Json_StringSerializer();
        serializer.WriteBool(false);
        AssertEqual(serializer.GetString(), "false");
    };
};

[Test("V30_JSON_TEST_StringSerializerSuite")]
class V30_JSON_TEST_StringSerialization_IntSerialization : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto serializer = new V30_Json_StringSerializer();
        serializer.WriteInt(42);
        AssertEqual(serializer.GetString(), "42");
    };
};

[Test("V30_JSON_TEST_StringSerializerSuite")]
class V30_JSON_TEST_StringSerialization_FloatSerialization : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto serializer = new V30_Json_StringSerializer();
        serializer.WriteFloat(3.14);
        AssertEqual(serializer.GetString(), "3.14");
    };
};

[Test("V30_JSON_TEST_StringSerializerSuite")]
class V30_JSON_TEST_StringSerialization_StringSerialization : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto serializer = new V30_Json_StringSerializer();
        serializer.WriteString("Hello, World!");
        AssertEqual(serializer.GetString(), "\"Hello, World!\"");
    };
};

[Test("V30_JSON_TEST_StringSerializerSuite")]
class V30_JSON_TEST_StringSerialization_EmptyArraySerialization : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto serializer = new V30_Json_StringSerializer();
        serializer.WriteArrayBegin();
        serializer.WriteArrayEnd();
        AssertEqual(serializer.GetString(), "[]");
    };
};

[Test("V30_JSON_TEST_StringSerializerSuite")]
class V30_JSON_TEST_StringSerialization_SingleNullArraySerialization : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto serializer = new V30_Json_StringSerializer();
        serializer.WriteArrayBegin();
            serializer.WriteNull();
        serializer.WriteArrayEnd();
        AssertEqual(serializer.GetString(), "[null]");
    };
};

[Test("V30_JSON_TEST_StringSerializerSuite")]
class V30_JSON_TEST_StringSerialization_SingleTrueBoolArraySerialization : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto serializer = new V30_Json_StringSerializer();
        serializer.WriteArrayBegin();
            serializer.WriteBool(true);
        serializer.WriteArrayEnd();
        AssertEqual(serializer.GetString(), "[true]");
    };
};

[Test("V30_JSON_TEST_StringSerializerSuite")]
class V30_JSON_TEST_StringSerialization_SingleFalseBoolArraySerialization : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto serializer = new V30_Json_StringSerializer();
        serializer.WriteArrayBegin();
            serializer.WriteBool(false);
        serializer.WriteArrayEnd();
        AssertEqual(serializer.GetString(), "[false]");
    };
};

[Test("V30_JSON_TEST_StringSerializerSuite")]
class V30_JSON_TEST_StringSerialization_SingleIntArraySerialization : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto serializer = new V30_Json_StringSerializer();
        serializer.WriteArrayBegin();
            serializer.WriteInt(42);
        serializer.WriteArrayEnd();
        AssertEqual(serializer.GetString(), "[42]");
    };
};

[Test("V30_JSON_TEST_StringSerializerSuite")]
class V30_JSON_TEST_StringSerialization_SingleFloatArraySerialization : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto serializer = new V30_Json_StringSerializer();
        serializer.WriteArrayBegin();
            serializer.WriteFloat(3.14);
        serializer.WriteArrayEnd();
        AssertEqual(serializer.GetString(), "[3.14]");
    };
};

[Test("V30_JSON_TEST_StringSerializerSuite")]
class V30_JSON_TEST_StringSerialization_SingleStringArraySerialization : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto serializer = new V30_Json_StringSerializer();
        serializer.WriteArrayBegin();
            serializer.WriteString("Hello, World!");
        serializer.WriteArrayEnd();
        AssertEqual(serializer.GetString(), "[\"Hello, World!\"]");
    };
};

[Test("V30_JSON_TEST_StringSerializerSuite")]
class V30_JSON_TEST_StringSerialization_SingleEmptyArrayArraySerialization : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto serializer = new V30_Json_StringSerializer();
        serializer.WriteArrayBegin();
            serializer.WriteArrayBegin();
            serializer.WriteArrayEnd();
        serializer.WriteArrayEnd();
        AssertEqual(serializer.GetString(), "[[]]");
    };
};

[Test("V30_JSON_TEST_StringSerializerSuite")]
class V30_JSON_TEST_StringSerialization_SingleEmptyObjectArraySerialization : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto serializer = new V30_Json_StringSerializer();
        serializer.WriteArrayBegin();
            serializer.WriteObjectBegin();
            serializer.WriteObjectEnd();
        serializer.WriteArrayEnd();
        AssertEqual(serializer.GetString(), "[{}]");
    };
};

[Test("V30_JSON_TEST_StringSerializerSuite")]
class V30_JSON_TEST_StringSerialization_MultipleNullArraySerialization : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto serializer = new V30_Json_StringSerializer();
        serializer.WriteArrayBegin();
            serializer.WriteNull(); serializer.WriteComma();
            serializer.WriteNull(); serializer.WriteComma();
            serializer.WriteNull();
        serializer.WriteArrayEnd();
        AssertEqual(serializer.GetString(), "[null,null,null]");
    };
};

[Test("V30_JSON_TEST_StringSerializerSuite")]
class V30_JSON_TEST_StringSerialization_MultipleBoolArraySerialization : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto serializer = new V30_Json_StringSerializer();
        serializer.WriteArrayBegin();
            serializer.WriteBool(true); serializer.WriteComma();
            serializer.WriteBool(false); serializer.WriteComma();
            serializer.WriteBool(true);
        serializer.WriteArrayEnd();
        AssertEqual(serializer.GetString(), "[true,false,true]");
    };
};

[Test("V30_JSON_TEST_StringSerializerSuite")]
class V30_JSON_TEST_StringSerialization_MultipleIntArraySerialization : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto serializer = new V30_Json_StringSerializer();
        serializer.WriteArrayBegin();
            serializer.WriteInt(42); serializer.WriteComma();
            serializer.WriteInt(69); serializer.WriteComma();
            serializer.WriteInt(1337);
        serializer.WriteArrayEnd();
        AssertEqual(serializer.GetString(), "[42,69,1337]");
    };
};

[Test("V30_JSON_TEST_StringSerializerSuite")]
class V30_JSON_TEST_StringSerialization_MultipleFloatArraySerialization : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto serializer = new V30_Json_StringSerializer();
        serializer.WriteArrayBegin();
            serializer.WriteFloat(3.14); serializer.WriteComma();
            serializer.WriteFloat(1.41); serializer.WriteComma();
            serializer.WriteFloat(2.71);
        serializer.WriteArrayEnd();
        AssertEqual(serializer.GetString(), "[3.14,1.41,2.71]");
    };
};

[Test("V30_JSON_TEST_StringSerializerSuite")]
class V30_JSON_TEST_StringSerialization_MultipleStringArraySerialization : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto serializer = new V30_Json_StringSerializer();
        serializer.WriteArrayBegin();
            serializer.WriteString("apple"); serializer.WriteComma();
            serializer.WriteString("orange"); serializer.WriteComma();
            serializer.WriteString("banana");
        serializer.WriteArrayEnd();
        AssertEqual(serializer.GetString(), "[\"apple\",\"orange\",\"banana\"]");
    };
};

[Test("V30_JSON_TEST_StringSerializerSuite")]
class V30_JSON_TEST_StringSerialization_MultipleContainerArraySerialization : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto serializer = new V30_Json_StringSerializer();
        serializer.WriteArrayBegin();
            serializer.WriteArrayBegin();
            serializer.WriteArrayEnd(); serializer.WriteComma();
            serializer.WriteObjectBegin();
            serializer.WriteObjectEnd(); serializer.WriteComma();
            serializer.WriteArrayBegin();
            serializer.WriteArrayEnd();
        serializer.WriteArrayEnd();
        AssertEqual(serializer.GetString(), "[[],{},[]]");
    };
};

[Test("V30_JSON_TEST_StringSerializerSuite")]
class V30_JSON_TEST_StringSerialization_ComplexArraySerialization : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto serializer = new V30_Json_StringSerializer();
        serializer.WriteArrayBegin();
            serializer.WriteNull(); serializer.WriteComma();
            serializer.WriteBool(true); serializer.WriteComma();
            serializer.WriteBool(false); serializer.WriteComma();
            serializer.WriteInt(42); serializer.WriteComma();
            serializer.WriteFloat(3.14); serializer.WriteComma();
            serializer.WriteString("Hello, World!"); serializer.WriteComma();
            serializer.WriteArrayBegin();
            serializer.WriteArrayEnd(); serializer.WriteComma();
            serializer.WriteObjectBegin();
            serializer.WriteObjectEnd();
        serializer.WriteArrayEnd();
        AssertEqual(serializer.GetString(), "[null,true,false,42,3.14,\"Hello, World!\",[],{}]");
    };
};

[Test("V30_JSON_TEST_StringSerializerSuite")]
class V30_JSON_TEST_StringSerialization_MultiDimensionalArraySerialization : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto serializer = new V30_Json_StringSerializer();
        serializer.WriteArrayBegin();
            serializer.WriteArrayBegin();
                serializer.WriteArrayBegin();
                    serializer.WriteNull();
                serializer.WriteArrayEnd(); serializer.WriteComma();
                serializer.WriteArrayBegin();
                    serializer.WriteBool(true);
                serializer.WriteArrayEnd(); serializer.WriteComma();
                serializer.WriteArrayBegin();
                    serializer.WriteBool(false);
                serializer.WriteArrayEnd();
            serializer.WriteArrayEnd(); serializer.WriteComma();
            serializer.WriteArrayBegin();
                serializer.WriteArrayBegin();
                    serializer.WriteInt(42);
                serializer.WriteArrayEnd(); serializer.WriteComma();
                serializer.WriteArrayBegin();
                    serializer.WriteFloat(3.14);
                serializer.WriteArrayEnd(); serializer.WriteComma();
                serializer.WriteArrayBegin();
                    serializer.WriteString("Hello, World!");
                serializer.WriteArrayEnd();
            serializer.WriteArrayEnd(); serializer.WriteComma();
            serializer.WriteArrayBegin();
                serializer.WriteArrayBegin();
                    serializer.WriteArrayBegin();
                    serializer.WriteArrayEnd();
                serializer.WriteArrayEnd(); serializer.WriteComma();
                serializer.WriteArrayBegin();
                    serializer.WriteObjectBegin();
                    serializer.WriteObjectEnd();
                serializer.WriteArrayEnd();
            serializer.WriteArrayEnd();
        serializer.WriteArrayEnd();
        AssertEqual(serializer.GetString(), "[[[null],[true],[false]],[[42],[3.14],[\"Hello, World!\"]],[[[]],[{}]]]");
    };
};

[Test("V30_JSON_TEST_StringSerializerSuite")]
class V30_JSON_TEST_StringSerialization_EmptyObjectSerialization : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto serializer = new V30_Json_StringSerializer();
        serializer.WriteObjectBegin();
        serializer.WriteObjectEnd();
        AssertEqual(serializer.GetString(), "{}");
    };
};

[Test("V30_JSON_TEST_StringSerializerSuite")]
class V30_JSON_TEST_StringSerialization_ComplexObjectSerialization : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto serializer = new V30_Json_StringSerializer();
        serializer.WriteObjectBegin();
            serializer.WriteString("null"); serializer.WriteColon(); serializer.WriteNull(); serializer.WriteComma();
            serializer.WriteString("true"); serializer.WriteColon(); serializer.WriteBool(true); serializer.WriteComma();
            serializer.WriteString("false"); serializer.WriteColon(); serializer.WriteBool(false); serializer.WriteComma();
            serializer.WriteString("int"); serializer.WriteColon(); serializer.WriteInt(42); serializer.WriteComma();
            serializer.WriteString("float"); serializer.WriteColon(); serializer.WriteFloat(3.14); serializer.WriteComma();
            serializer.WriteString("string"); serializer.WriteColon(); serializer.WriteString("Hello, World!"); serializer.WriteComma();
            serializer.WriteString("array"); serializer.WriteColon(); serializer.WriteArrayBegin();
            serializer.WriteArrayEnd(); serializer.WriteComma();
            serializer.WriteString("object"); serializer.WriteColon(); serializer.WriteObjectBegin();
            serializer.WriteObjectEnd();
        serializer.WriteObjectEnd();
        AssertEqual(serializer.GetString(), "{\"null\":null,\"true\":true,\"false\":false,\"int\":42,\"float\":3.14,\"string\":\"Hello, World!\",\"array\":[],\"object\":{}}");
    };
};

[Test("V30_JSON_TEST_StringSerializerSuite")]
class V30_JSON_TEST_StringSerialization_MultiDimensionalObjectSerialization : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto serializer = new V30_Json_StringSerializer();
        serializer.WriteObjectBegin();
            serializer.WriteString("a"); serializer.WriteColon(); serializer.WriteObjectBegin();
                serializer.WriteString("null"); serializer.WriteColon(); serializer.WriteNull(); serializer.WriteComma();
                serializer.WriteString("true"); serializer.WriteColon(); serializer.WriteBool(true); serializer.WriteComma();
                serializer.WriteString("false"); serializer.WriteColon(); serializer.WriteBool(false);
            serializer.WriteObjectEnd(); serializer.WriteComma();
            serializer.WriteString("b"); serializer.WriteColon(); serializer.WriteObjectBegin();
                serializer.WriteString("int"); serializer.WriteColon(); serializer.WriteInt(42); serializer.WriteComma();
                serializer.WriteString("float"); serializer.WriteColon(); serializer.WriteFloat(3.14); serializer.WriteComma();
                serializer.WriteString("string"); serializer.WriteColon(); serializer.WriteString("Hello, World!");
            serializer.WriteObjectEnd(); serializer.WriteComma();
            serializer.WriteString("c"); serializer.WriteColon(); serializer.WriteObjectBegin();
                serializer.WriteString("array"); serializer.WriteColon(); serializer.WriteArrayBegin();
                serializer.WriteArrayEnd(); serializer.WriteComma();
                serializer.WriteString("object"); serializer.WriteColon(); serializer.WriteObjectBegin();
                serializer.WriteObjectEnd();
            serializer.WriteObjectEnd();
        serializer.WriteObjectEnd();
        AssertEqual(serializer.GetString(), "{\"a\":{\"null\":null,\"true\":true,\"false\":false},\"b\":{\"int\":42,\"float\":3.14,\"string\":\"Hello, World!\"},\"c\":{\"array\":[],\"object\":{}}}");
    };
};

#endif // WORKBENCH
