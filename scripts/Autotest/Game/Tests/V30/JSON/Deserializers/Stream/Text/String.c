#ifdef WORKBENCH

[BaseContainerProps(category: "Autotest/V30/JSON")]
class V30_JSON_TEST_StringDeserializerSuite : V30_JSON_TEST_Suite {
	override ResourceName GetWorldFile() {
		return SCR_AutotestHelper.WORLD_EMPTY;
	};
};

class V30_JSON_TEST_StringDeserializerCase : V30_JSON_TEST_Case {
    protected ref V30_JSON_StringDeserializer m_Deserializer;

    [Step(EStage.Setup)]
    void Setup() {
        m_Deserializer = new V30_JSON_StringDeserializer();
    };

    [Step(EStage.Main)]
    void Execute() {
        auto data = GetData();
        if (!m_Deserializer.BeginDeserialization(data)) {
            if (!GetResult() || !GetResult().Failure())
		        SetResult(SCR_AutotestResult.AsFailure("Failed to begin deserialization for: \"%1\"", data));
            return;
        };
        if (!Deserialize(m_Deserializer)) {
            if (!GetResult() || !GetResult().Failure())
                SetResult(SCR_AutotestResult.AsFailure("Failed to deserialize: \"%1\"", data));
            return;
        };
        if (!m_Deserializer.EndDeserialization()) {
            if (!GetResult() || !GetResult().Failure())
                SetResult(SCR_AutotestResult.AsFailure("Failed to end deserialization for: \"%1\"", data));
            return;
        };
        SetResult(SCR_AutotestResult.AsSuccess());
    };

    string GetData();

    bool Deserialize(notnull V30_JSON_StringDeserializer deserializer);
};

[Test(suite: V30_JSON_TEST_StringDeserializerSuite)]
class V30_JSON_TEST_StringDeserializerSuite_Null : V30_JSON_TEST_StringDeserializerCase {
    override string GetData() {
        return "null";
    };

    override bool Deserialize(notnull V30_JSON_StringDeserializer deserializer) {
        return deserializer.DeserializeNull();
    };
};

class V30_JSON_TEST_StringDeserializerSuite_Bool : V30_JSON_TEST_StringDeserializerCase {
    bool GetValue();

    override string GetData() {
        return GetValue().ToString();
    };

    override bool Deserialize(notnull V30_JSON_StringDeserializer deserializer) {
        bool result;
        if (!deserializer.DeserializeBool(result))
            return false;
        auto expected = GetValue();
        if (AssertTrue(result == expected, string.Format("Result %1 doesn't equal to %2", result.ToString(), expected.ToString())))
            return false;
        return true;
    };
};

[Test(suite: V30_JSON_TEST_StringDeserializerSuite)]
class V30_JSON_TEST_StringDeserializerSuite_BoolTrue : V30_JSON_TEST_StringDeserializerSuite_Bool {
    override bool GetValue() {
        return true;
    };
};

[Test(suite: V30_JSON_TEST_StringDeserializerSuite)]
class V30_JSON_TEST_StringDeserializerSuite_BoolFalse : V30_JSON_TEST_StringDeserializerSuite_Bool {
    override bool GetValue() {
        return false;
    };
};

class V30_JSON_TEST_StringDeserializerSuite_Int : V30_JSON_TEST_StringDeserializerCase {
    int GetValue();

    override string GetData() {
        return GetValue().ToString();
    };

    override bool Deserialize(notnull V30_JSON_StringDeserializer deserializer) {
        int result;
        if (!deserializer.DeserializeInt(result))
            return false;
        auto expected = GetValue();
        if (AssertTrue(result == expected, string.Format("Result %1 doesn't equal to %2", result, expected)))
            return false;
        return true;
    };
};

[Test(suite: V30_JSON_TEST_StringDeserializerSuite)]
class V30_JSON_TEST_StringDeserializerSuite_IntZero : V30_JSON_TEST_StringDeserializerSuite_Int {
    override int GetValue() {
        return 0;
    };
};

[Test(suite: V30_JSON_TEST_StringDeserializerSuite)]
class V30_JSON_TEST_StringDeserializerSuite_IntNumber : V30_JSON_TEST_StringDeserializerSuite_Int {
    override int GetValue() {
        return 42;
    };
};

[Test(suite: V30_JSON_TEST_StringDeserializerSuite)]
class V30_JSON_TEST_StringDeserializerSuite_IntMinusNumber : V30_JSON_TEST_StringDeserializerSuite_Int {
    override int GetValue() {
        return -42;
    };
};

[Test(suite: V30_JSON_TEST_StringDeserializerSuite)]
class V30_JSON_TEST_StringDeserializerSuite_IntOne : V30_JSON_TEST_StringDeserializerSuite_Int {
    override int GetValue() {
        return 1;
    };
};

[Test(suite: V30_JSON_TEST_StringDeserializerSuite)]
class V30_JSON_TEST_StringDeserializerSuite_IntMinusOne : V30_JSON_TEST_StringDeserializerSuite_Int {
    override int GetValue() {
        return -1;
    };
};

[Test(suite: V30_JSON_TEST_StringDeserializerSuite)]
class V30_JSON_TEST_StringDeserializerSuite_IntOneM : V30_JSON_TEST_StringDeserializerSuite_Int {
    override int GetValue() {
        return 1000000;
    };
};

[Test(suite: V30_JSON_TEST_StringDeserializerSuite)]
class V30_JSON_TEST_StringDeserializerSuite_IntMax : V30_JSON_TEST_StringDeserializerSuite_Int {
    override int GetValue() {
        return 2147483647;
    };
};

[Test(suite: V30_JSON_TEST_StringDeserializerSuite)]
class V30_JSON_TEST_StringDeserializerSuite_IntMin : V30_JSON_TEST_StringDeserializerSuite_Int {
    override int GetValue() {
        return -2147483648;
    };
};

class V30_JSON_TEST_StringDeserializerSuite_Float : V30_JSON_TEST_StringDeserializerCase {
    override bool Deserialize(notnull V30_JSON_StringDeserializer deserializer) {
        float result;
        if (!deserializer.DeserializeFloat(result))
            return false;
        auto data = GetData();
        int parsed;
        auto expected = data.ToFloat(parsed: parsed);
        if (AssertTrue(parsed == data.Length(), string.Format("Failed to natively parse: \"%1\", parsed: %2, epxected: %3", data, parsed, data.Length())))
            return false;
        if (AssertTrue(result == expected, string.Format("Result %1 doesn't equal to %2", result, expected)))
            return false;
        return true;
    };
};

[Test(suite: V30_JSON_TEST_StringDeserializerSuite)]
class V30_JSON_TEST_StringDeserializerSuite_FloatZero : V30_JSON_TEST_StringDeserializerSuite_Float {
    override string GetData() {
        return "0.0";
    };
};

[Test(suite: V30_JSON_TEST_StringDeserializerSuite)]
class V30_JSON_TEST_StringDeserializerSuite_FloatOne : V30_JSON_TEST_StringDeserializerSuite_Float {
    override string GetData() {
        return "1.0";
    };
};

[Test(suite: V30_JSON_TEST_StringDeserializerSuite)]
class V30_JSON_TEST_StringDeserializerSuite_FloatMinusOne : V30_JSON_TEST_StringDeserializerSuite_Float {
    override string GetData() {
        return "-1.0";
    };
};

[Test(suite: V30_JSON_TEST_StringDeserializerSuite)]
class V30_JSON_TEST_StringDeserializerSuite_FloatZeroOne : V30_JSON_TEST_StringDeserializerSuite_Float {
    override string GetData() {
        return "0.1";
    };
};

[Test(suite: V30_JSON_TEST_StringDeserializerSuite)]
class V30_JSON_TEST_StringDeserializerSuite_FloatPi : V30_JSON_TEST_StringDeserializerSuite_Float {
    override string GetData() {
        return "3.14159274101257324";
    };
};

[Test(suite: V30_JSON_TEST_StringDeserializerSuite)]
class V30_JSON_TEST_StringDeserializerSuite_FloatPiShort : V30_JSON_TEST_StringDeserializerSuite_Float {
    override string GetData() {
        return "3.14";
    };
};

[Test(suite: V30_JSON_TEST_StringDeserializerSuite)]
class V30_JSON_TEST_StringDeserializerSuite_FloatOneThird : V30_JSON_TEST_StringDeserializerSuite_Float {
    override string GetData() {
        return "0.333333343267440796";
    };
};

[Test(suite: V30_JSON_TEST_StringDeserializerSuite)]
class V30_JSON_TEST_StringDeserializerSuite_FloatNumber : V30_JSON_TEST_StringDeserializerSuite_Float {
    override string GetData() {
        return "123.456";
    };
};

[Test(suite: V30_JSON_TEST_StringDeserializerSuite)]
class V30_JSON_TEST_StringDeserializerSuite_FloatOneM : V30_JSON_TEST_StringDeserializerSuite_Float {
    override string GetData() {
        return "1000000.0";
    };
};

[Test(suite: V30_JSON_TEST_StringDeserializerSuite)]
class V30_JSON_TEST_StringDeserializerSuite_FloatMaxInt : V30_JSON_TEST_StringDeserializerSuite_Float {
    override string GetData() {
        return "16777216.0";
    };
};

[Test(suite: V30_JSON_TEST_StringDeserializerSuite)]
class V30_JSON_TEST_StringDeserializerSuite_FloatMinInt : V30_JSON_TEST_StringDeserializerSuite_Float {
    override string GetData() {
        return "-16777216.0";
    };
};

[Test(suite: V30_JSON_TEST_StringDeserializerSuite)]
class V30_JSON_TEST_StringDeserializerSuite_FloatExponent : V30_JSON_TEST_StringDeserializerSuite_Float {
    override string GetData() {
        return "0.123E+4";
    };
};

[Test(suite: V30_JSON_TEST_StringDeserializerSuite)]
class V30_JSON_TEST_StringDeserializerSuite_FloatExponentLC : V30_JSON_TEST_StringDeserializerSuite_Float {
    override string GetData() {
        return "0.123e+4";
    };
};

[Test(suite: V30_JSON_TEST_StringDeserializerSuite)]
class V30_JSON_TEST_StringDeserializerSuite_FloatExponentMinus : V30_JSON_TEST_StringDeserializerSuite_Float {
    override string GetData() {
        return "0.123E-4";
    };
};

[Test(suite: V30_JSON_TEST_StringDeserializerSuite)]
class V30_JSON_TEST_StringDeserializerSuite_FloatMinPositive : V30_JSON_TEST_StringDeserializerSuite_Float {
    override string GetData() {
        return "1.1754943508E-38";
    };
};

[Test(suite: V30_JSON_TEST_StringDeserializerSuite)]
class V30_JSON_TEST_StringDeserializerSuite_FloatMinPositiveSubnormal : V30_JSON_TEST_StringDeserializerSuite_Float {
    override string GetData() {
        return "1.4012984643E-45";
    };
};

[Test(suite: V30_JSON_TEST_StringDeserializerSuite)]
class V30_JSON_TEST_StringDeserializerSuite_FloatMaxPositiveSubnormal : V30_JSON_TEST_StringDeserializerSuite_Float {
    override string GetData() {
        return "1.1754942107E-38";
    };
};

[Test(suite: V30_JSON_TEST_StringDeserializerSuite)]
class V30_JSON_TEST_StringDeserializerSuite_FloatMaxPositive : V30_JSON_TEST_StringDeserializerSuite_Float {
    override string GetData() {
        return "3.4028234664E+38";
    };
};

[Test(suite: V30_JSON_TEST_StringDeserializerSuite)]
class V30_JSON_TEST_StringDeserializerSuite_FloatMaxLessOne : V30_JSON_TEST_StringDeserializerSuite_Float {
    override string GetData() {
        return "0.999999940395355225";
    };
};

[Test(suite: V30_JSON_TEST_StringDeserializerSuite)]
class V30_JSON_TEST_StringDeserializerSuite_FloatMinLargeOne : V30_JSON_TEST_StringDeserializerSuite_Float {
    override string GetData() {
        return "1.00000011920928955";
    };
};

class V30_JSON_TEST_StringDeserializerSuite_String : V30_JSON_TEST_StringDeserializerCase {
    override bool Deserialize(notnull V30_JSON_StringDeserializer deserializer) {
        string result;
        if (!deserializer.DeserializeString(result))
            return false;
        auto expected = GetString();
        if (AssertTrue(result == expected, string.Format("Result \"%1\" doesn't equal to \"%2\"", result, expected))) {
            string resultChars = "result = ";
            for (auto i = 0; i < result.Length(); i++)
                resultChars += result.ToAscii(i).ToString();
            Print(resultChars);
            string expectedChars = "expected = ";
            for (auto i = 0; i < expected.Length(); i++)
                expectedChars += expected.ToAscii(i).ToString();
            Print(expectedChars);
            return false;
        };
        return true;
    };

    override string GetData() {
        return "\"" + GetJsonString() + "\"";
    };

    string GetJsonString() {
        return GetString();
    };

    string GetString();
};

[Test(suite: V30_JSON_TEST_StringDeserializerSuite)]
class V30_JSON_TEST_StringDeserializerSuite_StringEmpty : V30_JSON_TEST_StringDeserializerSuite_String {
    override string GetString() {
        return "";
    };
};

[Test(suite: V30_JSON_TEST_StringDeserializerSuite)]
class V30_JSON_TEST_StringDeserializerSuite_StringHello : V30_JSON_TEST_StringDeserializerSuite_String {
    override string GetString() {
        return "hello";
    };
};

[Test(suite: V30_JSON_TEST_StringDeserializerSuite)]
class V30_JSON_TEST_StringDeserializerSuite_StringHelloWorld : V30_JSON_TEST_StringDeserializerSuite_String {
    override string GetString() {
        return "hello world";
    };
};

[Test(suite: V30_JSON_TEST_StringDeserializerSuite)]
class V30_JSON_TEST_StringDeserializerSuite_StringNumber : V30_JSON_TEST_StringDeserializerSuite_String {
    override string GetString() {
        return "123";
    };
};

[Test(suite: V30_JSON_TEST_StringDeserializerSuite)]
class V30_JSON_TEST_StringDeserializerSuite_StringBoolean : V30_JSON_TEST_StringDeserializerSuite_String {
    override string GetString() {
        return "true";
    };
};

[Test(suite: V30_JSON_TEST_StringDeserializerSuite)]
class V30_JSON_TEST_StringDeserializerSuite_StringNull : V30_JSON_TEST_StringDeserializerSuite_String {
    override string GetString() {
        return "null";
    };
};

[Test(suite: V30_JSON_TEST_StringDeserializerSuite)]
class V30_JSON_TEST_StringDeserializerSuite_StringQuote : V30_JSON_TEST_StringDeserializerSuite_String {
    override string GetJsonString() {
        return "\\\"";
    };

    override string GetString() {
        return "\"";
    };
};

[Test(suite: V30_JSON_TEST_StringDeserializerSuite)]
class V30_JSON_TEST_StringDeserializerSuite_StringSlash : V30_JSON_TEST_StringDeserializerSuite_String {
    override string GetJsonString() {
        return "\\\\";
    };

    override string GetString() {
        return "\\";
    };
};

[Test(suite: V30_JSON_TEST_StringDeserializerSuite)]
class V30_JSON_TEST_StringDeserializerSuite_StringFormardSlash : V30_JSON_TEST_StringDeserializerSuite_String {
    override string GetJsonString() {
        return "\\/";
    };

    override string GetString() {
        return "/";
    };
};

[Test(suite: V30_JSON_TEST_StringDeserializerSuite)]
class V30_JSON_TEST_StringDeserializerSuite_StringEscape : V30_JSON_TEST_StringDeserializerSuite_String {
    override string GetJsonString() {
        return "\\b\\f\\n\\r\\t";
    };

    override string GetString() {
        return (0x08).AsciiToString() /*\b*/ + (0x0C).AsciiToString() /*\f*/ + "\n\r\t";
    };
};

[Test(suite: V30_JSON_TEST_StringDeserializerSuite)]
class V30_JSON_TEST_StringDeserializerSuite_StringMultiline : V30_JSON_TEST_StringDeserializerSuite_String {
    override string GetJsonString() {
        return "line1\\nline2";
    };

    override string GetString() {
        return "line1\nline2";
    };
};

[Test(suite: V30_JSON_TEST_StringDeserializerSuite)]
class V30_JSON_TEST_StringDeserializerSuite_StringWinPath : V30_JSON_TEST_StringDeserializerSuite_String {
    override string GetJsonString() {
        return "C:\\\\Program Files\\\\App\\\\App.exe";
    };

    override string GetString() {
        return "C:\\Program Files\\App\\App.exe";
    };
};

[Test(suite: V30_JSON_TEST_StringDeserializerSuite)]
class V30_JSON_TEST_StringDeserializerSuite_StringLinPath : V30_JSON_TEST_StringDeserializerSuite_String {
    override string GetString() {
        return "/usr/bin/app";
    };
};

[Test(suite: V30_JSON_TEST_StringDeserializerSuite)]
class V30_JSON_TEST_StringDeserializerSuite_StringUnicode : V30_JSON_TEST_StringDeserializerSuite_String {
    override string GetJsonString() {
        return "\\u0041";
    };

    override string GetString() {
        return "A";
    };
};

[Test(suite: V30_JSON_TEST_StringDeserializerSuite)]
class V30_JSON_TEST_StringDeserializerSuite_StringUnicodePi : V30_JSON_TEST_StringDeserializerSuite_String {
    override string GetJsonString() {
        return "\\u03C0";
    };

    override string GetString() {
        return "π";
    };
};

[Test(suite: V30_JSON_TEST_StringDeserializerSuite)]
class V30_JSON_TEST_StringDeserializerSuite_StringUnicodeEmoji : V30_JSON_TEST_StringDeserializerSuite_String {
    override string GetJsonString() {
        return "\\uD83D\\uDE00";
    };

    override string GetString() {
        return "😀";
    };
};

[Test(suite: V30_JSON_TEST_StringDeserializerSuite)]
class V30_JSON_TEST_StringDeserializerSuite_StringLocalized : V30_JSON_TEST_StringDeserializerSuite_String {
    override string GetString() {
        return "привет";
    };
};

#endif
