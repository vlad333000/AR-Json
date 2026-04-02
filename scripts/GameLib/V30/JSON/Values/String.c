class V30_JSON_String : V30_JSON_Value {
    protected string value;

    void V30_JSON_String(string value = "") {
        SetValue(value);
    };

    int Length() {
        return this.value.Length();
    };

    string GetValue() {
        return this.value;
    };

    void SetValue(string value) {
        this.value = value;
    };
};
