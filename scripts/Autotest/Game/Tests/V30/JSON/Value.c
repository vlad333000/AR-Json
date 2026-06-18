#ifdef WORKBENCH

[BaseContainerProps(category: "Autotest/V30/JSON")]
class V30_JSON_TEST_ValueSuite : V30_JSON_TEST_Suite {};

[Test(suite: V30_JSON_TEST_ValueSuite)]
class V30_JSON_TEST_Value_Null : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto value = new V30_JSON_Null();
        AssertTrue(!!value, "Failed to create `V30_JSON_Null`.");
        AssertTrue(value.IsInherited(Managed), "`V30_JSON_Null` isn't `Managed`.");
        AssertTrue(value.GetValue() == null, "`V30_JSON_Null` returns non-null value.");
		SetResult(SCR_AutotestResult.AsSuccess());
    };
};

[Test(suite: V30_JSON_TEST_ValueSuite)]
class V30_JSON_TEST_Value_Int : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto value = new V30_JSON_Int();
        AssertTrue(!!value, "Failed to create `V30_JSON_Int`.");
        AssertTrue(value.IsInherited(Managed), "`V30_JSON_Int` isn't `Managed`.");
        AssertTrue(value.IsInherited(V30_JSON_Number), "`V30_JSON_Int` isn't `V30_JSON_Number`.");
        AssertTrue(value.GetValue() == 0, "`V30_JSON_Int()` failed to return `0`.");
        value.SetValue(42);
        AssertTrue(value.GetValue() == 42, "`V30_JSON_Int.SetValue(42)` failed to return `42`.");
        value = new V30_JSON_Int(69);
        AssertTrue(value.GetValue() == 69, "`V30_JSON_Int(69)` failed to return `69`.");
        value.SetValue(141);
        AssertTrue(value.GetValue() == 141, "`V30_JSON_Int.SetValue(141)` failed to return `141`.");
		SetResult(SCR_AutotestResult.AsSuccess());
    };
};

[Test(suite: V30_JSON_TEST_ValueSuite)]
class V30_JSON_TEST_Value_Float : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto value = new V30_JSON_Float();
        AssertTrue(!!value, "Failed to create `V30_JSON_Float`.");
        AssertTrue(value.IsInherited(Managed), "`V30_JSON_Float` isn't `Managed`.");
        AssertTrue(value.IsInherited(V30_JSON_Number), "`V30_JSON_Float` isn't `V30_JSON_Number`.");
        AssertTrue(value.GetValue() == 0.0, "`V30_JSON_Float()` failed to return `0.0`.");
        value.SetValue(3.14);
        AssertTrue(value.GetValue() == 3.14, "`V30_JSON_Float.SetValue(3.14)` failed to return `3.14`.");
        value = new V30_JSON_Float(1.41);
        AssertTrue(value.GetValue() == 1.41, "`V30_JSON_Float(1.41)` failed to return `1.41`.");
        value.SetValue(2.71);
        AssertTrue(value.GetValue() == 2.71, "`V30_JSON_Float.SetValue(2.71)` failed to return `2.71`.");
		SetResult(SCR_AutotestResult.AsSuccess());
    };
};

[Test(suite: V30_JSON_TEST_ValueSuite)]
class V30_JSON_TEST_Value_String : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto value = new V30_JSON_String();
        AssertTrue(!!value, "Failed to create `V30_JSON_String`.");
        AssertTrue(value.IsInherited(Managed), "`V30_JSON_String` isn't `Managed`.");
        AssertTrue(value.GetValue() == "", "`V30_JSON_String()` failed to return `\"" + "\"`.");
        AssertTrue(value.Length() == 0, "`V30_JSON_String().Length()` failed to return `0`.");
        value.SetValue("Banana");
        AssertTrue(value.GetValue() == "Banana", "`V30_JSON_String.SetValue(\"Banana\")` failed to return `\"Banana\"`.");
        AssertTrue(value.Length() == 6, "`V30_JSON_String.SetValue(\"Banana\").Length()` failed to return `6`.");
        value = new V30_JSON_String("Apple");
        AssertTrue(value.GetValue() == "Apple", "`V30_JSON_String(\"Apple\")` failed to return `\"Apple\"`.");
        AssertTrue(value.Length() == 5, "`V30_JSON_String(\"Apple\").Length()` failed to return `5`.");
        value.SetValue("Orange");
        AssertTrue(value.GetValue() == "Orange", "`V30_JSON_String.SetValue(\"Orange\")` failed to return `\"Orange\"`.");
        AssertTrue(value.Length() == 6, "`V30_JSON_String.SetValue(\"Orange\").Length()` failed to return `6`.");
		SetResult(SCR_AutotestResult.AsSuccess());
    };
};

[Test(suite: V30_JSON_TEST_ValueSuite)]
class V30_JSON_TEST_Value_Array : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto value = new V30_JSON_Array();
        AssertTrue(!!value, "Failed to create `V30_JSON_Array`.");
        AssertTrue(value.IsInherited(Managed), "`V30_JSON_Array` isn't `Managed`.");
        AssertTrue(value.IsInherited(V30_JSON_Container), "`V30_JSON_Array` isn't `V30_JSON_Container`.");
        AssertTrue(value.Count() == 0, "`V30_JSON_Array().Count()` failed to return `0`.");
        AssertTrue(!value.IsIndexValid(-1), "`V30_JSON_Array().IsIndexValid(-1)` failed.");
        AssertTrue(!value.IsIndexValid(0), "`V30_JSON_Array().IsIndexValid(0)` failed.");
        AssertTrue(!value.IsIndexValid(1), "`V30_JSON_Array().IsIndexValid(1)` failed.");
		SetResult(SCR_AutotestResult.AsSuccess());
    };
};

[Test(suite: V30_JSON_TEST_ValueSuite)]
class V30_JSON_TEST_Value_Object : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto value = new V30_JSON_Object();
        AssertTrue(!!value, "Failed to create `V30_JSON_Object`.");
        AssertTrue(value.IsInherited(Managed), "`V30_JSON_Object` isn't `Managed`.");
        AssertTrue(value.IsInherited(V30_JSON_Container), "`V30_JSON_Object` isn't `V30_JSON_Container`.");
        AssertTrue(value.Count() == 0, "`V30_JSON_Object().Count()` failed to return `0`.");
        AssertTrue(!value.Contains(""), "`V30_JSON_Object().Contains(\"" + "\")` failed.");
		SetResult(SCR_AutotestResult.AsSuccess());
    };
};

class V30_JSON_TEST_Equals_Case : V30_JSON_TEST_Case {
    [Step(EStage.Main)]
    void Execute() {
        auto a = GetLeft();
        auto b = GetRight();
        auto r = IsEquals();
        if (r)
            AssertTrue(a && a.IsEqualTo(b) || b && b.IsEqualTo(a) || !a == !b, string.Format("%1 == %2 returns false\n\t%3 == %4", Stringify(a), Stringify(b), a, b));
        else
            AssertTrue(a && !a.IsEqualTo(b) || b && !b.IsEqualTo(a) || !a != !b, string.Format("%1 != %2 returns false\n\t%3 == %4", Stringify(a), Stringify(b), a, b));
		SetResult(SCR_AutotestResult.AsSuccess());
    };

    protected string Stringify(V30_JSON_Value value) {
        if (!value)
            return "NULL";
        return value.DebugString();
    };

    V30_JSON_Value GetLeft();

    V30_JSON_Value GetRight();

    bool IsEquals() {
        return true;
    };
};

class V30_JSON_TEST_NotEquals_Case : V30_JSON_TEST_Equals_Case {
    override bool IsEquals() {
        return false;
    };
};

[Test(suite: V30_JSON_TEST_ValueSuite)]
class V30_JSON_TEST_Value_Equals_Base1 : V30_JSON_TEST_Equals_Case {
    override V30_JSON_Value GetLeft() {
        return null;
    };
    override V30_JSON_Value GetRight() {
        return null;
    };
};

[Test(suite: V30_JSON_TEST_ValueSuite)]
class V30_JSON_TEST_Value_Equals_Base2 : V30_JSON_TEST_NotEquals_Case {
    override V30_JSON_Value GetLeft() {
        return new V30_JSON_Int(42);
    };
    override V30_JSON_Value GetRight() {
        return null;
    };
};

[Test(suite: V30_JSON_TEST_ValueSuite)]
class V30_JSON_TEST_Value_Equals_Base3 : V30_JSON_TEST_NotEquals_Case {
    override V30_JSON_Value GetLeft() {
        return null;
    };
    override V30_JSON_Value GetRight() {
        return new V30_JSON_Int(42);
    };
};

[Test(suite: V30_JSON_TEST_ValueSuite)]
class V30_JSON_TEST_Value_Equals_Base4 : V30_JSON_TEST_Equals_Case {
    protected ref V30_JSON_Int m_Value = new V30_JSON_Int(42);

    override V30_JSON_Value GetLeft() {
        return m_Value;
    };
    override V30_JSON_Value GetRight() {
        return m_Value;
    };
};

[Test(suite: V30_JSON_TEST_ValueSuite)]
class V30_JSON_TEST_Value_Equals_Null1 : V30_JSON_TEST_Equals_Case {
    override V30_JSON_Value GetLeft() {
        return V30_JSON_Null.GetInstance();
    };
    override V30_JSON_Value GetRight() {
        return V30_JSON_Null.GetInstance();
    };
};

[Test(suite: V30_JSON_TEST_ValueSuite)]
class V30_JSON_TEST_Value_Equals_Null2 : V30_JSON_TEST_Equals_Case {
    override V30_JSON_Value GetLeft() {
        return new V30_JSON_Null();
    };
    override V30_JSON_Value GetRight() {
        return V30_JSON_Null.GetInstance();
    };
};

[Test(suite: V30_JSON_TEST_ValueSuite)]
class V30_JSON_TEST_Value_Equals_Null3 : V30_JSON_TEST_Equals_Case {
    override V30_JSON_Value GetLeft() {
        return V30_JSON_Null.GetInstance();
    };
    override V30_JSON_Value GetRight() {
        return new V30_JSON_Null();
    };
};

[Test(suite: V30_JSON_TEST_ValueSuite)]
class V30_JSON_TEST_Value_Equals_Null4 : V30_JSON_TEST_Equals_Case {
    override V30_JSON_Value GetLeft() {
        return new V30_JSON_Null();
    };
    override V30_JSON_Value GetRight() {
        return new V30_JSON_Null();
    };
};

[Test(suite: V30_JSON_TEST_ValueSuite)]
class V30_JSON_TEST_Value_Equals_Null5 : V30_JSON_TEST_NotEquals_Case {
    override V30_JSON_Value GetLeft() {
        return new V30_JSON_Null();
    };
    override V30_JSON_Value GetRight() {
        return new V30_JSON_Int(42);
    };
};

[Test(suite: V30_JSON_TEST_ValueSuite)]
class V30_JSON_TEST_Value_Equals_Bool1 : V30_JSON_TEST_Equals_Case {
    override V30_JSON_Value GetLeft() {
        return new V30_JSON_Bool();
    };
    override V30_JSON_Value GetRight() {
        return new V30_JSON_Bool();
    };
};

[Test(suite: V30_JSON_TEST_ValueSuite)]
class V30_JSON_TEST_Value_Equals_Bool2 : V30_JSON_TEST_Equals_Case {
    override V30_JSON_Value GetLeft() {
        return new V30_JSON_Bool(true);
    };
    override V30_JSON_Value GetRight() {
        return new V30_JSON_Bool(true);
    };
};

[Test(suite: V30_JSON_TEST_ValueSuite)]
class V30_JSON_TEST_Value_Equals_Bool3 : V30_JSON_TEST_NotEquals_Case {
    override V30_JSON_Value GetLeft() {
        return new V30_JSON_Bool(false);
    };
    override V30_JSON_Value GetRight() {
        return new V30_JSON_Bool(true);
    };
};

[Test(suite: V30_JSON_TEST_ValueSuite)]
class V30_JSON_TEST_Value_Equals_Bool4 : V30_JSON_TEST_NotEquals_Case {
    override V30_JSON_Value GetLeft() {
        return new V30_JSON_Bool(true);
    };
    override V30_JSON_Value GetRight() {
        return new V30_JSON_Bool(false);
    };
};

[Test(suite: V30_JSON_TEST_ValueSuite)]
class V30_JSON_TEST_Value_Equals_Bool5 : V30_JSON_TEST_NotEquals_Case {
    override V30_JSON_Value GetLeft() {
        return new V30_JSON_Bool(true);
    };
    override V30_JSON_Value GetRight() {
        return null;
    };
};

[Test(suite: V30_JSON_TEST_ValueSuite)]
class V30_JSON_TEST_Value_Equals_Bool6 : V30_JSON_TEST_NotEquals_Case {
    override V30_JSON_Value GetLeft() {
        return new V30_JSON_Bool(true);
    };
    override V30_JSON_Value GetRight() {
        return new V30_JSON_Null();
    };
};

[Test(suite: V30_JSON_TEST_ValueSuite)]
class V30_JSON_TEST_Value_Equals_Bool7 : V30_JSON_TEST_NotEquals_Case {
    override V30_JSON_Value GetLeft() {
        return new V30_JSON_Bool(true);
    };
    override V30_JSON_Value GetRight() {
        return new V30_JSON_Int(42);
    };
};

[Test(suite: V30_JSON_TEST_ValueSuite)]
class V30_JSON_TEST_Value_Equals_Int1 : V30_JSON_TEST_Equals_Case {
    override V30_JSON_Value GetLeft() {
        return new V30_JSON_Int();
    };
    override V30_JSON_Value GetRight() {
        return new V30_JSON_Int();
    };
};

[Test(suite: V30_JSON_TEST_ValueSuite)]
class V30_JSON_TEST_Value_Equals_Int2 : V30_JSON_TEST_Equals_Case {
    override V30_JSON_Value GetLeft() {
        return new V30_JSON_Int(42);
    };
    override V30_JSON_Value GetRight() {
        return new V30_JSON_Int(42);
    };
};

[Test(suite: V30_JSON_TEST_ValueSuite)]
class V30_JSON_TEST_Value_Equals_Int3 : V30_JSON_TEST_NotEquals_Case {
    override V30_JSON_Value GetLeft() {
        return new V30_JSON_Int(69);
    };
    override V30_JSON_Value GetRight() {
        return new V30_JSON_Int(42);
    };
};

[Test(suite: V30_JSON_TEST_ValueSuite)]
class V30_JSON_TEST_Value_Equals_Int4 : V30_JSON_TEST_NotEquals_Case {
    override V30_JSON_Value GetLeft() {
        return new V30_JSON_Int(42);
    };
    override V30_JSON_Value GetRight() {
        return new V30_JSON_Int(69);
    };
};

[Test(suite: V30_JSON_TEST_ValueSuite)]
class V30_JSON_TEST_Value_Equals_Int5 : V30_JSON_TEST_NotEquals_Case {
    override V30_JSON_Value GetLeft() {
        return new V30_JSON_Int(42);
    };
    override V30_JSON_Value GetRight() {
        return null;
    };
};

[Test(suite: V30_JSON_TEST_ValueSuite)]
class V30_JSON_TEST_Value_Equals_Int6 : V30_JSON_TEST_NotEquals_Case {
    override V30_JSON_Value GetLeft() {
        return new V30_JSON_Int(42);
    };
    override V30_JSON_Value GetRight() {
        return new V30_JSON_Null();
    };
};

[Test(suite: V30_JSON_TEST_ValueSuite)]
class V30_JSON_TEST_Value_Equals_Int7 : V30_JSON_TEST_NotEquals_Case {
    override V30_JSON_Value GetLeft() {
        return new V30_JSON_Int(42);
    };
    override V30_JSON_Value GetRight() {
        return new V30_JSON_Bool(true);
    };
};

[Test(suite: V30_JSON_TEST_ValueSuite)]
class V30_JSON_TEST_Value_Equals_Float1 : V30_JSON_TEST_Equals_Case {
    override V30_JSON_Value GetLeft() {
        return new V30_JSON_Float();
    };
    override V30_JSON_Value GetRight() {
        return new V30_JSON_Float();
    };
};

[Test(suite: V30_JSON_TEST_ValueSuite)]
class V30_JSON_TEST_Value_Equals_Float2 : V30_JSON_TEST_Equals_Case {
    override V30_JSON_Value GetLeft() {
        return new V30_JSON_Float(3.14);
    };
    override V30_JSON_Value GetRight() {
        return new V30_JSON_Float(3.14);
    };
};

[Test(suite: V30_JSON_TEST_ValueSuite)]
class V30_JSON_TEST_Value_Equals_Float3 : V30_JSON_TEST_NotEquals_Case {
    override V30_JSON_Value GetLeft() {
        return new V30_JSON_Float(3.14);
    };
    override V30_JSON_Value GetRight() {
        return new V30_JSON_Float(1.41);
    };
};

[Test(suite: V30_JSON_TEST_ValueSuite)]
class V30_JSON_TEST_Value_Equals_Float4 : V30_JSON_TEST_NotEquals_Case {
    override V30_JSON_Value GetLeft() {
        return new V30_JSON_Float(1.41);
    };
    override V30_JSON_Value GetRight() {
        return new V30_JSON_Float(3.14);
    };
};

[Test(suite: V30_JSON_TEST_ValueSuite)]
class V30_JSON_TEST_Value_Equals_Float5 : V30_JSON_TEST_NotEquals_Case {
    override V30_JSON_Value GetLeft() {
        return new V30_JSON_Float(3.14);
    };
    override V30_JSON_Value GetRight() {
        return null;
    };
};

[Test(suite: V30_JSON_TEST_ValueSuite)]
class V30_JSON_TEST_Value_Equals_Float6 : V30_JSON_TEST_NotEquals_Case {
    override V30_JSON_Value GetLeft() {
        return new V30_JSON_Float(3.14);
    };
    override V30_JSON_Value GetRight() {
        return new V30_JSON_Null();
    };
};

[Test(suite: V30_JSON_TEST_ValueSuite)]
class V30_JSON_TEST_Value_Equals_Float7 : V30_JSON_TEST_NotEquals_Case {
    override V30_JSON_Value GetLeft() {
        return new V30_JSON_Float(3.14);
    };
    override V30_JSON_Value GetRight() {
        return new V30_JSON_Int(42);
    };
};

[Test(suite: V30_JSON_TEST_ValueSuite)]
class V30_JSON_TEST_Value_Equals_String1 : V30_JSON_TEST_Equals_Case {
    override V30_JSON_Value GetLeft() {
        return new V30_JSON_String();
    };
    override V30_JSON_Value GetRight() {
        return new V30_JSON_String();
    };
};

[Test(suite: V30_JSON_TEST_ValueSuite)]
class V30_JSON_TEST_Value_Equals_String2 : V30_JSON_TEST_Equals_Case {
    override V30_JSON_Value GetLeft() {
        return new V30_JSON_String("Apple");
    };
    override V30_JSON_Value GetRight() {
        return new V30_JSON_String("Apple");
    };
};

[Test(suite: V30_JSON_TEST_ValueSuite)]
class V30_JSON_TEST_Value_Equals_String3 : V30_JSON_TEST_NotEquals_Case {
    override V30_JSON_Value GetLeft() {
        return new V30_JSON_String("Apple");
    };
    override V30_JSON_Value GetRight() {
        return new V30_JSON_String("Orange");
    };
};

[Test(suite: V30_JSON_TEST_ValueSuite)]
class V30_JSON_TEST_Value_Equals_String4 : V30_JSON_TEST_NotEquals_Case {
    override V30_JSON_Value GetLeft() {
        return new V30_JSON_String("Orange");
    };
    override V30_JSON_Value GetRight() {
        return new V30_JSON_String("Apple");
    };
};

[Test(suite: V30_JSON_TEST_ValueSuite)]
class V30_JSON_TEST_Value_Equals_String5 : V30_JSON_TEST_NotEquals_Case {
    override V30_JSON_Value GetLeft() {
        return new V30_JSON_String("Apple");
    };
    override V30_JSON_Value GetRight() {
        return null;
    };
};

[Test(suite: V30_JSON_TEST_ValueSuite)]
class V30_JSON_TEST_Value_Equals_String6 : V30_JSON_TEST_NotEquals_Case {
    override V30_JSON_Value GetLeft() {
        return new V30_JSON_String("Apple");
    };
    override V30_JSON_Value GetRight() {
        return new V30_JSON_Null();
    };
};

[Test(suite: V30_JSON_TEST_ValueSuite)]
class V30_JSON_TEST_Value_Equals_String7 : V30_JSON_TEST_NotEquals_Case {
    override V30_JSON_Value GetLeft() {
        return new V30_JSON_String("Apple");
    };
    override V30_JSON_Value GetRight() {
        return new V30_JSON_Int(42);
    };
};

#endif // WORKBENCH
