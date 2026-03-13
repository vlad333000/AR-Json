class V30_Json_SimpleStringSerializationTestSuite : SCR_AutotestSuiteBase {};

[Test("V30_Json_SimpleStringSerializationTestSuite")]
TestResultBase V30_Json_SimpleStringSerialization_NullTest() {
	auto serializer = new V30_Json_StringSerializer();
    serializer.PutNull();
    auto json = serializer.GetString();
    if (json != "null")
        return SCR_AutotestResult.AsFailure("Expected 'null', got '%1'", json);
    return SCR_AutotestResult.AsSuccess();
};

[Test("V30_Json_SimpleStringSerializationTestSuite")]
TestResultBase V30_Json_SimpleStringSerialization_TrueBoolTest() {
	auto serializer = new V30_Json_StringSerializer();
    serializer.PutBool(true);
    auto json = serializer.GetString();
    if (json != "true")
        return SCR_AutotestResult.AsFailure("Expected 'true', got '%1'", json);
    return SCR_AutotestResult.AsSuccess();
};

[Test("V30_Json_SimpleStringSerializationTestSuite")]
TestResultBase V30_Json_SimpleStringSerialization_FalseBoolTest() {
	auto serializer = new V30_Json_StringSerializer();
    serializer.PutBool(false);
    auto json = serializer.GetString();
    if (json != "false")
        return SCR_AutotestResult.AsFailure("Expected 'false', got '%1'", json);
    return SCR_AutotestResult.AsSuccess();
};

[Test("V30_Json_SimpleStringSerializationTestSuite")]
TestResultBase V30_Json_SimpleStringSerialization_IntTest() {
	auto serializer = new V30_Json_StringSerializer();
    serializer.PutInt(42);
    auto json = serializer.GetString();
    if (json != "42")
        return SCR_AutotestResult.AsFailure("Expected '42', got '%1'", json);
    return SCR_AutotestResult.AsSuccess();
};

[Test("V30_Json_SimpleStringSerializationTestSuite")]
TestResultBase V30_Json_SimpleStringSerialization_FloatTest() {
	auto serializer = new V30_Json_StringSerializer();
    serializer.PutFloat(3.14);
    auto json = serializer.GetString();
    if (json != "3.14")
        return SCR_AutotestResult.AsFailure("Expected '3.14', got '%1'", json);
    return SCR_AutotestResult.AsSuccess();
};

[Test("V30_Json_SimpleStringSerializationTestSuite")]
TestResultBase V30_Json_SimpleStringSerialization_StringTest() {
	auto serializer = new V30_Json_StringSerializer();
    serializer.PutString("Hello, World!");
    auto json = serializer.GetString();
    if (json != "\"Hello, World!\"")
        return SCR_AutotestResult.AsFailure("Expected '\"Hello, World!\"', got '%1'", json);
    return SCR_AutotestResult.AsSuccess();
};

[Test("V30_Json_SimpleStringSerializationTestSuite")]
TestResultBase V30_Json_SimpleStringSerialization_EmptyArrayTest() {
	auto serializer = new V30_Json_StringSerializer();
    serializer.BeginArray();
    serializer.EndArray();
    auto json = serializer.GetString();
    if (json != "[]")
        return SCR_AutotestResult.AsFailure("Expected '[]', got '%1'", json);
    return SCR_AutotestResult.AsSuccess();
};

[Test("V30_Json_SimpleStringSerializationTestSuite")]
TestResultBase V30_Json_SimpleStringSerialization_SingleNullArrayTest() {
	auto serializer = new V30_Json_StringSerializer();
    serializer.BeginArray();
        serializer.PutNull();
    serializer.EndArray();
    auto json = serializer.GetString();
    if (json != "[null]")
        return SCR_AutotestResult.AsFailure("Expected '[null]', got '%1'", json);
    return SCR_AutotestResult.AsSuccess();
};

[Test("V30_Json_SimpleStringSerializationTestSuite")]
TestResultBase V30_Json_SimpleStringSerialization_SingleTrueBoolArrayTest() {
	auto serializer = new V30_Json_StringSerializer();
    serializer.BeginArray();
        serializer.PutBool(true);
    serializer.EndArray();
    auto json = serializer.GetString();
    if (json != "[true]")
        return SCR_AutotestResult.AsFailure("Expected '[true]', got '%1'", json);
    return SCR_AutotestResult.AsSuccess();
};

[Test("V30_Json_SimpleStringSerializationTestSuite")]
TestResultBase V30_Json_SimpleStringSerialization_SingleFalseBoolArrayTest() {
	auto serializer = new V30_Json_StringSerializer();
    serializer.BeginArray();
        serializer.PutBool(false);
    serializer.EndArray();
    auto json = serializer.GetString();
    if (json != "[false]")
        return SCR_AutotestResult.AsFailure("Expected '[false]', got '%1'", json);
    return SCR_AutotestResult.AsSuccess();
};

[Test("V30_Json_SimpleStringSerializationTestSuite")]
TestResultBase V30_Json_SimpleStringSerialization_SingleIntArrayTest() {
	auto serializer = new V30_Json_StringSerializer();
    serializer.BeginArray();
        serializer.PutInt(42);
    serializer.EndArray();
    auto json = serializer.GetString();
    if (json != "[42]")
        return SCR_AutotestResult.AsFailure("Expected '[42]', got '%1'", json);
    return SCR_AutotestResult.AsSuccess();
};

[Test("V30_Json_SimpleStringSerializationTestSuite")]
TestResultBase V30_Json_SimpleStringSerialization_SingleFloatArrayTest() {
	auto serializer = new V30_Json_StringSerializer();
    serializer.BeginArray();
        serializer.PutFloat(3.14);
    serializer.EndArray();
    auto json = serializer.GetString();
    if (json != "[3.14]")
        return SCR_AutotestResult.AsFailure("Expected '[3.14]', got '%1'", json);
    return SCR_AutotestResult.AsSuccess();
};

[Test("V30_Json_SimpleStringSerializationTestSuite")]
TestResultBase V30_Json_SimpleStringSerialization_SingleStringArrayTest() {
	auto serializer = new V30_Json_StringSerializer();
    serializer.BeginArray();
        serializer.PutString("Hello, World!");
    serializer.EndArray();
    auto json = serializer.GetString();
    if (json != "[\"Hello, World!\"]")
        return SCR_AutotestResult.AsFailure("Expected '[\"Hello, World!\"]', got '%1'", json);
    return SCR_AutotestResult.AsSuccess();
};

[Test("V30_Json_SimpleStringSerializationTestSuite")]
TestResultBase V30_Json_SimpleStringSerialization_SingleEmptyArrayArrayTest() {
	auto serializer = new V30_Json_StringSerializer();
    serializer.BeginArray();
        serializer.BeginArray();
        serializer.EndArray();
    serializer.EndArray();
    auto json = serializer.GetString();
    if (json != "[[]]")
        return SCR_AutotestResult.AsFailure("Expected '[[]]', got '%1'", json);
    return SCR_AutotestResult.AsSuccess();
};

[Test("V30_Json_SimpleStringSerializationTestSuite")]
TestResultBase V30_Json_SimpleStringSerialization_SingleEmptyObjectArrayTest() {
	auto serializer = new V30_Json_StringSerializer();
    serializer.BeginArray();
        serializer.BeginObject();
        serializer.EndObject();
    serializer.EndArray();
    auto json = serializer.GetString();
    if (json != "[{}]")
        return SCR_AutotestResult.AsFailure("Expected '[{}]', got '%1'", json);
    return SCR_AutotestResult.AsSuccess();
};

[Test("V30_Json_SimpleStringSerializationTestSuite")]
TestResultBase V30_Json_SimpleStringSerialization_MultipleNullArrayTest() {
	auto serializer = new V30_Json_StringSerializer();
    serializer.BeginArray();
        serializer.PutNull(); serializer.PutComma();
        serializer.PutNull(); serializer.PutComma();
        serializer.PutNull();
    serializer.EndArray();
    auto json = serializer.GetString();
    if (json != "[null,null,null]")
        return SCR_AutotestResult.AsFailure("Expected '[null,null,null]', got '%1'", json);
    return SCR_AutotestResult.AsSuccess();
};

[Test("V30_Json_SimpleStringSerializationTestSuite")]
TestResultBase V30_Json_SimpleStringSerialization_MultipleBoolArrayTest() {
	auto serializer = new V30_Json_StringSerializer();
    serializer.BeginArray();
        serializer.PutBool(true); serializer.PutComma();
        serializer.PutBool(false); serializer.PutComma();
        serializer.PutBool(true);
    serializer.EndArray();
    auto json = serializer.GetString();
    if (json != "[true,false,true]")
        return SCR_AutotestResult.AsFailure("Expected '[true,false,true]', got '%1'", json);
    return SCR_AutotestResult.AsSuccess();
};

[Test("V30_Json_SimpleStringSerializationTestSuite")]
TestResultBase V30_Json_SimpleStringSerialization_MultipleIntArrayTest() {
	auto serializer = new V30_Json_StringSerializer();
    serializer.BeginArray();
        serializer.PutInt(42); serializer.PutComma();
        serializer.PutInt(69); serializer.PutComma();
        serializer.PutInt(1337);
    serializer.EndArray();
    auto json = serializer.GetString();
    if (json != "[42,69,1337]")
        return SCR_AutotestResult.AsFailure("Expected '[42,69,1337]', got '%1'", json);
    return SCR_AutotestResult.AsSuccess();
};

[Test("V30_Json_SimpleStringSerializationTestSuite")]
TestResultBase V30_Json_SimpleStringSerialization_MultipleFloatArrayTest() {
	auto serializer = new V30_Json_StringSerializer();
    serializer.BeginArray();
        serializer.PutFloat(3.14); serializer.PutComma();
        serializer.PutFloat(1.41); serializer.PutComma();
        serializer.PutFloat(2.71);
    serializer.EndArray();
    auto json = serializer.GetString();
    if (json != "[3.14,1.41,2.71]")
        return SCR_AutotestResult.AsFailure("Expected '[3.14,1.41,2.71]', got '%1'", json);
    return SCR_AutotestResult.AsSuccess();
};

[Test("V30_Json_SimpleStringSerializationTestSuite")]
TestResultBase V30_Json_SimpleStringSerialization_MultipleStringArrayTest() {
	auto serializer = new V30_Json_StringSerializer();
    serializer.BeginArray();
        serializer.PutString("apple"); serializer.PutComma();
        serializer.PutString("orange"); serializer.PutComma();
        serializer.PutString("banana");
    serializer.EndArray();
    auto json = serializer.GetString();
    if (json != "[\"apple\",\"orange\",\"banana\"]")
        return SCR_AutotestResult.AsFailure("Expected '[\"apple\",\"orange\",\"banana\"]', got '%1'", json);
    return SCR_AutotestResult.AsSuccess();
};

[Test("V30_Json_SimpleStringSerializationTestSuite")]
TestResultBase V30_Json_SimpleStringSerialization_MultipleContainerArrayTest() {
	auto serializer = new V30_Json_StringSerializer();
    serializer.BeginArray();
        serializer.BeginArray();
        serializer.EndArray(); serializer.PutComma();
        serializer.BeginObject();
        serializer.EndObject(); serializer.PutComma();
        serializer.BeginArray();
        serializer.EndArray();
    serializer.EndArray();
    auto json = serializer.GetString();
    if (json != "[[],{},[]]")
        return SCR_AutotestResult.AsFailure("Expected '[[],{},[]]', got '%1'", json);
    return SCR_AutotestResult.AsSuccess();
};

[Test("V30_Json_SimpleStringSerializationTestSuite")]
TestResultBase V30_Json_SimpleStringSerialization_ComplexArrayTest() {
	auto serializer = new V30_Json_StringSerializer();
    serializer.BeginArray();
        serializer.PutNull(); serializer.PutComma();
        serializer.PutBool(true); serializer.PutComma();
        serializer.PutBool(false); serializer.PutComma();
        serializer.PutInt(42); serializer.PutComma();
        serializer.PutFloat(3.14); serializer.PutComma();
        serializer.PutString("Hello, World!"); serializer.PutComma();
        serializer.BeginArray();
        serializer.EndArray(); serializer.PutComma();
        serializer.BeginObject();
        serializer.EndObject();
    serializer.EndArray();
    auto json = serializer.GetString();
    if (json != "[null,true,false,42,3.14,\"Hello, World!\",[],{}]")
        return SCR_AutotestResult.AsFailure("Expected '[null,true,false,42,3.14,\"Hello, World!\",[],{}]', got '%1'", json);
    return SCR_AutotestResult.AsSuccess();
};

[Test("V30_Json_SimpleStringSerializationTestSuite")]
TestResultBase V30_Json_SimpleStringSerialization_MultiDimensionalArrayTest() {
	auto serializer = new V30_Json_StringSerializer();
    serializer.BeginArray();
        serializer.BeginArray();
            serializer.BeginArray();
                serializer.PutNull();
            serializer.EndArray(); serializer.PutComma();
            serializer.BeginArray();
                serializer.PutBool(true);
            serializer.EndArray(); serializer.PutComma();
            serializer.BeginArray();
                serializer.PutBool(false);
            serializer.EndArray();
        serializer.EndArray(); serializer.PutComma();
        serializer.BeginArray();
            serializer.BeginArray();
                serializer.PutInt(42);
            serializer.EndArray(); serializer.PutComma();
            serializer.BeginArray();
                serializer.PutFloat(3.14);
            serializer.EndArray(); serializer.PutComma();
            serializer.BeginArray();
                serializer.PutString("Hello, World!");
            serializer.EndArray();
        serializer.EndArray(); serializer.PutComma();
        serializer.BeginArray();
            serializer.BeginArray();
                serializer.BeginArray();
                serializer.EndArray();
            serializer.EndArray(); serializer.PutComma();
            serializer.BeginArray();
                serializer.BeginObject();
                serializer.EndObject();
            serializer.EndArray();
        serializer.EndArray();
    serializer.EndArray();
    auto json = serializer.GetString();
    if (json != "[[[null],[true],[false]],[[42],[3.14],[\"Hello, World!\"]],[[[]],[{}]]]")
        return SCR_AutotestResult.AsFailure("Expected '[[[null],[true],[false]],[[42],[3.14],[\"Hello, World!\"]],[[[]],[{}]]]', got '%1'", json);
    return SCR_AutotestResult.AsSuccess();
};

[Test("V30_Json_SimpleStringSerializationTestSuite")]
TestResultBase V30_Json_SimpleStringSerialization_EmptyObjectTest() {
	auto serializer = new V30_Json_StringSerializer();
    serializer.BeginObject();
    serializer.EndObject();
    auto json = serializer.GetString();
    if (json != "{}")
        return SCR_AutotestResult.AsFailure("Expected '{}', got '%1'", json);
    return SCR_AutotestResult.AsSuccess();
};

[Test("V30_Json_SimpleStringSerializationTestSuite")]
TestResultBase V30_Json_SimpleStringSerialization_ComplexObjectTest() {
	auto serializer = new V30_Json_StringSerializer();
    serializer.BeginObject();
        serializer.PutKey("null"); serializer.PutNull(); serializer.PutComma();
        serializer.PutKey("true"); serializer.PutBool(true); serializer.PutComma();
        serializer.PutKey("false"); serializer.PutBool(false); serializer.PutComma();
        serializer.PutKey("int"); serializer.PutInt(42); serializer.PutComma();
        serializer.PutKey("float"); serializer.PutFloat(3.14); serializer.PutComma();
        serializer.PutKey("string"); serializer.PutString("Hello, World!"); serializer.PutComma();
        serializer.PutKey("array"); serializer.BeginArray();
        serializer.EndArray(); serializer.PutComma();
        serializer.PutKey("object"); serializer.BeginObject();
        serializer.EndObject();
    serializer.EndObject();
    auto json = serializer.GetString();
    if (json != "{\"null\":null,\"true\":true,\"false\":false,\"int\":42,\"float\":3.14,\"string\":\"Hello, World!\",\"array\":[],\"object\":{}}")
        return SCR_AutotestResult.AsFailure("Expected '{\"null\":null,\"true\":true,\"false\":false,\"int\":42,\"float\":3.14,\"string\":\"Hello, World!\",\"array\":[],\"object\":{}}', got '%1'", json);
    return SCR_AutotestResult.AsSuccess();
};

[Test("V30_Json_SimpleStringSerializationTestSuite")]
TestResultBase V30_Json_SimpleStringSerialization_MultiDimensionalObjectTest() {
	auto serializer = new V30_Json_StringSerializer();
    serializer.BeginObject();
        serializer.PutKey("a"); serializer.BeginObject();
            serializer.PutKey("null"); serializer.PutNull(); serializer.PutComma();
            serializer.PutKey("true"); serializer.PutBool(true); serializer.PutComma();
            serializer.PutKey("false"); serializer.PutBool(false);
        serializer.EndObject(); serializer.PutComma();
        serializer.PutKey("b"); serializer.BeginObject();
            serializer.PutKey("int"); serializer.PutInt(42); serializer.PutComma();
            serializer.PutKey("float"); serializer.PutFloat(3.14); serializer.PutComma();
            serializer.PutKey("string"); serializer.PutString("Hello, World!");
        serializer.EndObject(); serializer.PutComma();
        serializer.PutKey("c"); serializer.BeginObject();
            serializer.PutKey("array"); serializer.BeginArray();
            serializer.EndArray(); serializer.PutComma();
            serializer.PutKey("object"); serializer.BeginObject();
            serializer.EndObject();
        serializer.EndObject();
    serializer.EndObject();
    auto json = serializer.GetString();
    if (json != "{\"a\":{\"null\":null,\"true\":true,\"false\":false},\"b\":{\"int\":42,\"float\":3.14,\"string\":\"Hello, World!\"},\"c\":{\"array\":[],\"object\":{}}}")
        return SCR_AutotestResult.AsFailure("Expected '{\"a\":{\"null\":null,\"true\":true,\"false\":false},\"b\":{\"int\":42,\"float\":3.14,\"string\":\"Hello, World!\"},\"c\":{\"array\":[],\"object\":{}}}', got '%1'", json);
    return SCR_AutotestResult.AsSuccess();
};
