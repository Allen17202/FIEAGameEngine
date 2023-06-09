#include "pch.h"
#include "Scope.h"


namespace FIEAGameEngine
{
	RTTI_DEFINITIONS(Scope);
	Scope::Scope(std::size_t capacity) :
		_map(capacity), _orderVector(capacity)
	{};
	Scope::Scope(const Scope& other) :
		_map(other._map.Capacity()), _orderVector(other._orderVector.Capacity())
	{
		for (auto it : other._orderVector)
		{
			Datum anotherDatum;
			Datum& datum = (*it).second;
			if (datum.Type() == Datum::DatumTypes::Table)
			{
				anotherDatum.SetType(Datum::DatumTypes::Table);
				for (std::size_t i = 0; i < datum.Size(); ++i)
				{
					Scope* copyChildren = datum.GetTable(i).Clone();
					copyChildren->_parent = this;
					anotherDatum.PushBackTable(*copyChildren);
				}
			}
			else
			{
				anotherDatum = datum;
			}
			std::pair pairEntry = std::make_pair((*it).first, anotherDatum);
			std::pair insertionResult = _map.Insert(pairEntry);
			_orderVector.PushBack(&(*insertionResult.first));
		}
	}
	Scope& Scope::operator=(const Scope& other)
	{
		if (&other != this && !other.IsDescendentOf(*this) && !other.IsAncestorOf(*this))
		{
			Clear();
			_map = HashMap<std::string, Datum>(other._map.Capacity());
			_orderVector = Vector<typename HashMap<std::string, Datum>::pair_type*>(other._orderVector.Capacity());
			for (auto it : _orderVector)
			{
				Datum anotherDatum;
				Datum& datum = (*it).second;
				if (datum.Type() == Datum::DatumTypes::Table)
				{
					anotherDatum.SetType(Datum::DatumTypes::Table);
					for (size_t i = 0; i < datum.Size(); ++i)
					{
						Scope* copyChildren = datum.GetTable(i).Clone();
						copyChildren->_parent = this;
						anotherDatum.PushBackTable(*copyChildren);
					}
				}
				else
				{
					anotherDatum = datum;
				}
				std::pair pairEntry = std::make_pair((*it).first, anotherDatum);
				std::pair insertionResult = _map.Insert(pairEntry);
				_orderVector.PushBack(&(*insertionResult.first));
			}
		}
		return *this;
	}
	Scope::Scope(Scope&& other) noexcept:
		_map(std::move(other._map)), _orderVector(std::move(other._orderVector))
	{
		for (auto it : _orderVector)
		{
			Datum& datum = (*it).second;
			if (datum.Type() == Datum::DatumTypes::Table)
			{
				for (size_t i = 0; i < datum.Size(); ++i)
				{
					datum.GetTable(i)._parent = this;
				}
			}
		}
		if (other._parent != nullptr)
		{
			other._parent->Orphan(other);
			other._parent = nullptr;
		}
		other.Clear();
	}
	Scope& Scope::operator=(Scope&& other) noexcept
	{
		if (_parent != nullptr)
		{
			_parent->Orphan(*this);
			_parent = nullptr;
		}
		Clear();

		_map = std::move(other._map);
		_orderVector = std::move(other._orderVector);

		if (other._parent != nullptr)
		{
			other._parent->Orphan(other);
			other._parent = nullptr;
		}
		other.Clear();
		return *this;
	}
	Scope::~Scope()
	{
		if (_parent != nullptr)
		{
			_parent->Orphan(*this);
			_parent = nullptr;
		}
		Clear();
	}
	bool Scope::operator==(const Scope& other) const
	{
		bool isSameScope = true;
		if (this != &other)
		{
			if (_orderVector.Size() == other._orderVector.Size())
			{
				for (size_t i = 0; i < _orderVector.Size(); ++i)
				{
					auto& leftPair = *_orderVector[i];
					auto& rightPair = *other._orderVector[i];

					if(leftPair != rightPair)
					{
						isSameScope = false;
						break;
					}
				}
			}
			else
			{
				isSameScope = false;
			}
		}
		return isSameScope;
	}
	bool Scope::operator!=(const Scope& rhs) const
	{
		return !operator==(rhs);
	}
	Datum& Scope::operator[](const std::string& valueName)
	{
		return Append(valueName);
	}
	Datum& Scope::operator[](std::size_t valueIndex)
	{
		return (*_orderVector[valueIndex]).second;
	}
	const Datum& Scope::operator[](const std::string& valueName) const
	{
		if (_map.ContainsKey(valueName))
		{
			return (*_map.Find(valueName)).second;
		}
		throw std::runtime_error("Name was not located in Hashmap");
	}
	const Datum& Scope::operator[](std::size_t valueIndex) const
	{
		return (*_orderVector[valueIndex]).second;
	}
	gsl::owner<Scope*> Scope::Clone() const
	{
		return new Scope(*this);
	}
	Datum* Scope::Find(const std::string& valueName)
	{
		if (_map.ContainsKey(valueName))
		{
			return &(_map.At(valueName));
		}
		else
		{
			return nullptr;
		}
	}
	const Datum* Scope::Find(const std::string& valueName) const
	{
		if (_map.ContainsKey(valueName))
		{
			return &(_map.At(valueName));
		}
		return nullptr;
	}
	Datum* Scope::Search(const std::string& valueName)
	{
		if (_map.ContainsKey(valueName))
		{
			return &(_map.At(valueName));
		}
		else
		{
			if (_parent != nullptr)
			{
				return _parent->Search(valueName);
			}
			return nullptr;
		}
	}
	const Datum* Scope::Search(const std::string& valueName) const
	{
		if (_map.ContainsKey(valueName))
		{
			return &(_map.At(valueName));
		}
		else
		{
			if (_parent != nullptr)
			{
				return _parent->Search(valueName);
			}
			return nullptr;
		}
	}
	Datum* Scope::Search(const std::string& valueName, Scope*& foundScope)
	{
		if (_map.ContainsKey(valueName))
		{
			foundScope = this;
			return &(_map.At(valueName));
		}
		else
		{
			if (_parent != nullptr)
			{
				return _parent->Search(valueName, foundScope);
			}
			return nullptr;
		}
	}
	const Datum* Scope::Search(const std::string& valueName, const Scope*& foundScope) const
	{
		if (_map.ContainsKey(valueName))
		{
			foundScope = this;
			return &(_map.At(valueName));
		}
		else
		{
			if (_parent != nullptr)
			{
				return _parent->Search(valueName, foundScope);
			}
			return nullptr;
		}
	}
	Datum& Scope::Append(const std::string& valueName)
	{
		bool wasAppended;
		return Append(valueName, wasAppended);
	}
	Scope& Scope::AppendScope(const std::string& valueName)
	{
		bool wasAppended;
		Datum& datum = Append(valueName, wasAppended);
		Scope* appendThisScope = new Scope();
		appendThisScope->_parent = this;
		datum.PushBackTable(*appendThisScope);
		return datum.GetTable();
	}
	bool Scope::Equals(const RTTI* other) const
	{
		if (this == other)
		{
			return true;
		}
		if (other == nullptr)
		{
			return false;
		}

		const Scope* otherScope = other->As<Scope>();
		if (otherScope != nullptr)
		{
			return *this == *otherScope;
		}
		else
		{
			return false;
		}
	}
	void Scope::Adopt(Scope& child, const std::string& valueName)
	{
		if (&child == this)
		{
			throw::std::runtime_error("Scope can not adopt itself");
		}
		if (child.IsAncestorOf(*this))
		{
			throw::std::runtime_error("Scope can not adopt its ancestor");
		}

		bool wasAppended;
		Datum& datum = Append(valueName, wasAppended);
		if (wasAppended)
		{
			if (datum.Type() != Datum::DatumTypes::Table && datum.Type() != Datum::DatumTypes::Unknown)
			{
				throw::std::runtime_error("Key was located on a Datum with different type");
			}
		}

		if (child._parent != nullptr)
		{
			child._parent->Orphan(child);
		}
		child._parent = this;
		datum.PushBackTable(child);
	}
	void Scope::Orphan(Scope& child)
	{
		auto [datum, valueIndex] = FindContainedScope(child);
		if (datum != nullptr)
		{
			datum->RemoveAt(valueIndex);
			child._parent = nullptr;
		}
	}
	Scope* Scope::GetParent() const
	{
		return _parent;
	}
	void Scope::Clear()
	{
		for (auto it : _orderVector)
		{
			Datum& datum = it->second;
			if (datum.Type() == Datum::DatumTypes::Table)
			{
				assert(!datum.isExternal());
				for (size_t i = 0; i < datum.Size(); i++)
				{
					datum.GetTable(i)._parent = nullptr;
					delete& datum.GetTable(i);
				}
				datum.Clear();
			}
		}
		_map.Clear();
		_orderVector.Clear();
	}
	std::size_t Scope::Size() const
	{
		return _orderVector.Size();
	}
	std::pair<Datum*, std::size_t> Scope::FindContainedScope(const Scope& other) const
	{
		std::pair<Datum*, std::size_t> foundScope = std::make_pair(nullptr, std::numeric_limits<std::size_t>::min());
		for (auto it : _orderVector)
		{
			Datum& datum = (*it).second;
			if (datum.Type() == Datum::DatumTypes::Table)
			{
				for (std::size_t i = 0; i < datum.Size(); ++i)
				{
					if (datum.GetTable(i) == other)
					{
						foundScope.first = &datum;
						foundScope.second = i;
						break;
					}
				}
			}
		}
		return foundScope;
	}

	bool Scope::IsAncestorOf(const Scope& scope) const
	{
		bool isAncestor = false;
		Scope* p = scope._parent;
		while (p != nullptr)
		{
			if (p == this)
			{
				isAncestor = true;
				break;
			}
			p = p->_parent;
		}
		return isAncestor;
	}
	bool Scope::IsDescendentOf(const Scope& scope) const
	{
		return scope.IsAncestorOf(*this);
	}
	Datum& Scope::Append(const std::string& valueName, bool& wasAppended)
	{
		std::pair inserted = _map.Insert(std::make_pair(valueName, Datum()));
		auto& key = inserted.first;
		wasAppended = inserted.second;

		if (wasAppended)
		{
			_orderVector.PushBack(&(*key));
		}
		return (*key).second;

	}
}