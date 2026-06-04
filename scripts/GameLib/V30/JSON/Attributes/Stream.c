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
};
