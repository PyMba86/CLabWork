///////////////////////////////////////////////////////////////////////////////
// Название:    Work3/Utf.h
// Цель:        Unicode
// Автор:       Артем Матвейчук
// Создан:      03.05.2016
// Емайл:       pymba-96@mail.ru
// Программа:   Work3 | labWork
///////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef LABWORK_UTF_H
#define LABWORK_UTF_H

#include <iostream>
#include "Character.h"

namespace lab
{
    namespace detail {

        template<typename C>
        struct UtfEncoding;

        template<>
        struct  UtfEncoding<char> {
                static constexpr size_t max_units = 4;

                static size_t decode(const types::byte_t *src, size_t n,
                char32_t &dst) noexcept;

                static size_t decode_fast(const types::byte_t *src, size_t n,
                char32_t &dst) noexcept;

                static size_t decode_prev(const types::byte_t *src, size_t pos,
                char32_t &dst) noexcept;

                static size_t encode(char32_t src, types::byte_t* dst) noexcept;

                static const char *name() noexcept { return "UTF-8"; }
        };

        template<>
        struct  UtfEncoding<char16_t> {
                static constexpr size_t max_units = 2;

                static size_t decode(const char16_t *src,
                size_t n, char32_t &dst) noexcept;

                static size_t decode_fast(const char16_t *src,
                size_t n, char32_t &dst) noexcept;

                static size_t decode_prev(const char16_t *src,
                size_t pos, char32_t &dst) noexcept;

                static size_t encode(char32_t src, char16_t *dst) noexcept;

                static const char *name() noexcept { return "UTF-16"; }
        };

        inline size_t UtfEncoding<char16_t>::decode_fast(
                const char16_t *src, size_t n, char32_t &dst) noexcept {
            if (n >= 2 && char_is_surrogate(src[0])) {
                dst = 0x10000 + ((char32_t(src[0]) & 0x3ff) << 10)
                      + (char32_t(src[1]) & 0x3ff);
                return 2;
            }
            else {
                dst = src[0];
                return 1;
            }
        }

        template<>
        struct  UtfEncoding<char32_t> {
                static constexpr size_t max_units = 1;

                static size_t decode(const char32_t *src,
                size_t /*n*/, char32_t &dst) noexcept {
                    dst = *src;
                    return 1;
                }

                static size_t decode_fast(const char32_t *src,
                size_t /*n*/, char32_t &dst) noexcept {
                    dst = *src;
                    return 1;
                }

                static size_t decode_prev(const char32_t *src,
                size_t pos, char32_t &dst) noexcept {
                    dst = src[pos - 1];
                    return 1;
                }

                static size_t encode(char32_t src,
                char32_t *dst) noexcept {
                    *dst = src;
                    return 1;
                }

                static const char *name() noexcept { return "UTF-32"; }
        };

        template<>
        struct  UtfEncoding<wchar_t> {
                using utf = UtfEncoding<char16_t>;

                static constexpr size_t max_units = utf::max_units;

                static size_t decode(const wchar_t *src, size_t n,
                char32_t &dst) noexcept {
                    return utf::decode(
                            reinterpret_cast<const char16_t *>(src), n, dst);
                }

                static size_t decode_fast(const wchar_t *src, size_t n,
                char32_t &dst) noexcept {
                    return utf::decode_fast(
                            reinterpret_cast<const char16_t *>(src), n, dst);
                }

                static size_t decode_prev(const wchar_t *src, size_t pos,
                char32_t &dst) noexcept {
                    return utf::decode_prev(
                            reinterpret_cast<const char16_t *>(src), pos, dst);
                }

                static size_t encode(char32_t src, wchar_t *dst) noexcept {
                    return utf::encode(
                            src, reinterpret_cast<char16_t *>(dst));
                }

                static const char *name() noexcept { return "wchar_t"; }
        };

        // --------------------------------------------------------------
        // Unicode UTF-8:
        // 1.0x00000000 - 0x0000007F: 0xxxxxxx
        // 2.0x00000080 - 0x000007FF : 110xxxxx 10xxxxxx
        // 3.0x00000800 - 0x0000FFFF : 1110xxxx 10xxxxxx 10xxxxxx
        // 4.0x00010000 - 0x001FFFFF : 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
        // --------------------------------------------------------------
        inline size_t UtfEncoding<char>::decode_fast(const types::byte_t *src,
                                                     size_t n, char32_t &dst) noexcept {
            auto code = src;
            if (code[0] <= 0xc1 || n < 2)    /*1*/
            {
                dst = code[0];
                return 1;
            }
            if (code[0] <= 0xdf || n < 3) {    /*2*/
                dst = (char32_t(code[0] & 0x1f) << 6)
                      | char32_t(code[1] & 0x3f);
                return 2;
            }
            if (code[0] <= 0xef || n < 4) {    /*3*/
                dst = (char32_t(code[0] & 0x0f) << 12)
                      | (char32_t(code[1] & 0x3f) << 6)
                      | char32_t(code[2] & 0x3f);
                return 3;
            }                                /*4*/
            dst = (char32_t(code[0] & 0x07) << 18)
                  | (char32_t(code[1] & 0x3f) << 12)
                  | (char32_t(code[2] & 0x3f) << 6)
                  | char32_t(code[3] & 0x3f);
            return 4;
        }
    } // namespace detail

    // ================================================================
    // SINGLE CHARACTER FUNCTIONS
    // ================================================================

    size_t  byte_from_utf8(const types::byte_t *src, char32_t &dst) noexcept;

     size_t   char_from_utf16(const char16_t *src, char32_t &dst) noexcept;

    size_t   char_from_wchar(const wchar_t *src, char32_t &dst) noexcept;

     size_t  char_to_utf8(char32_t src, char *dst) noexcept;

     size_t  char_to_utf16(char32_t src, char16_t *dst) noexcept;

    size_t  char_to_wchar(char32_t src, wchar_t *dst) noexcept;

    size_t  char_to_byte(char32_t src, types::byte_t *dst) noexcept;

    // UTF conversion functions

    namespace detail {

        template<typename C1, typename C2>
         struct Recode {
            void operator()(const C1 *src, size_t n, std::basic_string<C2> &dst, uint32_t flags = 0) const {
                if (!src)
                    return;
                size_t pos = 0;
                char32_t u = 0;
                C2 buf[UtfEncoding<C2>::max_units];
                while (pos < n) {
                    auto rc = UtfEncoding<C1>::decode(src + pos, n - pos, u);
                    if (!char_is_unicode(u)) {
                        u = replacement_char;
                    }
                    pos += rc;
                    rc = UtfEncoding<C2>::encode(u, buf);
                    dst.append(buf, rc);
                }
            }
        };

        template<typename C1>
         struct Recode<C1, char32_t> {
            void operator()(const C1 *src, size_t n, std::u32string &dst, uint32_t flags = 0) const {
                if (!src)
                    return;
                size_t pos = 0;
                char32_t u = 0;
                if (flags) {
                    while (pos < n) {
                        pos += UtfEncoding<C1>::decode(src + pos, n - pos, u);
                        dst += u;
                    }
                }
                else {
                    while (pos < n) {
                        auto rc = UtfEncoding<C1>::decode(src + pos, n - pos, u);
                        if (char_is_unicode(u))
                            dst += u;
                        else
                            dst += replacement_char;
                        pos += rc;
                    }
                }
            }
        };

        template<typename C2>
         struct Recode<char32_t, C2> {
            void operator()(const char32_t *src, size_t n, std::basic_string<C2> &dst, uint32_t flags = 0) const {
                if (!src)
                    return;
                char32_t u = 0;
                C2 buf[UtfEncoding<C2>::max_units];
                for (size_t pos = 0; pos < n; ++pos) {
                    if (n == std::u32string::npos && src[pos] == 0)
                        break;
                    else if (char_is_unicode(src[pos]))
                        u = src[pos];
                    else
                        u = replacement_char;
                    auto rc = UtfEncoding<C2>::encode(u, buf);
                    dst.append(buf, rc);
                }
            }
        };

        template<typename C>
         struct Recode<C, C> {
            void operator()(const C *src, size_t n, std::basic_string<C> &dst, uint32_t flags = 0) const {
                if (!src)
                    return;

                size_t pos = 0;
                char32_t u = 0;
                C buf[UtfEncoding<C>::max_units];
                if (flags) {
                    while (pos < n) {
                        auto rc = UtfEncoding<C>::decode(src + pos, n - pos, u);
                        dst.append(src + pos, rc);
                        pos += rc;
                    }
                }
                else {
                    while (pos < n) {
                        auto rc = UtfEncoding<C>::decode(src + pos, n - pos, u);
                        if (char_is_unicode(u)) {
                            dst.append(src + pos, rc);
                        }
                        else {
                            auto rc2 = UtfEncoding<C>::encode(replacement_char, buf);
                            dst.append(buf, rc2);
                        }
                        pos += rc;
                    }
                }
            }
        };

        template<>
         struct Recode<char32_t, char32_t> {
            void operator()(const char32_t *src, size_t n, std::u32string &dst, uint32_t flags = 0) const {
                if (!src)
                    return;

                for (size_t pos = 0; pos < n; ++pos) {
                    if (n == std::u32string::npos && src[pos] == 0)
                        break;
                    else if ((flags) || char_is_unicode(src[pos]))
                        dst += src[pos];
                    else
                        dst += replacement_char;
                }
            }
        };

    };

    template<typename C1, typename C2>
    void recode(const std::basic_string<C1> &src, std::basic_string<C2> &dst,
                uint32_t flags = 0) {
        std::basic_string<C2> result;
        detail::Recode<C1, C2>()(src.data(), src.size(), result, flags);
        dst.swap(result);
    }

    template<typename C1, typename C2>
    void recode(const std::basic_string<C1> &src, size_t offset, std::basic_string<C2> &dst,
                uint32_t flags = 0) {
        std::basic_string<C2> result;
        if (offset < src.size())
            detail::Recode<C1, C2>()(src.data() + offset, src.size() - offset, result, flags);
        dst.swap(result);
    }

    template<typename C1, typename C2>
    void recode(const C1 *src, size_t count, std::basic_string<C2> &dst, uint32_t flags = 0) {
        std::basic_string<C2> result;
        detail::Recode<C1, C2>()(src, count, result, flags);
        dst.swap(result);
    }

    template<typename C2, typename C1>
    std::basic_string<C2>  recode(const std::basic_string<C1> &src, uint32_t flags = 0) {
        std::basic_string<C2> result;
        detail::Recode<C1, C2>()(src.data(), src.size(), result, flags);
        return result;
    }

    template<typename C2, typename C1>
    std::basic_string<C2> recode(const std::basic_string<C1> &src, size_t offset, uint32_t flags) {
        std::basic_string<C2> result;
        if (offset < src.size())
            detail::Recode<C1, C2>()(src.data() + offset, src.size() - offset, result, flags);
        return result;
    }

    template<typename C>
    types::u8string to_utf8(const std::basic_string<C> &src, uint32_t flags = 0) {
        return recode<char>(src, flags);
    }

    template<typename C>
    std::u16string to_utf16(const std::basic_string<C> &src, uint32_t flags = 0) {
        return recode<char16_t>(src, flags);
    }

    template<typename C>
    std::u32string to_utf32(const std::basic_string<C> &src, uint32_t flags = 0) {
        return recode<char32_t>(src, flags);
    }

    template<typename C>
    std::wstring to_wstring(const std::basic_string<C> &src, uint32_t flags = 0) {
        return recode<wchar_t>(src, flags);
    }

    template<typename C>
    vaca::String to_String(const std::basic_string<C> &src, uint32_t flags = 0) {
        using  value_type = vaca::String::value_type;
        return recode<value_type>(src, flags);
    }
}

#endif //LABWORK_UTF_H
