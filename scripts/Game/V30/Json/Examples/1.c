#ifdef WORKBENCH

[V30_Json_Example1_Foo_Attribute()]
class V30_Json_Example1_Foo : Managed {
	string name;

	void V30_Json_Example1_Foo(string n) {
		name = n;
	};
};

class V30_Json_Example1_Foo_Attribute : V30_Json_Attribute {
	override V30_Json_Value Serialize(Class instance) {
        auto inst = V30_Json_Attribute_HelperRefT<V30_Json_Example1_Foo>.Get(instance);
        if (!inst)
            return V30_Json_null();
        return V30_Json_string(inst.name);
	};

	override V30_Json_Value SerializeArray(Managed arr) {
        return V30_Json_Attribute_HelperRefT<V30_Json_Example1_Foo>.SerializeArray(this, arr);
	};

	override V30_Json_Value SerializeObject(Managed obj) {
        return V30_Json_Attribute_HelperRefT<V30_Json_Example1_Foo>.SerializeObject(this, obj);
	};
};

class V30_Json_Example1_Bar : Managed {
    string hello = "Hello!";
};

class V30_Json_Example1_S : Managed {
	bool m_bBool;
	int m_iInt;
	float m_fFloat;
	string m_sString;
	V30_Json_Example1_Foo m_Foo;
	ref V30_Json_Example1_Foo m_RefFoo;
    V30_Json_Example1_Bar m_Bar;
    ref V30_Json_Example1_Bar m_RefBar;
    // TODO: ResourceName rs = "Test";

	ref array<bool> m_aBools;
	ref array<int> m_aInts;
	ref array<float> m_aFloats;
	ref array<string> m_aStrings;
	ref array<V30_Json_Example1_Foo> m_aFoos;
	ref array<ref V30_Json_Example1_Foo> m_aRefFoos;
    // TODO: ref array<ResourceName> rss = { "#1", "#2" };

	ref map<string, bool> m_mBools;
	ref map<string, int> m_mInts;
	ref map<string, float> m_mFloats;
	ref map<string, string> m_mStrings;
	ref map<string, V30_Json_Example1_Foo> m_mFoos;
	ref map<string, ref V30_Json_Example1_Foo> m_mRefFoos;
    // TODO: ref map<string, ResourceName> mrss;

	void V30_Json_Example1_S() {
	    m_bBool = true;
	    m_iInt = 42;
	    m_fFloat = 3.14;
	    m_sString = "Hello, World!";
	    m_Foo = null;
	    m_RefFoo = new V30_Json_Example1_Foo("plain");
		m_Bar = null;
		m_RefBar = new V30_Json_Example1_Bar();

        m_aBools = new array<bool>();
        m_aBools.Insert(true);
        m_aBools.Insert(false);
        m_aInts = new array<int>();
        m_aInts.Insert(69);
        m_aInts.Insert(141);
        m_aFloats = new array<float>();
        m_aFloats.Insert(2.71);
        m_aFloats.Insert(1.41);
        m_aStrings = new array<string>();
        m_aStrings.Insert("apple");
        m_aStrings.Insert("android");
        m_aFoos = new array<V30_Json_Example1_Foo>();
        m_aFoos.Insert(null);
        m_aFoos.Insert(null);
        m_aRefFoos = new array<ref V30_Json_Example1_Foo>();
        m_aRefFoos.Insert(new V30_Json_Example1_Foo("orange"));
        m_aRefFoos.Insert(new V30_Json_Example1_Foo("banana"));

		m_mBools = new map<string, bool>();
		m_mBools.Insert("a", true);
		m_mBools.Insert("b", false);
		m_mInts = new map<string, int>();
		m_mInts.Insert("a", 69);
		m_mInts.Insert("b", 141);
		m_mFloats = new map<string, float>();
		m_mFloats.Insert("a", 2.71);
		m_mFloats.Insert("b", 1.41);
		m_mStrings = new map<string, string>();
		m_mStrings.Insert("a", "apple");
		m_mStrings.Insert("b", "android");
		m_mFoos = new map<string, V30_Json_Example1_Foo>();
		m_mFoos.Insert("a", null);
		m_mFoos.Insert("b", null);
		m_mRefFoos = new map<string, ref V30_Json_Example1_Foo>();
		m_mRefFoos.Insert("a", new V30_Json_Example1_Foo("orange"));
		m_mRefFoos.Insert("b", new V30_Json_Example1_Foo("banana"));
	};
};

#endif