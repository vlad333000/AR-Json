class V30_JSON_Bool : V30_JSON_Value {
    protected bool value;

    void V30_JSON_Bool(bool value = false) {
        SetValue(value);
    };

    bool GetValue() {
        return this.value;
    };

    void SetValue(bool value) {
        this.value = value;
    };
};
