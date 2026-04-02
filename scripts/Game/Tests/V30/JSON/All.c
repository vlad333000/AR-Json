#ifdef WORKBENCH

[BaseContainerProps(category: "Autotest/V30/JSON")]
class V30_JSON_TEST_Suite : SCR_AutotestSuiteBase {
	override ResourceName GetWorldFile() {
		return SCR_AutotestHelper.WORLD_EMPTY;
	};
};

[Test(suite: "V30_JSON_TEST_Suite")]
class V30_JSON_TEST_Case : SCR_AutotestCaseBase {};

#endif // WORKBENCH
