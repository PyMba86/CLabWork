#include "FileReader.h"

namespace lab {
    namespace stream
    {
        // ---------------------------------------------------------------------
        FileReader::FileReader(FileInputStream *inputStream, encoding::TextEncoding
        decoder, uint32_t sizeBuffer)
                : m_nInputBufferPos(0), m_nInputBufferLength(0)
        {
            setBufferSize(sizeBuffer);
            setDecoder(encoding::BaseDecoder::getDecoder(decoder));
            setInputStream(inputStream);
        }

        // ------------------------------------------------------------------
        bool FileReader::readChar(char32_t &bValue)
        {
            if (!fillBuffer(4))
                return false;
            m_nInputBufferPos += m_Decoder->decodeChar(m_arrInputBuffer + m_nInputBufferPos, bValue);
            return true;
        }

        // ------------------------------------------------------------------
        bool FileReader::readPreamble(encoding::TextEncoding& eEncoding)
        {

            int nBytesLeft = fillBuffer(4);
            if (nBytesLeft <= 0)
                return false;
            types::byte_t* pBytes = m_arrInputBuffer + m_nInputBufferPos;
            if (nBytesLeft >= sizeof(g_arrUTF8Preamble) &&
                memcmp(pBytes, g_arrUTF8Preamble, sizeof(g_arrUTF8Preamble)) == 0)
            {
                eEncoding = encoding::TextEncoding::Utf8;
                m_nInputBufferPos += sizeof(g_arrUTF8Preamble);
                return true;
            }
            return false;
        };

        // ------------------------------------------------------------------
        encoding::BaseDecoder* FileReader::getDecoder() const
        {
            return m_Decoder;
        };

        // ------------------------------------------------------------------
        bool FileReader::setDecoder(encoding::BaseDecoder* pDecoder)
        {
            if(pDecoder) {
                m_Decoder = pDecoder;
                return true;
            }
            return false;
        };


        // ------------------------------------------------------------------
        void FileReader::setInputStream(FileInputStream* pInputStream)
        {
            m_InputStream = pInputStream;
            m_nInputBufferPos = 0;
            m_nInputBufferLength = 0;
            m_bEndOfFile = false;
        };


        // ------------------------------------------------------------------
        FileInputStream* FileReader::getInputStream() const
        {
            return m_InputStream;
        };


        // ------------------------------------------------------------------
        bool FileReader::checkEncoding()
        {
            encoding::TextEncoding eEncoding;
            if (! readPreamble(eEncoding))
                return false;
            return setDecoder(encoding::BaseDecoder::getDecoder(eEncoding));
        };

        // ------------------------------------------------------------------
       size_t FileReader::readString(char32_t* str, size_t count)
        {
            char32_t decChar;
            size_t nNumRead = 0;
            while (nNumRead < count)
            {
                if (!readChar(decChar))
                    break;
                str[nNumRead++] = decChar;
            }
            return nNumRead;
        }

        // ------------------------------------------------------------------
        void FileReader::setBufferSize(uint32_t nBufferSize)
        {
            m_sizeBuffer = nBufferSize;
            if (nBufferSize > 0)
            {
                m_arrInputBuffer = new unsigned char[nBufferSize];
                if (m_arrInputBuffer == nullptr)
                {
                    nBufferSize = 0;
                    throw std::range_error
                            ("FileReader::SetBufferSize()*: Buffer size equal null");
                }
            }
            else
                m_arrInputBuffer = nullptr;
        };

        // ------------------------------------------------------------------
        uint32_t FileReader::getBufferSize() const
        {
            return m_sizeBuffer;
        };

        // ------------------------------------------------------------------
        vaca::String FileReader::readLine(const std::u32string& delim)
        {
            char32_t decChar;
            size_t countDelim = delim.length();
            size_t equalChar = 0;
            std::u32string tmp;
            if (countDelim)
                while (readChar(decChar)) {
                    if (decChar == delim[equalChar]) {
                        ++equalChar;
                        if (countDelim == equalChar)
                            break;
                    }
                    else {
                        tmp.push_back(decChar);
                    }
                }
            return to_String(tmp);
        }

        // ------------------------------------------------------------------
        bool FileReader::isEndOfFile() const
        {
            return m_bEndOfFile && (m_nInputBufferPos == m_nInputBufferLength);
        }

        // ------------------------------------------------------------------
        size_t FileReader::fillBuffer(size_t nNumBytes)
        {
            size_t nBytesLeft = m_nInputBufferLength - m_nInputBufferPos;
            if (nBytesLeft < nNumBytes && ! m_bEndOfFile)
            {
                MoveMemory(m_arrInputBuffer,
                           m_arrInputBuffer + m_nInputBufferPos, nBytesLeft);
                m_nInputBufferPos = 0;
                size_t nFreeSize = sizeof(m_arrInputBuffer) - nBytesLeft;
                size_t nBytesRead = m_InputStream->readBytes(m_arrInputBuffer + nBytesLeft, nFreeSize);
                m_nInputBufferLength = nBytesLeft + nBytesRead;
                m_bEndOfFile = nBytesRead < nFreeSize;
                nBytesLeft = m_nInputBufferLength;
            }
            return nBytesLeft;
        }
    }
}
