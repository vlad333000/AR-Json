[TestSuite()]
class V30_Json_SmartSerializationTestSuite : SCR_AutotestSuiteBase {
	static TestResultBase Test(string serialized, string expected) {
		if (serialized == expected)
			return SCR_AutotestResult.AsSuccess();
		else
			return SCR_AutotestResult.AsFailure("Expected '%1', got '%2'", expected, serialized);
	};

	static TestResultBase Test(notnull V30_Json_StringSerializer serializer, string expected) {
		return this.Test(serializer.GetString(), expected);
	};

	static TestResultBase Test(notnull V30_Json_SmartSerializer smart, string expected) {
        if (!smart.IsEnded())
			return SCR_AutotestResult.AsFailure("Serialization is not finished.");
		return this.Test(V30_Json_StringSerializer.Cast(smart.GetSerializer()), expected);
	};
};

[Test("V30_Json_SmartSerializationTestSuite")]
TestResultBase V30_Json_SmartSerialization_NullTest() {
	auto serializer = new V30_Json_StringSerializer();
    auto smart = new V30_Json_SmartSerializer(serializer);
    smart.PutNull();
	return V30_Json_SmartSerializationTestSuite.Test(smart, "null");
};

[Test("V30_Json_SmartSerializationTestSuite")]
TestResultBase V30_Json_SmartSerialization_TrueBoolTest() {
	auto serializer = new V30_Json_StringSerializer();
    auto smart = new V30_Json_SmartSerializer(serializer);
    smart.PutBool(true);
	return V30_Json_SmartSerializationTestSuite.Test(smart, "true");
};

[Test("V30_Json_SmartSerializationTestSuite")]
TestResultBase V30_Json_SmartSerialization_FalseBoolTest() {
	auto serializer = new V30_Json_StringSerializer();
    auto smart = new V30_Json_SmartSerializer(serializer);
    smart.PutBool(false);
	return V30_Json_SmartSerializationTestSuite.Test(smart, "false");
};

[Test("V30_Json_SmartSerializationTestSuite")]
TestResultBase V30_Json_SmartSerialization_IntTest() {
	auto serializer = new V30_Json_StringSerializer();
    auto smart = new V30_Json_SmartSerializer(serializer);
    smart.PutInt(42);
	return V30_Json_SmartSerializationTestSuite.Test(smart, "42");
};

[Test("V30_Json_SmartSerializationTestSuite")]
TestResultBase V30_Json_SmartSerialization_FloatTest() {
	auto serializer = new V30_Json_StringSerializer();
    auto smart = new V30_Json_SmartSerializer(serializer);
    smart.PutFloat(3.14);
	return V30_Json_SmartSerializationTestSuite.Test(smart, "3.14");
};

[Test("V30_Json_SmartSerializationTestSuite")]
TestResultBase V30_Json_SmartSerialization_StringTest() {
	auto serializer = new V30_Json_StringSerializer();
    auto smart = new V30_Json_SmartSerializer(serializer);
    smart.PutString("Hello, World!");
	return V30_Json_SmartSerializationTestSuite.Test(smart, "\"Hello, World!\"");
};

[Test("V30_Json_SmartSerializationTestSuite")]
TestResultBase V30_Json_SmartSerialization_EmptyArrayTest() {
	auto serializer = new V30_Json_StringSerializer();
    auto smart = new V30_Json_SmartSerializer(serializer);
    smart.BeginArray();
    smart.EndArray();
	return V30_Json_SmartSerializationTestSuite.Test(smart, "[]");
};

[Test("V30_Json_SmartSerializationTestSuite")]
TestResultBase V30_Json_SmartSerialization_SingleNullArrayTest() {
	auto serializer = new V30_Json_StringSerializer();
    auto smart = new V30_Json_SmartSerializer(serializer);
    smart.BeginArray();
        smart.PutNull();
    smart.EndArray();
	return V30_Json_SmartSerializationTestSuite.Test(smart, "[null]");
};

[Test("V30_Json_SmartSerializationTestSuite")]
TestResultBase V30_Json_SmartSerialization_SingleTrueBoolArrayTest() {
	auto serializer = new V30_Json_StringSerializer();
    auto smart = new V30_Json_SmartSerializer(serializer);
    smart.BeginArray();
        smart.PutBool(true);
    smart.EndArray();
	return V30_Json_SmartSerializationTestSuite.Test(smart, "[true]");
};

[Test("V30_Json_SmartSerializationTestSuite")]
TestResultBase V30_Json_SmartSerialization_SingleFalseBoolArrayTest() {
	auto serializer = new V30_Json_StringSerializer();
    auto smart = new V30_Json_SmartSerializer(serializer);
    smart.BeginArray();
        smart.PutBool(false);
    smart.EndArray();
	return V30_Json_SmartSerializationTestSuite.Test(smart, "[false]");
};

[Test("V30_Json_SmartSerializationTestSuite")]
TestResultBase V30_Json_SmartSerialization_SingleIntArrayTest() {
	auto serializer = new V30_Json_StringSerializer();
    auto smart = new V30_Json_SmartSerializer(serializer);
    smart.BeginArray();
        smart.PutInt(42);
    smart.EndArray();
	return V30_Json_SmartSerializationTestSuite.Test(smart, "[42]");
};

[Test("V30_Json_SmartSerializationTestSuite")]
TestResultBase V30_Json_SmartSerialization_SingleFloatArrayTest() {
	auto serializer = new V30_Json_StringSerializer();
    auto smart = new V30_Json_SmartSerializer(serializer);
    smart.BeginArray();
        smart.PutFloat(3.14);
    smart.EndArray();
	return V30_Json_SmartSerializationTestSuite.Test(smart, "[3.14]");
};

[Test("V30_Json_SmartSerializationTestSuite")]
TestResultBase V30_Json_SmartSerialization_SingleStringArrayTest() {
	auto serializer = new V30_Json_StringSerializer();
    auto smart = new V30_Json_SmartSerializer(serializer);
    smart.BeginArray();
        smart.PutString("Hello, World!");
    smart.EndArray();
	return V30_Json_SmartSerializationTestSuite.Test(smart, "[\"Hello, World!\"]");
};

[Test("V30_Json_SmartSerializationTestSuite")]
TestResultBase V30_Json_SmartSerialization_SingleEmptyArrayArrayTest() {
	auto serializer = new V30_Json_StringSerializer();
    auto smart = new V30_Json_SmartSerializer(serializer);
    smart.BeginArray();
        smart.BeginArray();
        smart.EndArray();
    smart.EndArray();
	return V30_Json_SmartSerializationTestSuite.Test(smart, "[[]]");
};

[Test("V30_Json_SmartSerializationTestSuite")]
TestResultBase V30_Json_SmartSerialization_SingleEmptyObjectArrayTest() {
	auto serializer = new V30_Json_StringSerializer();
    auto smart = new V30_Json_SmartSerializer(serializer);
    smart.BeginArray();
        smart.BeginObject();
        smart.EndObject();
    smart.EndArray();
	return V30_Json_SmartSerializationTestSuite.Test(smart, "[{}]");
};

[Test("V30_Json_SmartSerializationTestSuite")]
TestResultBase V30_Json_SmartSerialization_MultipleNullArrayTest() {
	auto serializer = new V30_Json_StringSerializer();
    auto smart = new V30_Json_SmartSerializer(serializer);
    smart.BeginArray();
        smart.PutNull();
        smart.PutNull();
        smart.PutNull();
    smart.EndArray();
	return V30_Json_SmartSerializationTestSuite.Test(smart, "[null,null,null]");
};

[Test("V30_Json_SmartSerializationTestSuite")]
TestResultBase V30_Json_SmartSerialization_MultipleBoolArrayTest() {
	auto serializer = new V30_Json_StringSerializer();
    auto smart = new V30_Json_SmartSerializer(serializer);
    smart.BeginArray();
        smart.PutBool(true);
        smart.PutBool(false);
        smart.PutBool(true);
    smart.EndArray();
	return V30_Json_SmartSerializationTestSuite.Test(smart, "[true,false,true]");
};

[Test("V30_Json_SmartSerializationTestSuite")]
TestResultBase V30_Json_SmartSerialization_MultipleIntArrayTest() {
	auto serializer = new V30_Json_StringSerializer();
    auto smart = new V30_Json_SmartSerializer(serializer);
    smart.BeginArray();
        smart.PutInt(42);
        smart.PutInt(69);
        smart.PutInt(1337);
    smart.EndArray();
	return V30_Json_SmartSerializationTestSuite.Test(smart, "[42,69,1337]");
};

[Test("V30_Json_SmartSerializationTestSuite")]
TestResultBase V30_Json_SmartSerialization_MultipleFloatArrayTest() {
	auto serializer = new V30_Json_StringSerializer();
    auto smart = new V30_Json_SmartSerializer(serializer);
    smart.BeginArray();
        smart.PutFloat(3.14);
        smart.PutFloat(1.41);
        smart.PutFloat(2.71);
    smart.EndArray();
	return V30_Json_SmartSerializationTestSuite.Test(smart, "[3.14,1.41,2.71]");
};

[Test("V30_Json_SmartSerializationTestSuite")]
TestResultBase V30_Json_SmartSerialization_MultipleStringArrayTest() {
	auto serializer = new V30_Json_StringSerializer();
    auto smart = new V30_Json_SmartSerializer(serializer);
    smart.BeginArray();
        smart.PutString("apple");
        smart.PutString("orange");
        smart.PutString("banana");
    smart.EndArray();
	return V30_Json_SmartSerializationTestSuite.Test(smart, "[\"apple\",\"orange\",\"banana\"]");
};

[Test("V30_Json_SmartSerializationTestSuite")]
TestResultBase V30_Json_SmartSerialization_MultipleContainerArrayTest() {
	auto serializer = new V30_Json_StringSerializer();
    auto smart = new V30_Json_SmartSerializer(serializer);
    smart.BeginArray();
        smart.BeginArray();
        smart.EndArray();
        smart.BeginObject();
        smart.EndObject();
        smart.BeginArray();
        smart.EndArray();
    smart.EndArray();
	return V30_Json_SmartSerializationTestSuite.Test(smart, "[[],{},[]]");
};

[Test("V30_Json_SmartSerializationTestSuite")]
TestResultBase V30_Json_SmartSerialization_ComplexArrayTest() {
	auto serializer = new V30_Json_StringSerializer();
    auto smart = new V30_Json_SmartSerializer(serializer);
    smart.BeginArray();
        smart.PutNull();
        smart.PutBool(true);
        smart.PutBool(false);
        smart.PutInt(42);
        smart.PutFloat(3.14);
        smart.PutString("Hello, World!");
        smart.BeginArray();
        smart.EndArray();
        smart.BeginObject();
        smart.EndObject();
    smart.EndArray();
	return V30_Json_SmartSerializationTestSuite.Test(smart, "[null,true,false,42,3.14,\"Hello, World!\",[],{}]");
};

[Test("V30_Json_SmartSerializationTestSuite")]
TestResultBase V30_Json_SmartSerialization_MultiDimensionalArrayTest() {
	auto serializer = new V30_Json_StringSerializer();
    auto smart = new V30_Json_SmartSerializer(serializer);
    smart.BeginArray();
        smart.BeginArray();
            smart.BeginArray();
                smart.PutNull();
            smart.EndArray();
            smart.BeginArray();
                smart.PutBool(true);
            smart.EndArray();
            smart.BeginArray();
                smart.PutBool(false);
            smart.EndArray();
        smart.EndArray();
        smart.BeginArray();
            smart.BeginArray();
                smart.PutInt(42);
            smart.EndArray();
            smart.BeginArray();
                smart.PutFloat(3.14);
            smart.EndArray();
            smart.BeginArray();
                smart.PutString("Hello, World!");
            smart.EndArray();
        smart.EndArray();
        smart.BeginArray();
            smart.BeginArray();
                smart.BeginArray();
                smart.EndArray();
            smart.EndArray();
            smart.BeginArray();
                smart.BeginObject();
                smart.EndObject();
            smart.EndArray();
        smart.EndArray();
    smart.EndArray();
	return V30_Json_SmartSerializationTestSuite.Test(smart, "[[[null],[true],[false]],[[42],[3.14],[\"Hello, World!\"]],[[[]],[{}]]]");
};

[Test("V30_Json_SmartSerializationTestSuite")]
TestResultBase V30_Json_SmartSerialization_EmptyObjectTest() {
	auto serializer = new V30_Json_StringSerializer();
    auto smart = new V30_Json_SmartSerializer(serializer);
    smart.BeginObject();
    smart.EndObject();
	return V30_Json_SmartSerializationTestSuite.Test(serializer, "{}");
};

[Test("V30_Json_SmartSerializationTestSuite")]
TestResultBase V30_Json_SmartSerialization_ComplexObjectTest() {
	auto serializer = new V30_Json_StringSerializer();
    auto smart = new V30_Json_SmartSerializer(serializer);
    smart.BeginObject();
        smart.PutKey("null"); smart.PutNull();
        smart.PutKey("true"); smart.PutBool(true);
        smart.PutKey("false"); smart.PutBool(false);
        smart.PutKey("int"); smart.PutInt(42);
        smart.PutKey("float"); smart.PutFloat(3.14);
        smart.PutKey("string"); smart.PutString("Hello, World!");
        smart.PutKey("array"); smart.BeginArray();
        smart.EndArray();
        smart.PutKey("object"); smart.BeginObject();
        smart.EndObject();
    smart.EndObject();
	return V30_Json_SmartSerializationTestSuite.Test(smart, "{\"null\":null,\"true\":true,\"false\":false,\"int\":42,\"float\":3.14,\"string\":\"Hello, World!\",\"array\":[],\"object\":{}}");
};

[Test("V30_Json_SmartSerializationTestSuite")]
TestResultBase V30_Json_SmartSerialization_MultiDimensionalObjectTest() {
	auto serializer = new V30_Json_StringSerializer();
    auto smart = new V30_Json_SmartSerializer(serializer);
    smart.BeginObject();
        smart.PutKey("a"); smart.BeginObject();
            smart.PutKey("null"); smart.PutNull();
            smart.PutKey("true"); smart.PutBool(true);
            smart.PutKey("false"); smart.PutBool(false);
        smart.EndObject();
        smart.PutKey("b"); smart.BeginObject();
            smart.PutKey("int"); smart.PutInt(42);
            smart.PutKey("float"); smart.PutFloat(3.14);
            smart.PutKey("string"); smart.PutString("Hello, World!");
        smart.EndObject();
        smart.PutKey("c"); smart.BeginObject();
            smart.PutKey("array"); smart.BeginArray();
            smart.EndArray();
            smart.PutKey("object"); smart.BeginObject();
            smart.EndObject();
        smart.EndObject();
    smart.EndObject();
	return V30_Json_SmartSerializationTestSuite.Test(smart, "{\"a\":{\"null\":null,\"true\":true,\"false\":false},\"b\":{\"int\":42,\"float\":3.14,\"string\":\"Hello, World!\"},\"c\":{\"array\":[],\"object\":{}}}");
};
