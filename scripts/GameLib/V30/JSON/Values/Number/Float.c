class V30_JSON_Float : V30_JSON_Number {
    protected float value;

    void V30_JSON_Float(float value = 0.0) {
        SetValue(value);
    };

    float GetValue() {
        return this.value;
    };

    void SetValue(float value) {
        this.value = value;
    };
};
