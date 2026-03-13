// TODO: Implement
class V30_Json_BasicPrettySerializer : V30_Json_BasicSerializer {
    protected int tabSpaceCount;

    protected int tabLevel;

    // param `tabSpaceCount` - `-1` to use tabs and values greater or equal to zero for spaces.
	void V30_Json_BasicPrettySerializer(int tabSpaceCount = -1);

    int GetTabSpaceCount() {
        return this.tabSpaceCount;
    };

    bool IsTabSpaces() {
        return this.tabSpaceCount >= 0;
    };

    int GetTabLevel() {
        return this.tabLevel;
    };

    void PutLineComment(string comment);

    protected void WriteIntend() {
        if (IsTabSpaces())
            for (auto i = 0; i < this.tabLevel; i++)
                for (auto j = 0; j < this.tabSpaceCount; j++)
                    Write(" ");
        else
            for (auto i = 0; i < this.tabLevel; i++)
                Write("\t");
    };
};

enum V30_Json_PrettySerializer_EContainerFormat {
    // [1, 2, ...] or { "a": 1, "b": 2, ... }
    SingleLine,
    // [\n1,\n2\n...] or {\n"a": 1,\n"b": 2,\n...}
    MultiLine
};
