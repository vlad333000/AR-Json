#ifdef WORKBENCH

class V30_Json_TestSuite : SCR_AutotestSuiteBase {
	override ResourceName GetWorldFile() {
		return SCR_AutotestHelper.WORLD_EMPTY;
	};
};

class V30_Json_TestHelper {
	static TestResultBase Equal(string serialized, string expected) {
		if (serialized == expected)
			return SCR_AutotestResult.AsSuccess();
		else
			return SCR_AutotestResult.AsFailure("Expected '%1', got '%2'", expected, serialized);
	};

	static TestResultBase Equal(notnull V30_Json_StringSerializer serializer, string expected) {
        auto got = serializer.GetString();
		return Equal(got, expected);
	};
};

class V30_Json_TestHelperT<Class T> {
    static string ExpectedArrayToString(notnull Managed arr, notnull array<string> expectedValues) {
        auto expected = "[";
        foreach (auto i, auto _ : array<T>.Cast(arr)) {
            if (i > 0)
                expected += ",";
            expected += expectedValues.Get(i);
        };
        expected += "]";
        return expected;
    };

    static string ExpectedObjectToString(notnull Managed obj, notnull map<string, string> expectedValues) {
        auto expected = "{";
        auto comma = false;
        foreach (auto key, auto _ : map<string, T>.Cast(obj)) {
            string valueExpected;
            if (!expectedValues.Find(key, valueExpected))
                Debug.Error(string.Format("[V30][JSON][TestHelper] ExpectedObjectToString(Managed, map<string,string>): Missing key \"%1\" in expected.", key));
            if (comma)
                expected += ",";
            else
                comma = true;
            expected += "\"" + key + "\":" + valueExpected;
        };
        expected += "}";
        return expected;
    };
};

class V30_Json_TestHelperRefT<Managed T> {
    static string ExpectedArrayToString(notnull Managed arr, notnull array<string> expectedValues) {
        auto expected = "[";
        foreach (auto i, auto _ : array<ref T>.Cast(arr)) {
            if (i > 0)
                expected += ",";
            expected += expectedValues.Get(i);
        };
        expected += "]";
        return expected;
    };

    static string ExpectedObjectToString(notnull Managed obj, notnull map<string, string> expectedValues) {
        auto expected = "{";
        auto comma = false;
        foreach (auto key, auto _ : map<string, ref T>.Cast(obj)) {
            string valueExpected;
            if (!expectedValues.Find(key, valueExpected))
                Debug.Error(string.Format("[V30][JSON][TestHelper] ExpectedObjectToString(Managed, map<string,string>): Missing key \"%1\" in expected.", key));
            if (comma)
                expected += ",";
            else
                comma = true;
            expected += "\"" + key + "\":" + valueExpected;
        };
        expected += "}";
        return expected;
    };
};

#endif // WORKBENCH
