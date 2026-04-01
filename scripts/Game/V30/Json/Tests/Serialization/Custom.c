#ifdef WORKBENCH

[V30_JSON_TEST_CustomSerializer_Attribute(), Friend(V30_JSON_TEST_CustomSerializer_Attribute)]
class V30_JSON_TEST_CustomSerializer_Class {
    protected bool b;
    protected int i;
    protected float f;
    protected string s;

    void V30_JSON_TEST_CustomSerializer_Class(bool b = false, int i = 0, float f = 0.0, string s = "") {
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

class V30_JSON_TEST_CustomSerializer_Attribute : V30_Json_SerializerAttribute {
    override void SerializeClass(notnull V30_Json_Serializer serializer, Class instance) {
        auto instanceReal = V30_JSON_TEST_CustomSerializer_Class.Cast(instance);
        if (!instanceReal) {
            serializer.SerializeNull();
			return;
        };
        serializer.SerializeObjectBegin();
            serializer.SerializeString("n"); serializer.SerializeColon(); serializer.SerializeNull(); serializer.SerializeComma();
            serializer.SerializeString("b"); serializer.SerializeColon(); serializer.SerializeBool(instanceReal.GetBool()); serializer.SerializeComma();
            serializer.SerializeString("i"); serializer.SerializeColon(); serializer.SerializeInt(instanceReal.GetInt()); serializer.SerializeComma();
            serializer.SerializeString("f"); serializer.SerializeColon(); serializer.SerializeFloat(instanceReal.GetFloat()); serializer.SerializeComma();
            serializer.SerializeString("s"); serializer.SerializeColon(); serializer.SerializeString(instanceReal.GetString());
        serializer.SerializeObjectEnd();
    };

    override void SerializeArray(notnull V30_Json_Serializer serializer, notnull Managed arr) {
        V30_Json_SerializerAttributeHelperT<V30_JSON_TEST_CustomSerializer_Class>.SerializeArray(serializer, arr, this);
    };

    override void SerializeArrayRef(notnull V30_Json_Serializer serializer, notnull Managed arr) {
        V30_Json_SerializerAttributeHelperRefT<V30_JSON_TEST_CustomSerializer_Class>.SerializeArray(serializer, arr, this);
    };

    override void SerializeObject(notnull V30_Json_Serializer serializer, notnull Managed obj) {
        V30_Json_SerializerAttributeHelperT<V30_JSON_TEST_CustomSerializer_Class>.SerializeObject(serializer, obj, this);
    };

    override void SerializeObjectRef(notnull V30_Json_Serializer serializer, notnull Managed obj) {
        V30_Json_SerializerAttributeHelperRefT<V30_JSON_TEST_CustomSerializer_Class>.SerializeObject(serializer, obj, this);
    };
};

[BaseContainerProps(category: "Autotest/V30/JSON")]
class V30_JSON_TEST_CustomSerializerSuite : V30_JSON_TEST_Suite {};

[Test("V30_JSON_TEST_CustomSerializerSuite")]
class V30_JSON_TEST_CustomSerializer_NullSerialization : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto instance = null;
        auto serializer = new V30_Json_StringSerializer();
        auto instanceSerializer = V30_Json_SerializerHelper.GetSerializerAttribute(V30_JSON_TEST_CustomSerializer_Class);
        instanceSerializer.SerializeClass(serializer, instance);
	    AssertEqual(serializer.GetString(), "null");
    };
};

[Test("V30_JSON_TEST_CustomSerializerSuite")]
class V30_JSON_TEST_CustomSerializer_InstanceSerialization : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto instance = new V30_JSON_TEST_CustomSerializer_Class(true, 42, 3.14, "Hello, World!");
        auto serializer = new V30_Json_StringSerializer();
        auto instanceSerializer = V30_Json_SerializerHelper.GetSerializerAttribute(V30_JSON_TEST_CustomSerializer_Class);
        instanceSerializer.SerializeClass(serializer, instance);
        AssertEqual(serializer.GetString(), "{\"n\":null,\"b\":true,\"i\":42,\"f\":3.14,\"s\":\"Hello, World!\"}");
    };
};

[Test("V30_JSON_TEST_CustomSerializerSuite")]
class V30_JSON_TEST_CustomSerializer_ArraySerialization : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto instances = new array<ref V30_JSON_TEST_CustomSerializer_Class>();
        auto expecteds = new array<string>();
        instances.Insert(new V30_JSON_TEST_CustomSerializer_Class(true, 42, 3.14, "Hello, World!"));
        expecteds.Insert("{\"n\":null,\"b\":true,\"i\":42,\"f\":3.14,\"s\":\"Hello, World!\"}");
        instances.Insert(new V30_JSON_TEST_CustomSerializer_Class(false, 69, 1.41, "Orange"));
        expecteds.Insert("{\"n\":null,\"b\":false,\"i\":69,\"f\":1.41,\"s\":\"Orange\"}");
        instances.Insert(new V30_JSON_TEST_CustomSerializer_Class(true, 141, 2.71, "Apple"));
        expecteds.Insert("{\"n\":null,\"b\":true,\"i\":141,\"f\":2.71,\"s\":\"Apple\"}");
        auto serializer = new V30_Json_StringSerializer();
        V30_Json_SerializerHelper.Serialize(serializer, instances);
        auto expected = V30_Json_TestHelperRefT<V30_JSON_TEST_CustomSerializer_Class>.ExpectedArrayToString(instances, expecteds);
        AssertEqual(serializer.GetString(), expected);
    };
};

[Test("V30_JSON_TEST_CustomSerializerSuite")]
class V30_JSON_TEST_CustomSerializer_ObjectSerialization : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto instances = new map<string, ref V30_JSON_TEST_CustomSerializer_Class>();
        auto expecteds = new map<string, string>();
        instances.Insert("World", new V30_JSON_TEST_CustomSerializer_Class(true, 42, 3.14, "Hello, World!"));
        expecteds.Insert("World", "{\"n\":null,\"b\":true,\"i\":42,\"f\":3.14,\"s\":\"Hello, World!\"}");
        instances.Insert("Orange", new V30_JSON_TEST_CustomSerializer_Class(false, 69, 1.41, "Orange"));
        expecteds.Insert("Orange", "{\"n\":null,\"b\":false,\"i\":69,\"f\":1.41,\"s\":\"Orange\"}");
        instances.Insert("Apple", new V30_JSON_TEST_CustomSerializer_Class(true, 141, 2.71, "Apple"));
        expecteds.Insert("Apple", "{\"n\":null,\"b\":true,\"i\":141,\"f\":2.71,\"s\":\"Apple\"}");
        auto serializer = new V30_Json_StringSerializer();
        V30_Json_SerializerHelper.Serialize(serializer, instances);
        auto expected = V30_Json_TestHelperRefT<V30_JSON_TEST_CustomSerializer_Class>.ExpectedObjectToString(instances, expecteds);
        AssertEqual(serializer.GetString(), expected);
    };
};

#endif // WORKBENCH
