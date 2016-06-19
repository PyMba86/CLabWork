#include "Encoder.h"

namespace lab {
    namespace encoding {

        UTF8Encoding UTF8Encoding::m_instance;
        AnsiEncoding AnsiEncoding::m_instance;

        // ---------------------------------------------------------------------
        BaseEncoder *BaseEncoder::getEncoding(TextEncoding eEncoding) {
            switch (eEncoding) {
                case TextEncoding::Utf8:
                    return &UTF8Encoding::getInstance();
                case TextEncoding::Ansi:
                    return &AnsiEncoding::getInstance();
            }
        }

        // ---------------------------------------------------------------------
        size_t BaseEncoder::encodingString(const char32_t *str, size_t count,
                                            types::byte_t *pBytes, size_t nNumBytes) {
            size_t nCharPos = 0;
            size_t nNumBytesInChar = 0;
            size_t nBytePos = 0;

            while ((nCharPos < count) && (nBytePos < nNumBytes)) {
                nNumBytesInChar = encodingChar(str[nCharPos], pBytes + nBytePos);
                if (!nNumBytesInChar)
                    break;
                nBytePos += nNumBytesInChar;
                ++nCharPos;
            }
            return nCharPos;
        };

        // ---------------------------------------------------------------------
        TextEncoding UTF8Encoding::getEncoding() const {
            return TextEncoding::Utf8;
        }

        // ---------------------------------------------------------------------
        size_t UTF8Encoding::encodingChar(const char32_t &bValue, types::byte_t *pBytes) {
            return char_to_byte(bValue, pBytes);
        }

        // ---------------------------------------------------------------------
        TextEncoding AnsiEncoding::getEncoding() const {
            return TextEncoding::Ansi;
        }

        // ---------------------------------------------------------------------
        size_t AnsiEncoding::encodingChar(const char32_t &bValue, types::byte_t *pBytes) {
            if (char_is_ascii(bValue))
                return char_to_byte(bValue, pBytes);
            return 0;
        }
    }
}


