///////////////////////////////////////////////////////////////////////////////
// Название:    Work2/NArrayIterator.h
// Цель:        Описание итераторов для массива
// Автор:       Артем Матвейчук
// Создан:      05.03.2016
// Емайл:       pymba-96@mail.ru
// Программа:   Work2 | labWork
///////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef NARRAYITERATOR_H
#define NARRAYITERATOR_H

#include <iterator>
// - std::random_acess_iterator_tag

#include "Util.h"

namespace lab
{
	namespace detail
	{
		namespace narray
		{
			template <class T, types::dim_t N>
			class NArrayIterator 
			{
			public:
				typedef std::random_access_iterator_tag iterator_category;
				typedef typename std::remove_const<T>::type type;
				typedef T value_type;
				typedef std::ptrdiff_t difference_type;
				typedef T& reference;
				typedef T* pointer;

			private:
				using Point = detail::narray::Point<N>;
				using NArrayHeader = detail::narray::NArrayHeader<type>;
				using dim_t = detail::narray::types::dim_t;
				using pos_t = detail::narray::types::pos_t;
				using PTR = detail::narray::PTR;

			public:
				NArrayIterator()
					: m_header(),
					m_base(nullptr),
					m_dims(),
					m_step(),
					m_pos(0)
					
				{

				}

				NArrayIterator(const NArray<T,N>& arr, pos_t pos = 0)
					: m_header(arr.m_header),
					m_base(arr.m_base),
					m_dims(arr.m_dims),
					m_step(arr.m_step),
					m_pos(pos)
					{

					}

			
				NArrayIterator(const NArrayIterator<T, N>& iter)
					: m_header(iter.m_header),
					m_base(iter.m_base),
					m_dims(iter.m_dims),
					m_step(iter.m_step),
					m_pos(iter.m_pos)
				{

				}

				NArrayIterator(const NArrayIterator<T, N>& iter, pos_t pos)
					: m_header(iter.m_header),
					m_base(iter.m_base),
					m_dims(iter.m_dims),
					m_step(iter.m_step),
					m_pos(pos)
				{

				}

				NArrayIterator<T, N>& operator= (const NArrayIterator<T, N>& iter)
				{
					m_header = iter.m_header;
					m_base = iter.m_base;
					m_dims = iter.m_dims;
					m_step = iter.m_step;
					m_pos = iter.m_pos;

					return *this;
				}


				NArrayIterator<T, N>& operator+= (const ptrdiff_t pos)
				{
					m_pos += pos;
					return *this;
				}


				NArrayIterator<T, N>& operator-= (const ptrdiff_t pos)
				{
					m_pos -= pos;
					return *this;
				}


				reference operator* () const
				{
					if (m_pos < 0 || m_pos >= _size(m_dims))
						throw std::domain_error("NArrayIterator*(): pointing outside bounds");

					return *_at(m_pos);
				}


				pointer operator-> () const
				{
					if (m_pos < 0 || m_pos > _size(m_dims))
						throw std::domain_error("NArrayIterator*(): pointing outside bounds");

					return _at(m_pos);
				}

				reference operator[] (pos_t pos) const
				{
					pos_t loc = m_pos + pos;
					if (loc < 0 || loc > _size(m_dims))
						throw std::domain_error("NArrayIterator*(): pointing outside bounds");

					return *_at(loc);
				}

				bool operator==(const NArrayIterator<T, N>& iter) const
				{
					return m_base == iter.m_base &&
						m_dims == iter.m_dims &&
						m_step == iter.m_step &&
						m_pos == iter.m_pos;
				}
				
				bool operator!= (const NArrayIterator<T, N>& iter) const
				{
					return !(*this == iter);
				}

				bool operator<  (const NArrayIterator<T, N>& iter) const
				{
					return m_pos < iter.m_pos;
				}
				
				bool operator>  (const NArrayIterator<T, N>& iter) const
				{
					return m_pos > iter.m_pos;
				}

				bool operator<= (const NArrayIterator<T, N>& iter) const
				{
					return m_pos <= iter.m_pos;
				}

				bool operator>= (const NArrayIterator<T, N>& iter) const
				{
					return !(*this < iter);
				}

				NArrayIterator<T, N>& operator++ ()
				{
					++m_pos;
					return *this;
				}

				NArrayIterator<T, N>& operator-- ()
				{
					--m_pos;
					return *this;
				}

				NArrayIterator<T, N> operator++ (int)
				{
					return NArrayIterator<T, N>(*this, m_pos++);
				}

				NArrayIterator<T, N> operator-- (int)
				{
					return NArrayIterator<T, N>(*this, m_pos--);
				}

				difference_type operator+ (const NArrayIterator<T, N>& iter) const
				{
					return m_pos + iter.m_pos;
				}

				difference_type operator- (const NArrayIterator<T, N>& iter) const
				{
					return m_pos - iter.m_pos;
				}

				NArrayIterator<T, N> operator+ (const ptrdiff_t pos)
				{
					return NArrayIterator<T, N>(*this, m_pos + pos);
				}

				NArrayIterator<T, N> operator- (const ptrdiff_t pos)
				{
					return NArrayIterator<T, N>(*this, m_pos - pos);
				}

				Point position() const
				{
					return _idx2pos(m_dims, m_pos);
				}

			private:
				NArrayHeader m_header;
				type* m_base;
				Point m_dims;
				Point m_step;
				pos_t m_pos;

				pointer _at(pos_t pos) const
				{
					Point loc = _idx2pos(m_dims, m_pos);
					pointer ptr = m_base;
					for (dim_t i = 0; i < N; ++i)
						ptr += loc[i] * m_step[i];

					return ptr;
				}
			};
		}
	}
}


#endif // !NARRAYITERATOR_H

