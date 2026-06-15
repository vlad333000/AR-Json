class V30_JSON_ValueSerializer : V30_JSON_StreamSerializer {
    protected ref V30_JSON_ValueSerializer_Stack stack;

    protected ref V30_JSON_Value m_Value;

    void V30_JSON_ValueSerializer() {
        stack = new V30_JSON_ValueSerializer_Stack();
    };

    V30_JSON_Value GetValue() {
        return m_Value;
    };

    void ClearValue() {
        m_Value = null;
        stack.Clear();
    };



    override void SerializeNull() {
        auto json = new V30_JSON_Null();
        PutJson(json);
    };

    override void SerializeBool(bool value) {
        auto json = new V30_JSON_Bool(value);
        PutJson(json);
    };

    override void SerializeInt(int value) {
        auto json = new V30_JSON_Int(value);
        PutJson(json);
    };

    override void SerializeFloat(float value) {
        auto json = new V30_JSON_Float(value);
        PutJson(json);
    };

    override void SerializeString(string value) {
        auto json = new V30_JSON_String(value);
        PutJson(json);
    };

    override void BeginArraySerialization() {
        auto value = new V30_JSON_Array();
        PutJson(value);
        stack.Push(value);
    };

    override void EndArraySerialization() {
        auto value = stack.Pop();
        if (stack.IsEmpty())
            m_Value = value;
    };

    override void BeginObjectSerialization() {
        auto value = new V30_JSON_Object();
        PutJson(value);
        stack.Push(value);
    };

    override void SerializeKey(string key) {
        auto value = new V30_JSON_ValueSerializer_Key(key);
        stack.Push(value);
    };

    override void EndObjectSerialization() {
        auto value = stack.Pop();
        if (stack.IsEmpty())
            m_Value = value;
    };

    void PutJson(notnull V30_JSON_Value value) {
        if (IsRoot()) {
            m_Value = value;
        }
        else if (IsArray()) {
			auto top = stack.Peak();
			V30_JSON_Array.Cast(top).Insert(value);
        }
        else {
            auto top = stack.Pop();
            auto key = V30_JSON_ValueSerializer_Key.Cast(top).GetKey();
			auto obj = stack.Peak();
            V30_JSON_Object.Cast(obj).Insert(key, value);
        };
    };

    bool IsRoot() {
        return stack.IsEmpty();
    };

    bool IsContainer() {
        auto top = stack.Peak();
        return top && top.IsInherited(V30_JSON_Container);
    };

    bool IsArray() {
        auto top = stack.Peak();
        return top && top.IsInherited(V30_JSON_Array);
    };

    bool IsObject() {
        auto top = stack.Peak();
        return top && top.IsInherited(V30_JSON_Object);
    };

    bool IsKey() {
        auto top = stack.Peak();
        return top && top.IsInherited(V30_JSON_ValueSerializer_Key);
    };

    bool IsEnded() {
        return m_Value != null;
    };
};

class V30_JSON_ValueSerializer_Stack {
    protected ref array<ref V30_JSON_Value> stack;

    void V30_JSON_ValueSerializer_Stack(int reserve = -1) {
        stack = new array<ref V30_JSON_Value>();
        if (reserve != -1)
            stack.Reserve(reserve);
    };

    void Push(notnull V30_JSON_Value value) {
        stack.Insert(value);
    };

    V30_JSON_Value Pop() {
        auto last = stack.Count() - 1;
        auto value = stack.Get(last);
        stack.RemoveOrdered(last);
        return value;
    };

    V30_JSON_Value Peak() {
        if (stack.IsEmpty())
            return null;
        auto last = stack.Count() - 1;
        return stack.Get(last);
    };

	bool IsEmpty() {
		return stack.IsEmpty();
	};

    int Count() {
        return stack.Count();
    };

    array<ref V30_JSON_Value> Get() {
        return stack;
    };

    V30_JSON_Value Get(int index) {
        return stack.Get(index);
    };

    void Clear() {
        stack.Clear();
    };
};

[Friend(V30_JSON_ValueSerializer)]
class V30_JSON_ValueSerializer_Key : V30_JSON_Value {
    protected string m_Key;

    void V30_JSON_ValueSerializer_Key(string key) {
        m_Key = key;
    };

    string GetKey() {
        return m_Key;
    };
};
