class V30_JSON_StreamSerializerAttribute : V30_JSON_SerializerAttribute {
    /*modded*/ void StreamSerialize(notnull V30_JSON_StreamSerializer serializer, Class instance);

    override void Serialize(notnull V30_JSON_Serializer serializer, Class instance) {
        auto streamSerializer = V30_JSON_StreamSerializer.Cast(serializer);
        if (!streamSerializer) {
            auto valueSerializer = new V30_JSON_ValueSerializer();
            StreamSerialize(valueSerializer, instance);
            auto value = valueSerializer.GetValue();
            serializer.Serialize(value);
            return;
        };
        StreamSerialize(streamSerializer, instance);
    };

    /*modded*/ void StreamDeserialize(out Class instance, notnull V30_JSON_StreamDeserializer deserializer);

	override void Deserialize(out Class instance, notnull V30_JSON_Deserializer deserializer) {
		auto streamDeserializer = V30_JSON_StreamDeserializer.Cast(deserializer);
		if (!streamDeserializer)
			Debug.Error("TODO: need V30_JSON_ValueDeserializer");
		StreamDeserialize(instance, streamDeserializer);
	};
};
