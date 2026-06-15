[V30_JSON_ObjectSerializerAttribute()]
class V30_JSON_Object : V30_JSON_Container {
    protected ref map<string, ref V30_JSON_Value> m_Value;

    void V30_JSON_Object(map<string, ref V30_JSON_Value> value = null) {
        if (value)
            SetValue(value);
        else
            m_Value = new map<string, ref V30_JSON_Value>();
    };

    override bool IsEmpty() {
        return m_Value.IsEmpty();
    };

    override int Count() {
        return m_Value.Count();
    };

    string GetKey(int index) {
        return m_Value.GetKey(index);
    };

    bool Contains(string key) {
        return m_Value.Contains(key);
    };

    bool Insert(string key, notnull V30_JSON_Value newValue) {
        return m_Value.Insert(key, newValue);
    };

    void Set(string key, notnull V30_JSON_Value newValue) {
        m_Value.Set(key, newValue);
    };

    V30_JSON_Value Remove(string key) {
        V30_JSON_Value value;
        if (!m_Value.Take(key, value))
            return null;
        return value;
    };

    V30_JSON_Value Get(string key) {
        V30_JSON_Value value;
        if (!m_Value.Find(key, value))
            return null;
        return value;
    };

    bool Find(string key, out V30_JSON_Value outValue) {
        return m_Value.Find(key, outValue);
    };

    map<string, ref V30_JSON_Value> GetValue() {
		return m_Value;
	};

    void SetValue(map<string, ref V30_JSON_Value> newValue) {
		m_Value = newValue;
	};
};

class V30_JSON_ObjectSerializerAttribute : V30_JSON_StreamSerializerAttribute {
    override void StreamSerialize(notnull V30_JSON_StreamSerializer serializer, Class instance) {
        serializer.BeginObjectSerialization();
            foreach (auto key, auto value : V30_JSON_Object.Cast(instance).GetValue())
                V30_JSON_SerializerHelper.SerializePair(serializer, key, value);
        serializer.EndObjectSerialization();
    };

    override void SerializeArray(notnull V30_JSON_Serializer serializer, notnull Managed arr) {
        V30_JSON_SerializerAttributeHelperT<V30_JSON_Object>.SerializeArray(serializer, arr);
    };

    override void SerializeArrayRef(notnull V30_JSON_Serializer serializer, notnull Managed arr) {
        V30_JSON_SerializerAttributeHelperRefT<V30_JSON_Object>.SerializeArray(serializer, arr);
    };

    override void SerializeObject(notnull V30_JSON_Serializer serializer, notnull Managed obj) {
        V30_JSON_SerializerAttributeHelperT<V30_JSON_Object>.SerializeObject(serializer, obj);
    };

    override void SerializeObjectRef(notnull V30_JSON_Serializer serializer, notnull Managed obj) {
        V30_JSON_SerializerAttributeHelperRefT<V30_JSON_Object>.SerializeObject(serializer, obj);
    };
};
