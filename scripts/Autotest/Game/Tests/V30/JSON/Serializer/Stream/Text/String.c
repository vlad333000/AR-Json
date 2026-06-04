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
        serializer.Serialize(null);
        return "null";
    };
};

[Test(suite: V30_JSON_TEST_StringSerializerSuite)]
class V30_JSON_TEST_StringSerializerSuite_BoolTrue : V30_JSON_TEST_StringSerializerCase {
    override string Serialize() {
        serializer.Serialize(true);
        return "true";
    };
};

[Test(suite: V30_JSON_TEST_StringSerializerSuite)]
class V30_JSON_TEST_StringSerializerSuite_BoolFalse : V30_JSON_TEST_StringSerializerCase {
    override string Serialize() {
        serializer.Serialize(false);
        return "false";
    };
};

[Test(suite: V30_JSON_TEST_StringSerializerSuite)]
class V30_JSON_TEST_StringSerializerSuite_Int : V30_JSON_TEST_StringSerializerCase {
    override string Serialize() {
        serializer.Serialize(42);
        return "42";
    };
};

[Test(suite: V30_JSON_TEST_StringSerializerSuite)]
class V30_JSON_TEST_StringSerializerSuite_Float : V30_JSON_TEST_StringSerializerCase {
    override string Serialize() {
        serializer.Serialize(3.14);
        return "3.14";
    };
};

[Test(suite: V30_JSON_TEST_StringSerializerSuite)]
class V30_JSON_TEST_StringSerializerSuite_String : V30_JSON_TEST_StringSerializerCase {
    override string Serialize() {
        serializer.Serialize("Hello, World!");
        return "\"Hello, World!\"";
    };
};

[Test(suite: V30_JSON_TEST_StringSerializerSuite)]
class V30_JSON_TEST_StringSerializerSuite_StringEscape : V30_JSON_TEST_StringSerializerCase {
    override string Serialize() {
        serializer.Serialize(string.Format("%1Escape sequences:%2%3%4%5%1", "\"", "\\", "\t", "\n", "\r"));
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
            serializer.Serialize(null);
            serializer.Serialize(true);
            serializer.Serialize(42);
            serializer.Serialize(3.14);
            serializer.Serialize("Hello, World!");
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
                    serializer.Serialize(null);
                    serializer.Serialize(true);
                serializer.EndArraySerialization();
                serializer.BeginArraySerialization();
                    serializer.Serialize(42);
                    serializer.Serialize(3.14);
                    serializer.Serialize("Hello, World!");
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
            serializer.Serialize("n", null);
            serializer.Serialize("b", true);
            serializer.Serialize("i", 42);
            serializer.Serialize("f", 3.14);
            serializer.Serialize("s", "Hello, World!");
            serializer.BeginArraySerialization("a");
            serializer.EndArraySerialization();
            serializer.BeginObjectSerialization("o");
            serializer.EndObjectSerialization();
        serializer.EndObjectSerialization();
        return "{\"n\":null,\"b\":true,\"i\":42,\"f\":3.14,\"s\":\"Hello, World!\",\"a\":[],\"o\":{}}";
    };
};

[Test(suite: V30_JSON_TEST_StringSerializerSuite)]
class V30_JSON_TEST_StringSerializerSuite_MultiDimensionalObject : V30_JSON_TEST_StringSerializerCase {
    override string Serialize() {
        serializer.BeginObjectSerialization();
            serializer.BeginObjectSerialization("141");
                serializer.BeginObjectSerialization("Apple");
                    serializer.Serialize("n", null);
                    serializer.Serialize("b", true);
                serializer.EndObjectSerialization();
                serializer.BeginObjectSerialization("Banana");
                    serializer.Serialize("i", 42);
                    serializer.Serialize("f", 3.14);
                    serializer.Serialize("s", "Hello, World!");
                serializer.EndObjectSerialization();
                serializer.BeginObjectSerialization("Orange");
                    serializer.BeginArraySerialization("a");
                    serializer.EndArraySerialization();
                serializer.EndObjectSerialization();
                serializer.BeginObjectSerialization("o");
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
            serializer.BeginArraySerialization("Banana");
                serializer.Serialize(null);
                serializer.Serialize(true);
            serializer.EndArraySerialization();
            serializer.BeginObjectSerialization("Apple");
                serializer.Serialize("i", 42);
                serializer.Serialize("f", 3.14);
            serializer.EndObjectSerialization();
            serializer.BeginArraySerialization("Orange");
                serializer.BeginArraySerialization();
                    serializer.Serialize("Hello, World!");
                serializer.EndArraySerialization();
            serializer.EndArraySerialization();
            serializer.BeginObjectSerialization("Pear");
                serializer.BeginArraySerialization("Test");
                serializer.EndArraySerialization();
            serializer.EndObjectSerialization();
            serializer.BeginArraySerialization("a");
            serializer.EndArraySerialization();
            serializer.BeginObjectSerialization("o");
            serializer.EndObjectSerialization();
        serializer.EndObjectSerialization();
        return "{\"Banana\":[null,true],\"Apple\":{\"i\":42,\"f\":3.14},\"Orange\":[[\"Hello, World!\"]],\"Pear\":{\"Test\":[]},\"a\":[],\"o\":{}}";
    };
};



[Test(suite: V30_JSON_TEST_StringSerializerSuite)]
class V30_JSON_TEST_StringSerializerSuite_JsonNull : V30_JSON_TEST_StringSerializerCase {
    override string Serialize() {
        auto value = V30_JSON_Null.GetInstance();
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
        value.Insert(V30_JSON_Null.GetInstance());
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
        value.Insert("n", V30_JSON_Null.GetInstance());
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
