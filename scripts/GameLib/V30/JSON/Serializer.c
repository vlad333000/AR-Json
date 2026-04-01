// JSON serializer.
class V30_Json_Serializer : Managed {
	// Serialize `null`.
	void SerializeNull();

	// Serialize boolean value (`true` or `false`).
	void SerializeBool(bool value);

	// Serialize integer value.
	void SerializeInt(int value);

	// Serialize floating point value.
	void SerializeFloat(float value);

	// Serialize string (includes sanitization).
	void SerializeString(string value);

	// Starts serialization of array.
	void SerializeArrayBegin();

	// Ends serialization of array.
	void SerializeArrayEnd();

	// Starts serialization of object (key-value pairs).
	void SerializeObjectBegin();

	// Ends serialization of object (key-value pairs).
	void SerializeObjectEnd();

	// Serialize separator for array or object elements.
	void SerializeComma();

	// Serialize separator for key and value of object element.
	void SerializeColon();
};
