#include "Factory.h"
#include "HashMap.h"

namespace FIEAGameEngine
{
	template <typename T>
	Factory<T>::~Factory()
	{
	}


	template<typename T>
	std::shared_ptr<const Factory<T>> Factory<T>::Find(const std::string& className)
	{
		auto iterator = factoryManager.Find(className);
		if (iterator != factoryManager.end())
		{
			return (*iterator).second;
		}
		else
		{
			return std::shared_ptr<const Factory<T>>(nullptr);
		}
	}

	template<typename T>
	inline void Factory<T>::Add(std::shared_ptr<Factory> factory)
	{
		if (factoryManager.ContainsKey(factory->ClassName()))
		{
			throw std::runtime_error("Factory already exists in hashmap");
		}
		else
		{
			factoryManager.Insert(std::make_pair(factory->ClassName(), std::move(factory)));
		}
	}

	template<typename T>
	inline void Factory<T>::Remove(std::shared_ptr<Factory> factory)
	{
		factoryManager.Remove(factory->ClassName());
	}

	template<typename T>
	inline gsl::owner<T*> Factory<T>::Create(const std::string& name)
	{
		auto iterator = factoryManager.Find(name);
		return (iterator != factoryManager.end() ? iterator->second->Create() : nullptr);
	}

	template<typename T>
	inline void Factory<T>::Clear()
	{
		factoryManager.Clear();
	}

	template<typename T>
	inline std::size_t Factory<T>::Size()
	{
		return factoryManager.Size();
	}

}
