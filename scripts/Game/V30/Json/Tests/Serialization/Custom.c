#ifdef WORKBENCH

[V30_Json_CustomSerializerTestAttribute(), Friend(V30_Json_CustomSerializerTestAttribute)]
class V30_Json_CustomSerializerTestClass {
    protected bool b;
    protected int i;
    protected float f;
    protected string s;

    void V30_Json_CustomSerializerTestClass(bool b = false, int i = 0, float f = 0.0, string s = "") {
        this.b = b;
        this.i = i;
        this.f = f;
        this.s = s;
    };

    protected bool GetBool() {
        return b;
    };

    protected int GetInt() {
        return i;
    };

    protected float GetFloat() {
        return f;
    };

    protected string GetString() {
        return s;
    };
};

class V30_Json_CustomSerializerTestAttribute : V30_Json_SerializerAttribute {
    override void Serialize(notnull V30_Json_Serializer serializer, Class instance) {
        auto instanceReal = V30_Json_CustomSerializerTestClass.Cast(instance);
        if (!instanceReal) {
            serializer.WriteNull();
			return;
        };
        serializer.WriteObjectBegin();
            serializer.WriteString("n"); serializer.WriteColon(); serializer.WriteNull(); serializer.WriteComma();
            serializer.WriteString("b"); serializer.WriteColon(); serializer.WriteBool(instanceReal.GetBool()); serializer.WriteComma();
            serializer.WriteString("i"); serializer.WriteColon(); serializer.WriteInt(instanceReal.GetInt()); serializer.WriteComma();
            serializer.WriteString("f"); serializer.WriteColon(); serializer.WriteFloat(instanceReal.GetFloat()); serializer.WriteComma();
            serializer.WriteString("s"); serializer.WriteColon(); serializer.WriteString(instanceReal.GetString());
        serializer.WriteObjectEnd();
    };

    override void SerializeArray(notnull V30_Json_Serializer serializer, notnull Managed arr) {
        V30_Json_SerializerAttributeHelperT<V30_Json_CustomSerializerTestClass>.SerializeArray(serializer, arr, this);
    };

    override void SerializeArrayRef(notnull V30_Json_Serializer serializer, notnull Managed arr) {
        V30_Json_SerializerAttributeHelperRefT<V30_Json_CustomSerializerTestClass>.SerializeArray(serializer, arr, this);
    };

    override void SerializeObject(notnull V30_Json_Serializer serializer, notnull Managed obj) {
        V30_Json_SerializerAttributeHelperT<V30_Json_CustomSerializerTestClass>.SerializeObject(serializer, obj, this);
    };

    override void SerializeObjectRef(notnull V30_Json_Serializer serializer, notnull Managed obj) {
        V30_Json_SerializerAttributeHelperRefT<V30_Json_CustomSerializerTestClass>.SerializeObject(serializer, obj, this);
    };
};

class V30_Json_CustomSerializerTestSuite : V30_Json_TestSuite {};

[Test("V30_Json_TestSuite")]
TestResultBase V30_Json_CustomSerializer_NullTest() {
    auto instance = null;

	auto serializer = new V30_Json_StringSerializer();
    serializer.WriteClass(instance);

	return V30_Json_TestHelper.Equal(serializer, "null");
};

[Test("V30_Json_CustomSerializerTestSuite")]
TestResultBase V30_Json_CustomSerializer_TypedNullTest() {
    auto instance = null;

	auto serializer = new V30_Json_StringSerializer();
    serializer.WriteClassT(instance, V30_Json_CustomSerializerTestClass);

	return V30_Json_TestHelper.Equal(serializer, "null");
};

[Test("V30_Json_CustomSerializerTestSuite")]
TestResultBase V30_Json_CustomSerializer_InstanceTest() {
    auto instance = new V30_Json_CustomSerializerTestClass(true, 42, 3.14, "Hello, World!");

	auto serializer = new V30_Json_StringSerializer();
    serializer.WriteClass(instance);

	return V30_Json_TestHelper.Equal(serializer, "{\"n\":null,\"b\":true,\"i\":42,\"f\":3.14,\"s\":\"Hello, World!\"}");
};

[Test("V30_Json_CustomSerializerTestSuite")]
TestResultBase V30_Json_CustomSerializer_ArrayTest() {
    auto instances = new array<ref V30_Json_CustomSerializerTestClass>();
	auto expecteds = new array<string>();

    instances.Insert(new V30_Json_CustomSerializerTestClass(true, 42, 3.14, "Hello, World!"));
	expecteds.Insert("{\"n\":null,\"b\":true,\"i\":42,\"f\":3.14,\"s\":\"Hello, World!\"}");

    instances.Insert(new V30_Json_CustomSerializerTestClass(false, 69, 1.41, "Orange"));
	expecteds.Insert("{\"n\":null,\"b\":false,\"i\":69,\"f\":1.41,\"s\":\"Orange\"}");

    instances.Insert(new V30_Json_CustomSerializerTestClass(true, 141, 2.71, "Apple"));
	expecteds.Insert("{\"n\":null,\"b\":true,\"i\":141,\"f\":2.71,\"s\":\"Apple\"}");

	auto serializer = new V30_Json_StringSerializer();
    V30_Json_SerializerHelper.Write(serializer, instances);

    auto expected = V30_Json_TestHelperRefT<V30_Json_CustomSerializerTestClass>.ExpectedArrayToString(instances, expecteds);
	return V30_Json_TestHelper.Equal(serializer, expected);
};

[Test("V30_Json_CustomSerializerTestSuite")]
TestResultBase V30_Json_CustomSerializer_ObjectTest() {
    auto instances = new map<string, ref V30_Json_CustomSerializerTestClass>();
    auto expecteds = new map<string, string>();

    instances.Insert("World", new V30_Json_CustomSerializerTestClass(true, 42, 3.14, "Hello, World!"));
    expecteds.Insert("World", "{\"n\":null,\"b\":true,\"i\":42,\"f\":3.14,\"s\":\"Hello, World!\"}");

    instances.Insert("Orange", new V30_Json_CustomSerializerTestClass(false, 69, 1.41, "Orange"));
    expecteds.Insert("Orange", "{\"n\":null,\"b\":false,\"i\":69,\"f\":1.41,\"s\":\"Orange\"}");

    instances.Insert("Apple", new V30_Json_CustomSerializerTestClass(true, 141, 2.71, "Apple"));
    expecteds.Insert("Apple", "{\"n\":null,\"b\":true,\"i\":141,\"f\":2.71,\"s\":\"Apple\"}");

	auto serializer = new V30_Json_StringSerializer();
    V30_Json_SerializerHelper.Write(serializer, instances);

    auto expected = V30_Json_TestHelperRefT<V30_Json_CustomSerializerTestClass>.ExpectedObjectToString(instances, expecteds);
	return V30_Json_TestHelper.Equal(serializer, expected);
};

#endif // WORKBENCH
