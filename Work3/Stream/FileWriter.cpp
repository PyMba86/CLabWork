#include "FileWriter.h"

namespace lab
{
    namespace stream {

        FileWriter::FileWriter(FileOutputStream* outputStream, encoding::TextEncoding
                encoder) : m_OutputStream(outputStream)
                {
                        setEncoder(encoding::BaseEncoder::getEncoding(encoder));
                }

        // -------------------------------------------------------------------
        bool FileWriter::writeChar(const char32_t &bValue)
        {
            types::byte_t buffer[4];
            size_t nNumBytesInChar = m_Encoder->encodingChar(bValue,buffer);
            if(nNumBytesInChar)
            if (m_OutputStream->writeBytes(buffer,nNumBytesInChar) == nNumBytesInChar)
                return true;
            return false;
        }

       // -------------------------------------------------------------------
        encoding::BaseEncoder* FileWriter::getEncoder() const
        {
            return m_Encoder;
        };

        // -------------------------------------------------------------------
        bool FileWriter::setEncoder(encoding::BaseEncoder* pEncoder)
        {
            if(pEncoder) {
                m_Encoder = pEncoder;
                return true;
            }
            return false;
        };

        // -------------------------------------------------------------------
        FileOutputStream* FileWriter::getOutputStream() const
        {
            return m_OutputStream;
        };

        // -------------------------------------------------------------------
        void FileWriter::writeString(const char32_t* str, size_t count)
        {
            size_t nNumWrite = 0;
            while (nNumWrite < count)
            {
                if (!writeChar(str[nNumWrite++]))
                    break;
            }
        }

        // -------------------------------------------------------------------
        void FileWriter::writeString(const vaca::String& str)
        {
            std::u32string result;
            result = to_utf32(str);
            if (result.length())
                writeString(result.c_str(),result.length());
        }
    }

}