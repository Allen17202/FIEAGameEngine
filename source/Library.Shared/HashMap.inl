#include "HashMap.h"

namespace FIEAGameEngine
{
	template<typename TKey, typename TData>
	inline HashMap<TKey, TData>::HashMap(std::initializer_list<pair_type> list)
	{
		_table.Reserve(list.size());
		for (size_type i = 0; i < list.size(); ++i)
		{
			_table.PushBack(chain_type{});
		}

		for (auto& value : list)
		{
			Insert(value);
		}
	}
	template<typename TKey, typename TData>
	inline HashMap<TKey, TData>::HashMap(HashMap&& rhs) noexcept :
		_table(std::move(rhs._table)), _size(rhs._size), _hash(std::move(rhs._hash))
	{
		rhs._size = 0;
	}
	template<typename TKey, typename TData>
	inline HashMap<TKey, TData>::HashMap(size_type chainCount, HashFunctor hash) :
		_hash(hash)
	{
		if (chainCount < 2)
		{
			chainCount = 2;
		}

		_table.Reserve(chainCount);
		for (size_type i = 0; i < chainCount; ++i)
		{
			_table.PushBack(chain_type{});
		}
	}

	template<typename TKey, typename TData>
	inline HashMap<TKey, TData>& HashMap<TKey, TData>::operator=(HashMap&& rhs) noexcept
	{
		if (this != &rhs)
		{
			_table = std::move(rhs._table);
			_size = rhs._size;
			_hash = std::move(rhs._hash);
			rhs._size = 0;
		}
		return *this;
	}

	template<typename TKey, typename TData>
	inline void HashMap<TKey, TData>::Remove(const TKey& key, EqualityFunctor equals)
	{

		if (Capacity() == 0 || _size == 0) 
		{ 
			return; 
		}
		size_t hashIndex = (_hash(key)) % Capacity();

		if (_table[hashIndex].IsEmpty()) 
		{ 
			return; 
		}

		std::pair<TKey, TData> temp(key, TData());
		//auto chainIt = _table[hashIndex].Find(temp, [&equals](pair_type left, pair_type right) {return equals(left.first, right.first); });
		auto chainIt = _table[hashIndex].Find(temp);
		if (chainIt == _table[hashIndex].end()) 
		{ 
			return; 
		}
		--_size;
		_table[hashIndex].Remove(chainIt);
	}

	template<typename TKey, typename TData>
	inline TData& HashMap<TKey, TData>::operator[](const TKey& key)
	{
		
		Iterator it = Find(key);
		if (it != end())
		{
			return (*it).second;
			
		}
		return (*Insert(std::make_pair(key, TData())).first).second;
	}


	template<typename TKey, typename TData>
	inline const TData& HashMap<TKey, TData>::operator[](const TKey& key) const
	{
		return At(key);
	}

	template<typename TKey, typename TData>
	inline HashMap<TKey, TData>::Iterator::Iterator(HashMap<TKey, TData>& container, size_type containerIndex, typename chain_type::Iterator it) :
		_container(&container), _containerIndex(containerIndex)
	{
		_it = it;
	}

	template<typename TKey, typename TData>
	inline std::pair<const TKey, TData>& HashMap<TKey, TData>::Iterator::operator*() const
	{
		if (_container == nullptr)
		{
			throw std::runtime_error("Iterator is not associated with a container");
		}
		if (_containerIndex >=_container->Capacity())
		{
			throw std::runtime_error("Dereferencing nullpointer");
		}
		return *_it;
	}

	template<typename TKey, typename TData>
	inline std::pair<const TKey, TData>* HashMap<TKey, TData>::Iterator::operator->() const
	{
		if (_container == nullptr)
		{
			throw std::runtime_error("Iterator is not associated with a container");
		}
		return &(this->operator*());
	}

	template<typename TKey, typename TData>
	inline bool HashMap<TKey, TData>::Iterator::operator==(const Iterator& other) const
	{
		return ((_container == other._container) && (_containerIndex == other._containerIndex) && (_it == other._it));
	}

	template<typename TKey, typename TData>
	inline bool HashMap<TKey, TData>::Iterator::operator!=(const Iterator& other) const
	{
		return !operator==(other);
	}

	template<typename TKey, typename TData>
	inline typename HashMap<TKey, TData>::Iterator& HashMap<TKey, TData>::Iterator::operator++()
	{
		if (_container == nullptr)
		{
			throw std::runtime_error("Iterator is not associated with a container");
		}
		if (_containerIndex >= _container->Capacity())
		{
			throw std::runtime_error("Out of bounds");
		}

		if (_it != _container->_table[_containerIndex].end())
		{
			_it++;
			if (_it != _container->_table[_containerIndex].end())
			{
				return *this;
			}
			else
			{
				do { _containerIndex++; } while (_containerIndex < _container->Capacity() && _container->_table[_containerIndex].IsEmpty());
				if (_containerIndex >= _container->Capacity())
				{
					*this = _container->end();
					return *this;
				}
				_it = _container->_table[_containerIndex].begin();
			}
		}
		return *this;
	}

	template<typename TKey, typename TData>
	inline typename HashMap<TKey, TData>::Iterator HashMap<TKey, TData>::Iterator::operator++(int)
	{
		operator++();
		return *this;
	}

	template<typename TKey, typename TData>
	inline HashMap<TKey, TData>::ConstIterator::ConstIterator(const HashMap<TKey, TData>& container, size_type containerIndex, typename chain_type::ConstIterator it):
		_container(&container), _containerIndex(containerIndex)
	{
		_it = it;
	}

	template<typename TKey, typename TData>
	inline HashMap<TKey, TData>::ConstIterator::ConstIterator(const Iterator& other) :
		_container(other._container), _containerIndex(other._containerIndex)
	{
		_it = other._it;
	}

	template<typename TKey, typename TData>
	inline const std::pair<const TKey, TData>& HashMap<TKey, TData>::ConstIterator::operator*() const
	{
		if (_container == nullptr)
		{
			throw std::runtime_error("Iterator is not associated with a container");
		}
		if (_containerIndex >=_container->Capacity())
		{
			throw std::runtime_error("Dereferencing nullpointer");
		}
		return *_it;
	}

	template<typename TKey, typename TData>
	inline const std::pair<const TKey, TData>* HashMap<TKey, TData>::ConstIterator::operator->() const
	{
		if (_container == nullptr)
		{
			throw std::runtime_error("Iterator is not associated with a container");
		}
		if (_containerIndex >= _container->Capacity())
		{
			throw std::runtime_error("Out of bounds");
		}
		return &(this->operator*());
	}

	template<typename TKey, typename TData>
	inline bool HashMap<TKey, TData>::ConstIterator::operator==(const ConstIterator& other) const
	{
		return ((_container == other._container) && (_containerIndex == other._containerIndex) && (_it == other._it));
	}

	template<typename TKey, typename TData>
	inline bool HashMap<TKey, TData>::ConstIterator::operator!=(const ConstIterator& other) const
	{
		return !operator==(other);
	}

	template<typename TKey, typename TData>
	inline typename HashMap<TKey, TData>::ConstIterator& HashMap<TKey, TData>::ConstIterator::operator++()
	{
		if (_container == nullptr)
		{
			throw std::runtime_error("Iterator is not associated with a container");
		}
		if (_containerIndex >= _container->Capacity())
		{
			throw std::runtime_error("Out of bounds");
		}

		if (_it != _container->_table[_containerIndex].end())
		{
			_it++;
			if (_it != _container->_table[_containerIndex].end())
			{
				return *this;
			}
			else
			{
				do { _containerIndex++; } while (_containerIndex < _container->Capacity() && _container->_table[_containerIndex].IsEmpty());
				if (_containerIndex >= _container->Capacity())
				{
					*this = _container->end();
					return *this;
				}
				_it = _container->_table[_containerIndex].begin();
			}
		}
		return *this;
	}

	template<typename TKey, typename TData>
	inline typename HashMap<TKey, TData>::ConstIterator HashMap<TKey, TData>::ConstIterator::operator++(int)
	{
		operator++();
		return *this;
	}

	template<typename TKey, typename TData>
	inline typename HashMap<TKey, TData>::Iterator HashMap<TKey, TData>::begin()
	{
		if (_size == 0)
		{
			return this->end();
		}
		size_t index;
		for (index = 0; index < Capacity(); index++)
		{
			if (!_table[index].IsEmpty())
			{
				break;
			}
		}
		return Iterator(*this, index, _table[index].begin());
	}

	template<typename TKey, typename TData>
	inline typename HashMap<TKey, TData>::Iterator HashMap<TKey, TData>::end()
	{
		return Iterator(*this, Capacity(), typename chain_type::Iterator());
	}

	template<typename TKey, typename TData>
	inline typename HashMap<TKey, TData>::ConstIterator HashMap<TKey, TData>::begin() const
	{
		return cbegin();
	}

	template<typename TKey, typename TData>
	inline typename HashMap<TKey, TData>::ConstIterator HashMap<TKey, TData>::cbegin() const
	{
		if(_size == 0)
		{
			return this->end();
		}
		size_t index = 0;
		for (index = 0; index < Capacity(); ++index)
		{
			if (!_table[index].IsEmpty())
			{
				break;
			}
		}
		return ConstIterator(*this, index, _table[index].begin());
	}

	template<typename TKey, typename TData>
	inline typename HashMap<TKey, TData>::ConstIterator HashMap<TKey, TData>::cend() const
	{
		return ConstIterator(*this, Capacity(), chain_type::ConstIterator());
	}

	template<typename TKey, typename TData>
	inline typename HashMap<TKey, TData>::ConstIterator HashMap<TKey, TData>::end() const
	{
		return typename HashMap<TKey, TData>::ConstIterator(*this, Capacity(), typename HashMap<TKey, TData>::chain_type::ConstIterator());
	}
	template<typename TKey, typename TData>
	inline  typename HashMap<TKey, TData>::Iterator HashMap<TKey, TData>::Find(const TKey& keyToBeFound, EqualityFunctor equals)
	{
		size_t chainIndex;
		return Find(keyToBeFound, chainIndex, equals);
	}

	template<typename TKey, typename TData>
	inline typename HashMap<TKey, TData>::Iterator HashMap<TKey, TData>::Find(const TKey& keyToBeFound, size_t& chainIndex, EqualityFunctor equals)
	{
		chainIndex = _hash(keyToBeFound) % _table.Size();
		auto& chain = _table.At(chainIndex);

		for (auto position = chain.begin(); position != chain.end(); ++position)
		{
			auto& entry = *position;
			if (equals(keyToBeFound, entry.first))
			{
				return Iterator(*this, chainIndex, position);
			}
		}
		return end();
	}

	template<typename TKey, typename TData>
	inline typename HashMap<TKey, TData>::ConstIterator HashMap<TKey, TData>::Find(const TKey& keyToBeFound, EqualityFunctor equals) const
	{
		size_t chainIndex;
		return Find(keyToBeFound, chainIndex, equals);
	}

	template<typename TKey, typename TData>
	inline typename HashMap<TKey, TData>::ConstIterator HashMap<TKey, TData>::Find(const TKey& keyToBeFound, size_t& chainIndex, EqualityFunctor equals) const
	{
		chainIndex = _hash(keyToBeFound) % _table.Size();
		auto& chain = _table.At(chainIndex);

		for (auto position = chain.begin(); position != chain.end(); ++position)
		{
			auto& entry = *position;
			if (equals(keyToBeFound, entry.first))
			{
				return ConstIterator(*this, chainIndex, position);
			}
		}
		return end();
	}

	template<typename TKey, typename TData>
	inline bool HashMap<TKey, TData>::ContainsKey(const TKey& key) const
	{
		return (Find(key) != end());
	}

	template<typename TKey, typename TData>
	inline size_t HashMap<TKey, TData>::Capacity() const
	{
		return _table.Capacity();
	}

	template<typename TKey, typename TData>
	inline size_t HashMap<TKey, TData>::Size() const
	{
		return _size;
	}

	template<typename TKey, typename TData>
	inline TData& HashMap<TKey, TData>::At(const TKey& key)
	{
		Iterator it = Find(key);
		if (it == end())
		{
			throw std::runtime_error("The key value was not located");
		}
		return it->second;
	}

	template<typename TKey, typename TData>
	inline const TData& HashMap<TKey, TData>::At(const TKey& key) const
	{
		ConstIterator it = Find(key);
		if (it == end())
		{
			throw std::runtime_error("The key value was not located");
		}
		return it->second;
	}

	template<typename TKey, typename TData>
	inline void HashMap<TKey, TData>::Clear()
	{
		for (size_t i = 0; i < Capacity(); i++)
		{
			_table[i].Clear();
		}
		_size = 0;
	}

	template<typename TKey, typename TData>
	std::pair<typename HashMap<TKey, TData>::Iterator, bool> HashMap<TKey, TData>::Insert(const pair_type& pairToBeAdded, EqualityFunctor equals)
	{
		bool isInserted = false;
		size_t chainIndex;
		auto position = Find(pairToBeAdded.first, chainIndex, equals);
		if (position == end())
		{
			auto chainPosition = _table[chainIndex].PushBack(pairToBeAdded);
			position = Iterator{ *this, chainIndex,chainPosition };
			isInserted = true;
			_size++;
		}

		return std::make_pair(std::move(position), isInserted);
	}

}
