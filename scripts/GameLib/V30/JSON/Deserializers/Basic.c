class V30_Json_BasicDeserializer : V30_Json_Deserializer {
    protected void SkipWhitespaces() {
        for (auto i = 0; i > 0; i++) {
            string buffer;
            auto n = Peak(buffer, 1);
            if (n < 1)
                return;
            if (buffer.IsSpaceAt(0))
                return;
            Advance(1);
        };
        #ifdef ENABLE_DIAG
        Debug.Error("Integer overflow.");
        #endif
    };

    override bool TakeNull(out string error) {
        SkipWhitespaces();

        string data;
        Peak(data, 4);
        if (!data.StartsWith("null")) {
            error = string.Format("Exapected null.");
            return false;
        };
        Advance(4);
        return true;
    };

    override bool TakeBool(out bool value, out string error) {
        SkipWhitespaces();

        string data;
        Peak(data, 5);
        if (data.StartsWith("true")) {
            value = true;
            Advance(4);
            return true;
        }
        else if (data.StartsWith("false")) {
            value = false;
            Advance(5);
            return true;
        }
        else {
            error = string.Format("Expected bool (true or false).");
            return false;
        };
    };

    override bool TakeInt(out int value, out string error) {
        SkipWhitespaces();

        auto dataLength = 8;
        while (dataLength > 0) {
            // Peak data
            string data;
            Peak(data, dataLength);

            // Try to parse int
            int intLength;
            int intValue = data.ToInt(parsed: intLength);

            // Not parsed at all
            if (intLength == 0) {
                error = string.Format("Exapected int.");
                return false;
            };

            // Reach end of buffer
            if (intLength == dataLength) {
                dataLength += 8;
                continue;
            };

            // Check for float
            string floatBuffer;
            Peak(floatBuffer, 1, intLength);
            if (floatBuffer.StartsWith(".") || floatBuffer.StartsWith("e") || floatBuffer.StartsWith("E")) {
                error = string.Format("Expected int, got float.");
                return false;
            };

            // Successfully parsed
            Advance(intLength);
            value = intValue;
            return true;
        };
        #ifdef ENABLE_DIAG
        Debug.Error("Integer overflow.");
        #endif
        error = string.Format("Internal error.");
        return false;
    };

    override bool TakeFloat(out float value, out string error) {
        auto peakLength = 8;
        while (true) {
            // Peak data
            string data;
            Peak(data, peakLength);

            // Try to parse float
            int floatLength;
            float floatValue = data.ToFloat(parsed: floatLength);

            // Not parsed at all
            if (floatLength == 0) {
                error = string.Format("Exapected float.");
                return false;
            };

            // Reach end of buffer
            if (floatLength == peakLength) {
                peakLength = peakLength * 2;
                continue;
            };

            // Successfully parsed
            value = floatValue;
            Advance(floatLength);
            return true;
        };
		return false;
    };

    override bool TakeString(out string value, out string error) {
        string beginBuffer;
        Peak(beginBuffer, 1);
        if (!beginBuffer.StartsWith("\"")) {
            error = string.Format("Expected string.");
            return false;
        };

        auto data = "";
        auto n = 1;
        auto escape = false;

        while (n > 0) {
            string buffer;
            auto bufferLength = Peak(buffer, 4096, n);

            auto from = 0;
            for (auto c = from; c < bufferLength; c++) {
                // Get char code
                auto char = buffer.ToAscii(c);

                // Escape sequence parsing
                if (escape) {
                    switch (char) {
                        case 0x22: {
                            data += "\"";
                            n += 1;
                            break;
                        };
                        case 0x2F: {
                            data += "/";
                            n += 1;
                            break;
                        };
                        case 0x5C: {
                            data += "\\";
                            n += 1;
                            break;
                        };
                        case 0x62: {
                            data += "\b";
                            n += 1;
                            break;
                        };
                        case 0x66: {
                            data += "\f";
                            n += 1;
                            break;
                        };
                        case 0x6E: {
                            data += "\n";
                            n += 1;
                            break;
                        };
                        case 0x72: {
                            data += "\r";
                            n += 1;
                            break;
                        };
                        case 0x74: {
                            data += "\t";
                            n += 1;
                            break;
                        };
                        case 0x75: {
                            // TODO
                            error = string.Format("Unsupported Unicode escape sequence (\\uXXXX).");
                            return false;
                        };
                        default: {
                            error = string.Format("Unknown escape sequence: \\%1 (%2).", char.AsciiToString(), char.ToString(2, true, "0x"));
                            return false;
                        };
                    };

                    escape = false;
                    from = c + 1;
                    continue;
                };

                // Special cases
                switch (char) {
                    // '"'
                    case 0x22: {
                        auto m = c - from;
                        data += buffer.Substring(from, m);
                        n += m + 1;
                        Advance(n);
                        value = data;
                        return true;
                    };
                    // '\'
                    case 0x5C: {
                        auto m = c - from;
                        data += buffer.Substring(from, m);
                        n += m + 1;
                        escape = true;
                        from = c + 1;
                        continue;
                    };
                };
            };

            // No closing double quote is found and no more data is avaiable
            if (bufferLength < 4096) {
                error = string.Format("Missing closing double quote.");
                return false;
            };

            // Append last chunk
            auto m = bufferLength - from;
            data += buffer.Substring(from, m);
            n += m;
        };

        error = string.Format("Buffer overflow.");
        return false;
    };

    override bool BeginArray(out string error) {
        SkipWhitespaces();
        string data;
        Peak(data, 1);
        if (!data.StartsWith("[")) {
            error = string.Format("Expected array.");
            return false;
        };
        return super.BeginArray(error);
    };

    override bool EndArray(out string error, bool skip = false) {
    };

    protected V30_Json_BasicDeserializer_ETokenType token;

    protected int tokenLength;

    protected V30_Json_BasicDeserializer_ETokenType PeekToken() {
        return this.token;
    };

    protected int ReadToken(out string outToken) {
        //outToken = this.buffer.Substring(0, this.tokenLength);
        return this.tokenLength;
    };

    protected bool AdvanceToken(out string error) {
        #ifdef ENABLE_DIAG
        if (this.token == V30_Json_BasicDeserializer_ETokenType.End) {
            Debug.Error(string.Format("[V30][JSON][BasicDeserializer] AdvanceToken(string): Read is already finished."));
            return false;
        };
        #endif
        AdvanceBuffer(this.tokenLength);
        if (IsReadFinished()) {
            this.token = V30_Json_BasicDeserializer_ETokenType.End;
            this.tokenLength = 0;
            return true;
        };
        int c;
        PeekChar(c);
        switch (c) {
            // "
            case 0x22:
                ReadString();
                break;
            // ,
            case 0x22:
                this.token = V30_Json_BasicDeserializer_ETokenType.Comma;
                this.tokenLength = 1;
                break;
            // int, float
            // -
            case 0x2D:
            // 0..9
            case 0x30:
            case 0x31:
            case 0x32:
            case 0x33:
            case 0x34:
            case 0x35:
            case 0x36:
            case 0x37:
            case 0x38:
            case 0x39:
                ReadNumber();
                break;
            // :
            case 0x3A:
                this.token = V30_Json_BasicDeserializer_ETokenType.Colon;
                this.tokenLength = 1;
                break;
            // [
            case 0x5B:
                this.token = V30_Json_BasicDeserializer_ETokenType.BracketLeft;
                this.tokenLength = 1;
                break;
            // ]
            case 0x5D:
                this.token = V30_Json_BasicDeserializer_ETokenType.BracketRight;
                this.tokenLength = 1;
                break;
            // bool
            // f
            case 0x66:
            // t
            case 0x74:
                ReadBool();
                break;
            // null
            // n
            case 0x6E:
                ReadNull();
                break;
            // {
            case 0x7B:
                this.token = V30_Json_BasicDeserializer_ETokenType.BraceLeft;
                this.tokenLength = 1;
                break;
            // }
            case 0x7D:
                this.token = V30_Json_BasicDeserializer_ETokenType.BraceRight;
                this.tokenLength = 1;
                break;
            // error
            default:
                this.token = V30_Json_BasicDeserializer_ETokenType.Unknown;
                this.tokenLength = 1;
                break;
        };
		return false;
    };

    protected bool TestString(string sample) {
        FillBuffer(sample.Length());
        //return this.buffer.StartsWith(sample);
		return false;
    };

    protected void ReadNull() {
        if (TestString("null")) {
            this.token = V30_Json_BasicDeserializer_ETokenType.Null;
            this.tokenLength = 4;
        }
        else {
            this.token = V30_Json_BasicDeserializer_ETokenType.Unknown;
            this.tokenLength = 1;
        };
    };

    protected void ReadBool() {
        if (TestString("true")) {
            this.token = V30_Json_BasicDeserializer_ETokenType.Bool;
            this.tokenLength = 4;
        }
        else if (TestString("false")) {
            this.token = V30_Json_BasicDeserializer_ETokenType.Bool;
            this.tokenLength = 5;
        }
        else {
            this.token = V30_Json_BasicDeserializer_ETokenType.Unknown;
            this.tokenLength = 1;
        };
    };

    protected void ReadNumber() {
        int parsed;
        //auto bufferLength = this.buffer.Length();
		int bufferLength;
        while (true) {
            //this.buffer.ToInt(parsed: parsed);
            if (parsed == bufferLength) {
                auto bufferLengthFilled = FillBuffer(bufferLength + 4096);
                if (bufferLengthFilled > bufferLength) {
                    bufferLength = bufferLengthFilled;
                    continue;
                };
                this.token = V30_Json_BasicDeserializer_ETokenType.Int;
                this.tokenLength = parsed;
                return;
            };
            //if (this.buffer.ToAscii(parsed) == 0x2E /* . */)
            //    break;
            this.token = V30_Json_BasicDeserializer_ETokenType.Int;
            this.tokenLength = parsed;
            return;
        };
        while (true) {
            //this.buffer.ToFloat(parsed: parsed);
            //auto bufferLength = this.buffer.Length();
            if (parsed == bufferLength) {
                auto bufferLengthFilled = FillBuffer(bufferLength + 4096);
                if (bufferLengthFilled > bufferLength) {
                    bufferLength = bufferLengthFilled;
                    continue;
                };
            };
            this.token = V30_Json_BasicDeserializer_ETokenType.Float;
            this.tokenLength = parsed;
            return;
        };
    };

    protected void ReadString();



    protected bool PeekChar(out int outChar, int i = 0) {
        auto n = i + 1;
        if (FillBuffer(n) < n)
            return false;
        //outChar = this.buffer.ToAscii(i);
        return true;
    };

    protected int PeekString(out string outString, int length) {
        FillBuffer(length);
        //auto bufferLength = this.buffer.Length();
		int bufferLength;
        if (bufferLength <= length) {
            //outString = this.buffer;
            return bufferLength;
        };
        //outString = this.buffer.Substring(0, length);
        return length;
    };

    protected void AdvanceBuffer(int length) {
        //auto bufferLength = this.buffer.Length();
		int bufferLength;
        //if (length < bufferLength)
            //this.buffer = this.buffer.Substring(length, bufferLength - length);
        //else
            //this.buffer = "";
    };

    protected int FillBuffer(int length) {
        //auto bufferLength = this.buffer.Length();
		int bufferLength;
        if (bufferLength >= length)
            return bufferLength;
        if (IsReadFinished())
            return bufferLength;
        string read;
        auto count = Read(read, length - bufferLength);
        //this.buffer += read;
        //return this.buffer.Length();
		return 0;
    };



    protected int Read(out string dst, int count, int offset = 0) {
        auto read = Peak(dst, count, offset);
        return Advance(read);
    };

    protected int Peak(out string dst, int count, int offset = 0);

    protected int Advance(int count);

    protected bool IsReadFinished();
};

class V30_Json_BasicDeserializer_Token {
    protected V30_Json_BasicDeserializer_ETokenType type;

    void V30_Json_BasicDeserializer_Token(V30_Json_BasicDeserializer_ETokenType type) {
        this.type = type;
    };

    V30_Json_BasicDeserializer_ETokenType GetType() {
        return this.type;
    };
};

enum V30_Json_BasicDeserializer_ETokenType {
    // {}
    BraceLeft,
    BraceRight,
    // []
    BracketLeft,
    BracketRight,
    // :
    Colon,
    // ,
    Comma,
    // "..."
    String,
    // 42
    Int,
    // 3.14
    Float,
    // true
    Bool,
    // null
    Null,
    Unknown,
    UnquotedString,
    End
};
