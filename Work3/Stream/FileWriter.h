///////////////////////////////////////////////////////////////////////////////
// Название:    Work3/FileWriter.h
// Цель:        Выходной поток символов в файл
// Автор:       Артем Матвейчук
// Создан:      05.05.2016
// Емайл:       pymba-96@mail.ru
// Программа:   Work3 | labWork
///////////////////////////////////////////////////////////////////////////////


#ifndef LABWORK_FILEWRITER_H
#define LABWORK_FILEWRITER_H

#include "FileOutputStream.h"
#include "../Encoding/Encoder.h"

namespace lab
{
    namespace stream
    {
        class FileWriter
        {
        public:
            FileWriter(FileOutputStream* outputStream, encoding::TextEncoding
            encoder = encoding::TextEncoding::Ansi);

            bool writeChar(const char32_t &bValue);

            /// Get text decoder.
            virtual encoding::BaseEncoder* getEncoder() const;
            /// Set text decoder.
            virtual bool setEncoder(encoding::BaseEncoder* pEncoder);
            /// Get pointer to the input stream.
            FileOutputStream* getOutputStream() const;

            void writeString(const char32_t* str, size_t count);

            void writeString(const vaca::String& str);


        protected:
            FileOutputStream* m_OutputStream;
            encoding::BaseEncoder* m_Encoder;

        private:
            /// Object can't be copied.
            FileWriter(const FileWriter& rStream) = delete;
            /// Object can't be copied.
            FileWriter& operator=(const FileWriter& rStream) = delete;
        };
    }
}

#endif //LABWORK_FILEWRITER_H
