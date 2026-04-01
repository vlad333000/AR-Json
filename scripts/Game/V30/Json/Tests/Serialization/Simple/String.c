[TestSuite()]
class V30_Json_SimpleStringSerializationTestSuite : SCR_AutotestSuiteBase {
	static TestResultBase Test(string serialized, string expected) {
		if (serialized == expected)
			return SCR_AutotestResult.AsSuccess();
		else
			return SCR_AutotestResult.AsFailure("Expected '%1', got '%2'", expected, serialized);
	};

	static TestResultBase Test(notnull V30_Json_StringSerializer serializer, string expected) {
		return this.Test(serializer.GetString(), expected);
	};
};

[Test("V30_Json_SimpleStringSerializationTestSuite")]
TestResultBase V30_Json_SimpleStringSerialization_NullTest() {
	auto serializer = new V30_Json_StringSerializer();
    serializer.WriteNull();
	return V30_Json_SimpleStringSerializationTestSuite.Test(serializer, "null");
};

[Test("V30_Json_SimpleStringSerializationTestSuite")]
TestResultBase V30_Json_SimpleStringSerialization_TrueBoolTest() {
	auto serializer = new V30_Json_StringSerializer();
    serializer.WriteBool(true);
	return V30_Json_SimpleStringSerializationTestSuite.Test(serializer, "true");
};

[Test("V30_Json_SimpleStringSerializationTestSuite")]
TestResultBase V30_Json_SimpleStringSerialization_FalseBoolTest() {
	auto serializer = new V30_Json_StringSerializer();
    serializer.WriteBool(false);
	return V30_Json_SimpleStringSerializationTestSuite.Test(serializer, "false");
};

[Test("V30_Json_SimpleStringSerializationTestSuite")]
TestResultBase V30_Json_SimpleStringSerialization_IntTest() {
	auto serializer = new V30_Json_StringSerializer();
    serializer.WriteInt(42);
	return V30_Json_SimpleStringSerializationTestSuite.Test(serializer, "42");
};

[Test("V30_Json_SimpleStringSerializationTestSuite")]
TestResultBase V30_Json_SimpleStringSerialization_FloatTest() {
	auto serializer = new V30_Json_StringSerializer();
    serializer.WriteFloat(3.14);
	return V30_Json_SimpleStringSerializationTestSuite.Test(serializer, "3.14");
};

[Test("V30_Json_SimpleStringSerializationTestSuite")]
TestResultBase V30_Json_SimpleStringSerialization_StringTest() {
	auto serializer = new V30_Json_StringSerializer();
    serializer.WriteString("Hello, World!");
	return V30_Json_SimpleStringSerializationTestSuite.Test(serializer, "\"Hello, World!\"");
};

[Test("V30_Json_SimpleStringSerializationTestSuite")]
TestResultBase V30_Json_SimpleStringSerialization_EmptyArrayTest() {
	auto serializer = new V30_Json_StringSerializer();
    serializer.WriteArrayBegin();
    serializer.WriteArrayEnd();
	return V30_Json_SimpleStringSerializationTestSuite.Test(serializer, "[]");
};

[Test("V30_Json_SimpleStringSerializationTestSuite")]
TestResultBase V30_Json_SimpleStringSerialization_SingleNullArrayTest() {
	auto serializer = new V30_Json_StringSerializer();
    serializer.WriteArrayBegin();
        serializer.WriteNull();
    serializer.WriteArrayEnd();
	return V30_Json_SimpleStringSerializationTestSuite.Test(serializer, "[null]");
};

[Test("V30_Json_SimpleStringSerializationTestSuite")]
TestResultBase V30_Json_SimpleStringSerialization_SingleTrueBoolArrayTest() {
	auto serializer = new V30_Json_StringSerializer();
    serializer.WriteArrayBegin();
        serializer.WriteBool(true);
    serializer.WriteArrayEnd();
	return V30_Json_SimpleStringSerializationTestSuite.Test(serializer, "[true]");
};

[Test("V30_Json_SimpleStringSerializationTestSuite")]
TestResultBase V30_Json_SimpleStringSerialization_SingleFalseBoolArrayTest() {
	auto serializer = new V30_Json_StringSerializer();
    serializer.WriteArrayBegin();
        serializer.WriteBool(false);
    serializer.WriteArrayEnd();
	return V30_Json_SimpleStringSerializationTestSuite.Test(serializer, "[false]");
};

[Test("V30_Json_SimpleStringSerializationTestSuite")]
TestResultBase V30_Json_SimpleStringSerialization_SingleIntArrayTest() {
	auto serializer = new V30_Json_StringSerializer();
    serializer.WriteArrayBegin();
        serializer.WriteInt(42);
    serializer.WriteArrayEnd();
	return V30_Json_SimpleStringSerializationTestSuite.Test(serializer, "[42]");
};

[Test("V30_Json_SimpleStringSerializationTestSuite")]
TestResultBase V30_Json_SimpleStringSerialization_SingleFloatArrayTest() {
	auto serializer = new V30_Json_StringSerializer();
    serializer.WriteArrayBegin();
        serializer.WriteFloat(3.14);
    serializer.WriteArrayEnd();
	return V30_Json_SimpleStringSerializationTestSuite.Test(serializer, "[3.14]");
};

[Test("V30_Json_SimpleStringSerializationTestSuite")]
TestResultBase V30_Json_SimpleStringSerialization_SingleStringArrayTest() {
	auto serializer = new V30_Json_StringSerializer();
    serializer.WriteArrayBegin();
        serializer.WriteString("Hello, World!");
    serializer.WriteArrayEnd();
	return V30_Json_SimpleStringSerializationTestSuite.Test(serializer, "[\"Hello, World!\"]");
};

[Test("V30_Json_SimpleStringSerializationTestSuite")]
TestResultBase V30_Json_SimpleStringSerialization_SingleEmptyArrayArrayTest() {
	auto serializer = new V30_Json_StringSerializer();
    serializer.WriteArrayBegin();
        serializer.WriteArrayBegin();
        serializer.WriteArrayEnd();
    serializer.WriteArrayEnd();
	return V30_Json_SimpleStringSerializationTestSuite.Test(serializer, "[[]]");
};

[Test("V30_Json_SimpleStringSerializationTestSuite")]
TestResultBase V30_Json_SimpleStringSerialization_SingleEmptyObjectArrayTest() {
	auto serializer = new V30_Json_StringSerializer();
    serializer.WriteArrayBegin();
        serializer.WriteObjectBegin();
        serializer.WriteObjectEnd();
    serializer.WriteArrayEnd();
	return V30_Json_SimpleStringSerializationTestSuite.Test(serializer, "[{}]");
};

[Test("V30_Json_SimpleStringSerializationTestSuite")]
TestResultBase V30_Json_SimpleStringSerialization_MultipleNullArrayTest() {
	auto serializer = new V30_Json_StringSerializer();
    serializer.WriteArrayBegin();
        serializer.WriteNull(); serializer.WriteComma();
        serializer.WriteNull(); serializer.WriteComma();
        serializer.WriteNull();
    serializer.WriteArrayEnd();
	return V30_Json_SimpleStringSerializationTestSuite.Test(serializer, "[null,null,null]");
};

[Test("V30_Json_SimpleStringSerializationTestSuite")]
TestResultBase V30_Json_SimpleStringSerialization_MultipleBoolArrayTest() {
	auto serializer = new V30_Json_StringSerializer();
    serializer.WriteArrayBegin();
        serializer.WriteBool(true); serializer.WriteComma();
        serializer.WriteBool(false); serializer.WriteComma();
        serializer.WriteBool(true);
    serializer.WriteArrayEnd();
	return V30_Json_SimpleStringSerializationTestSuite.Test(serializer, "[true,false,true]");
};

[Test("V30_Json_SimpleStringSerializationTestSuite")]
TestResultBase V30_Json_SimpleStringSerialization_MultipleIntArrayTest() {
	auto serializer = new V30_Json_StringSerializer();
    serializer.WriteArrayBegin();
        serializer.WriteInt(42); serializer.WriteComma();
        serializer.WriteInt(69); serializer.WriteComma();
        serializer.WriteInt(1337);
    serializer.WriteArrayEnd();
	return V30_Json_SimpleStringSerializationTestSuite.Test(serializer, "[42,69,1337]");
};

[Test("V30_Json_SimpleStringSerializationTestSuite")]
TestResultBase V30_Json_SimpleStringSerialization_MultipleFloatArrayTest() {
	auto serializer = new V30_Json_StringSerializer();
    serializer.WriteArrayBegin();
        serializer.WriteFloat(3.14); serializer.WriteComma();
        serializer.WriteFloat(1.41); serializer.WriteComma();
        serializer.WriteFloat(2.71);
    serializer.WriteArrayEnd();
	return V30_Json_SimpleStringSerializationTestSuite.Test(serializer, "[3.14,1.41,2.71]");
};

[Test("V30_Json_SimpleStringSerializationTestSuite")]
TestResultBase V30_Json_SimpleStringSerialization_MultipleStringArrayTest() {
	auto serializer = new V30_Json_StringSerializer();
    serializer.WriteArrayBegin();
        serializer.WriteString("apple"); serializer.WriteComma();
        serializer.WriteString("orange"); serializer.WriteComma();
        serializer.WriteString("banana");
    serializer.WriteArrayEnd();
	return V30_Json_SimpleStringSerializationTestSuite.Test(serializer, "[\"apple\",\"orange\",\"banana\"]");
};

[Test("V30_Json_SimpleStringSerializationTestSuite")]
TestResultBase V30_Json_SimpleStringSerialization_MultipleContainerArrayTest() {
	auto serializer = new V30_Json_StringSerializer();
    serializer.WriteArrayBegin();
        serializer.WriteArrayBegin();
        serializer.WriteArrayEnd(); serializer.WriteComma();
        serializer.WriteObjectBegin();
        serializer.WriteObjectEnd(); serializer.WriteComma();
        serializer.WriteArrayBegin();
        serializer.WriteArrayEnd();
    serializer.WriteArrayEnd();
	return V30_Json_SimpleStringSerializationTestSuite.Test(serializer, "[[],{},[]]");
};

[Test("V30_Json_SimpleStringSerializationTestSuite")]
TestResultBase V30_Json_SimpleStringSerialization_ComplexArrayTest() {
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
	return V30_Json_SimpleStringSerializationTestSuite.Test(serializer, "[null,true,false,42,3.14,\"Hello, World!\",[],{}]");
};

[Test("V30_Json_SimpleStringSerializationTestSuite")]
TestResultBase V30_Json_SimpleStringSerialization_MultiDimensionalArrayTest() {
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
	return V30_Json_SimpleStringSerializationTestSuite.Test(serializer, "[[[null],[true],[false]],[[42],[3.14],[\"Hello, World!\"]],[[[]],[{}]]]");
};

[Test("V30_Json_SimpleStringSerializationTestSuite")]
TestResultBase V30_Json_SimpleStringSerialization_EmptyObjectTest() {
	auto serializer = new V30_Json_StringSerializer();
    serializer.WriteObjectBegin();
    serializer.WriteObjectEnd();
	return V30_Json_SimpleStringSerializationTestSuite.Test(serializer, "{}");
};

[Test("V30_Json_SimpleStringSerializationTestSuite")]
TestResultBase V30_Json_SimpleStringSerialization_ComplexObjectTest() {
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
	return V30_Json_SimpleStringSerializationTestSuite.Test(serializer, "{\"null\":null,\"true\":true,\"false\":false,\"int\":42,\"float\":3.14,\"string\":\"Hello, World!\",\"array\":[],\"object\":{}}");
};

[Test("V30_Json_SimpleStringSerializationTestSuite")]
TestResultBase V30_Json_SimpleStringSerialization_MultiDimensionalObjectTest() {
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
	return V30_Json_SimpleStringSerializationTestSuite.Test(serializer, "{\"a\":{\"null\":null,\"true\":true,\"false\":false},\"b\":{\"int\":42,\"float\":3.14,\"string\":\"Hello, World!\"},\"c\":{\"array\":[],\"object\":{}}}");
};
