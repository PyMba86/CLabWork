///////////////////////////////////////////////////////////////////////////////
// Название:    Work3/Decoder.h
// Цель:        Декодер - преобразует из потока байтов в символы кодировки
// Автор:       Артем Матвейчук
// Создан:      03.05.2016
// Емайл:       pymba-96@mail.ru
// Программа:   Work3 | labWork
///////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef LABWORK_DECODER_H
#define LABWORK_DECODER_H

#include "../Core.h"
#include "../Utf.h"

namespace lab
{
    namespace encoding
    {
        enum class TextEncoding
        {
            Ansi,
            Utf8
        };

        class BaseDecoder
        {
        public:
            virtual ~BaseDecoder() = default;

            virtual TextEncoding getEncoding() const = 0;

            virtual size_t decodeChar( const types::byte_t* pBytes, char32_t &bValue) = 0;

            virtual size_t decodeString(const types::byte_t* pBytes, size_t nNumBytes,
                                        char32_t* str, size_t count);

            static BaseDecoder* getDecoder(TextEncoding eEncoding);

        protected:
            size_t decodeByte( const types::byte_t* pBytes, char32_t &bValue);
        };


        // ======================================================================
        // IMPLEMENTATION DECODER
        // ======================================================================

        class UTF8Decoder : public BaseDecoder
        {
        public:
            TextEncoding getEncoding() const override;
            size_t decodeChar(const types::byte_t* pBytes, char32_t &bValue) override;
            static UTF8Decoder& getInstance()
            {  return m_instance; }

        private:
            UTF8Decoder(const UTF8Decoder&) = delete;
            UTF8Decoder& operator=(const UTF8Decoder&) = delete;
            UTF8Decoder() = default;

            static UTF8Decoder m_instance;
        };


        class AnsiDecoder : public BaseDecoder
        {
        public:
            /// Return current encoding.
            TextEncoding getEncoding() const override;
            /// Decode single character.
            size_t decodeChar(const types::byte_t* pBytes, char32_t &bValue) override;
            /// Get single object instance.
            static AnsiDecoder& getInstance()
            { return m_instance; }

        private:
            /// Hides object constructor.
            AnsiDecoder() = default;
            /// Object can't be copied.
            AnsiDecoder(const AnsiDecoder&) = delete;
            /// Object can't be copied.
            AnsiDecoder& operator=(const AnsiDecoder&) = delete;
            /// Single object instance.
            static AnsiDecoder m_instance;
        };



}
}

#endif //LABWORK_DECODER_H
