///////////////////////////////////////////////////////////////////////////////
// Название:    Work2/NArrayHeader.h
// Цель:        Информация о массиве
// Автор:       Артем Матвейчук
// Создан:      05.03.2016
// Емайл:       pymba-96@mail.ru
// Программа:   Work2 | labWork
///////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef NARRAYHEADER_H
#define NARRAYHEADER_H

#include "Util.h"

namespace lab
{
	namespace detail
	{
		namespace narray
		{
			template <class T, class A = std::allocator<T>>
			class NArrayHeader
			{
			public:
				class Node
				{
				public:
					T* data;
					std::size_t size;
					std::size_t refs;
					A alloc;
					bool isOwned;

					Node()
						: data(nullptr),
						size(0),
						refs(0),
						alloc(),
						isOwned(true)
					{

					}

					Node(std::size_t _size)
						: data(nullptr),
						size(_size),
						refs(1),
						alloc(),
						isOwned(true)
					{
						data = alloc.allocate(_size);
						if (!raw_t<T>::value())
							for (size_t i = 0; i < _size; ++i)
								alloc.construct(data + i);
					}

					Node(std::size_t _size, const T& val)
						: data(nullptr),
						size(_size),
						refs(1),
						alloc(),
						isOwned(true)
					{
						data = alloc.allocate(_size);
						for (std::size_t i = 0; i < _size; ++i)
							alloc.construct(data + i, val);
					}

					Node(std::size_t _size, T* _data, PTR ltype)
						: data(nullptr),
						size(_size),
						refs(1),
						alloc(),
						isOwned(true)
					{
						switch (ltype)
						{
						case PTR::ASSUME:
							data = _data;
							break;
						case PTR::COPY:
							data = alloc.allocate(_size);
							for (size_t i = 0; i < _size; ++i)
								alloc.construct(data + i, _data[i]);
							break;
						case PTR::REF:
							data = _data;
							isOwned = false;
							break;
						default:
							break;
						}
					}

					template <class Generator>
					Node(std::size_t _size, Generator gen)
						: data(nullptr),
						size(_size),
						refs(1),
						alloc(),
						isOwned(true)
					{
						data = alloc.allocate(_size);
						for (size_t i = 0; i < _size; ++i)
							alloc.construct(data + i, gen());
					}

					~Node()
					{
						if (data && isOwned)
						{
							if (!raw_t<T>::value())
								for (std::size_t i = 0; i < size; ++i)
									alloc.destroy(data + i);
							alloc.deallocate(data, size);
						}
					}
				};

				NArrayHeader()
					: m_node(nullptr)
				{

				}

				NArrayHeader(types::pos_t size)
					: m_node(nullptr)
				{
					if (size > 0)
						m_node = new Node(size);
				}

				NArrayHeader(types::pos_t size, const T& val)
					: m_node(nullptr)
				{
					if (size > 0)
						m_node = new Node(size, val);
				}

				NArrayHeader(types::pos_t size, T* ptr, PTR ltype)
					: m_node(nullptr)
				{
					if (size > 0)
						m_node = new Node(size, ptr, ltype);
				}

				template <class Generator>
				NArrayHeader(types::pos_t size, Generator gen)
					: m_node(nullptr)
				{
					if (size > 0)
						m_node = new Node(size, gen);
				}


				NArrayHeader(const NArrayHeader<T, A>& header)
					: m_node(header.m_node)
				{
					_incref();
				}

				~NArrayHeader()
				{
					_decref();
				}

				NArrayHeader<T, A>& operator= (const NArrayHeader<T, A>& header)
				{
					_decref();
					m_node = header.m_node;
					_incref();
					return *this;
				}

				void clear()
				{
					_decref();
					m_node = nullptr;
				}

				Node& operator* () const
				{
					return *m_node;
				}
				Node* operator-> () const
				{
					return m_node;
				}

				Node* _ptr() const
				{
					return m_node;
				}


			private:
				Node* m_node;

				void _incref()
				{
					if (m_node)
						++m_node->refs;
				}

				void _decref()
				{
					if (m_node && --m_node->refs == 0)
						delete m_node;
				}
			};
		}
	}
}


#endif // !NARRAYHEADER_H

