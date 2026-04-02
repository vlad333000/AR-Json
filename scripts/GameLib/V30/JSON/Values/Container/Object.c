class V30_JSON_Object : V30_JSON_Container {
    protected ref map<string, ref V30_JSON_Value> value;

    void V30_JSON_Object(map<string, ref V30_JSON_Value> value = null) {
        if (value)
            this.value = value;
        else
            this.value = new map<string, ref V30_JSON_Value>();
    };

    int Count() {
        return this.value.Count();
    };

    string GetKey(int index) {
        return this.value.GetKey(index);
    };

    bool Contains(string key) {
        return this.value.Contains(key);
    };

    bool Insert(string key, notnull V30_JSON_Value value) {
        return this.value.Insert(key, value);
    };

    void Set(string key, notnull V30_JSON_Value value) {
        this.value.Set(key, value);
    };

    V30_JSON_Value Remove(string key) {
        V30_JSON_Value value;
        if (!this.value.Take(key, value))
            return null;
        return value;
    };

    V30_JSON_Value Get(string key) {
        V30_JSON_Value value;
        if (!this.value.Find(key, value))
            return null;
        return value;
    };

    bool Find(string key, out V30_JSON_Value value) {
        return this.value.Find(key, value);
    };

    map<string, ref V30_JSON_Value> GetValue();

    void SetValue(map<string, ref V30_JSON_Value> value);
};
