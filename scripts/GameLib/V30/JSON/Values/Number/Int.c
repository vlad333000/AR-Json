class V30_JSON_Int : V30_JSON_Number {
    protected int value;

    void V30_JSON_Int(int value = 0) {
        SetValue(value);
    };

    int GetValue() {
        return this.value;
    };

    void SetValue(int value) {
        this.value = value;
    };
};
