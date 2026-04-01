#ifdef WORKBENCH

[BaseContainerProps(category: "Autotest/V30/JSON")]
class V30_JSON_TEST_StringSerializerSuite : V30_JSON_TEST_Suite {};

[Test("V30_JSON_TEST_StringSerializerSuite")]
class V30_JSON_TEST_StringSerialization_NullSerialization : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto serializer = new V30_Json_StringSerializer();
        serializer.SerializeNull();
        AssertEqual(serializer.GetString(), "null");
    };
};

[Test("V30_JSON_TEST_StringSerializerSuite")]
class V30_JSON_TEST_StringSerialization_TrueBoolSerialization : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto serializer = new V30_Json_StringSerializer();
        serializer.SerializeBool(true);
        AssertEqual(serializer.GetString(), "true");
    };
};

[Test("V30_JSON_TEST_StringSerializerSuite")]
class V30_JSON_TEST_StringSerialization_FalseBoolSerialization : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto serializer = new V30_Json_StringSerializer();
        serializer.SerializeBool(false);
        AssertEqual(serializer.GetString(), "false");
    };
};

[Test("V30_JSON_TEST_StringSerializerSuite")]
class V30_JSON_TEST_StringSerialization_IntSerialization : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto serializer = new V30_Json_StringSerializer();
        serializer.SerializeInt(42);
        AssertEqual(serializer.GetString(), "42");
    };
};

[Test("V30_JSON_TEST_StringSerializerSuite")]
class V30_JSON_TEST_StringSerialization_FloatSerialization : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto serializer = new V30_Json_StringSerializer();
        serializer.SerializeFloat(3.14);
        AssertEqual(serializer.GetString(), "3.14");
    };
};

[Test("V30_JSON_TEST_StringSerializerSuite")]
class V30_JSON_TEST_StringSerialization_StringSerialization : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto serializer = new V30_Json_StringSerializer();
        serializer.SerializeString("Hello, World!");
        AssertEqual(serializer.GetString(), "\"Hello, World!\"");
    };
};

[Test("V30_JSON_TEST_StringSerializerSuite")]
class V30_JSON_TEST_StringSerialization_EmptyArraySerialization : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto serializer = new V30_Json_StringSerializer();
        serializer.SerializeArrayBegin();
        serializer.SerializeArrayEnd();
        AssertEqual(serializer.GetString(), "[]");
    };
};

[Test("V30_JSON_TEST_StringSerializerSuite")]
class V30_JSON_TEST_StringSerialization_SingleNullArraySerialization : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto serializer = new V30_Json_StringSerializer();
        serializer.SerializeArrayBegin();
            serializer.SerializeNull();
        serializer.SerializeArrayEnd();
        AssertEqual(serializer.GetString(), "[null]");
    };
};

[Test("V30_JSON_TEST_StringSerializerSuite")]
class V30_JSON_TEST_StringSerialization_SingleTrueBoolArraySerialization : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto serializer = new V30_Json_StringSerializer();
        serializer.SerializeArrayBegin();
            serializer.SerializeBool(true);
        serializer.SerializeArrayEnd();
        AssertEqual(serializer.GetString(), "[true]");
    };
};

[Test("V30_JSON_TEST_StringSerializerSuite")]
class V30_JSON_TEST_StringSerialization_SingleFalseBoolArraySerialization : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto serializer = new V30_Json_StringSerializer();
        serializer.SerializeArrayBegin();
            serializer.SerializeBool(false);
        serializer.SerializeArrayEnd();
        AssertEqual(serializer.GetString(), "[false]");
    };
};

[Test("V30_JSON_TEST_StringSerializerSuite")]
class V30_JSON_TEST_StringSerialization_SingleIntArraySerialization : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto serializer = new V30_Json_StringSerializer();
        serializer.SerializeArrayBegin();
            serializer.SerializeInt(42);
        serializer.SerializeArrayEnd();
        AssertEqual(serializer.GetString(), "[42]");
    };
};

[Test("V30_JSON_TEST_StringSerializerSuite")]
class V30_JSON_TEST_StringSerialization_SingleFloatArraySerialization : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto serializer = new V30_Json_StringSerializer();
        serializer.SerializeArrayBegin();
            serializer.SerializeFloat(3.14);
        serializer.SerializeArrayEnd();
        AssertEqual(serializer.GetString(), "[3.14]");
    };
};

[Test("V30_JSON_TEST_StringSerializerSuite")]
class V30_JSON_TEST_StringSerialization_SingleStringArraySerialization : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto serializer = new V30_Json_StringSerializer();
        serializer.SerializeArrayBegin();
            serializer.SerializeString("Hello, World!");
        serializer.SerializeArrayEnd();
        AssertEqual(serializer.GetString(), "[\"Hello, World!\"]");
    };
};

[Test("V30_JSON_TEST_StringSerializerSuite")]
class V30_JSON_TEST_StringSerialization_SingleEmptyArrayArraySerialization : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto serializer = new V30_Json_StringSerializer();
        serializer.SerializeArrayBegin();
            serializer.SerializeArrayBegin();
            serializer.SerializeArrayEnd();
        serializer.SerializeArrayEnd();
        AssertEqual(serializer.GetString(), "[[]]");
    };
};

[Test("V30_JSON_TEST_StringSerializerSuite")]
class V30_JSON_TEST_StringSerialization_SingleEmptyObjectArraySerialization : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto serializer = new V30_Json_StringSerializer();
        serializer.SerializeArrayBegin();
            serializer.SerializeObjectBegin();
            serializer.SerializeObjectEnd();
        serializer.SerializeArrayEnd();
        AssertEqual(serializer.GetString(), "[{}]");
    };
};

[Test("V30_JSON_TEST_StringSerializerSuite")]
class V30_JSON_TEST_StringSerialization_MultipleNullArraySerialization : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto serializer = new V30_Json_StringSerializer();
        serializer.SerializeArrayBegin();
            serializer.SerializeNull(); serializer.SerializeComma();
            serializer.SerializeNull(); serializer.SerializeComma();
            serializer.SerializeNull();
        serializer.SerializeArrayEnd();
        AssertEqual(serializer.GetString(), "[null,null,null]");
    };
};

[Test("V30_JSON_TEST_StringSerializerSuite")]
class V30_JSON_TEST_StringSerialization_MultipleBoolArraySerialization : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto serializer = new V30_Json_StringSerializer();
        serializer.SerializeArrayBegin();
            serializer.SerializeBool(true); serializer.SerializeComma();
            serializer.SerializeBool(false); serializer.SerializeComma();
            serializer.SerializeBool(true);
        serializer.SerializeArrayEnd();
        AssertEqual(serializer.GetString(), "[true,false,true]");
    };
};

[Test("V30_JSON_TEST_StringSerializerSuite")]
class V30_JSON_TEST_StringSerialization_MultipleIntArraySerialization : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto serializer = new V30_Json_StringSerializer();
        serializer.SerializeArrayBegin();
            serializer.SerializeInt(42); serializer.SerializeComma();
            serializer.SerializeInt(69); serializer.SerializeComma();
            serializer.SerializeInt(1337);
        serializer.SerializeArrayEnd();
        AssertEqual(serializer.GetString(), "[42,69,1337]");
    };
};

[Test("V30_JSON_TEST_StringSerializerSuite")]
class V30_JSON_TEST_StringSerialization_MultipleFloatArraySerialization : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto serializer = new V30_Json_StringSerializer();
        serializer.SerializeArrayBegin();
            serializer.SerializeFloat(3.14); serializer.SerializeComma();
            serializer.SerializeFloat(1.41); serializer.SerializeComma();
            serializer.SerializeFloat(2.71);
        serializer.SerializeArrayEnd();
        AssertEqual(serializer.GetString(), "[3.14,1.41,2.71]");
    };
};

[Test("V30_JSON_TEST_StringSerializerSuite")]
class V30_JSON_TEST_StringSerialization_MultipleStringArraySerialization : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto serializer = new V30_Json_StringSerializer();
        serializer.SerializeArrayBegin();
            serializer.SerializeString("apple"); serializer.SerializeComma();
            serializer.SerializeString("orange"); serializer.SerializeComma();
            serializer.SerializeString("banana");
        serializer.SerializeArrayEnd();
        AssertEqual(serializer.GetString(), "[\"apple\",\"orange\",\"banana\"]");
    };
};

[Test("V30_JSON_TEST_StringSerializerSuite")]
class V30_JSON_TEST_StringSerialization_MultipleContainerArraySerialization : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto serializer = new V30_Json_StringSerializer();
        serializer.SerializeArrayBegin();
            serializer.SerializeArrayBegin();
            serializer.SerializeArrayEnd(); serializer.SerializeComma();
            serializer.SerializeObjectBegin();
            serializer.SerializeObjectEnd(); serializer.SerializeComma();
            serializer.SerializeArrayBegin();
            serializer.SerializeArrayEnd();
        serializer.SerializeArrayEnd();
        AssertEqual(serializer.GetString(), "[[],{},[]]");
    };
};

[Test("V30_JSON_TEST_StringSerializerSuite")]
class V30_JSON_TEST_StringSerialization_ComplexArraySerialization : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto serializer = new V30_Json_StringSerializer();
        serializer.SerializeArrayBegin();
            serializer.SerializeNull(); serializer.SerializeComma();
            serializer.SerializeBool(true); serializer.SerializeComma();
            serializer.SerializeBool(false); serializer.SerializeComma();
            serializer.SerializeInt(42); serializer.SerializeComma();
            serializer.SerializeFloat(3.14); serializer.SerializeComma();
            serializer.SerializeString("Hello, World!"); serializer.SerializeComma();
            serializer.SerializeArrayBegin();
            serializer.SerializeArrayEnd(); serializer.SerializeComma();
            serializer.SerializeObjectBegin();
            serializer.SerializeObjectEnd();
        serializer.SerializeArrayEnd();
        AssertEqual(serializer.GetString(), "[null,true,false,42,3.14,\"Hello, World!\",[],{}]");
    };
};

[Test("V30_JSON_TEST_StringSerializerSuite")]
class V30_JSON_TEST_StringSerialization_MultiDimensionalArraySerialization : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto serializer = new V30_Json_StringSerializer();
        serializer.SerializeArrayBegin();
            serializer.SerializeArrayBegin();
                serializer.SerializeArrayBegin();
                    serializer.SerializeNull();
                serializer.SerializeArrayEnd(); serializer.SerializeComma();
                serializer.SerializeArrayBegin();
                    serializer.SerializeBool(true);
                serializer.SerializeArrayEnd(); serializer.SerializeComma();
                serializer.SerializeArrayBegin();
                    serializer.SerializeBool(false);
                serializer.SerializeArrayEnd();
            serializer.SerializeArrayEnd(); serializer.SerializeComma();
            serializer.SerializeArrayBegin();
                serializer.SerializeArrayBegin();
                    serializer.SerializeInt(42);
                serializer.SerializeArrayEnd(); serializer.SerializeComma();
                serializer.SerializeArrayBegin();
                    serializer.SerializeFloat(3.14);
                serializer.SerializeArrayEnd(); serializer.SerializeComma();
                serializer.SerializeArrayBegin();
                    serializer.SerializeString("Hello, World!");
                serializer.SerializeArrayEnd();
            serializer.SerializeArrayEnd(); serializer.SerializeComma();
            serializer.SerializeArrayBegin();
                serializer.SerializeArrayBegin();
                    serializer.SerializeArrayBegin();
                    serializer.SerializeArrayEnd();
                serializer.SerializeArrayEnd(); serializer.SerializeComma();
                serializer.SerializeArrayBegin();
                    serializer.SerializeObjectBegin();
                    serializer.SerializeObjectEnd();
                serializer.SerializeArrayEnd();
            serializer.SerializeArrayEnd();
        serializer.SerializeArrayEnd();
        AssertEqual(serializer.GetString(), "[[[null],[true],[false]],[[42],[3.14],[\"Hello, World!\"]],[[[]],[{}]]]");
    };
};

[Test("V30_JSON_TEST_StringSerializerSuite")]
class V30_JSON_TEST_StringSerialization_EmptyObjectSerialization : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto serializer = new V30_Json_StringSerializer();
        serializer.SerializeObjectBegin();
        serializer.SerializeObjectEnd();
        AssertEqual(serializer.GetString(), "{}");
    };
};

[Test("V30_JSON_TEST_StringSerializerSuite")]
class V30_JSON_TEST_StringSerialization_ComplexObjectSerialization : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto serializer = new V30_Json_StringSerializer();
        serializer.SerializeObjectBegin();
            serializer.SerializeString("null"); serializer.SerializeColon(); serializer.SerializeNull(); serializer.SerializeComma();
            serializer.SerializeString("true"); serializer.SerializeColon(); serializer.SerializeBool(true); serializer.SerializeComma();
            serializer.SerializeString("false"); serializer.SerializeColon(); serializer.SerializeBool(false); serializer.SerializeComma();
            serializer.SerializeString("int"); serializer.SerializeColon(); serializer.SerializeInt(42); serializer.SerializeComma();
            serializer.SerializeString("float"); serializer.SerializeColon(); serializer.SerializeFloat(3.14); serializer.SerializeComma();
            serializer.SerializeString("string"); serializer.SerializeColon(); serializer.SerializeString("Hello, World!"); serializer.SerializeComma();
            serializer.SerializeString("array"); serializer.SerializeColon(); serializer.SerializeArrayBegin();
            serializer.SerializeArrayEnd(); serializer.SerializeComma();
            serializer.SerializeString("object"); serializer.SerializeColon(); serializer.SerializeObjectBegin();
            serializer.SerializeObjectEnd();
        serializer.SerializeObjectEnd();
        AssertEqual(serializer.GetString(), "{\"null\":null,\"true\":true,\"false\":false,\"int\":42,\"float\":3.14,\"string\":\"Hello, World!\",\"array\":[],\"object\":{}}");
    };
};

[Test("V30_JSON_TEST_StringSerializerSuite")]
class V30_JSON_TEST_StringSerialization_MultiDimensionalObjectSerialization : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto serializer = new V30_Json_StringSerializer();
        serializer.SerializeObjectBegin();
            serializer.SerializeString("a"); serializer.SerializeColon(); serializer.SerializeObjectBegin();
                serializer.SerializeString("null"); serializer.SerializeColon(); serializer.SerializeNull(); serializer.SerializeComma();
                serializer.SerializeString("true"); serializer.SerializeColon(); serializer.SerializeBool(true); serializer.SerializeComma();
                serializer.SerializeString("false"); serializer.SerializeColon(); serializer.SerializeBool(false);
            serializer.SerializeObjectEnd(); serializer.SerializeComma();
            serializer.SerializeString("b"); serializer.SerializeColon(); serializer.SerializeObjectBegin();
                serializer.SerializeString("int"); serializer.SerializeColon(); serializer.SerializeInt(42); serializer.SerializeComma();
                serializer.SerializeString("float"); serializer.SerializeColon(); serializer.SerializeFloat(3.14); serializer.SerializeComma();
                serializer.SerializeString("string"); serializer.SerializeColon(); serializer.SerializeString("Hello, World!");
            serializer.SerializeObjectEnd(); serializer.SerializeComma();
            serializer.SerializeString("c"); serializer.SerializeColon(); serializer.SerializeObjectBegin();
                serializer.SerializeString("array"); serializer.SerializeColon(); serializer.SerializeArrayBegin();
                serializer.SerializeArrayEnd(); serializer.SerializeComma();
                serializer.SerializeString("object"); serializer.SerializeColon(); serializer.SerializeObjectBegin();
                serializer.SerializeObjectEnd();
            serializer.SerializeObjectEnd();
        serializer.SerializeObjectEnd();
        AssertEqual(serializer.GetString(), "{\"a\":{\"null\":null,\"true\":true,\"false\":false},\"b\":{\"int\":42,\"float\":3.14,\"string\":\"Hello, World!\"},\"c\":{\"array\":[],\"object\":{}}}");
    };
};

#endif // WORKBENCH
