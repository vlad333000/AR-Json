#ifdef WORKBENCH

[BaseContainerProps(category: "Autotest/V30/JSON")]
class V30_JSON_TEST_StringSerializerSuite : V30_JSON_TEST_Suite {
	override ResourceName GetWorldFile() {
		return SCR_AutotestHelper.WORLD_EMPTY;
	};
};

class V30_JSON_TEST_StringSerializerCase : V30_JSON_TEST_Case {
    void AssertEqual(string result, string expect) {
        Print("\tResult: " + result);
        Print("\tExpect: " + expect);
        AssertTrue(result == expect, "Result isn't equal to expected");
    };

    void AssertEqual(V30_JSON_StringSerializer serializer, string expect) {
        AssertEqual(serializer.GetString(), expect);
    };

    protected ref V30_JSON_StringSerializer serializer;

    [Step(EStage.Setup)]
    void Setup() {
        serializer = new V30_JSON_StringSerializer();
    };

    [Step(EStage.Main)]
    void Execute() {
        auto expect = Serialize();
        auto result = serializer.GetString();
        Print("\tResult: " + result);
        Print("\tExpect: " + expect);
        AssertTrue(result == expect, "Result isn't equal to expected");
		SetResult(SCR_AutotestResult.AsSuccess());
    };

    string Serialize();
};

[Test(suite: V30_JSON_TEST_StringSerializerSuite)]
class V30_JSON_TEST_StringSerializerSuite_Null : V30_JSON_TEST_StringSerializerCase {
    override string Serialize() {
        serializer.SerializeNull();
        return "null";
    };
};

[Test(suite: V30_JSON_TEST_StringSerializerSuite)]
class V30_JSON_TEST_StringSerializerSuite_BoolTrue : V30_JSON_TEST_StringSerializerCase {
    override string Serialize() {
        serializer.SerializeBool(true);
        return "true";
    };
};

[Test(suite: V30_JSON_TEST_StringSerializerSuite)]
class V30_JSON_TEST_StringSerializerSuite_BoolFalse : V30_JSON_TEST_StringSerializerCase {
    override string Serialize() {
        serializer.SerializeBool(false);
        return "false";
    };
};

[Test(suite: V30_JSON_TEST_StringSerializerSuite)]
class V30_JSON_TEST_StringSerializerSuite_Int : V30_JSON_TEST_StringSerializerCase {
    override string Serialize() {
        serializer.SerializeInt(42);
        return "42";
    };
};

[Test(suite: V30_JSON_TEST_StringSerializerSuite)]
class V30_JSON_TEST_StringSerializerSuite_Float : V30_JSON_TEST_StringSerializerCase {
    override string Serialize() {
        serializer.SerializeFloat(3.14);
        return "3.14";
    };
};

[Test(suite: V30_JSON_TEST_StringSerializerSuite)]
class V30_JSON_TEST_StringSerializerSuite_String : V30_JSON_TEST_StringSerializerCase {
    override string Serialize() {
        serializer.SerializeString("Hello, World!");
        return "\"Hello, World!\"";
    };
};

[Test(suite: V30_JSON_TEST_StringSerializerSuite)]
class V30_JSON_TEST_StringSerializerSuite_StringEscape : V30_JSON_TEST_StringSerializerCase {
    override string Serialize() {
        serializer.SerializeString(string.Format("%1Escape sequences:%2%3%4%5%1", "\"", "\\", "\t", "\n", "\r"));
        return string.Format("\"%1Escape sequences:%2%3%4%5%1\"", "\\"+"\"", "\\"+"\\", "\\"+"t", "\\"+"n", "\\"+"r");
    };
};

[Test(suite: V30_JSON_TEST_StringSerializerSuite)]
class V30_JSON_TEST_StringSerializerSuite_EmptyArray : V30_JSON_TEST_StringSerializerCase {
    override string Serialize() {
        serializer.BeginArraySerialization();
        serializer.EndArraySerialization();
        return "[]";
    };
};

[Test(suite: V30_JSON_TEST_StringSerializerSuite)]
class V30_JSON_TEST_StringSerializerSuite_FilledArray : V30_JSON_TEST_StringSerializerCase {
    override string Serialize() {
        serializer.BeginArraySerialization();
            serializer.SerializeNull();
            serializer.SerializeBool(true);
            serializer.SerializeInt(42);
            serializer.SerializeFloat(3.14);
            serializer.SerializeString("Hello, World!");
            serializer.BeginArraySerialization();
            serializer.EndArraySerialization();
            serializer.BeginObjectSerialization();
            serializer.EndObjectSerialization();
        serializer.EndArraySerialization();
        return "[null,true,42,3.14,\"Hello, World!\",[],{}]";
    };
};

[Test(suite: V30_JSON_TEST_StringSerializerSuite)]
class V30_JSON_TEST_StringSerializerSuite_MultiDimensionalArray : V30_JSON_TEST_StringSerializerCase {
    override string Serialize() {
        serializer.BeginArraySerialization();
            serializer.BeginArraySerialization();
                serializer.BeginArraySerialization();
                    serializer.SerializeNull();
                    serializer.SerializeBool(true);
                serializer.EndArraySerialization();
                serializer.BeginArraySerialization();
                    serializer.SerializeInt(42);
                    serializer.SerializeFloat(3.14);
                    serializer.SerializeString("Hello, World!");
                serializer.EndArraySerialization();
                serializer.BeginArraySerialization();
                	serializer.BeginArraySerialization();
                    serializer.EndArraySerialization();
                serializer.EndArraySerialization();
                serializer.BeginObjectSerialization();
                serializer.EndObjectSerialization();
            serializer.EndArraySerialization();
        serializer.EndArraySerialization();
        return "[[[null,true],[42,3.14,\"Hello, World!\"],[[]],{}]]";
    };
};

[Test(suite: V30_JSON_TEST_StringSerializerSuite)]
class V30_JSON_TEST_StringSerializerSuite_EmptyObject : V30_JSON_TEST_StringSerializerCase {
    override string Serialize() {
        serializer.BeginObjectSerialization();
        serializer.EndObjectSerialization();
        return "{}";
    };
};

[Test(suite: V30_JSON_TEST_StringSerializerSuite)]
class V30_JSON_TEST_StringSerializerSuite_FilledObject : V30_JSON_TEST_StringSerializerCase {
    override string Serialize() {
        serializer.BeginObjectSerialization();
            serializer.SerializeKey("n");
            serializer.SerializeNull();
            serializer.SerializeKey("b");
            serializer.SerializeBool(true);
            serializer.SerializeKey("i");
            serializer.SerializeInt(42);
            serializer.SerializeKey("f");
            serializer.SerializeFloat(3.14);
            serializer.SerializeKey("s");
            serializer.SerializeString("Hello, World!");
            serializer.SerializeKey("a");
            serializer.BeginArraySerialization();
            serializer.EndArraySerialization();
            serializer.SerializeKey("o");
            serializer.BeginObjectSerialization();
            serializer.EndObjectSerialization();
        serializer.EndObjectSerialization();
        return "{\"n\":null,\"b\":true,\"i\":42,\"f\":3.14,\"s\":\"Hello, World!\",\"a\":[],\"o\":{}}";
    };
};

[Test(suite: V30_JSON_TEST_StringSerializerSuite)]
class V30_JSON_TEST_StringSerializerSuite_MultiDimensionalObject : V30_JSON_TEST_StringSerializerCase {
    override string Serialize() {
        serializer.BeginObjectSerialization();
            serializer.SerializeKey("141");
            serializer.BeginObjectSerialization();
                serializer.SerializeKey("Apple");
                serializer.BeginObjectSerialization();
                    serializer.SerializeKey("n");
                    serializer.SerializeNull();
                    serializer.SerializeKey("b");
                    serializer.SerializeBool(true);
                serializer.EndObjectSerialization();
                serializer.SerializeKey("Banana");
                serializer.BeginObjectSerialization();
                    serializer.SerializeKey("i");
                    serializer.SerializeInt(42);
                    serializer.SerializeKey("f");
                    serializer.SerializeFloat(3.14);
                    serializer.SerializeKey("s");
                    serializer.SerializeString("Hello, World!");
                serializer.EndObjectSerialization();
                serializer.SerializeKey("Orange");
                serializer.BeginObjectSerialization();
                    serializer.SerializeKey("a");
                    serializer.BeginArraySerialization();
                    serializer.EndArraySerialization();
                serializer.EndObjectSerialization();
                serializer.SerializeKey("o");
                serializer.BeginObjectSerialization();
                serializer.EndObjectSerialization();
            serializer.EndObjectSerialization();
        serializer.EndObjectSerialization();
        return "{\"141\":{\"Apple\":{\"n\":null,\"b\":true},\"Banana\":{\"i\":42,\"f\":3.14,\"s\":\"Hello, World!\"},\"Orange\":{\"a\":[]},\"o\":{}}}";
    };
};

[Test(suite: V30_JSON_TEST_StringSerializerSuite)]
class V30_JSON_TEST_StringSerializerSuite_MixedArrayObject : V30_JSON_TEST_StringSerializerCase {
    override string Serialize() {
        serializer.BeginObjectSerialization();
            serializer.SerializeKey("Banana");
            serializer.BeginArraySerialization();
                serializer.SerializeNull();
                serializer.SerializeBool(true);
            serializer.EndArraySerialization();
            serializer.SerializeKey("Apple");
            serializer.BeginObjectSerialization();
                serializer.SerializeKey("i");
                serializer.SerializeInt(42);
                serializer.SerializeKey("f");
                serializer.SerializeFloat(3.14);
            serializer.EndObjectSerialization();
            serializer.SerializeKey("Orange");
            serializer.BeginArraySerialization();
                serializer.BeginArraySerialization();
                    serializer.SerializeString("Hello, World!");
                serializer.EndArraySerialization();
            serializer.EndArraySerialization();
            serializer.SerializeKey("Pear");
            serializer.BeginObjectSerialization();
                serializer.SerializeKey("Test");
                serializer.BeginArraySerialization();
                serializer.EndArraySerialization();
            serializer.EndObjectSerialization();
            serializer.SerializeKey("a");
            serializer.BeginArraySerialization();
            serializer.EndArraySerialization();
            serializer.SerializeKey("o");
            serializer.BeginObjectSerialization();
            serializer.EndObjectSerialization();
        serializer.EndObjectSerialization();
        return "{\"Banana\":[null,true],\"Apple\":{\"i\":42,\"f\":3.14},\"Orange\":[[\"Hello, World!\"]],\"Pear\":{\"Test\":[]},\"a\":[],\"o\":{}}";
    };
};



[Test(suite: V30_JSON_TEST_StringSerializerSuite)]
class V30_JSON_TEST_StringSerializerSuite_JsonNull : V30_JSON_TEST_StringSerializerCase {
    override string Serialize() {
        auto value = new V30_JSON_Null();
        serializer.Serialize(value);
        return "null";
    };
};

[Test(suite: V30_JSON_TEST_StringSerializerSuite)]
class V30_JSON_TEST_StringSerializerSuite_JsonBool : V30_JSON_TEST_StringSerializerCase {
    override string Serialize() {
        auto value = new V30_JSON_Bool(true);
        serializer.Serialize(value);
        return "true";
    };
};

[Test(suite: V30_JSON_TEST_StringSerializerSuite)]
class V30_JSON_TEST_StringSerializerSuite_JsonInt : V30_JSON_TEST_StringSerializerCase {
    override string Serialize() {
        auto value = new V30_JSON_Int(42);
        serializer.Serialize(value);
        return "42";
    };
};

[Test(suite: V30_JSON_TEST_StringSerializerSuite)]
class V30_JSON_TEST_StringSerializerSuite_JsonFloat : V30_JSON_TEST_StringSerializerCase {
    override string Serialize() {
        auto value = new V30_JSON_Float(3.14);
        serializer.Serialize(value);
        return "3.14";
    };
};

[Test(suite: V30_JSON_TEST_StringSerializerSuite)]
class V30_JSON_TEST_StringSerializerSuite_JsonString : V30_JSON_TEST_StringSerializerCase {
    override string Serialize() {
        auto value = new V30_JSON_String("Hello, World!");
        serializer.Serialize(value);
        return "\"Hello, World!\"";
    };
};

[Test(suite: V30_JSON_TEST_StringSerializerSuite)]
class V30_JSON_TEST_StringSerializerSuite_JsonArray : V30_JSON_TEST_StringSerializerCase {
    override string Serialize() {
        auto value = new V30_JSON_Array();
        value.Insert(new V30_JSON_Null());
        value.Insert(new V30_JSON_Bool(true));
        value.Insert(new V30_JSON_Int(42));
        value.Insert(new V30_JSON_Float(3.14));
        value.Insert(new V30_JSON_String("Hello, World!"));
        value.Insert(new V30_JSON_Array());
        value.Insert(new V30_JSON_Object());
        serializer.Serialize(value);
        return "[null,true,42,3.14,\"Hello, World!\",[],{}]";
    };
};

[Test(suite: V30_JSON_TEST_StringSerializerSuite)]
class V30_JSON_TEST_StringSerializerSuite_JsonObject : V30_JSON_TEST_StringSerializerCase {
    override string Serialize() {
        auto value = new V30_JSON_Object();
        value.Insert("n", new V30_JSON_Null());
        value.Insert("b", new V30_JSON_Bool(true));
        value.Insert("i", new V30_JSON_Int(42));
        value.Insert("f", new V30_JSON_Float(3.14));
        value.Insert("s", new V30_JSON_String("Hello, World!"));
        value.Insert("a", new V30_JSON_Array());
        value.Insert("o", new V30_JSON_Object());
        serializer.Serialize(value);
        return "{\"n\":null,\"b\":true,\"i\":42,\"f\":3.14,\"s\":\"Hello, World!\",\"a\":[],\"o\":{}}";
    };
};

#endif // WORKBENCH
