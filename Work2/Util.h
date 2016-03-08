///////////////////////////////////////////////////////////////////////////////
// Название:    Work2/Util.h
// Цель:        Определение типов для массива
// Автор:       Артем Матвейчук
// Создан:      05.03.2016
// Емайл:       pymba-96@mail.ru
// Программа:   Work2 | labWork
///////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef UTIL_H
#define UTIL_H

#include <cstddef>
// - std::size_t
// - std::ptrdiff_t
#include <cstdint>
// - uint8_t

namespace lab
{
	////////////////////////////////////////////////////
	template <class T, std::size_t N> class NArray;
	///////////////////////////////////////////////////
	namespace detail
	{
		namespace narray
		{
			namespace types
			{
				typedef std::size_t dim_t;
				typedef std::ptrdiff_t pos_t;
			}

			enum PTR
			{
				ASSUME,
				COPY,
				REF
			};

			template <class T> struct raw_t { static bool value() { return false; } };
			template <> struct raw_t<uint8_t> { static bool value() { return true; } };
			template <> struct raw_t<uint16_t> { static bool value() { return true; } };
			template <> struct raw_t<uint32_t> { static bool value() { return true; } };
			template <> struct raw_t<uint64_t> { static bool value() { return true; } };
			template <> struct raw_t<int8_t> { static bool value() { return true; } };
			template <> struct raw_t<int16_t> { static bool value() { return true; } };
			template <> struct raw_t<int32_t> { static bool value() { return true; } };
			template <> struct raw_t<int64_t> { static bool value() { return true; } };

		}
	}
}



#endif // !UTIL_H

