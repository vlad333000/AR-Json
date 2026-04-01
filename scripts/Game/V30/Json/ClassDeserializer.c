class V30_Json_ClassDeserializer {
    bool Deserialize(notnull V30_Json_Value json, out Managed instance, out string error);

    //V30_Json_ClassDeserializer_ArrayHelper BeginArray(notnull V30_Json_Value json);

    //V30_Json_ClassDeserializer_ObjectHelper BeginObject(notnull V30_Json_Value json);
};

// class V30_Json_ClassDeserializer_ArrayHelper {
//     protected ref V30_Json_Array jsonArr;

//     protected void V30_Json_ClassDeserializer_ArrayHelper(notnull V30_Json_Array jsonArr) {
//         this.jsonArr = jsonArr;
//     };

//     V30_Json_ClassDeserializer_ArrayHelper BeginArray(notnull V30_Json_Value json) {
//         if (!json.IsArray())
//             return null;
//         return new V30_Json_ClassDeserializer_ArrayHelper
//     };

//     V30_Json_ClassDeserializer_ObjectHelper BeginObject(notnull V30_Json_Value json);
// };

// class V30_Json_ClassDeserializer_ObjectHelper {
//     protected ref V30_Json_Object object;

//     protected void V30_Json_ClassDeserializer_ObjectHelper(notnull V30_Json_Object object) {
//         this.object = object;
//     };

//     bool Contains(string key) {
//         return this.object.ContainsAt(key);
//     };

//     V30_Json_Value Get(string key) {
//         return this.object.GetAt(key);
//     };

//     bool IsNull(string key) {
//         return this.object.GetAt(key).IsNull();
//     };

//     bool IsBool(string key) {
//         return this.object.GetAt(key).IsBool();
//     };

//     bool GetBool(string key, out bool value, out string error, bool optional = false, bool defaultValue = false) {
//         V30_Json_Value valueJson;
//         if (!this.object.FindAt(key, valueJson)) {
//             if (optional) {
//                 value = defaultValue;
//                 return true;
//             }
//             else {
//                 error = "Key \"" + key + "\" not found.";
//                 return false;
//             };
//         };
//         if (valueJson.IsBool()) {
//             value = valueJson.AsBool().Get();
//             return true;
//         }
//         else if (optional && valueJson.IsNull()) {
//             value = defaultValue;
//             return true;
//         }
//         else {
//             error = string.Format("Key \"%1\" is not a boolean.", key);
//             return false;
//         };
//     };

//     bool IsInt(string key) {
//         return this.object.GetAt(key).IsInt();
//     };

//     bool GetInt(string key, out int value, out string error, bool optional = false, int defaultValue = 0) {
//         V30_Json_Value valueJson;
//         if (!this.object.FindAt(key, valueJson)) {
//             if (optional) {
//                 value = defaultValue;
//                 return true;
//             }
//             else {
//                 error = "Key \"" + key + "\" not found.";
//                 return false;
//             };
//         };
//         if (valueJson.IsInt()) {
//             value = valueJson.AsInt().Get();
//             return true;
//         }
//         else if (optional && valueJson.IsNull()) {
//             value = defaultValue;
//             return true;
//         }
//         else {
//             error = string.Format("Key \"%1\" is not an integer.", key);
//             return false;
//         };
//     };

//     bool IsFloat(string key) {
//         return this.object.GetAt(key).IsFloat();
//     };

//     bool GetFloat(string key, out float value, out string error, bool optional = false, float defaultValue = 0.0) {
//         V30_Json_Value valueJson;
//         if (!this.object.FindAt(key, valueJson)) {
//             if (optional) {
//                 value = defaultValue;
//                 return true;
//             }
//             else {
//                 error = "Key \"" + key + "\" not found.";
//                 return false;
//             };
//         };
//         if (valueJson.IsFloat()) {
//             value = valueJson.AsFloat().Get();
//             return true;
//         }
//         else if (optional && valueJson.IsNull()) {
//             value = defaultValue;
//             return true;
//         }
//         else {
//             error = string.Format("Key \"%1\" is not a float.", key);
//             return false;
//         };
//     };

//     bool IsString(string key) {
//         return this.object.GetAt(key).IsString();
//     };

//     bool GetString(string key, out string value, out string error, bool optional = false, string defaultValue = null) {
//         V30_Json_Value valueJson;
//         if (!this.object.FindAt(key, valueJson)) {
//             if (optional) {
//                 value = defaultValue;
//                 return true;
//             }
//             else {
//                 error = "Key \"" + key + "\" not found.";
//                 return false;
//             };
//         };
//         if (valueJson.IsString()) {
//             value = valueJson.AsString().Get();
//             return true;
//         }
//         else if (optional && valueJson.IsNull()) {
//             value = defaultValue;
//             return true;
//         }
//         else {
//             error = string.Format("Key \"%1\" is not a string.", key);
//             return false;
//         };
//     };

//     bool IsArray(string key) {
//         return this.object.GetAt(key).IsArray();
//     };

//     bool GetArray(string key, out V30_Json_Array value, out string error, bool optional = false, V30_Json_Array defaultValue = null) {
//         V30_Json_Value valueJson;
//         if (!this.object.FindAt(key, valueJson)) {
//             if (optional) {
//                 value = defaultValue;
//                 return true;
//             }
//             else {
//                 error = "Key \"" + key + "\" not found.";
//                 return false;
//             };
//         };
//         if (valueJson.IsArray()) {
//             value = valueJson.AsArray();
//             return true;
//         }
//         else if (optional && valueJson.IsNull()) {
//             value = defaultValue;
//             return true;
//         }
//         else {
//             error = string.Format("Key \"%1\" is not an array.", key);
//             return false;
//         };
//     };

//     bool IsObject(string key) {
//         return this.object.GetAt(key).IsObject();
//     };

//     bool GetObject(string key, out V30_Json_Object value, out string error, bool optional = false, V30_Json_Object defaultValue = null) {
//         V30_Json_Value valueJson;
//         if (!this.object.FindAt(key, valueJson)) {
//             if (optional) {
//                 value = defaultValue;
//                 return true;
//             }
//             else {
//                 error = "Key \"" + key + "\" not found.";
//                 return false;
//             };
//         };
//         if (valueJson.IsObject()) {
//             value = valueJson.AsObject();
//             return true;
//         }
//         else if (optional && valueJson.IsNull()) {
//             value = defaultValue;
//             return true;
//         }
//         else {
//             error = string.Format("Key \"%1\" is not an object.", key);
//             return false;
//         };
//     };

//     bool IsNumber(string key);
// };
