///////////////////////////////////////////////////////////////////////////////
// Название:    Work3/Encoder.h
// Цель:        Кодировка
// Автор:       Артем Матвейчук
// Создан:      03.05.2016
// Емайл:       pymba-96@mail.ru
// Программа:   Work3 | labWork
///////////////////////////////////////////////////////////////////////////////

#ifndef LABWORK_ENCODING_H
#define LABWORK_ENCODING_H

#include "../Core.h"
#include "../Utf.h"
#include "Decoder.h"

namespace lab {
    namespace encoding {

        class BaseEncoder {
        public:
            virtual ~BaseEncoder() = default;

            virtual TextEncoding getEncoding() const = 0;

            virtual size_t encodingChar(const char32_t &bValue, types::byte_t *pBytes) = 0;

            virtual size_t encodingString(const char32_t *str, size_t count, types::byte_t *pBytes, size_t nNumBytes);

            static BaseEncoder *getEncoding(TextEncoding eEncoding);
        };


        // ======================================================================
        // IMPLEMENTATION DECODER
        // ======================================================================

        class UTF8Encoding : public BaseEncoder {
        public:
            TextEncoding getEncoding() const override;

            size_t encodingChar(const char32_t &bValue, types::byte_t *pBytes) override;

            static UTF8Encoding &getInstance() { return m_instance; }

        private:
            UTF8Encoding(const UTF8Encoding &) = delete;

            UTF8Encoding &operator=(const UTF8Encoding &) = delete;

            UTF8Encoding() = default;

            static UTF8Encoding m_instance;
        };

        class AnsiEncoding : public BaseEncoder {
        public:
            TextEncoding getEncoding() const override;

            size_t encodingChar(const char32_t &bValue, types::byte_t *pBytes) override;

            static AnsiEncoding &getInstance() { return m_instance; }

        private:
            AnsiEncoding(const AnsiEncoding &) = delete;

            AnsiEncoding &operator=(const AnsiEncoding &) = delete;

            AnsiEncoding() = default;

            static AnsiEncoding m_instance;
        };

    }
}



#endif //LABWORK_ENCODING_H
