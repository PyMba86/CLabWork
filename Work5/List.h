///////////////////////////////////////////////////////////////////////////////
// Название:    Work3/List.hpp
// Цель:        Вызов WinMain
// Автор:       Артем Матвейчук
// Создан:      21.05.2016
// Емайл:       pymba-96@mail.ru
// Программа:   Work3 | labWork
///////////////////////////////////////////////////////////////////////////////


#ifndef LABWORK_LIST_H
#define LABWORK_LIST_H

#include <initializer_list>

namespace lab {
	// ----------------------------------------------------------------------
	struct ListNodeBase {
		ListNodeBase *next;
		ListNodeBase *prev;

		void insert(ListNodeBase *nodeBase) noexcept;
		void remove() noexcept;
	};

	template<typename T>
	struct ListNode : ListNodeBase {
		T value;
	};

	// ----------------------------------------------------------------------
	template<typename T, typename P, typename R>
	struct ListIterator {

		using value = T;
		using pointer = P;
		using reference = R;
		using node_t = ListNode<T>;
		using difference = ptrdiff_t;
		using iterator = ListIterator<T, T*, T &>;
		using this_t = ListIterator<T, P, R>;
		using const_iterator = ListIterator<T, const T*, const T &>;

		node_t* node;

		ListIterator() noexcept;
		ListIterator(const ListNodeBase *nodeBase) noexcept;
		ListIterator(const iterator &x) noexcept;

		iterator next() const noexcept;
		iterator prev() const noexcept;

		reference operator*() const noexcept;
		pointer operator->() const noexcept;
		this_t &operator++() noexcept;
		iterator operator++(int) noexcept;
		this_t &operator--() noexcept;
		iterator operator--(int) noexcept;
	};


	// ----------------------------------------------------------------------
	template<typename T>
	class ListBase
	{
	public:

		using value_type = T;
		using node_t = ListNode<T>;
		using node_base = ListNodeBase;
		using size_type = size_t;
		using difference_type = ptrdiff_t;

	protected:
		ListBase();
		virtual ~ListBase();

		node_t* allocateNode();
		void freeNode(node_t* node);
		void initialize() noexcept;
		void clearNodeAll();

		node_base node;
		size_type m_size;
		std::allocator<node_t> allocator;

	};

	template<typename T>
	class List : public ListBase<T> {

		using base_t = ListBase<T>;
		using this_t = List<T>;

	public:
		using value_type = T;
		using pointer = T *;
		using const_pointer = const T *;
		using reference = T &;
		using const_reference = const T &;
		using size_type = typename base_t::size_type;
		using difference = typename base_t::difference_type;
		using node_t = typename base_t::node_t;
		using node_base = typename base_t::node_base;

		using base_t::m_size;
		using base_t::node;
		using base_t::allocator;
		using base_t::allocateNode;
		using base_t::freeNode;
		using base_t::clearNodeAll;
		using base_t::initialize;

		using iterator = ListIterator<T, T *, T &>;
		using const_iterator = ListIterator<T, const T *, const T &>;

		List();
		explicit List(size_type n);
		List(size_type n, const value_type& value);

		bool empty() const noexcept;

		void remove(const value_type& value);
		size_type size() const noexcept;

		void resize(size_type n);
		void resize(size_type n, const value_type& value);

		void clear() noexcept;

		iterator begin() noexcept;
		const_iterator begin() const noexcept;
		const_iterator cbegin() const noexcept;
		iterator end() noexcept;
		const_iterator end() const noexcept;
		const_iterator cend() const noexcept;

		reference front();
		const_reference front() const;
		reference back();
		const_reference back() const;

		void push_front(const value_type &value);
		void push_front(value_type &&value);
		reference push_front();
		void push_back(const value_type &value);
		void push_back(value_type &&value);
		reference push_back();

		iterator erase(const_iterator first, const_iterator last);
		iterator erase(const_iterator position);

		iterator emplace(const_iterator position, const value_type& value);
		iterator emplace(const_iterator position, value_type&& value);
		void emplace_front(const value_type&& value);
		void emplace_back(const value_type&& value);
		void emplace_front(const value_type& value);
		void emplace_back(const value_type& value);

		iterator insert(const_iterator position);
		iterator insert(const_iterator position, const value_type &value);
		iterator insert(const_iterator position, value_type &&value);
		void insert(const_iterator position, size_type n, const value_type &value);
		iterator insert(const_iterator position, std::initializer_list<value_type> ilist);

	protected:
		void insertValues(ListNodeBase* nodeBase, size_type n, const value_type& value);
		void insertValue(ListNodeBase* pNode, value_type&& value);
		void insertValue(ListNodeBase* pNode, const value_type& value);

		node_t* createNode();
		node_t* createNode(value_type&& value);
		node_t* createNode(const value_type& value);

		void eraseNode(node_base* node);

	};

	/////////////////////////////////////////////////////////////////////////
	// IMPLEMENTATION FUNCTION
	/////////////////////////////////////////////////////////////////////////

	inline void ListNodeBase::insert(ListNodeBase *nodeBase) noexcept {
		next = nodeBase;
		prev = nodeBase->prev;
		nodeBase->prev->next = this;
		nodeBase->prev = this;
	}

	// ----------------------------------------------------------------------
	inline void ListNodeBase::remove() noexcept {
		next->prev = prev;
		prev->next = next;
	}

	// ----------------------------------------------------------------------
	template<typename T, typename P, typename R>
	ListIterator<T, P, R>::ListIterator() noexcept
		: node(nullptr) {

	}

	// ----------------------------------------------------------------------
	template<typename T, typename P, typename R>
	ListIterator<T, P, R>::ListIterator(const ListNodeBase *nodeBase) noexcept
		: node(static_cast<ListNode<T> *>(const_cast<ListNodeBase *>(nodeBase))) {

	}

	// ----------------------------------------------------------------------
	template<typename T, typename P, typename R>
	ListIterator<T, P, R>::ListIterator(const iterator &x) noexcept
		: node(x.node) {
	}

	// ----------------------------------------------------------------------
	template<typename T, typename P, typename R>
	typename ListIterator<T, P, R>::iterator ListIterator<T, P, R>::next() const noexcept {
		return ListIterator(node->next);
	}

	// ----------------------------------------------------------------------
	template<typename T, typename P, typename R>
	typename ListIterator<T, P, R>::iterator ListIterator<T, P, R>::prev() const noexcept {
		return ListIterator(node->prev);
	}

	// ----------------------------------------------------------------------
	template<typename T, typename P, typename R>
	typename ListIterator<T, P, R>::reference ListIterator<T, P, R>::operator*() const noexcept {
		return node->value;
	}

	// ----------------------------------------------------------------------
	template<typename T, typename P, typename R>
	typename ListIterator<T, P, R>::pointer ListIterator<T, P, R>::operator->() const noexcept {
		return &node->value;
	}

	// ----------------------------------------------------------------------
	template<typename T, typename P, typename R>
	typename ListIterator<T, P, R>::this_t& ListIterator<T, P, R>::operator++() noexcept {
		node = static_cast<node_t*>(node->next);
		return *this;
	}

	// ----------------------------------------------------------------------
	template<typename T, typename P, typename R>
	typename ListIterator<T, P, R>::iterator ListIterator<T, P, R>::operator++(int) noexcept {
		auto temp(*this);
		node = static_cast<node_t*>(node->next);
		return temp;
	}

	// ----------------------------------------------------------------------
	template<typename T, typename P, typename R>
	typename ListIterator<T, P, R>::this_t& ListIterator<T, P, R>::operator--() noexcept {
		node = static_cast<node_t*>(node->prev);
		return *this;
	}

	// ----------------------------------------------------------------------
	template<typename T, typename P, typename R>
	typename ListIterator<T, P, R>::iterator ListIterator<T, P, R>::operator--(int) noexcept {
		auto temp(*this);
		node = static_cast<node_t*>(node->prev);
		return temp;
	}

	// ----------------------------------------------------------------------
	template <typename T>
	ListBase<T>::ListBase()
		: node(), m_size(0)
	{
		initialize();
	}

	// ----------------------------------------------------------------------
	template <typename T>
	ListBase<T>::~ListBase() {
		clearNodeAll();
	}

	// ----------------------------------------------------------------------
	template <typename T>
	typename ListBase<T>::node_t* ListBase<T>::allocateNode() {
		return allocator.allocate(1);
	}

	// ----------------------------------------------------------------------
	template <typename T>
	void ListBase<T>::freeNode(node_t* p)
	{
		allocator.deallocate(p, sizeof(node_t));
	}

	// ----------------------------------------------------------------------
	template <typename T>
	void ListBase<T>::initialize() noexcept
	{
		node.next = static_cast<ListNode<T>*>(&node);
		node.prev = static_cast<ListNode<T>*>(&node);
	}

	// ----------------------------------------------------------------------
	template <typename T>
	void ListBase<T>::clearNodeAll()
	{
		auto p = static_cast<node_t*>(node.next);

		while (p != &node)
		{
			auto const pTemp = p;
			p = static_cast<node_t*>(p->next);
			allocator.destroy(pTemp);
			allocator.deallocate(pTemp, sizeof(node_t));
		}
	}

	/////////////////////////////////////////////////////////////////////////
	// LIST
	/////////////////////////////////////////////////////////////////////////

	template <typename T, typename PointerA, typename ReferenceA,
		typename PointerB, typename ReferenceB>
		bool operator==(const ListIterator<T, PointerA, ReferenceA>& a,
			const ListIterator<T, PointerB, ReferenceB>& b) noexcept
	{
		return a.node == b.node;
	}

	// ----------------------------------------------------------------------
	template <typename T, typename PointerA, typename ReferenceA, typename PointerB, typename ReferenceB>
	bool operator!=(const ListIterator<T, PointerA, ReferenceA>& a,
		const ListIterator<T, PointerB, ReferenceB>& b) noexcept
	{
		return a.node != b.node;
	}

	// ----------------------------------------------------------------------
	template <typename T, typename P, typename R>
	bool operator!=(const ListIterator<T, P, R>& a,
		const ListIterator<T, P, R>& b) noexcept
	{
		return a.node != b.node;
	}

	// ----------------------------------------------------------------------
	template <typename T>
	List<T>::List()
		: base_t()
	{

	}

	// ----------------------------------------------------------------------
	template <typename T>
	List<T>::List(size_type n)
		: base_t()
	{
		insertValues(&node, n, value_type());
	}

	// ----------------------------------------------------------------------
	template <typename T>
	List<T>::List(size_type n, const value_type &value)
	{
		insertValues(&node, n, value);
	}

	// ----------------------------------------------------------------------
	template <typename T>  typename List<T>::iterator
		List<T>::begin() noexcept
	{
		return iterator(node.next);
	}

	// ----------------------------------------------------------------------
	template <typename T>  typename List<T>::const_iterator
		List<T>::begin() const noexcept
	{
		return const_iterator(node.next);
	}

	// ----------------------------------------------------------------------
	template <typename T>  typename List<T>::const_iterator
		List<T>::cbegin() const noexcept
	{
		return const_iterator(node.next);
	}

	// ----------------------------------------------------------------------
	template <typename T>  typename List<T>::iterator
		List<T>::end() noexcept
	{
		return iterator(&node);
	}

	// ----------------------------------------------------------------------
	template <typename T>  typename List<T>::const_iterator
		List<T>::end() const noexcept
	{
		return const_iterator(&node);
	}

	// ----------------------------------------------------------------------
	template <typename T>  typename List<T>::const_iterator
		List<T>::cend() const noexcept
	{
		return const_iterator(&node);
	}

	// ----------------------------------------------------------------------
	template <typename T>   typename List<T>::reference
		List<T>::front()
	{
		return static_cast<node_t*>(node.next)->value;
	}

	// ----------------------------------------------------------------------
	template <typename T>
	typename List<T>::const_reference
		List<T>::front() const
	{
		return static_cast<node_t*>(node.next)->value;
	}

	// ----------------------------------------------------------------------
	template <typename T>
	typename List<T>::reference
		List<T>::back()
	{
		return static_cast<node_t*>(node.prev)->value;
	}

	// ----------------------------------------------------------------------
	template <typename T>
	typename List<T>::const_reference
		List<T>::back() const
	{
		return static_cast<node_t*>(node.prev)->value;
	}

	// ----------------------------------------------------------------------
	template <typename T>
	bool List<T>::empty() const noexcept
	{
		return m_size == 0;
	}

	// ----------------------------------------------------------------------
	template <typename T>
	typename List<T>::size_type List<T>::size() const noexcept
	{
		return m_size;
	}

	// ----------------------------------------------------------------------
	template <typename T>
	void List<T>::resize(size_type n, const value_type& value)
	{
		iterator current(node.next);
		size_type i = 0;

		while ((current.node != &node) && (i < n))
		{
			++current;
			++i;
		}
		if (i == n)
			erase(current, &node);
		else
			insert(&node, n - i, value);
	}

	// ----------------------------------------------------------------------
	template <typename T>
	void List<T>::resize(size_type n)
	{
		resize(n, value_type());
	}

	// ----------------------------------------------------------------------
	template <typename T>
	void List<T>::clear() noexcept
	{
		clearNodeAll();
		initialize();
		m_size = 0;

	}

	// ----------------------------------------------------------------------
	template <typename T>
	typename List<T>::node_t* List<T>::createNode()
	{
		auto const pNode = allocateNode();
		try
		{
			allocator.construct(&pNode->value, value_type());
		}
		catch (...)
		{
			freeNode(pNode);
			throw;
		}

		return pNode;
	}

	// ----------------------------------------------------------------------
	template <typename T>
	typename List<T>::node_t* List<T>::createNode(value_type &&value) {

		auto const pNode = allocateNode();
		try
		{
			allocator.construct(&pNode->value, value_type(std::move(value)));
		}
		catch (...)
		{
			freeNode(pNode);
			throw;
		}

		return pNode;
	}

	// ----------------------------------------------------------------------
	template <typename T>
	typename List<T>::node_t* List<T>::createNode(const value_type &value) {

		auto const pNode = allocateNode();
		try
		{
			allocator.construct(&pNode->value, value_type(value));
		}
		catch (...)
		{
			freeNode(pNode);
			throw;
		}

		return pNode;
	}

	// ----------------------------------------------------------------------
	template <typename T>
	void List<T>::insertValue(ListNodeBase* pNode, value_type&& value)
	{
		auto const newNode = createNode(std::move(value));
		newNode->insert(pNode);
		++m_size;
	}

	// ----------------------------------------------------------------------
	template <typename T>
	inline void List<T>::insertValue(ListNodeBase* pNode, const value_type& value)
	{
		auto const newNode = createNode(value);
		newNode->insert(pNode);
		++m_size;
	}


	// ----------------------------------------------------------------------
	template <typename T>
	typename List<T>::iterator List<T>::insert(const_iterator position, const value_type& value)
	{
		auto const newNode = createNode(value);
		newNode->insert(position.node);
		++m_size;
		return newNode;
	}

	// ----------------------------------------------------------------------
	template <typename T>
	typename List<T>::iterator
		List<T>::insert(const_iterator position, value_type&& value)
	{
		return emplace(position, std::move(value));
	}

	// ----------------------------------------------------------------------
	template <typename T>
	typename List<T>::iterator
		List<T>::insert(const_iterator position)
	{
		auto const newNode = createNode(value_type());
		newNode->insert(position.node);
		++m_size;
		return newNode;
	}

	// ----------------------------------------------------------------------
	template <typename T>
	void List<T>::push_front(const value_type &value)
	{
		insertValue(node.next, value);
	}

	// ----------------------------------------------------------------------
	template <typename T>
	inline void List<T>::push_front(value_type &&value)
	{
		emplace(begin(), std::move(value));
	}

	// ----------------------------------------------------------------------
	template <typename T>
	typename List<T>::reference List<T>::push_front()
	{
		auto const newNode = createNode();
		newNode->insert(node.next);
		++m_size;
		return static_cast<node_t*>(node.next)->value;
	}

	// ----------------------------------------------------------------------
	template <typename T>
	void List<T>::push_back(const value_type &value)
	{
		insertValue(&node, value);
	}

	// ----------------------------------------------------------------------
	template <typename T>
	void List<T>::push_back(value_type&& value)
	{
		emplace(end(), std::move(value));
	}

	// ----------------------------------------------------------------------
	template <typename T>
	typename List<T>::reference
		List<T>::push_back()
	{
		auto const pNode = createNode();
		pNode->insert(&node);
		++m_size;
		return static_cast<node_t*>(node.prev)->value;
	}

	// ----------------------------------------------------------------------
	template <typename T>
	void List<T>::insert(const_iterator position, size_type n, const value_type &value)
	{
		insertValues(position.node, n, value);
	}

	// ----------------------------------------------------------------------
	template <typename T>
	void List<T>::insertValues(ListNodeBase *nodeBase, size_type n, const value_type &value) {
		for (; n > 0; --n)
			insertValue(nodeBase, value);
	}

	// ----------------------------------------------------------------------
	template <typename T>
	typename List<T>::iterator List<T>::emplace(const_iterator position, const value_type &value) {
		insertValue(position.node, value);
		return iterator(position.node->prev);
	}

	// ----------------------------------------------------------------------
	template <typename T>
	void List<T>::emplace_front(const value_type&& value) {
		insertValue(node.next, std::move(value));
	}

	// ----------------------------------------------------------------------
	template <typename T>
	void List<T>::emplace_back(const value_type &value)
	{
		insertValue(&node, value);
	}

	// ----------------------------------------------------------------------
	template <typename T>
	void List<T>::emplace_front(const value_type &value)
	{
		insertValue(node.next, value);
	}

	// ----------------------------------------------------------------------
	template <typename T>
	void List<T>::emplace_back(const value_type &&value)
	{
		insertValue(&node, std::move(value));
	}

	// ----------------------------------------------------------------------
	template <typename T>
	typename List<T>::iterator List<T>::emplace(const_iterator position, value_type &&value) {
		insertValue(position.node, std::move(value));
		return iterator(position.node->prev);
	}

	// ----------------------------------------------------------------------
	template <typename T>
	typename List<T>::iterator List<T>::erase(const_iterator first, const_iterator last) {
		while (first != last)
			first = erase(first);
		return iterator(last.node);
	}

	// ----------------------------------------------------------------------
	template <typename T>
	typename List<T>::iterator List<T>::erase(const_iterator position) {
		++position;
		eraseNode(position.node->prev);
		return iterator(position.node);
	}

	template <typename T>
	void List<T>::eraseNode(node_base* node_base)
	{
		node_base->remove();
		allocator.destroy(node_base);
		freeNode(static_cast<ListNode<T>*>(node_base));
		--m_size;
	}

	// ----------------------------------------------------------------------
	template <typename T>
	void List<T>::remove(const value_type &value) {
		iterator current(node.next);
		while (current.node != &node) {
			if (*current != value)
				++current;
			else {
				++current;
				erase(current.node->prev);
			}
		}
	}

	// ----------------------------------------------------------------------
	template <typename T>
	inline typename List<T>::iterator List<T>::insert(const_iterator position, std::initializer_list<value_type> ilist)
	{
		iterator itPrev(position.node);
		--itPrev;
		auto pos = ilist.begin();
		while (pos != ilist.end()) {
			insert(position.node, *pos);
			++pos;
		}
		return ++itPrev;
	}


} //namespace lab

#endif //LABWORK_LIST_H
