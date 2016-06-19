///////////////////////////////////////////////////////////////////////////////
// Название:    Work3/FileInputStream.h
// Цель:        Входной поток файла
// Автор:       Артем Матвейчук
// Создан:      03.05.2016
// Емайл:       pymba-96@mail.ru
// Программа:   Work3 | labWork
///////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef LABWORK_FILEINPUTSTREAM_H
#define LABWORK_FILEINPUTSTREAM_H

#include "../Core.h"
#include "FileStream.h"

namespace lab
{
    namespace stream {
        class FileInputStream : public FileStream  {
        public:
            explicit FileInputStream(const vaca::String &path);
            // Read bytes
            virtual bool readByte(types::byte_t &bValue);
            virtual size_t readBytes(types::byte_t *arrBytes, size_t count);
        };
    }
}

#endif //LABWORK_FILEINPUTSTREAM_H
