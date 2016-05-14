///////////////////////////////////////////////////////////////////////////////
// Название:    Work3/FileOutputStream.h
// Цель:        Выходной поток в файл
// Автор:       Артем Матвейчук
// Создан:      05.05.2016
// Емайл:       pymba-96@mail.ru
// Программа:   Work3 | labWork
///////////////////////////////////////////////////////////////////////////////


#ifndef LABWORK_FILEOUTPUTSTREAM_H
#define LABWORK_FILEOUTPUTSTREAM_H

#include "../Core.h"
#include "FileStream.h"

namespace lab
{
    namespace stream
    {
        class FileOutputStream : public FileStream
        {
        public:
            explicit FileOutputStream(const vaca::String &path);

            // Write bytes
            virtual bool writeByte( const types::byte_t&  bValue);

            virtual size_t writeByte(const types::byte_t& bValue, size_t nCount);

            virtual size_t writeBytes(const types::byte_t* arrBytes, size_t nCount);
        };
    }
}

#endif //LABWORK_FILEOUTPUTSTREAM_H
