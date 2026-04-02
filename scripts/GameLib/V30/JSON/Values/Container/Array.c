class V30_JSON_Array : V30_JSON_Container {
    protected ref array<ref V30_JSON_Value> value;

    void V30_JSON_Array(array<ref V30_JSON_Value> value = null) {
        if (value)
            this.value = value;
        else
            this.value = new array<ref V30_JSON_Value>();
    };

    int Count() {
        return this.value.Count();
    };

    bool IsIndexValid(int index) {
        return this.value.IsIndexValid(index);
    };

    int Insert(notnull V30_JSON_Value value) {
        return this.value.Insert(value);
    };

    V30_JSON_Value Remove(int index) {
        if (!this.value.IsIndexValid(index))
            return null;
        auto value = this.value.Get(index);
        this.value.RemoveOrdered(index);
        return value;
    };

    V30_JSON_Value Get(int index) {
        if (!this.value.IsIndexValid(index))
            return null;
        return this.value.Get(index);
    };

    array<ref V30_JSON_Value> GetValue() {
        return this.value;
    };

    void SetValue(array<ref V30_JSON_Value> value) {
        this.value = value;
    };
};
