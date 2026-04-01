class V30_Json_ClassSerializer {
    bool Serialize(notnull Managed instance, out V30_Json_Value outValue, out string error) {
        error = string.Format("Type \"%1\" can't be serialized.", Type());
        return false;
    };

    bool Deserialize(bool value, out Managed instance, out string error) {
        error = string.Format("Type \"%1\" can't be deserialized from bool.", Type());
        return false;
    };

    bool Deserialize(int value, out Managed instance, out string error) {
        error = string.Format("Type \"%1\" can't be deserialized from int.", Type());
        return false;
    };

    bool Deserialize(float value, out Managed instance, out string error) {
        error = string.Format("Type \"%1\" can't be deserialized from float.", Type());
        return false;
    };

    bool Deserialize(string value, out Managed instance, out string error) {
        error = string.Format("Type \"%1\" can't be deserialized from string.", Type());
        return false;
    };

    bool Deserialize(notnull array<ref V30_Json_Value> value, out Managed instance, out string error) {
        error = string.Format("Type \"%1\" can't be deserialized from array.", Type());
        return false;
    };

    bool Deserialize(notnull map<string, ref V30_Json_Value> value, out Managed instance, out string error) {
        error = string.Format("Type \"%1\" can't be deserialized from object.", Type());
        return false;
    };



    // Utility
    V30_Json_ArraySerializationHelper BeginArray() {
        return V30_Json_ArraySerializationHelper.Begin();
    };

    V30_Json_ObjectSerializationHelper BeginObject() {
        return V30_Json_ObjectSerializationHelper.Begin();
    };
};

class V30_Json_ArraySerializationHelper {
    protected ref array<ref V30_Json_Value> values;

    static V30_Json_ArraySerializationHelper Begin();

    V30_Json_ArraySerializationHelper Insert() {
        values.Insert(new V30_Json_Null());
        return this;
    };

    V30_Json_ArraySerializationHelper Insert(bool value) {
        values.Insert(new V30_Json_bool(value));
        return this;
    };

    V30_Json_ArraySerializationHelper Insert(int value) {
        values.Insert(new V30_Json_Int(value));
        return this;
    };

    V30_Json_ArraySerializationHelper Insert(float value) {
        values.Insert(new V30_Json_Float(value));
        return this;
    };

    V30_Json_ArraySerializationHelper Insert(string value) {
        values.Insert(new V30_Json_String(value));
        return this;
    };

    V30_Json_ArraySerializationHelper Insert(notnull V30_Json_Array value) {
        values.Insert(value);
        return this;
    };

    V30_Json_ArraySerializationHelper Insert(notnull V30_Json_Object value) {
        values.Insert(value);
        return this;
    };

    V30_Json_Array End() {
        return new V30_Json_Array(values);
    };
};

class V30_Json_ObjectSerializationHelper {
    protected ref map<string, ref V30_Json_Value> values;

    static V30_Json_ObjectSerializationHelper Begin();

    V30_Json_ObjectSerializationHelper Insert(string key) {
        values.Insert(key, new V30_Json_Null());
        return this;
    };

    V30_Json_ObjectSerializationHelper Insert(string key, bool value) {
        values.Insert(key, new V30_Json_bool(value));
        return this;
    };

    V30_Json_ObjectSerializationHelper Insert(string key, int value) {
        values.Insert(key, new V30_Json_Int(value));
        return this;
    };

    V30_Json_ObjectSerializationHelper Insert(string key, float value) {
        values.Insert(key, new V30_Json_Float(value));
        return this;
    };

    V30_Json_ObjectSerializationHelper Insert(string key, string value) {
        values.Insert(key, new V30_Json_String(value));
        return this;
    };

    V30_Json_ObjectSerializationHelper Insert(string key, notnull V30_Json_Array value) {
        values.Insert(key, value);
        return this;
    };

    V30_Json_ObjectSerializationHelper Insert(string key, notnull V30_Json_Object value) {
        values.Insert(key, value);
        return this;
    };

    V30_Json_Object End() {
        return new V30_Json_Object(values);
    };
};
