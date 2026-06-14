class V30_JSON_Deserializer {
    protected bool m_InProcess;

    void V30_JSON_Deserializer() {
        m_InProcess = false;
    };

    void ~V30_JSON_Deserializer() {
        if (m_InProcess)
            if (!EndDeserialization()) {
                Error("failed to end deserialization in destructor");
                return;
            };
    };

    // Deserialize JSON value.
    bool Deserialize(out V30_JSON_Value value) {
        auto visitor = new V30_JSON_SimpleDeserializerVisitor();
        if (!Visit(visitor))
            return false;
        value = visitor.GetValue();
        return true;
    };

    // Deserialize null value.
    bool DeserializeNull();

    // Deserialize boolean value.
    bool DeserializeBool(out bool value);

    // Deserialize integer value.
    bool DeserializeInt(out int value);

    // Deserialize floating point value.
    bool DeserializeFloat(out float value);

    // Deserialize string value.
    bool DeserializeString(out string value);

    // Deserialzie array value.
    bool DeserializeArray(out V30_JSON_Array value) {
        auto visitor = new V30_JSON_SimpleDeserializerArrayVisitor();
        if (!ForEachArray(visitor))
            return false;
        value = visitor.GetArray();
        return true;
    };

    // Deserialize object value.
    bool DeserializeObject(out V30_JSON_Object value) {
        auto visitor = new V30_JSON_SimpleDeserializerObjectVisitor();
        if (!ForEachObject(visitor))
            return false;
        value = visitor.GetObject();
        return true;
    };

    // Deserialize object key.
    bool DeserializeKey(out string key) {
        return DeserializeString(key);
    };

    // // Deserialize class instance (Custom deserializer must be defined for type).
    // bool DeserializeClass(typename type, out Class value);


    // Begins deserialization (allocates resources and etc.)
    protected bool BeginDeserialization() {
        if (m_InProcess)
            if (!EndDeserialization())
                return Error("failed begin deserialization, because previous deserialization not ended properly");
        m_InProcess = true;
        return true;
    };

    // Ends deserialization (free resources, check for data after end and etc.)
    bool EndDeserialization() {
        if (!m_InProcess)
            return Error("deserialization not in process");
        m_InProcess = false;
        return true;
    };

    // Checks if deserialization in process.
    bool IsDeserializationInProcess() {
        return m_InProcess;
    };



    // Checks if value is null.
    bool IsNull();

    // Checks if value is boolean.
    bool IsBool();

    // Checks if value is number (integer or floating point value).
    bool IsNumber();

    // Checks if value is intger value.
    bool IsInt();

    // Checks if value is floating point value.
    bool IsFloat();

    // Checks if value is string value.
    bool IsString();

    // Checks if value is container (array or object (key-value pairs)).
    bool IsContainer();

    // Checks if value is an array.
    bool IsArray();

    // Checks if value is an object (key-value pairs).
    bool IsObject();

    // Checks if next value is object's key-value pair.
    bool IsKey();

    // Returns type of value.
    typename GetJsonType();



    bool Visit(notnull V30_JSON_DeserializerVisitor visitor) {
        auto jsonType = GetJsonType();
        switch (jsonType) {
            case V30_JSON_Null:
                return visitor.OnNull(this);
            case V30_JSON_Bool:
                return visitor.OnBool(this);
            case V30_JSON_Int:
                return visitor.OnInt(this);
            case V30_JSON_Float:
                return visitor.OnFloat(this);
            case V30_JSON_String:
                return visitor.OnString(this);
            case V30_JSON_Array:
                return visitor.OnArray(this);
            case V30_JSON_Object:
                return visitor.OnObject(this);
            default:
                return ErrorFormat("Unsupported JSON type: %1", jsonType.ToString());
        };
        return Error("Unreachable code reached");
    };

    // Iterate over array elements.
    bool ForEachArray(notnull V30_JSON_DeserializerArrayVisitor visitor);

    // Iterate over object (key-value pairs) elements.
    bool ForEachObject(notnull V30_JSON_DeserializerObjectVisitor visitor);



    // Helper function that generates error message and returns false to indicate that error occured.
    protected bool Error(string message = "internal error") {
        #ifdef ENABLE_DIAG
        Debug.Error(message);
        #else
        PrintFormat("[V30][JSON] Deserializer: %1.", message, level: LogLevel.ERROR);
        #endif
        return false;
    };

    // Helper function that generates error message with format and returns false to indicate that error occured.
    protected bool ErrorFormat(string format, string param1 = "", string param2 = "", string param3 = "", string param4 = "", string param5 = "", string param6 = "", string param7 = "", string param8 = "", string param9 = "") {
		auto message = string.Format(format, param1, param2, param3, param4, param5, param6, param7, param8, param9);
        return Error(message);
    };
};

class V30_JSON_DeserializerVisitor : Managed {
    bool OnNull(notnull V30_JSON_Deserializer deserializer) {
        return Error("value can't be null");
    };

    bool OnBool(notnull V30_JSON_Deserializer deserializer) {
        return Error("can't be boolean");
    };

    bool OnInt(notnull V30_JSON_Deserializer deserializer) {
        return Error("can't be integer");
    };

    bool OnFloat(notnull V30_JSON_Deserializer deserializer) {
        return Error("can't be floating point");
    };

    bool OnString(notnull V30_JSON_Deserializer deserializer) {
        return Error("can't be string");
    };

    bool OnArray(notnull V30_JSON_Deserializer deserializer) {
        return Error("can't be array");
    };

    bool OnObject(notnull V30_JSON_Deserializer deserializer) {
        return Error("can't be object (key-value pairs)");
    };

    protected bool Error(string message) {
        #ifdef ENABLE_DIAG
        Debug.Error(message);
        #else
        PrintFormat("[V30][JSON] %1: %2.", Type().ToString(), message, level: LogLevel.ERROR);
        #endif
        return false;
    };

    protected bool ErrorFormat(string format, string param1 = "", string param2 = "", string param3 = "", string param4 = "", string param5 = "", string param6 = "", string param7 = "", string param8 = "", string param9 = "") {
        auto message = string.Format(format, param1, param2, param3, param4, param5, param6, param7, param8, param9);
        return Error(message);
    };
};

class V30_JSON_DeserializerArrayVisitor : Managed {
    bool OnBegin(notnull V30_JSON_Deserializer deserializer);

    bool OnElement(notnull V30_JSON_Deserializer deserializer);

    bool OnEnd(notnull V30_JSON_Deserializer deserializer);

    protected bool Error(string message) {
        #ifdef ENABLE_DIAG
        Debug.Error(message);
        #else
        PrintFormat("[V30][JSON] %1: %2.", Type().ToString(), message, level: LogLevel.ERROR);
        #endif
        return false;
    };

    protected bool ErrorFormat(string format, string param1 = "", string param2 = "", string param3 = "", string param4 = "", string param5 = "", string param6 = "", string param7 = "", string param8 = "", string param9 = "") {
        auto message = string.Format(format, param1, param2, param3, param4, param5, param6, param7, param8, param9);
        return Error(message);
    };
};

class V30_JSON_WrapperDeserializerArrayVisitor : V30_JSON_DeserializerArrayVisitor {
    protected ref V30_JSON_DeserializerVisitor m_ElementVisitor;

    void V30_JSON_WrapperDeserializerArrayVisitor(notnull V30_JSON_DeserializerVisitor elementVisitor) {
        m_ElementVisitor = elementVisitor;
    };

    override bool OnElement(notnull V30_JSON_Deserializer deserializer) {
        return deserializer.Visit(m_ElementVisitor);
    };
};

class V30_JSON_DeserializerObjectVisitor : Managed {
    bool OnBegin(notnull V30_JSON_Deserializer deserializer);

    bool OnElement(notnull V30_JSON_Deserializer deserializer, string key);

    bool OnEnd(notnull V30_JSON_Deserializer deserializer);

    protected bool Error(string message) {
        #ifdef ENABLE_DIAG
        Debug.Error(message);
        #else
        PrintFormat("[V30][JSON] %1: %2.", Type().ToString(), message, level: LogLevel.ERROR);
        #endif
        return false;
    };

    protected bool ErrorFormat(string format, string param1 = "", string param2 = "", string param3 = "", string param4 = "", string param5 = "", string param6 = "", string param7 = "", string param8 = "", string param9 = "") {
        auto message = string.Format(format, param1, param2, param3, param4, param5, param6, param7, param8, param9);
        return Error(message);
    };
};

class V30_JSON_WrapperDeserializerObjectVisitor : V30_JSON_DeserializerObjectVisitor {
    protected ref V30_JSON_DeserializerVisitor m_ElementVisitor;

    void V30_JSON_WrapperDeserializerObjectVisitor(notnull V30_JSON_DeserializerVisitor elementVisitor) {
        m_ElementVisitor = elementVisitor;
    };

    override bool OnElement(notnull V30_JSON_Deserializer deserializer, string key) {
        return deserializer.Visit(m_ElementVisitor);
    };
};

class V30_JSON_SimpleDeserializerVisitor : V30_JSON_DeserializerVisitor {
    protected ref V30_JSON_Value m_JsonValue;

    void V30_JSON_SimpleDeserializerVisitor() {
        m_JsonValue = null;
    };

    V30_JSON_Value GetValue() {
        return m_JsonValue;
    };

    override bool OnNull(notnull V30_JSON_Deserializer deserializer) {
        if (!deserializer.DeserializeNull())
            return false;
        m_JsonValue = V30_JSON_Null.GetInstance();
        return true;
    };

    override bool OnBool(notnull V30_JSON_Deserializer deserializer) {
        bool value;
        if (!deserializer.DeserializeBool(value))
            return false;
        m_JsonValue = new V30_JSON_Bool(value);
        return true;
    };

    override bool OnInt(notnull V30_JSON_Deserializer deserializer) {
        int value;
        if (!deserializer.DeserializeInt(value))
            return false;
        m_JsonValue = new V30_JSON_Int(value);
        return true;
    };

    override bool OnFloat(notnull V30_JSON_Deserializer deserializer) {
        float value;
        if (!deserializer.DeserializeFloat(value))
            return false;
        m_JsonValue = new V30_JSON_Float(value);
        return true;
    };

    override bool OnString(notnull V30_JSON_Deserializer deserializer) {
        string value;
        if (!deserializer.DeserializeString(value))
            return false;
        m_JsonValue = new V30_JSON_String(value);
        return true;
    };

    override bool OnArray(notnull V30_JSON_Deserializer deserializer) {
        auto arrayVisitor = new V30_JSON_SimpleDeserializerArrayVisitor();
        if (!deserializer.ForEachArray(arrayVisitor))
            return false;
        m_JsonValue = arrayVisitor.GetArray();
        return true;
    };

    override bool OnObject(notnull V30_JSON_Deserializer deserializer) {
        auto objectVisitor = new V30_JSON_SimpleDeserializerObjectVisitor();
        if (!deserializer.ForEachObject(objectVisitor))
            return false;
        m_JsonValue = objectVisitor.GetObject();
        return true;
    };
};

class V30_JSON_SimpleDeserializerArrayVisitor : V30_JSON_DeserializerArrayVisitor {
    protected ref V30_JSON_Array m_JsonArray;

    void V30_JSON_SimpleDeserializerArrayVisitor() {
        m_JsonArray = null;
    };

    V30_JSON_Array GetArray() {
        return m_JsonArray;
    };

    override bool OnBegin(notnull V30_JSON_Deserializer deserializer) {
        m_JsonArray = new V30_JSON_Array();
        return true;
    };

    override bool OnElement(notnull V30_JSON_Deserializer deserializer) {
        V30_JSON_Value jsonValue;
        if (!deserializer.Deserialize(jsonValue))
            return false;
        m_JsonArray.Insert(jsonValue);
        return true;
    };

    override bool OnEnd(notnull V30_JSON_Deserializer deserializer) {
        return true;
    };
};

class V30_JSON_SimpleDeserializerObjectVisitor : V30_JSON_DeserializerObjectVisitor {
    protected ref V30_JSON_Object m_JsonObject;

    V30_JSON_Object GetObject() {
        return m_JsonObject;
    };

    override bool OnBegin(notnull V30_JSON_Deserializer deserializer) {
        m_JsonObject = new V30_JSON_Object();
        return true;
    };

    override bool OnElement(notnull V30_JSON_Deserializer deserializer, string key) {
        V30_JSON_Value jsonValue;
        if (!deserializer.Deserialize(jsonValue))
            return false;
        if (!m_JsonObject.Insert(key, jsonValue))
            return ErrorFormat("duplicated key \"%1\"", key);
        return true;
    };

    override bool OnEnd(notnull V30_JSON_Deserializer deserializer) {
        return true;
    };
};
