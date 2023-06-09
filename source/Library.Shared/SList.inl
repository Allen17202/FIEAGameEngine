#include "SList.h" 
#include "DefaultEquality.h"

namespace FIEAGameEngine
{
	template <typename T>
	inline SList<T>::SList(std::initializer_list<T> list)
	{
		for (const auto& value : list)
		{
			PushBack(value);
		}
	}
#pragma region ConstIterator
	template<typename T>
	inline SList<T>::ConstIterator::ConstIterator(const SList& container, Node* node):
		_container(&container), _node{ node }
	{
	}

	template<typename T>
	inline SList<T>::ConstIterator::ConstIterator(const Iterator& other) :
		_container(other._container), _node(other._node)
	{
	}

	template<typename T>
	inline SList<T>::ConstIterator::ConstIterator(const SList& container):
		_container(&container), _node(_container->_front)
	{
	}

	template<typename T>
	inline const T& SList<T>::ConstIterator::operator*() const
	{
		if (_node == nullptr)
		{
			throw std::runtime_error("Dereferencing an empty Iterator, please hold");
		}
		return _node->Data;
	}

	template<typename T>
	inline bool SList<T>::ConstIterator::operator!=(const ConstIterator& other) const
	{
		return !operator==(other);
	}

	template<typename T>
	inline bool SList<T>::ConstIterator::operator==(const ConstIterator& other) const
	{
		if (_container != other._container)
		{
			return false;
		}
		return (_node == other._node);
	}

	template<typename T>
	inline typename SList<T>::ConstIterator& SList<T>::ConstIterator::operator++()
	{
		if (_container == nullptr)
		{
			throw std::runtime_error("Iterator is not associated with a container");
		}

		if (_node != nullptr)
		{
			_node = _node->Next;
		}
		return *this;
	}

	template<typename T>
	inline typename SList<T>::ConstIterator& SList<T>::ConstIterator::operator++(int)
	{
		operator++();
		return *this;
	}
#pragma endregion ConstIterator
#pragma region Iterator
	template<typename T>
	inline SList<T>::Iterator::Iterator(const SList& container, Node* node) :
		_container(&container), _node{ node }
	{
	}
	template<typename T>
	inline SList<T>::Iterator::Iterator(const SList& container):
		_container(&container),_node(_container->_front)
	{
	}

	template <typename T>
	inline bool SList<T>::Iterator::operator==(const Iterator& other) const
	{
		if (_container != other._container)
		{
			return false;
		}
		return (_node == other._node); 
	}

	template <typename T>
	inline bool SList<T>::Iterator::operator!=(const Iterator& other) const
	{
		return !operator==(other);
	}

	template<typename T>
	inline typename SList<T>::Iterator& SList<T>::Iterator::operator++() 
	{
		if (_container == nullptr)
		{
			throw std::runtime_error("Iterator is not associated with a container");
		}

		if (_node != nullptr)
		{
			_node = _node->Next;
		}
		return *this;
	}

	template<typename T>
	inline typename SList<T>::Iterator& SList<T>::Iterator::operator++(int)
	{
		operator++(); 
		return *this;
	}

	template<typename T>
	inline T& SList<T>::Iterator::operator*() const
	{
		if (_node == nullptr)
		{
			throw std::runtime_error("Dereferencing an empty Iterator, please hold");
		}
		return _node->Data;
	}
#pragma endregion Iterator
#pragma region Node
	template<typename T>
	inline SList<T>::Node::Node(const T& data, Node* next) : Data(data), Next(next)
	{
	}
#pragma endregion Node
#pragma region SList Methods
	template<typename T>
	SList<T>& SList<T>::operator=(const SList<T>& other)
	{
		if (this != &other)
		{
			Clear();
			Node* currentNode = other._front;
			while (currentNode != nullptr)
			{
				PushBack(currentNode->Data);
				currentNode = currentNode->Next;
			}
		}
		return *this;
	}

	// Copy Constructor
	template<typename T>
	SList<T>::SList(const SList& rhs) 
	{
		Node* currentNode = rhs._front;
		while (currentNode != nullptr)
		{
			PushBack(currentNode->Data); 
			currentNode = currentNode->Next;
		}
	}

	// Destructor
	template<typename T>
	SList<T>::~SList()
	{
		Clear();
	}

	// Returns the number of items in the list as an unsigned int
	template <typename T> 
	inline std::size_t SList<T>::Size() const
	{
		return _size;
	}

	// Returns the front item in the linked list
	template<typename T>
	inline T& SList<T>::Front()
	{
		// Do not assert instead throw an exception
		if (IsEmpty())
		{
			throw std::runtime_error("List is empty");
		}

		return _front->Data;
	}

	// Returns the front item in the linked list
	template<typename T>
	inline const T& SList<T>::Front() const
	{
		// Do not assert insteadthrow an exception
		if (IsEmpty())
		{
			throw std::runtime_error("List is empty");
		}

		return _front->Data;
	}

	// Returns the last item in the linked list
	template<typename T>
	inline typename SList<T>::reference SList<T>::Back()
	{
		// Do not assert instead throw an exception
		if (IsEmpty())
		{
			throw std::runtime_error("List is empty");
		}

		return _back->Data;
	}

	// Returns the last item in the linked list
	template<typename T>
	inline typename SList<T>::const_reference SList<T>::Back() const
	{
		// Do not assert instead throw an exception
		if (IsEmpty())
		{
			throw std::runtime_error("List is empty");
		}

		return _back->Data;
	}

	template<typename T>
	void SList<T>::PushFront(const_reference dataToBeAddded)
	{
		_front = new Node(dataToBeAddded, _front);

		if (IsEmpty())
		{
			_back = _front;
		}
		_size++;
	}

	template<typename T>
	void SList<T>::PopFront()
	{
		if (!IsEmpty())
		{
			Node* node = _front->Next;
			delete _front;
			_front = node;
			_size--;
		}
		else
		{ 
			throw std::runtime_error("This is an empty list, You cannot Pop the front.");
		}
	}

	template<typename T>
	typename SList<T>::Iterator SList<T>::PushBack(const_reference dataToBeAdded)
	{
		Node* node = new Node(dataToBeAdded);
		if (IsEmpty())
		{
			_front = node;
			_back = _front;
		}
		else
		{
			_back->Next = node;
			_back = _back->Next;
		}
		_size++;
		return Iterator(*this, _back);
	}

	template<typename T>
	void SList<T>::PopBack()
	{
		if (IsEmpty())
		{
			throw std::runtime_error("This is an empty list, You cannot Pop the back of a empty list.");
		}

		if (_size == 1)
		{
			PopFront();
		}
		else if (_size > 1)
		{
			Node* currentNode = _front;
			while (currentNode->Next != _back)
			{
				currentNode = currentNode->Next;
			}
			currentNode->Next = nullptr;
			delete _back;
			_back = currentNode;
			--_size;
		}
	}

	template<typename T>
	inline bool SList<T>::IsEmpty() const
	{
		return _size == 0;
	}

	template<typename T>
	void SList<T>::Clear()
	{
		while (_size != size_t(0))
		{
			PopBack();
		}
	}

	template<typename T>
	inline typename SList<T>::Iterator SList<T>::begin()
	{
		return SList<T>::Iterator(*this, _front);
	}

	template<typename T>
	inline typename SList<T>::ConstIterator SList<T>::cbegin() const
	{
		return SList<T>::ConstIterator(*this, _front);
	}

	template<typename T>
	inline typename SList<T>::ConstIterator SList<T>::begin() const
	{
		return cbegin();
	}

	template<typename T>
	inline typename SList<T>::Iterator SList<T>::end()
	{
		return SList<T>::Iterator(*this, nullptr);
	}

	template<typename T>
	inline typename SList<T>::ConstIterator SList<T>::end() const
	{
		return cend();
	}

	template<typename T>
	inline typename SList<T>::ConstIterator SList<T>::cend() const
	{
		return SList<T>::ConstIterator(*this, nullptr);
	}

	template<typename T>
	inline typename SList<T>::Iterator SList<T>::InsertAfter(SList<T>::Iterator it, const T& dataToBeInserted)
	{
		if (it._container != this)
		{
			throw std::runtime_error("Containers do not match");
		}

		if (it._node == nullptr || it._node->Next == nullptr)
		{
			PushBack(dataToBeInserted);
			return Iterator(*this, _back);
		}

		Node* node = it._node->Next;
		it._node->Next = new Node(dataToBeInserted, node);
		_size++;
		++it;
		return it;
	}

	template<typename T>
	inline bool SList<T>::Remove(const_reference value)
	{
		return Remove(Find(value));
	}

	template<typename T>
	inline bool SList<T>::Remove(Iterator it)
	{
		if (it._container != this)
		{
			throw std::runtime_error("Containers do not match");
		}

		bool didRemove = false;
		if (_size > 0)
		{
			if (it._node == _front)
			{
				PopFront();
				didRemove = true;
			}

			if (it._node == _back)
			{
				PopBack();
				didRemove = true;
		 	}

			Iterator itTwo = begin();
			while (itTwo._node->Next != nullptr)
			{
				if (itTwo._node->Next == it._node)
				{
					itTwo._node->Next = it._node->Next;
					it._node->Next = nullptr;
					delete it._node;
					--_size;
					didRemove =  true;
					break;
				}
				++itTwo;
			}
		}
		return false;
	}

	template<typename T>
	inline typename SList<T>::Iterator SList<T>::Find(const_reference value, EqualityFunctor equals)
	{
		Iterator position = begin();
		Node* node = _front;

		for (; position != end(); ++position)
		{
			if (equals(node->Data, value))
			{
				break;
			}
			node = node->Next;
		}
		return position;
	}


	template<typename T>
	inline typename SList<T>::ConstIterator SList<T>::Find(const_reference value, EqualityFunctor equals) const
	{
		ConstIterator position = begin();
		Node* node = _front;

		for (; position != end(); ++position)
		{
			if (equals(node->Data, value))
			{
				break;
			}
			node = node->Next;
		}
		return position;
	}

#pragma endregion SList Methods
}