// class V30_Json_Example1_MyStruct {
//     int x;
//     int y;
//     int z;

//     void V30_Json_Example1_MyStruct(int x, int y, int z) {
//         this.x = x;
//         this.y = y;
//         this.z = z;
//     };
// };

// class V30_Json_Example1_MyStructSerializer : V30_Json_ClassSerializer {
//     override bool Serialize(notnull Managed instance, out V30_Json_Value outValue, out string error) {
//         auto myStruct = V30_Json_Example1_MyStruct.Cast(instance);
//         auto myStructObj = BeginObject();
//         myStructObj.Insert("x", myStruct.x);
//         myStructObj.Insert("y", myStruct.y);
//         myStructObj.Insert("z", myStruct.z);
//         outValue = myStructObj.End();
//         return true;
//     };
// };

// class V30_Json_Example1_MyStructDeserializer : V30_Json_ClassDeserializer {
//     override bool Deserialize(notnull V30_Json_Value json, out Managed instance, out string error) {
//         auto object = BeginObject(json, error);
//         if (!object) return false;

//         int x, y, z;
//         if (!object.Get("x", x, error)) return false;
//         if (!object.Get("y", y, error)) return false;
//         if (!object.Get("z", z, error)) return false;

//         instance = new V30_Json_Example1_MyStruct(x, y, z);
//         return true;
//     };
// };

// class V30_Json_Example1_TestSuite : SCR_AutotestSuiteBase {};

// [Test("V30_Json_Example1_TestSuite")]
// TestResultBase V30_Json_Example1_Test() {
//     auto x = 123; auto y = 456; auto z = 789;
//     auto myStruct = new V30_Json_Example1_MyStruct(x, y, z);

//     auto serializer = new V30_Json_Example1_MyStructSerializer();
//     V30_Json_Value myStructJson;
//     string myStructJsonError;
//     if (!serializer.Serialize(myStruct, myStructJson, myStructJsonError))
//         return SCR_AutotestResult.AsFailure("Failed to serialize MyStruct: %1.", error);

//     if (!myStructJson.IsObject())
//         return SCR_AutotestResult.AsFailure("MyStruct is not serialized to object: %1.", myStructJson);
//     auto myStructObject = myStructJson.AsObject();
//     auto values = new map<string, int>(); keys.Insert("x", x); keys.Insert("y", y); keys.Insert("z", z);
//     foreach (auto key, auto value : values) {
//         if (!myStructObject.ContainsAt(key))
//             return SCR_AutotestResult.AsFailure("MyStruct.%1 is not serialized.", key);
//         if (!myStructObject.GetAt(key).IsInt())
//             return SCR_AutotestResult.AsFailure("MyStruct.%1 is not serialized to int: %2.", key, myStructObject.GetAt(key));
//         if (!myStructObject.GetAt(key).AsInt().Get() != value)
//             return SCR_AutotestResult.AsFailure("MyStruct.%1 is serialized to wrong value: expected %2, got %2.", key, myStructObject.GetAt(key));
//     };

//     // auto serializer = new V30_Json_Example1_MyStructSerializer();
//     // auto xJson = new V30_Json_Int(123);
//     // auto yJson = new V30_Json_Int(456);
//     // auto zJson = new V30_Json_Int(789);
//     // auto myStructMap = new map<string, ref V30_Json_Value>();
//     // myStructMap.Insert("x", xJson);
//     // myStructMap.Insert("y", yJson);
//     // myStructMap.Insert("z", zJson);
//     // auto myStructJson = new V30_Json_Object(myStructMap);

//     // V30_Json_Example1_MyStruct myStruct;
//     // string error;
//     // if (!V30_Json_SerializationHelperT<V30_Json_Example1_MyStruct>.Deserialize(serializer, myStructJson, myStruct, error))
//     //     return SCR_AutotestResult.AsFailure(error);
// 	// else
// 	// 	Print("Deserialize success!");
//     // if (!myStruct.x == 123)
//     //     return SCR_AutotestResult.AsFailure(string.Format("X is expected to be 123, got %2.", myStruct.x));
//     // if (!myStruct.y == 456)
//     //     return SCR_AutotestResult.AsFailure(string.Format("Y is expected to be 456, got %2.", myStruct.y));
//     // if (!myStruct.z == 789)
//     //     return SCR_AutotestResult.AsFailure(string.Format("Z is expected to be 789, got %2.", myStruct.z));
//     // return SCR_AutotestResult.AsSuccess();
// };
