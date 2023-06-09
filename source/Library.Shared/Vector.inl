#include "Vector.h"


namespace FIEAGameEngine
{
	template<typename T>
	inline Vector<T>::Vector(std::size_t capacity)
	{
		if (capacity > 0)
		{
			Reserve(capacity);
		}
	}

	template<typename T>
	inline Vector<T>::Vector(std::initializer_list<T> list)
	{
		for (const auto& value : list)
		{
			PushBack(value);
		}
	}
	template<typename T>
	inline Vector<T>::Vector(Vector&& other) noexcept:
		_data(other._data), _capacity(other._capacity), _size(other._size)
	{
		other._data = nullptr;
		other._capacity = 0 ;
		other._size = 0;
	}

	template<typename T>
	inline Vector<T>& Vector<T>::operator=(Vector&& other) noexcept
	{
		if (this != &other)
		{
			Clear();
			free(_data);

			_data = other._data;
			_capacity = other._capacity;
			_size = other._size;

			other._data = nullptr;
			other._capacity = 0;
			other._size = 0;
		}
		return *this;
	}

	template<typename T>
	inline T& Vector<T>::operator[](size_type indexOfArray)
	{
		if (indexOfArray >= _size)
		{
			throw std::runtime_error("Array Index requested is out of bounds");
		}
		return _data[indexOfArray];
	}
	
	template<typename T>
	inline const T& Vector<T>::operator[](size_type indexOfArray) const
	{
		if (indexOfArray >= _size)
		{
			throw std::runtime_error("Array Index requested is out of bounds");
		}
		return _data[indexOfArray];
	}
	template<typename T>
	Vector<T>& Vector<T>::operator=(const Vector<T>& other)
	{
		if (this != &other)
		{
			Clear();
			for (size_t i = 0; i < other.Size(); i++)
			{
				PushBack(other[i]);
			}
			Reserve(other.Capacity());
		}
		return *this;
	}

	template<typename T>
	inline Vector<T>::Vector(const Vector& rhs)
	{
		Reserve(rhs.Size());
		for (size_t i = 0; i < rhs.Size(); i++)
		{
			PushBack(rhs[i]);
		}
	}
	template<typename T>
	inline Vector<T>::~Vector()
	{
		Clear();
		free(_data);
		_data = nullptr;
	}

	template<typename T>
	inline Vector<T>::Iterator::Iterator(Vector& container, size_type containerIndex)
	{
		if (containerIndex > container.Size())
		{
			throw std::runtime_error("Array Index requested is out of bounds");	
		}
		_container = &container;
		_containerIndex = containerIndex;
	}
	template<typename T>
	inline T& Vector<T>::Iterator::operator*() const
	{
		if (_container == nullptr)
		{
			throw std::runtime_error("Dereferencing an null Iterator");
		}
		else if (_container->Size() <= _containerIndex)
		{
			throw std::runtime_error("Dereferencing out of bounds");
		}
		return  (*_container)[_containerIndex];
	}
	template <typename T>
	inline bool Vector<T>::Iterator::operator==(const Iterator& other) const
	{
		return ((_container == other._container) && (_containerIndex == other._containerIndex));
	}
	template <typename T>
	inline bool Vector<T>::Iterator::operator!=(const Iterator& other) const
	{
		return !operator==(other);
	}
	template<typename T>
	inline typename Vector<T>::Iterator& Vector<T>::Iterator::operator++()
	{
		if (_container == nullptr)
		{
			throw std::runtime_error("Iterator is not associated with a container");
		}
		else if (_container->Size() <= _containerIndex)
		{
			throw std::runtime_error("Dereferencing out of bounds");
		}
		++_containerIndex;
		return *this;
	}
	template<typename T>
	inline typename Vector<T>::Iterator& Vector<T>::Iterator::operator++(int)
	{
		operator++();
		return *this;
	}

	template<typename T>
	inline typename Vector<T>::Iterator& Vector<T>::Iterator::operator--()
	{
		if (_container == nullptr)
		{
			throw std::runtime_error("Iterator is not associated with a container");
		}
		else if (_container->Size() <= _containerIndex)
		{
			throw std::runtime_error("Dereferencing out of bounds");
		}
		if (_containerIndex > 0)
		{
			--_containerIndex;
		}
		return *this;
	}

	template<typename T>
	inline typename Vector<T>::Iterator& Vector<T>::Iterator::operator--(int)
	{
		Iterator temp = *this;
		--(*this);
		return temp;
	}


	template<typename T>
	inline typename Vector<T>::ConstIterator& Vector<T>::ConstIterator::operator--()
	{
		if (_container == nullptr)
		{
			throw std::runtime_error("Iterator is not associated with a container");
		}
		else if (_container->Size() <= _containerIndex)
		{
			throw std::runtime_error("Dereferencing out of bounds");
		}
		if (_containerIndex > 0)
		{
			--_containerIndex;
		}
		return *this;
	}

	template<typename T>
	inline typename Vector<T>::ConstIterator& Vector<T>::ConstIterator::operator--(int)
	{
		ConstIterator temp = *this;
		--(*this);
		return temp;
	}

	template<typename T>
	inline Vector<T>::ConstIterator::ConstIterator(const Vector& container, size_type containerIndex)
	{
		if (containerIndex > container.Size())
		{
			throw std::runtime_error("Array Index requested is out of bounds");
		}
		_container = &container;
		_containerIndex = containerIndex;
	}

	template<typename T>
	inline Vector<T>::ConstIterator::ConstIterator(const Iterator& other) :
		_container(other._container), _containerIndex(other._containerIndex)
	{
	}

	template<typename T>
	inline const T& Vector<T>::ConstIterator::operator*() const
	{
		if (_container == nullptr)
		{
			throw std::runtime_error("Dereferencing an null Iterator");
		}
		else if (_container->Size() <= _containerIndex)
		{
			throw std::runtime_error("Dereferencing out of bounds");
		}
		return  (*_container)[_containerIndex];
	}

	template <typename T>
	inline bool Vector<T>::ConstIterator::operator==(const ConstIterator& other) const
	{
		return ((_container == other._container) && (_containerIndex == other._containerIndex));
	}

	template <typename T>
	inline bool Vector<T>::ConstIterator::operator!=(const ConstIterator& other) const
	{
		return !operator==(other);
	}

	template<typename T>
	inline typename Vector<T>::ConstIterator& Vector<T>::ConstIterator::operator++()
	{
		if (_container == nullptr)
		{
			throw std::runtime_error("Iterator is not associated with a container");
		}
		else if (_container->Size() <= _containerIndex)
		{
			throw std::runtime_error("Dereferencing out of bounds");
		}
		++_containerIndex;
		return *this;
	}

	template<typename T>
	inline typename Vector<T>::ConstIterator& Vector<T>::ConstIterator::operator++(int)
	{
		operator++();
		return *this;
	}

	template<typename T>
	inline void Vector<T>::Reserve(size_type capacity)
	{
		if (capacity > _capacity)
		{
			T* other = reinterpret_cast<T*>(realloc(_data, capacity * sizeof(T)));
			_data = other;
			_capacity = capacity;
		}
	}

	template <typename T>
	inline size_t Vector<T>::Size() const
	{
		return _size;
	}

	template <typename T>
	inline size_t Vector<T>::Capacity() const
	{
		return _capacity;
	}


	template<typename T>
	inline bool Vector<T>::IsEmpty() const
	{
		return _size == size_t(0);
	}

	template<typename T>
	inline T& Vector<T>::Front()
	{
			if (IsEmpty())
			{
				throw std::runtime_error("List is empty");
			}
			return _data[size_t(0)];
	}

	template<typename T>
	inline const T& Vector<T>::Front() const
	{
		if (IsEmpty())
		{
			throw std::runtime_error("List is empty");
		}
		return _data[size_t(0)];
	}

	template<typename T>
	inline T& Vector<T>::Back()
	{
		if (IsEmpty())
		{
			throw std::runtime_error("List is empty");
		}
		return _data[_size - size_t(1)];
	}

	template<typename T>
	inline const T& Vector<T>::Back() const
	{
		if (IsEmpty())
		{
			throw std::runtime_error("List is empty");
		}
		return _data[_size - size_t(1)];
	}

	template<typename T>
	inline void Vector<T>::PopBack()
	{
		if (!IsEmpty())
		{
			_data[_size - size_t(1)].~T();
			_size--;
		}
	}

	template<typename T>
	inline void Vector<T>::Clear()
	{
		while (_size > 0)
		{
			PopBack();
		}
	}

	template<typename T>
	inline void Vector<T>::Resize(std::size_t size)
	{
		if (size > _size)
		{
			Reserve(size);
			for (std::size_t i = _size; i < _capacity; ++i)
			{
				new(_data + i) T();
			}
			_size = size;
		}
		else
		{
			for (std::size_t i = size; i < _size; ++i)
			{
				_data[i].~T();
			}
			if (size == 0)
			{
				_capacity = 0;
				free(_data);
				_data = nullptr;
			}
			else
			{
				T* temp = static_cast<T*>(realloc(_data, sizeof(T) * size));
				//assert(temp != nullptr);
				_data = temp;
			}
		}
	}

	template<typename T>
	inline void Vector<T>::PushBack(rvalue_reference dataToBeAdded)
	{
		//size_type newCap = 0;
		//if (_capacity == 0)
		//{
		//	newCap = 5; // default value
		//}

		if (_size == _capacity)
		{
			//newCap = _capacity + 1;
			Reserve(_capacity + size_t(1));
		}
		//Reserve(newCap);
		new(_data + _size)T(dataToBeAdded);
		_size++;
	}

	template<typename T>
	inline void Vector<T>::PushBack(const_reference dataToBeAdded)
	{
		size_type newCap = 0;
		if (_capacity == 0)
		{
			newCap = 5; // default value
		}

		if (_size == _capacity)
		{
			newCap = _capacity + 1;
			//Reserve(_capacity + size_t(1));
		}
		Reserve(newCap);
		new(_data + _size)T(dataToBeAdded);
		_size++;
	}

	template<typename T>
	inline void Vector<T>::ShrinkToFit()
	{
		if (_capacity != _size)
		{
			T* other = reinterpret_cast<T*>(realloc(_data, _size * sizeof(T)));
			_data = other;
			_capacity = _size;
		}
	}

	template<typename T>
	inline typename Vector<T>::Iterator Vector<T>::begin()
	{
		return Vector<T>::Iterator(*this, 0);
	}

	template<typename T>
	inline typename Vector<T>::Iterator Vector<T>::end()
	{
		return Vector<T>::Iterator(*this, _size);
	}

	template<typename T>
	inline typename Vector<T>::ConstIterator Vector<T>::begin() const
	{
		return cbegin();
	}

	template<typename T>
	inline typename Vector<T>::ConstIterator Vector<T>::cbegin() const
	{
		return Vector<T>::ConstIterator(*this, 0);
	}

	template<typename T>
	inline typename Vector<T>::ConstIterator Vector<T>::end() const
	{
		return cend();
	}

	template<typename T>
	inline typename Vector<T>::ConstIterator Vector<T>::cend() const
	{
		return Vector<T>::ConstIterator(*this, _size);
	}

	template<typename T>
	inline T& Vector<T>::At(size_type indexofData)
	{
		if (indexofData >= _size)
		{
			throw std::runtime_error("Array Index requested is out of bounds");
		}
		return operator[](indexofData);
	}

	template<typename T>
	inline const T& Vector<T>::At(size_type indexofData) const
	{
		if (indexofData >= _size)
		{
			throw std::runtime_error("Array Index requested is out of bounds");
		}
		return operator[](indexofData);
	}

	template<typename T>
	inline typename Vector<T>::Iterator Vector<T>::Find(const_reference key)
	{
		Iterator position = begin();

		for (; position != end(); ++position)
		{
			if (*position == key)
			{
				break;
			}
		}
		return position;
	}

	template<typename T>
	inline typename Vector<T>::ConstIterator Vector<T>::Find(const_reference key) const
	{
		ConstIterator position = begin();

		for (; position != end(); ++position)
		{
			if (*position == key)
			{
				break;
			}
		}
		return position;
	}

	template<typename T>
	inline bool Vector<T>::Remove(const Iterator& it)
	{
		if (it._container != this)
		{
			throw std::runtime_error("Containers do not match");
		}
			
		bool didRemove = false;
		if (it != end() || !IsEmpty() || it._containerIndex < _size)
		{
			_data[it._containerIndex].~T();
			memmove_s((_data + it._containerIndex), ((_capacity - it._containerIndex) * sizeof(T)), (_data + it._containerIndex + 1), ((_capacity - it._containerIndex - 1) * sizeof(T)));

			_size--;
			didRemove = true;
		}
		return didRemove;
	}

	template<typename T>
	inline bool Vector<T>::Contains(const T& val) const
	{
		return Find(val) != cend();
	}

	template<typename T>
	inline bool Vector<T>::Remove(const_reference it)
	{
		return Remove(Find(it));
	}

	template<typename T>
	inline bool Vector<T>::Remove(const Iterator& start, const Iterator& end)
	{
		if (start._container != this)
		{
			throw std::runtime_error("Containers do not match");
		}

		if (end._container != this)
		{
			throw std::runtime_error("Containers do not match");
		}

		if (start._containerIndex > end._containerIndex)
		{
			throw std::runtime_error("Containers are out of order");
		}

		bool didRemove = false;

		if (start._containerIndex != end._containerIndex)
		{
			for (std::size_t i = start._containerIndex; i < end._containerIndex; ++i)
			{
				_data[i].~T();
				--_size;
			}
			memmove_s((_data + start._containerIndex), ((_capacity - start._containerIndex) * sizeof(T)), (_data + end._containerIndex), ((_capacity - end._containerIndex) * sizeof(T)));
			didRemove = true;
		}
		return didRemove;
	}
}