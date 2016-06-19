///////////////////////////////////////////////////////////////////////////////
// Название:    Work3/Character.h
// Цель:        Константы и функции Unicode
// Автор:       Артем Матвейчук
// Создан:      03.05.2016
// Емайл:       pymba-96@mail.ru
// Программа:   Work3 | labWork
///////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef LABWORK_CHARACTER_H
#define LABWORK_CHARACTER_H

#include <type_traits>

#include "Core.h"

namespace lab
{
    // ==================================================================
    // CONSTANTS
    // ==================================================================

    constexpr char32_t last_ascii_char               = 0x7f;            // Highest ASCII code point
    constexpr char32_t last_latin1_char              = 0xff;            // Highest ISO 8859 code point
    constexpr char32_t line_separator_char           = 0x2028;          // Line separator
    constexpr char32_t paragraph_separator_char      = 0x2029;          // Paragraph separator
    constexpr char32_t first_surrogate_char          = 0xd800;          // First UTF-16 surrogate code
    constexpr char32_t first_high_surrogate_char     = 0xd800;          // First UTF-16 high surrogate code
    constexpr char32_t last_high_surrogate_char      = 0xdbff;          // Last UTF-16 high surrogate code
    constexpr char32_t first_low_surrogate_char      = 0xdc00;          // First UTF-16 low surrogate code
    constexpr char32_t last_low_surrogate_char       = 0xdfff;          // Last UTF-16 low surrogate code
    constexpr char32_t last_surrogate_char           = 0xdfff;          // Last UTF-16 surrogate code
    constexpr char32_t first_private_use_char        = 0xe000;          // Beginning of BMP private use area
    constexpr char32_t last_private_use_char         = 0xf8ff;          // End of BMP private use area
    constexpr char32_t first_noncharacter            = 0xfdd0;          // Beginning of reserved noncharacter block
    constexpr char32_t last_noncharacter             = 0xfdef;          // End of reserved noncharacter block
    constexpr char32_t byte_order_mark               = 0xfeff;          // Byte order mark
    constexpr char32_t replacement_char              = 0xfffd;          // Unicode replacement character
    constexpr char32_t last_bmp_char                 = 0xffff;          // End of basic multilingual plane
    constexpr char32_t first_private_use_a_char      = 0xf0000;         // Beginning of supplementary private use area A
    constexpr char32_t last_private_use_a_char       = 0xffffd;         // End of supplementary private use area A
    constexpr char32_t first_private_use_b_char      = 0x100000;        // Beginning of supplementary private use area B
    constexpr char32_t last_private_use_b_char       = 0x10fffd;        // End of supplementary private use area B
    constexpr char32_t last_unicode_char             = 0x10ffff;        // Highest possible Unicode code point
    constexpr const char* utf8_bom                   = "\xef\xbb\xbf";  // Byte order mark (U+FEFF) in UTF-8
    constexpr const char* utf8_replacement           = "\xef\xbf\xbd";  // Unicode replacement character (U+FFFD) in UTF-8
    constexpr size_t max_case_decomposition          = 3;               // Maximum length of a full case mapping
    constexpr size_t max_canonical_decomposition     = 2;               // Maximum length of a canonical decomposition
    constexpr size_t max_compatibility_decomposition = 18;              // Maximum length of a compatibility decomposition

    // ==================================================================
    // FUNCTIONS
    // ==================================================================

    constexpr bool char_is_digit(char32_t c) noexcept
    {
        return c >= U'0' && c <= U'9';
    }

    constexpr bool char_is_ascii(char32_t c) noexcept
    {
        return c <= last_ascii_char;
    }



    constexpr bool char_is_surrogate(char32_t c) noexcept
    {
        return c >= first_surrogate_char && c <= last_surrogate_char;
    }

    constexpr bool char_is_unicode(char32_t c) noexcept
    {
        return c <= last_unicode_char && ! char_is_surrogate(c);
    }

    constexpr bool char_is_noncharacter(char32_t c) noexcept
    {
        return (c >= first_noncharacter && c <= last_noncharacter)
               || (c & 0xfffe) == 0xfffe;
    }

    template <typename C>
    constexpr uint32_t char_to_uint(C c) noexcept
    {
        return std::make_unsigned<C>::type(c);
    }

    constexpr bool char_is_high_surrogate(char32_t c) noexcept
    {
        return c >= first_high_surrogate_char && c <= last_high_surrogate_char;
    }

    constexpr bool char_is_low_surrogate(char32_t c) noexcept
    {
        return c >= first_low_surrogate_char && c <= last_low_surrogate_char;
    }

    constexpr bool char_is_bmp(char32_t c) noexcept
    {
        return c <= last_bmp_char && !char_is_surrogate(c);
    }

    constexpr bool char_is_latin1(char32_t c) noexcept
    {
        return c <= last_latin1_char;
    }
}

#endif //LABWORK_CHARACTER_H
