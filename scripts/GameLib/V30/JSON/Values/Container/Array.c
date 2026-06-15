[V30_JSON_ArraySerializerAttribute()]
class V30_JSON_Array : V30_JSON_Container {
    protected ref array<ref V30_JSON_Value> m_Value;

    void V30_JSON_Array(array<ref V30_JSON_Value> value = null) {
        if (value)
            SetValue(value);
        else
            m_Value = new array<ref V30_JSON_Value>();
    };

    override bool IsEmpty() {
        return m_Value.IsEmpty();
    };

    override int Count() {
        return m_Value.Count();
    };

    bool IsIndexValid(int index) {
        return m_Value.IsIndexValid(index);
    };

    int Insert(notnull V30_JSON_Value newValue) {
        return m_Value.Insert(newValue);
    };

    V30_JSON_Value Remove(int index) {
        if (!m_Value.IsIndexValid(index))
            return null;
        auto value = m_Value.Get(index);
        m_Value.RemoveOrdered(index);
        return value;
    };

    V30_JSON_Value Get(int index) {
        if (!m_Value.IsIndexValid(index))
            return null;
        return m_Value.Get(index);
    };

    array<ref V30_JSON_Value> GetValue() {
        return m_Value;
    };

    void SetValue(array<ref V30_JSON_Value> newValue) {
        m_Value = newValue;
    };
};

class V30_JSON_ArraySerializerAttribute : V30_JSON_StreamSerializerAttribute {
    override void StreamSerialize(notnull V30_JSON_StreamSerializer serializer, Class instance) {
        serializer.BeginArraySerialization();
            foreach (auto value : V30_JSON_Array.Cast(instance).GetValue())
                serializer.Serialize(value);
        serializer.EndArraySerialization();
    };

    override void SerializeArray(notnull V30_JSON_Serializer serializer, notnull Managed arr) {
        V30_JSON_SerializerAttributeHelperT<V30_JSON_Array>.SerializeArray(serializer, arr);
    };

    override void SerializeArrayRef(notnull V30_JSON_Serializer serializer, notnull Managed arr) {
        V30_JSON_SerializerAttributeHelperRefT<V30_JSON_Array>.SerializeArray(serializer, arr);
    };

    override void SerializeObject(notnull V30_JSON_Serializer serializer, notnull Managed obj) {
        V30_JSON_SerializerAttributeHelperT<V30_JSON_Array>.SerializeObject(serializer, obj);
    };

    override void SerializeObjectRef(notnull V30_JSON_Serializer serializer, notnull Managed obj) {
        V30_JSON_SerializerAttributeHelperRefT<V30_JSON_Array>.SerializeObject(serializer, obj);
    };
};
