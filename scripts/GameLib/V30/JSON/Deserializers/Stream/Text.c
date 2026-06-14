class V30_JSON_TextDeserializer : V30_JSON_StreamDeserializer {
    protected int m_Line;

    protected int m_Column;

    protected bool m_Comma;

    protected void V30_JSON_TextDeserializer() {
        m_Line = 1;
        m_Column = 1;
        m_Comma = false;
    };



    // Tells current position in text.
    void TellPos(out int line, out int column) {
        line = m_Line;
        column = m_Column;
    };

    // Tells current line in text.
    int TellLine() {
        return m_Line;
    };

    // Tells current column in text.
    int TellColumn() {
        return m_Column;
    };

    // Increase line counter.
    protected void NextLine() {
        m_Line++;
        m_Column = 1;
    };

    // Increase column counter.
    protected void NextColumn() {
        m_Column++;
    };

    // Advance column.
    protected void AdvanceColumn(int count) {
        m_Column += count;
    };

    override protected bool BeginDeserialization() {
        if (!super.BeginDeserialization())
            return false;
        m_Line = 1;
        m_Column = 1;
        m_Comma = false;
        return true;
    };

    override bool EndDeserialization() {
        SkipWhitespaces();
        return super.EndDeserialization();
    };



    // Peaks next character.
    protected bool PeakChar(out string char);

    // Peaks character at current position + `at`.
    protected bool PeakCharAt(out string char, int at);

    // Peaks char code for next character.
    protected bool PeakAscii(out int ascii);

    // Peaks char code for character at current position + `at`.
    protected bool PeakAsciiAt(out int ascii, int at);

    // Peaks string up to `count` characters.
    protected int PeakString(out string outData, int count);

    // Peaks string at current position + `from` and up to `count` characters.
    protected int PeakStringFrom(out string outData, int from, int count);

    // Reads next character.
    protected bool ReadChar(out string char) {
        if (!PeakChar(char))
            return false;
        #ifndef ENABLE_DIAG
        Next();
        #else
        if (!Next())
            return Error();
        #endif
        return true;
    };

    // Reads character at current position + `at`.
    protected bool ReadCharAt(out string char, int at) {
        #ifdef ENABLE_DIAG
        if (at < 0)
            return Error("in `ReadCharAt` method `at` argument can't be lower then `0`");
        #endif
        auto advanced = Advance(at);
        if (advanced < at)
            return false;
        return ReadChar(char);
    };

    // Reads char code for next character.
    protected bool ReadAscii(out int ascii) {
        string char;
        if (!ReadChar(char))
            return false;
        ascii = char.ToAscii();
        return true;
    };

    // Reads char code for character at current position + `at`.
    protected bool ReadAsciiAt(out int ascii, int at) {
        #ifdef ENABLE_DIAG
        if (at < 0)
            return Error("in `ReadAsciiAt` method `at` argument can't be lower then `0`");
        #endif
        auto advanced = Advance(at);
        if (advanced < at)
            return false;
        return ReadAscii(ascii);
    };

    // Reads string up to `count` characters.
    protected int ReadString(out string outData, int count) {
        auto peaked = PeakString(outData, count);
        #ifndef ENABLE_DIAG
        Advance(peaked);
        #else
        auto advanced = Advance(peaked);
        if (advanced < peaked)
            return Error();
        #endif
        return peaked;
    };

    // Reads string at current position + `from` and up to `count` characters.
    protected int ReadStringFrom(out string outData, int from, int count) {
        #ifdef ENABLE_DIAG
        if (from < 0)
            return Error("in `ReadStringFrom` method `from` argument can't be lower then `0`");
        #endif
        auto advanced = Advance(from);
        if (advanced < from)
            return false;
        return ReadString(outData, count);
    };

    // Checks if current position + `at` is end of stream.
    protected bool IsEndAt(int at);

    protected bool IsBorderAt(int at) {
        if (IsEndAt(at))
            return true;
        string char;
        if (!PeakCharAt(char, at))
            return false;
        auto ascii = char.ToAscii();
        auto isAscii = ascii >= 0;
        auto isUnderscore = char == "_";
        auto isDigit = char.IsDigitAt(0);
        auto isAlphaLC = ascii >= 97 /*a*/ && ascii <= 122 /*z*/;
        auto isAlphaUP = ascii >= 65 /*A*/ && ascii <= 90 /*Z*/;
        auto isAlpha = isAlphaLC || isAlphaUP;
        auto isAplhaNumeric = isDigit || isAlpha;
        return !isAscii || (!isUnderscore && !isAplhaNumeric);
    };



    // Consume single character. Returns `true` if character was consumed.
    protected bool Next();

    // Consume up to `count` characters. Returns number of consumed characters.
    protected int Advance(int count) {
        for (int i = 0; i < count; i++)
            if (!Next())
                return i;
        return count;
    };

    // Consume all whitespace characters until next character is not whitespace.
    protected int SkipWhitespaces() {
        string char;
        int count = 0;
        while (PeakChar(char)) {
            if (!char.IsSpaceAt(0))
                return count;
            Next();
            count++;
        };
        return count;
    };

    protected int PeakWhitespacesAt(int at) {
        string char;
        auto count = 0;
        while (PeakCharAt(char, at + count)) {
            if (!char.IsSpaceAt(0))
                return count;
            count++;
        };
        return count;
    };

    protected int GetValueAt() {
        if (!IsDeserializingObjectKey())
            return GetValueAt_Common();
        else
            return GetValueAt_Key();
    };

    protected int GetValueAt_Common() {
		SkipWhitespaces();
		
        auto at = 0;
		
        if (m_Comma) {
            string comma;
            if (!PeakCharAt(comma, at) || comma != ",")
                return -1;
            at++;
            at += PeakWhitespacesAt(at);
        };
        return at;
    };

    protected int GetValueAt_Key() {
        // Trailing whitespaces
        SkipWhitespaces();

		auto at = 0;
		
        // Comma
        if (m_Comma) {
            string comma;
            if (!PeakCharAt(comma, at) || comma != ",")
                return -1;

            // Whitespaces between comma and key
            at++;
            at += PeakWhitespacesAt(at);
        };

        // Key
        string char;
        if (!PeakCharAt(char, at) || char != "\"")
            return -1;
        at++;
        auto escaped = false;
        while (PeakCharAt(char, at)) {
            if (!escaped && char == "\"")
                break;
            escaped = !escaped && char == "\\";
            at++;
        };
        if (!PeakCharAt(char, at) || char != "\"")
            return -1;

        // Whitespaces between key and colon
        at++;
        at += PeakWhitespacesAt(at);

        // Colon
        if (!PeakCharAt(char, at) || char != ":")
            return -1;

        at++;
        at += PeakWhitespacesAt(at);
        return at;
    };



    override bool IsNull() {
        auto at = GetValueAt();
        if (at < 0)
            return false;
        string buffer;
        return PeakStringFrom(buffer, at, 4) == 4 && buffer == "null" && IsBorderAt(at + 4);
    };

    override bool IsBool() {
        auto at = GetValueAt();
        if (at < 0)
            return false;
        string buffer;
        return PeakStringFrom(buffer, at, 5) >= 4 && ((buffer.StartsWith("true") && IsBorderAt(at + 4)) || (buffer == "false" && IsBorderAt(at + 5)));
    };

    override bool IsNumber() {
        auto at = GetValueAt();
        if (at < 0)
            return false;
        string char;
        return PeakCharAt(char, at) && (char.IsDigitAt(0) || char == "-");
    };

    override bool IsInt() {
        auto valueAt = GetValueAt();
        if (valueAt < 0)
            return false;
        string first;
        auto readed = PeakStringFrom(first, valueAt, 1);
        if (!readed)
            return false; // no data -> not number
        if (!first.IsDigitAt(0) && first != "-")
            return false; // not digit and not sign -> not number
        auto from = valueAt + 1;
        while (readed) {
            string buffer;
            readed = PeakStringFrom(buffer, from, 8);
            auto n = buffer.Length();
            for (auto i = 0; i < n; i++) {
                if (!buffer.IsDigitAt(i)) {
                    if (buffer.ContainsAt(".", i))
                        return false; // fraction -> float
                    else if (buffer.ContainsAt("e", i) || buffer.ContainsAt("E", i))
                        return false; // exponent -> float
                    else
                        return true; // other symbol -> end of number -> int
                };
            };
            from += n;
        };
        return true; // all readed characters are related only to int
    };

    override bool IsFloat() {
        auto valueAt = GetValueAt();
        if (valueAt < 0)
            return false;
        string first;
        auto readed = PeakStringFrom(first, valueAt, 1);
        if (!readed)
            return false; // no data -> not number
        if (!first.IsDigitAt(0) && first != "-")
            return false; // not digit and not sign -> not number
        auto from = valueAt + 1;
        while (readed) {
            string buffer;
            readed = PeakStringFrom(buffer, from, 8);
            auto n = buffer.Length();
            for (auto i = 0; i < n; i++) {
                if (!buffer.IsDigitAt(i)) {
                    if (buffer.ContainsAt(".", i))
                        return true; // fraction -> float
                    else if (buffer.ContainsAt("e", i) || buffer.ContainsAt("E", i))
                        return true; // exponent -> float
                    else
                        return false; // other symbol -> end of number -> int
                };
            };
            from += n;
        };
        return false; // all readed characters are related only to int
    };

    override bool IsString() {
        auto at = GetValueAt();
        if (at < 0)
            return false;
        string char;
        return PeakCharAt(char, at) && char == "\"";
    };

    override bool IsContainer() {
        auto at = GetValueAt();
        if (at < 0)
            return false;
        string char;
        return PeakCharAt(char, at) && (char == "[" || char == "{");
    };

    override bool IsContainerEnd() {
        SkipWhitespaces();
        string char;
        return PeakChar(char) && (char.StartsWith("]") || char.StartsWith("}"));
    };

    override bool IsArray() {
        auto at = GetValueAt();
        if (at < 0)
            return false;
        string char;
        return PeakCharAt(char, at) && char == "[";
    };

    override bool IsArrayEnd() {
        SkipWhitespaces();
        string char;
        return PeakChar(char) && char == "]";
    };

    override bool IsObject() {
        auto at = GetValueAt();
        if (at < 0)
            return false;
        string char;
        return PeakCharAt(char, at) && char == "{";
    };

    override bool IsObjectEnd() {
        SkipWhitespaces();
        string char;
        return PeakChar(char) && char == "}";
    };

    protected bool IsComma() {
        SkipWhitespaces();
        string char;
        return PeakChar(char) && char == ",";
    };

    protected bool IsColon() {
        SkipWhitespaces();
        string char;
        return PeakChar(char) && char == ":";
    };

    override protected bool BeginValueDeserialization() {
        if (!super.BeginValueDeserialization())
            return false;
        if (!TryDeserializeComma())
            return false;
        return true;
    };

    override protected bool EndValueDeserialization() {
        if (!super.EndValueDeserialization())
            return false;
        if (!IsDeserializingRoot())
            m_Comma = true;
        return true;
    };

    override typename GetJsonType() {
        auto at = GetValueAt();
        if (at < 0)
            return typename.Empty;
        string char;
        if (!PeakCharAt(char, at))
            return typename.Empty;
        switch (char) {
            case "n":
                if (!IsNull())
                    return typename.Empty;
                return V30_JSON_Null;
            case "t":
            case "f":
                if (!IsBool())
                    return typename.Empty;
                return V30_JSON_Bool;
            case "0":
            case "1":
            case "2":
            case "3":
            case "4":
            case "5":
            case "6":
            case "7":
            case "8":
            case "9":
            case "-":
                if (IsFloat())
                    return V30_JSON_Float;
                else
                    return V30_JSON_Int;
		        Debug.Error("Unreachable.");
                return typename.Empty;
            case "\"":
                return V30_JSON_String;
            case "[":
                return V30_JSON_Array;
            case "{":
                return V30_JSON_Object;
            default:
                return typename.Empty;
        };
        Debug.Error("Unreachable.");
        return typename.Empty;
    };

    override bool DeserializeNull() {
        if (!BeginValueDeserialization())
            return false;
        if (!IsNull())
            return Error("expected null value");
        #ifndef ENABLE_DIAG
        Advance(4);
        #else
        string buffer;
        if (PeakString(buffer, 4) < 4)
            return Error();
        if (buffer != "null")
            return Error();
        if (Advance(4) < 4)
            return Error();
        #endif
        return EndValueDeserialization();
    };

    override bool DeserializeBool(out bool value) {
        if (!BeginValueDeserialization())
            return false;
        if (!IsBool())
            return Error("expected boolean value");
        string char;
        #ifndef ENABLE_DIAG
        PeakChar(char);
        if (char == "t") {
            Advance(4);
            value = true;
        }
        else {
            Advance(5);
            value = false;
        };
        #else
        if (!PeakChar(char))
            return Error();
        string buffer;
        if (char == "t") {
            if (PeakString(buffer, 4) < 4)
                return Error();
            if (buffer != "true")
                return Error();
            if (Advance(4) < 4)
                return Error();
            value = true;
        }
        else {
            if (PeakString(buffer, 5) < 5)
                return Error();
            if (buffer != "false")
                return Error();
            if (Advance(5) < 5)
                return Error();
            value = false;
        };
        #endif
        return EndValueDeserialization();
    };

    override bool DeserializeInt(out int value) {
        if (!BeginValueDeserialization())
            return false;
        if (!IsInt())
            return Error("integer value expected");
        auto n = 0;
        string char;
        // Sing
        if (!PeakChar(char))
            return Error("integer value expected");
        auto isSigned = false;
        if (char == "-") {
            isSigned = true;
            n++;
            if (!PeakCharAt(char, n))
                return Error("integer value expected");
        };
        // First digit
        if (!char.IsDigitAt(0))
            return Error("integer number expected");
        // Next digits
        n++;
        if (!IsEndAt(n)) {
            if (!PeakCharAt(char, n))
                return false;
            while (char.IsDigitAt(0)) {
                n++;
                if (IsEndAt(n))
                    break;
                if (!PeakCharAt(char, n))
                    return false;
            };
        };
        // End
        if (!IsBorderAt(n))
            return Error("invalid integer number");
        // Retrieve entire string
        string buffer;
        if (PeakString(buffer, n) < n)
            return false;
        // Check leading zero
        if (isSigned) {
            if (n > 2 && buffer.StartsWith("-0"))
                return Error("leading zero is not allowed");
        }
        else {
            if (n > 1 && buffer.StartsWith("0"))
                return Error("leading zero is not allowed");
        };
        // Parse
        int parsed;
        value = buffer.ToInt(parsed: parsed);
        if (parsed != n)
            return ErrorFormat("failed to parse integer value: parsed %1 characters, expected %2 characters", parsed.ToString(), n.ToString());
        Advance(n);
        return EndValueDeserialization();
    };

    override bool DeserializeFloat(out float value) {
        if (!BeginValueDeserialization())
            return false;
        if (!IsFloat())
            return Error("floating point value expected");
        auto n = 0;
        string char;
        // Sing
        if (!PeakChar(char))
            return Error("integer value expected");
        auto isSigned = false;
        if (char == "-") {
            isSigned = true;
            n++;
            if (!PeakCharAt(char, n))
                return Error("integer value expected");
        };
        // Integer part
        // First digit
        if (!char.IsDigitAt(0))
            return Error("integer part of floating point number expected");
        // Next digits
        n++;
        auto isFraction = false;
        if (!IsEndAt(n)) {
            if (!PeakCharAt(char, n))
                return Error();
            while (char.IsDigitAt(0)) {
                n++;
                if (IsEndAt(n))
                    break;
                if (!PeakCharAt(char, n))
                    return Error();
            };
            // Fraction part
            if (!IsEndAt(n) && char == ".") {
                isFraction = true;
                // First digit
                n++;
                if (!PeakCharAt(char, n))
                    return Error("fractional part of floating point number expected");
                if (!char.IsDigitAt(0))
                    return Error("fractional part of floating point number expected");
                // Next digits
                n++;
                if (!IsEndAt(n)) {
                    if (!PeakCharAt(char, n))
                        return false;
                    while (char.IsDigitAt(0)) {
                        n++;
                        if (IsEndAt(n))
                            break;
                        if (!PeakCharAt(char, n))
                            return false;
                    };
                };
            };
            // Exponent part
            if (!IsEndAt(n) && (char == "E" || char == "e")) {
                n++;
                if (!PeakCharAt(char, n))
                    return Error("exponent part of floating point number expected");
                // Sign
                if (char == "+" || char == "-") {
                    n++;
                    if (!PeakCharAt(char, n))
                        return Error("exponent part of floating point number expected");
                };
                // First digit
                if (!char.IsDigitAt(0))
                    return Error("exponent part of floating point number expected");
                // Next digits
                n++;
                if (!IsEndAt(n)) {
                    if (!PeakCharAt(char, n))
                        return false;
                    while (char.IsDigitAt(0)) {
                        n++;
                        if (IsEndAt(n))
                            break;
                        if (!PeakCharAt(char, n))
                            return false;
                    };
                };
            };
        };
        // End
        if (!IsBorderAt(n))
            return Error("invalid floating point number");
        // Retrieve entire string
        string buffer;
        if (PeakString(buffer, n) < n)
            return false;
        // Leading 0
        if (isSigned) {
            if (n > 2 && buffer.Get(1) == "0" && buffer.IsDigitAt(2))
                return Error("leading zero is not allowed");
        }
        else {
            if (n > 1 && buffer.Get(0) == "0" && buffer.IsDigitAt(1))
                return Error("leading zero is not allowed");
        };
        // Prase
        int parsed;
        value = buffer.ToFloat(parsed: parsed);
        if (parsed != n)
            return ErrorFormat("failed to parse floating point value: parsed %1 characters, expected %2 characters", parsed.ToString(), n.ToString());
        Advance(n);
        return EndValueDeserialization();
    };

    protected bool ParseUnicodeEscape(string buffer, int i, int length, out int unicode) {
        if (i + 4 >= length)
            return Error("unterminated unicode escape sequence");

        unicode = 0;
        for (int j = 1; j <= 4; j++) {
            int digit = buffer.ToAscii(i + j);
            if (digit >= 0x30 && digit <= 0x39)
                unicode = (unicode << 4) | (digit - 0x30);
            else if (digit >= 0x41 && digit <= 0x46)
                unicode = (unicode << 4) | (digit - 0x37);
            else if (digit >= 0x61 && digit <= 0x66)
                unicode = (unicode << 4) | (digit - 0x57);
            else
                return ErrorFormat("invalid unicode escape sequence: \\u%1", buffer.Substring(i + 1, 4));
        };

        return true;
    };

    protected string Utf8FromUnicode(int unicode) {
        if (unicode <= 0x7F) {
            return unicode.AsciiToString();
        }
        else if (unicode <= 0x7FF) {
            int b1 = 0xC0 | (unicode >> 6);
            int b2 = 0x80 | (unicode & 0x3F);
            b1 -= 0x100;
            b2 -= 0x100;
            return b1.AsciiToString() + b2.AsciiToString();
        }
        else if (unicode <= 0xFFFF) {
            int b1 = 0xE0 | (unicode >> 12);
            int b2 = 0x80 | ((unicode >> 6) & 0x3F);
            int b3 = 0x80 | (unicode & 0x3F);
            b1 -= 0x100;
            b2 -= 0x100;
            b3 -= 0x100;
            return b1.AsciiToString() + b2.AsciiToString() + b3.AsciiToString();
        }
        else {
            int b1 = 0xF0 | (unicode >> 18);
            int b2 = 0x80 | ((unicode >> 12) & 0x3F);
            int b3 = 0x80 | ((unicode >> 6) & 0x3F);
            int b4 = 0x80 | (unicode & 0x3F);
            b1 -= 0x100;
            b2 -= 0x100;
            b3 -= 0x100;
            b4 -= 0x100;
            return b1.AsciiToString() + b2.AsciiToString() + b3.AsciiToString() + b4.AsciiToString();
        };
    };

    override bool DeserializeString(out string value) {
        auto isKey = IsDeserializingObjectKey();
        if (!isKey)
            if (!BeginValueDeserialization())
                return false;
        if (isKey) {
            SkipWhitespaces();
            string keyChar;
            if (!PeakChar(keyChar) || keyChar != "\"")
                return Error("string value expected");
        }
        else if (!IsString())
            return Error("string value expected");
        string char;
        if (!ReadChar(char))
            return false;

        int n = 0;
        bool escaped = false;
        bool hasEscapes = false;
        int ascii;
        while (PeakCharAt(char, n)) {
            ascii = char.ToAscii();
            if ((ascii >= 0x00 && ascii <= 0x1F) || ascii == 0x7F)
                return ErrorFormat("illegal control character %1 (%2), at %3, it must be escaped", char, ascii.ToString(), (n + 1).ToString());
            if (!escaped) {
                if (char == "\"")
                    break;
                if (char == "\\")
                    hasEscapes = true;
            };
            escaped = !escaped && char == "\\";
            n++;
        };

        if (!PeakCharAt(char, n) || char != "\"")
            return Error("unterminated string value");

        if (!hasEscapes) {
            if (ReadString(value, n) < n)
                return false;
            if (!ReadChar(char))
                return false;
            if (!isKey)
                return EndValueDeserialization();
            return true;
        }

        string buffer;
        if (ReadString(buffer, n) < n)
            return false;
        if (!ReadChar(char))
            return false;

        value = "";
        int from = 0;
        int i = 0;
        int length = buffer.Length();
        while (i < length) {
            if (!buffer.ContainsAt("\\", i)) {
                i++;
                continue;
            };

            if (i > from)
                value += buffer.Substring(from, i - from);

            i++;
            if (i >= length)
                return Error("unterminated string escape sequence");

            switch (buffer.Get(i)) {
                case "\"":
                    value += "\"";
                    break;
                case "\\":
                    value += "\\";
                    break;
                case "/":
                    value += "/";
                    break;
                case "b":
                    value += (0x08).AsciiToString();
                    break;
                case "f":
                    value += (0x0C).AsciiToString();
                    break;
                case "n":
                    value += "\n";
                    break;
                case "r":
                    value += "\r";
                    break;
                case "t":
                    value += "\t";
                    break;
                case "u":
                    int unicode;
                    if (!ParseUnicodeEscape(buffer, i, length, unicode))
                        return false;

                    if (unicode >= 0xD800 && unicode <= 0xDBFF) {
                        if (i + 10 >= length || buffer.Get(i + 5) != "\\" || buffer.Get(i + 6) != "u")
                            return ErrorFormat("invalid unicode surrogate pair: \\u%1", buffer.Substring(i + 1, 4));

                        int lowSurrogate;
                        if (!ParseUnicodeEscape(buffer, i + 6, length, lowSurrogate))
                            return false;

                        if (lowSurrogate < 0xDC00 || lowSurrogate > 0xDFFF)
                            return ErrorFormat("invalid unicode surrogate pair: \\u%1\\u%2", buffer.Substring(i + 1, 4), buffer.Substring(i + 7, 4));

                        unicode = 0x10000 + ((unicode - 0xD800) << 10) + (lowSurrogate - 0xDC00);
                        i += 6;
                    }
                    else if (unicode >= 0xDC00 && unicode <= 0xDFFF) {
                        return ErrorFormat("invalid unicode surrogate pair: \\u%1", buffer.Substring(i + 1, 4));
                    };

                    value += Utf8FromUnicode(unicode);
                    i += 4;
                    break;
                default:
                    return ErrorFormat("invalid string escape sequence: \\%1", buffer.Get(i));
            };

            i++;
            from = i;
        };

        if (from < length)
            value += buffer.Substring(from, length - from);
        if (!isKey)
            return EndValueDeserialization();
        return true;
    };

    override bool BeginArrayDeserialization() {
        if (!super.BeginArrayDeserialization())
            return false;
        SkipWhitespaces();
        string char;
        if (!PeakChar(char))
            return false;
        if (char != "[")
            return Error("expected array begin");
        #ifndef ENABLE_DIAG
        Next();
        #else
        if (!ReadChar(char))
            return false;
        if (char != "[")
            return Error();
        #endif
        return true;
    };

    override bool EndArrayDeserialization() {
        if (!IsDeserializingArray())
            return Error("array end is not expected in current context");
        SkipWhitespaces();
        string char;
        if (!PeakChar(char))
            return false;
        if (char != "]")
            return Error("expected array end");
        #ifndef ENABLE_DIAG
        Next();
        #else
        if (!ReadChar(char))
            return false;
        if (char != "]")
            return Error();
        #endif
        return super.EndArrayDeserialization();
    };

    override bool BeginObjectDeserialization() {
        if (!super.BeginObjectDeserialization())
            return false;
        SkipWhitespaces();
        string char;
        if (!PeakChar(char))
            return false;
        if (char != "{")
            return Error("expected object begin");
        #ifndef ENABLE_DIAG
        Next();
        #else
        if (!ReadChar(char))
            return false;
        if (char != "{")
            return Error();
        #endif
        return true;
    };

    override protected bool DeserializeKey(out string key) {
        if (!TryDeserializeComma())
            return false;
        if (!super.DeserializeKey(key))
            return false;
        return DeserializeColon();
    };

    override bool EndObjectDeserialization() {
        if (!IsDeserializingObject())
            return Error("object end is not expected in current context");
        SkipWhitespaces();
        string char;
        if (!PeakChar(char))
            return false;
        if (char != "}")
            return Error("expected object end");
        #ifndef ENABLE_DIAG
        Next();
        #else
        if (!ReadChar(char))
            return false;
        if (char != "}")
            return Error();
        #endif
        return super.EndObjectDeserialization();
    };

    protected bool TryDeserializeComma() {
        if (!m_Comma)
            return true;
        return DeserializeComma();
    };

    protected bool DeserializeComma() {
        if (!m_Comma || !IsComma())
            return Error("expected comma");
        #ifndef ENABLE_DIAG
        Next();
        #else
        string char;
        if (!ReadChar(char))
            return false;
        if (char != ",")
            return Error();
        #endif
        m_Comma = false;
        return true;
    };

    protected bool DeserializeColon() {
        if (!IsColon())
            return Error("expected colon");
        #ifndef ENABLE_DIAG
        Next();
        #else
        string char;
        if (!ReadChar(char))
            return false;
        if (char != ":")
            return Error();
        #endif
        return true;
    };



    override protected bool Error(string message = "internal error") {
        return super.Error(string.Format("at %1:%2: %3", m_Line.ToString(), m_Column.ToString(), message));
    };

    protected bool ErrorAt(int lineShift, int columnShift, string message) {
        auto line = m_Line + lineShift;
        auto column = m_Column + columnShift;
        return super.ErrorFormat("at %1:%2: %3", line.ToString(), column.ToString(), message);
    };

    protected bool ErrorAtFormat(int lineShift, int columnShift, string format, string param1 = "", string param2 = "", string param3 = "", string param4 = "", string param5 = "", string param6 = "", string param7 = "", string param8 = "", string param9 = "") {
        auto line = m_Line + lineShift;
        auto column = m_Column + columnShift;
        auto message = string.Format(format, param1, param2, param3, param4, param5, param6, param7, param8, param9);
        return super.ErrorFormat("at %1:%2: %3", line.ToString(), column.ToString(), message);
    };
};
