///////////////////////////////////////////////////////////////////////////////
// Название:    Work3/FileReader.h
// Цель:        Чтение символов из потока
// Автор:       Артем Матвейчук
// Создан:      03.05.2016
// Емайл:       pymba-96@mail.ru
// Программа:   Work3 | labWork
///////////////////////////////////////////////////////////////////////////////


#ifndef LABWORK_READER_H
#define LABWORK_READER_H

#include "FileInputStream.h"
#include "../Encoding/Decoder.h"

namespace lab
{
    namespace stream
    {
        /// UTF-8 preamble.
        constexpr types::byte_t g_arrUTF8Preamble[] = { 0xEF, 0xBB, 0xBF };

        class FileReader
        {
        public:
             FileReader(FileInputStream* inputStream, encoding::TextEncoding
             decoder = encoding::TextEncoding::Ansi,uint32_t sizeBuffer = 4096);

            bool readChar(char32_t &bValue);

            /// Get byte order mark. This function is optional.
            virtual bool readPreamble(encoding::TextEncoding& eEncoding);

            /// Get text decoder.
            virtual encoding::BaseDecoder* getDecoder() const;
            /// Set text decoder.
            virtual bool setDecoder(encoding::BaseDecoder* pDecoder);

            /// Attach input stream to the object.
            void setInputStream(FileInputStream* pInputStream);
            /// Get pointer to the input stream.
            FileInputStream* getInputStream() const;

            /// Read and apply byte order mark.
            bool checkEncoding();

            virtual size_t readString(char32_t* str, size_t count);

            /// Set buffer size.
            void setBufferSize(uint32_t nBufferSize);
            /// Get buffer size.
            uint32_t getBufferSize() const;

            vaca::String readLine(const std::u32string& delim);

            bool isEndOfFile() const;

        protected:
            FileInputStream* m_InputStream;
            encoding::BaseDecoder* m_Decoder;
            types::byte_t* m_arrInputBuffer;
            // Позиция в буфере
            size_t m_nInputBufferPos;
            uint32_t m_sizeBuffer;
            // Число байтво в буфере
            size_t m_nInputBufferLength;
            // True after reaching end of file.
            bool m_bEndOfFile;
			size_t fillBuffer(size_t nNumBytes);


        private:
            /// Object can't be copied.
            FileReader(const FileReader& rStream) = delete;
            /// Object can't be copied.
            FileReader& operator=(const FileReader& rStream) = delete;
        };
    }
}

#endif //LABWORK_READER_H
