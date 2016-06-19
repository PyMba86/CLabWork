#include "Decoder.h"

namespace lab
{
    namespace encoding
    {
        UTF8Decoder UTF8Decoder::m_instance;
        AnsiDecoder AnsiDecoder::m_instance;

        // ---------------------------------------------------------------------
        BaseDecoder *BaseDecoder::getDecoder(TextEncoding eEncoding) {
            switch (eEncoding) {
                case TextEncoding::Utf8:
                    return &UTF8Decoder::getInstance();
                    case TextEncoding::Ansi:
                        return &AnsiDecoder::getInstance();
            }
        }

        size_t BaseDecoder::decodeByte(const types::byte_t *pBytes, char32_t &bValue)
        {
            return byte_from_utf8(pBytes,bValue);
        }

        // ---------------------------------------------------------------------
        size_t BaseDecoder::decodeString(const types::byte_t* pBytes,
                                         size_t nNumBytes, char32_t* str, size_t count)
        {
            size_t nBytePos = 0;
            char32_t c = 0;
            size_t nNumBytesInChar = 0;
            size_t nCharPos = 0;
            while ((nCharPos < count) && (nBytePos < nNumBytes)) {
                nNumBytesInChar = decodeChar(pBytes + nBytePos, c);
                if (!nNumBytesInChar)
                    break;
                nBytePos += nNumBytesInChar;
                str[nCharPos++] = c;
            }
            str[nCharPos++] = '\0';
            return nCharPos;
        };


        // ---------------------------------------------------------------------
        TextEncoding UTF8Decoder::getEncoding() const {
            return TextEncoding::Utf8;
        }

        // ---------------------------------------------------------------------
        size_t UTF8Decoder::decodeChar(const types::byte_t* pBytes, char32_t &bValue)
        {
            char32_t c;
            size_t nNumBytesInChar = decodeByte(pBytes,c);
            if (nNumBytesInChar && char_is_unicode(c))
                bValue = c;
            return nNumBytesInChar;
        }

        // ---------------------------------------------------------------------
        size_t AnsiDecoder::decodeChar(const lab::types::byte_t *pBytes, char32_t &bValue) {
            char32_t c;
            size_t nNumBytesInChar = decodeByte(pBytes,c);
            if (nNumBytesInChar && char_is_ascii(c))
                bValue = c;
            return nNumBytesInChar;
        }

        // ---------------------------------------------------------------------
        TextEncoding AnsiDecoder::getEncoding() const
        {
            return TextEncoding::Ansi;
        }

    }
}


