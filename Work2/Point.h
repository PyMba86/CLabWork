///////////////////////////////////////////////////////////////////////////////
// Название:    Work2/Point.h
// Цель:        Координаты значения в массиве
// Автор:       Артем Матвейчук
// Создан:      05.03.2016
// Емайл:       pymba-96@mail.ru
// Программа:   Work2 | labWork
///////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef POINT_H
#define POINT_H

#include "Util.h"

namespace lab
{
	namespace detail
	{
		namespace narray
		{
			template <types::dim_t N>
			class Point
			{
			public:

				Point()
				{
					m_size.fill(0); // заполнить контейнер 0 
				}

				Point(std::initializer_list<types::pos_t> list)
				{
					if (list.size() == 1)
						m_size.fill(*list.begin());
					else if (list.size() != N)
						throw std::invalid_argument("The list should match the size of");
					else
					{
						auto iter = list.begin();
						for (types::pos_t i = 0; i < N; ++i, ++iter)
							m_size[i] = *iter;
					}

				}

				Point(const Point<N>& pt)
					: m_size(pt.m_size)
				{

				}

				/////////// Операторы ///////////////////

				Point<N>& operator = (const Point<N>& pt)
				{
					m_size = pt.m_size;
					return *this;
				}

				Point<N>& operator += (const Point<N>& pt)
				{
					for (types::dim_t i = 0; i < N; ++i)
						m_size[i] += pt.m_size[i];
					return *this;
				}
				Point<N>& operator += (types::pos_t val)
				{
					for (types::dim_t i = 0; i < N; ++i)
						m_size[i] += val;
					return *this;
				}

				Point<N>& operator -= (const Point<N>& pt)
				{
					for (types::dim_t i = 0; i < N; ++i)
						m_size[i] -= pt.m_size[i];
					return *this;
				}

				Point<N>& operator -= (types::pos_t val)
				{
					for (types::dim_t i = 0; i < N; ++i)
						m_size[i] -= val;
					return *this;
				}

				Point<N>& operator *= (types::pos_t val)
				{
					for (types::dim_t i = 0; i < N; ++i)
						m_size[i] *= val;
					return *this;
				}

				Point<N>& operator /= (types::pos_t val)
				{
					for (types::dim_t i = 0; i < N; ++i)
						m_size[i] /= val;
					return *this;
				}

				types::pos_t& operator[] (types::dim_t n)
				{
					return m_size[n];
				}

				const types::pos_t& operator[] (types::dim_t n) const
				{
					return m_size[n];
				}

				//Функции заполнения и сброса значений
				void clear()
				{
					m_size.fill(0);
				}

				void fill(types::pos_t val)
				{
					m_size.fill(val);
				}


			private:
				std::array<types::pos_t, N> m_size;
			};



			//Вычисление шага для поиска элемента
			template <types::dim_t N>
			Point<N> _step(const Point<N>& dims)
			{
				Point<N> ret;
				ret[N - 1] = 1;
				for (types::dim_t i = N - 1; i > 0; --i)
					ret[i - 1] = ret[i] * dims[i];
				return ret;
			}

			//Вычисление размера
			template <types::dim_t N>
			types::pos_t _size(const Point<N>& dims)
			{
				types::pos_t ret = dims[0];
				for (types::dim_t i = 1; i < N; ++i)
					ret *= dims[i];
				return ret;
			}

			template <types::dim_t N>
			Point<N> _idx2pos(const Point<N>& dims, types::pos_t idx)
			{
				Point<N> ret;
				for (int i = N - 1; i >= 0; --i)
				{
					ret[i] = idx % dims[i];
					idx /= dims[i];
				}
				return ret;
			}

			template <types::dim_t N>
			types::pos_t _pos2idx(const Point<N>& dims, const Point<N>& pos)
			{
				types::pos_t idx = pos[N - 1];
				for (int i = N - 2; i >= 0; --i)
					idx += pos[i] * dims[i + 1];
				return idx;
			}


			template <types::dim_t N, types::dim_t M>
			bool operator== (const Point<N>& lhs, const Point<M>& rhs)
			{
				if (N != M)
					return false;

				for (types::dim_t i = 0; i < N; ++i)
					if (!(lhs[i] == rhs[i]))
						return false;

				return true;
			}


			template <types::dim_t N, types::dim_t M>
			bool operator!= (const Point<N>& lhs, const Point<M>& rhs)
			{
				if (N != M)
					return true;

				for (types::dim_t i = 0; i < N; ++i)
					if (!(lhs[i] == rhs[i]))
						return true;

				return false;
			}


			template <types::dim_t N>
			Point<N> operator+ (const Point<N>& lhs, const Point<N>& rhs)
			{
				Point<N> ret;
				for (types::dim_t i = 0; i < N; ++i)
					ret[i] = lhs[i] + rhs[i];
				return ret;
			}


			template <types::dim_t N>
			Point<N> operator- (const Point<N>& lhs, const Point<N>& rhs)
			{
				Point<N> ret;
				for (types::dim_t i = 0; i < N; ++i)
					ret[i] = lhs[i] - rhs[i];
				return ret;
			}



			template <types::dim_t N>
			Point<N> operator+ (const Point<N>& lhs, types::pos_t rhs)
			{
				Point<N> ret;
				for (types::dim_t i = 0; i < N; ++i)
					ret[i] = lhs[i] + rhs;
				return ret;
			}


			template <types::dim_t N>
			Point<N> operator- (const Point<N>& lhs, types::pos_t rhs)
			{
				Point<N> ret;
				for (types::dim_t i = 0; i < N; ++i)
					ret[i] = lhs[i] - rhs;
				return ret;
			}

			template <types::dim_t N>
			Point<N> operator* (const Point<N>& lhs, types::pos_t rhs)
			{
				Point<N> ret;
				for (types::dim_t i = 0; i < N; ++i)
					ret[i] = lhs[i] * rhs;
				return ret;
			}


			template <types::dim_t N>
			Point<N> operator/ (const Point<N>& lhs, types::pos_t rhs)
			{
				Point<N> ret;
				for (types::dim_t i = 0; i < N; ++i)
					ret[i] = lhs[i] / rhs;
				return ret;
			}


			template <types::dim_t N>
			Point<N> operator+ (types::pos_t lhs, const Point<N>& rhs)
			{
				Point<N> ret;
				for (types::dim_t i = 0; i < N; ++i)
					ret[i] = lhs + rhs[i];
				return ret;
			}

			template <types::dim_t N>
			Point<N> operator- (types::pos_t lhs, const Point<N>& rhs)
			{
				Point<N> ret;
				for (types::dim_t i = 0; i < N; ++i)
					ret[i] = lhs - rhs[i];
				return ret;
			}

			template <types::dim_t N>
			Point<N> operator* (types::pos_t lhs, const Point<N>& rhs)
			{
				Point<N> ret;
				for (types::dim_t i = 0; i < N; ++i)
					ret[i] = lhs * rhs[i];
				return ret;
			}

			template <types::dim_t N>
			Point<N> operator/ (types::pos_t lhs, const Point<N>& rhs)
			{
				Point<N> ret;
				for (types::dim_t i = 0; i < N; ++i)
					ret[i] = lhs / rhs[i];
				return ret;
			}
		}
	}
}

#endif // !POINT_H


