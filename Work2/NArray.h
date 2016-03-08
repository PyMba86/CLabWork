///////////////////////////////////////////////////////////////////////////////
// Название:    Work2/NArray.h
// Цель:        Многомерный массив
// Автор:       Артем Матвейчук
// Создан:      04.03.2016
// Емайл:       pymba-96@mail.ru
// Программа:   Work2 | labWork
///////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef ARRAY_H
#define ARRAY_H

#include <utility>
// - std::move
// - std::forward
// - std::initializer_list
// - std::declval
// - std::swap
#include <stdexcept>
// - std::invalid_argument
// - std::domain_error
// - std::out_of_range
#include <memory>
// - std::allocator
#include <type_traits>
// - std::remove_const
#include <array>
// - std::array

#include "Point.h"
#include "NArrayHeader.h"
#include "NArrayIterator.h"

namespace lab
{
	//Многомерный массив
	template <class T, detail::narray::types::dim_t N>
		class NArray
		{
		public:
			typedef typename std::remove_const<T>::type type;
			typedef T value;
			typedef T* pointer;
			typedef T& reference;
			typedef detail::narray::NArrayIterator<value, N> iterator;

		private:
			using Point = detail::narray::Point<N>;
			using NArrayHeader = detail::narray::NArrayHeader<type>;
			using dim_t = detail::narray::types::dim_t;
			using pos_t = detail::narray::types::pos_t;
			using PTR = detail::narray::PTR;

		public:

			//////// Констукторы ////////////////////////
			NArray()
				: m_header(), m_base(nullptr), m_dims(), m_step()
			{

			}

			explicit NArray(const Point& size)
				: m_header(),
				m_base(nullptr),
				m_dims(size),
				m_step(_step(size))
			{
				if (isValid())
					create();
				else
					clean();
			}

			NArray(const Point& size, const T& val)
				: m_header(),
				m_base(nullptr),
				m_dims(size),
				m_step(detail::narray::_step(size))
			{
				if (isValid())
					create(val);
				else
					clean();
			}

			NArray(const Point& size, T* ptr, PTR ltype)
				: m_header(),
				m_base(nullptr),
				m_dims(size),
				m_step(detail::narray::_step(size))
			{
				if (isValid())
					create(ptr, ltype);
				else
					clean();
			}

			NArray(const Point& size, std::initializer_list<T> list)
				: m_header(),
				m_base(nullptr),
				m_dims(size),
				m_step(detail::narray::_step(size))
			{
				if (isValid() && list.size() == _size(m_dims))
					create((T*)list.begin(), PTR::COPY);
				else
					clean();
			}

			template <class Generator>
			NArray(const Point& size, Generator gen)
				: m_header(),
				m_base(nullptr),
				m_dims(size),
				m_step(detail::narray::_step(size))
			{
				if (isValid())
					create(gen);
				else
					clean();
			}

			////////////Основыные функции ////////////////
			//Ссылка на элемент
			reference at(const Point& loc)
			{
				T* ptr = m_base;
				for (dim_t i = 0; i < N; ++i)
					if (loc[i] >= m_dims[i] || loc[i] < 0)
						throw std::out_of_range("at() element larger then dimensions");
					else
						ptr += loc[i] * m_step[i];
				return *ptr;
			}
			 

			//Возрашает размерность(обьем N)
			Point dims() const
			{
				return m_dims;
			}

			//Возрашает шаг по массиву
			Point step() const
			{
				return m_step;
			}

			//Возрашет колличество элементов в массиве
			pos_t size() const
			{
				return detail::narray::_size(m_dims);
			}

			//Возрашает длину массива в опрделенном измерении
			pos_t length(dim_t dim) const
			{
				if (dim >= N)
					throw std::out_of_range("lnegth() arg out of bounds");
				
				return m_dims[dim];
			}

			//Проверка на пустоту
			bool empty() const
			{
				return m_header._ptr() == nullptr;
			}

			//Указатель на участок начала массива
			pointer _basePtr()
			{
				return m_base;
			}

		//////////////////// Итераторы //////////////////////////
			iterator begin()
			{
				return iterator(*this);
			}

			iterator end()
			{
				return iterator(*this,size());
			}

			//Обрашение к protected и private переменным, функцииям
			friend class detail::narray::NArrayIterator<type, N>;

		protected:
			NArrayHeader m_header;
			type* m_base;
			Point m_dims;
			Point m_step;

		private:
			bool isValid() const
			{
				for (dim_t i = 0; i < N; ++i)
					if (m_dims[i] == 0)
						return false;
					else if (m_dims[i] < 0)
						throw std::invalid_argument("The size can not be negative");
				return true;
			}

			void create()
			{
				pos_t size = detail::narray::_size(m_dims);
				if (size > 0)
				{
					m_header = NArrayHeader(size);
					m_base = m_header->data;
				}
			}

			void create(const T& val)
			{
				pos_t size = detail::narray::_size(m_dims);
				if (size > 0)
				{
					m_header = NArrayHeader(size, val);
					m_base = m_header->data;
				}
			}

			void create(T* ptr, PTR ltype)
			{
				pos_t size = detail::narray::_size(m_dims);
				if (size > 0)
				{
					m_header = NArrayHeader(size, ptr, ltype);
					m_base = m_header->data;
				}
			}

			template <class Generator>
			void create(Generator gen)
			{
				pos_t size = detail::narray::_size(m_dims);
				if (size > 0)
				{
					m_header = NArrayHeader(size, gen);
					m_base = m_header->data;
				}
			}

			void clean()
			{
				m_dims.clear();
				m_step.clear();
			}
		};
	
};


#endif // !ARRAY_H
