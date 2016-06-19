///////////////////////////////////////////////////////////////////////////////
// Название:    Work3/Core.h
// Цель:        Обьявление типов
// Автор:       Артем Матвейчук
// Создан:      03.05.2016
// Емайл:       pymba-96@mail.ru
// Программа:   Work3 | labWork
///////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef LABWORK_CORE_H
#define LABWORK_CORE_H

#include <string>
#include <windows.h>

#include <vaca/vaca.h>

namespace lab
{
    constexpr auto finFilePath = L"fin.txt";
    constexpr auto foutFilePath = L"fout.txt";
    const std::u32string delim = U"\r\n";
    // ==========================================================================
    // BASIC TYPES
    // ==========================================================================

    namespace types
    {
        // not in c++11 and c++14
        using char8_t = char;
        using u8string = std::basic_string<char8_t>;
        using handle_t = HANDLE;
        using byte_t = unsigned char;
    }

} // namespace lab


#endif //LABWORK_CORE_H
