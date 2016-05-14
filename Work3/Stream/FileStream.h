///////////////////////////////////////////////////////////////////////////////
// Название:    Work3/FileStream.h
// Цель:        Поток файла
// Автор:       Артем Матвейчук
// Создан:      05.05.2016
// Емайл:       pymba-96@mail.ru
// Программа:   Work3 | labWork
///////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef LABWORK_FILESTREAM_H
#define LABWORK_FILESTREAM_H

#include "../Core.h"

namespace lab
{
    namespace stream
    {
        // ==========================================================================
        // MODE OPEN FILE AND ERROR
        // ==========================================================================

        namespace Mode
        {
            namespace  Seek
            {
                constexpr uint32_t Begin = FILE_BEGIN;//<-Позиция в начале
                constexpr uint32_t Current = FILE_CURRENT;//<-Текущая позиция
                constexpr uint32_t End = FILE_END;//<-Позиция в конце
            }

            //Права доступа - dwDesiredAccess
            namespace Access
            {
                constexpr uint32_t Info = 0;//<-Только для получения информации о файле
                constexpr uint32_t Read = GENERIC_READ; //<-Разрешается чтение из файла
                constexpr uint32_t Write = GENERIC_WRITE; //<-Разрешается запись в файл
            };

            //Права по совместному доступу из разных процессов к файлу
            namespace Share
            {
                constexpr uint32_t Only = 0; //<-Исключительный доступ
                constexpr uint32_t Read = FILE_SHARE_READ; //<-Разрешенно чтение из файла
                constexpr uint32_t Write = FILE_SHARE_WRITE; //<-Разрешенна запись в файл
            };

            namespace Attribute
            {
                constexpr uint32_t  ReadOnly = FILE_ATTRIBUTE_READONLY;  //<-Только для чтения
                constexpr uint32_t  Hidden = FILE_ATTRIBUTE_HIDDEN; //<-Скрытый файл. В списке не появляется
                constexpr uint32_t  System = FILE_ATTRIBUTE_SYSTEM; //<-Файл является частью ОС
                constexpr uint32_t  Directory = FILE_ATTRIBUTE_DIRECTORY; //<- ?
                constexpr uint32_t  Archive = FILE_ATTRIBUTE_ARCHIVE; //<-Файл является архивным
                constexpr uint32_t  Normal = FILE_ATTRIBUTE_NORMAL; //<- Не может использоватся в сочитании с другими
                constexpr uint32_t  Temporary = FILE_ATTRIBUTE_TEMPORARY; //<- Создает временный файл. Система пытается его не записывать
                constexpr uint32_t  Compressed = FILE_ATTRIBUTE_COMPRESSED; //<- ?
            };

            namespace Flag
            {
                constexpr uint32_t PosixSemantics = FILE_FLAG_POSIX_SEMANTICS; //<- При доступе используются правила POSIX
                constexpr uint32_t  BackupSemantics = FILE_FLAG_BACKUP_SEMANTICS; //<- Контроль за правами.
                constexpr uint32_t  DeleteOnClose = FILE_FLAG_DELETE_ON_CLOSE; //<- Файл после закрытия удаляется. Для временных обьектов
                constexpr uint32_t  SequentialScan = FILE_FLAG_SEQUENTIAL_SCAN; //<- Режим кеширования. Для последовательного доступа
                constexpr uint32_t  RandomAccess = FILE_FLAG_RANDOM_ACCESS; //<- Режим кешиорования для произвольного доступа
                constexpr uint32_t  NoBuffering = FILE_FLAG_NO_BUFFERING; //<- Система не буферезирует и не делает кеширование
                constexpr uint32_t  Overlapped = FILE_FLAG_OVERLAPPED; //<- Устанавливает асинхронный доступ
                constexpr uint32_t  WriteThrough  = FILE_FLAG_WRITE_THROUGH; //<- Отключает промежуточное кеширование
            };

            namespace Disposition
            {
                constexpr uint32_t CreateNew = CREATE_NEW; //<- Создает новый файл. Если существует, то ошибка
                constexpr uint32_t CreateAlways = CREATE_ALWAYS; //<- Создает новый файл. Если существует, то перезаписывает
                constexpr uint32_t OpenExisting = OPEN_EXISTING; //<- Открывает существующий файл. Если нет, то завершается ошибкой
                constexpr uint32_t OpenAlways = OPEN_ALWAYS; //<- Если файл с указанным именем существует, то открываетт, иначе создается
                constexpr uint32_t TruncateExisting = TRUNCATE_EXISTING; //<- Открывает сущест. файл, усекает размер до 0, иначе ошибка
            }
            namespace Error
            {
                constexpr HANDLE InvalidHandle = INVALID_HANDLE_VALUE;
            }
        }

        // ==========================================================================
        // FILE
        // ==========================================================================

        class FileStream
        {
        public:
            virtual ~FileStream()
            {
                close();
            };

           virtual bool isOpen() const
            {
                return m_handle != Mode::Error::InvalidHandle;
            };

        protected:
            virtual bool open(const vaca::String& path,
                              uint32_t Disposition,
                              uint32_t Access = Mode::Access::Read | Mode::Access::Write,
                              uint32_t Share = Mode::Share::Read,
                              uint32_t FlagsAndAttributes = Mode::Attribute::Normal)
            {
                m_handle = CreateFileW(path.c_str(), Access, Share, nullptr,
                                       Disposition, FlagsAndAttributes, nullptr);
                return isOpen();
            };

            types::handle_t m_handle;

        private:
            void close()
            {
                if (isOpen()) {
                    CloseHandle(m_handle);
                    m_handle = Mode::Error::InvalidHandle;
                }
            };

        };
    }
}

#endif //LABWORK_FILESTREAM_H
