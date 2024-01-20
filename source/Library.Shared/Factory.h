#pragma once
#ifdef _WIN32
#include <gsl/gsl>
#elif defined(__linux__)
#include <gsl/gsl>
#endif
#include "HashMap.h"
#include <memory>
#include <string>

namespace FIEAGameEngine
{
	template <typename T>
	class Factory
	{
	public:
		Factory() = default;
		Factory(const Factory&) = delete;
		Factory& operator=(const Factory&) = delete;
		Factory(Factory&&) noexcept = default;
		Factory& operator=(Factory&&) noexcept = default;
		virtual ~Factory();

		/// <summary>
		/// Finds the factory with the string names className
		/// </summary>
		/// <param name="className">name of the factory to be found</param>
		/// <returns>Pointer to the found factory or nullptr</returns>
		static std::shared_ptr<const Factory> Find(const std::string& className);
		/// <summary>
		/// Creates a class instance based on factory name
		/// </summary>
		/// <param name="name">name of the factory to produce a class instance</param>
		/// <returns>Pointer to the factory created object</returns>
		static gsl::owner<T*> Create(const std::string& name);
		/// <summary>
	/// Creates concrete product
	/// </summary>
	/// <returns>Pointer to concrete product</returns>
		virtual gsl::owner<T*> Create() const = 0;

		/// <summary>
		/// Clears the factories hashmap
		/// </summary>
		static void Clear();
		/// <summary>
		/// Getts the current size of the hashmap of factory manager
		/// </summary>
		/// <returns> size of the hashmap of factory manager</returns>
		static size_t Size();

		/// <summary>
		/// Getter for the class name of a derived factory class
		/// </summary>
		/// <returns> string name of the derived factory</returns>
		virtual const std::string& ClassName() const = 0;
		/// <summary>
		/// Adds a factory to the static factory manager
		/// </summary>
		/// <param name="factory">the factory to be added to the manager</param>
		static void Add(std::shared_ptr<Factory> factory);
		/// <summary>
		/// Removes a factory from the factory manager
		/// </summary>
		/// <param name="factory">factory to be removed</param>
		static void Remove(std::shared_ptr<Factory> factory);

	private:
		inline static HashMap<std::string, std::shared_ptr<const Factory<T>>> factoryManager;
	};

#define ConcreteFactory(ConcreteProductType,AbstractProductType) 														\
		class ConcreteProductType##Factory : public Factory<AbstractProductType>											    \
		{																														\
		public:																													\
			ConcreteProductType##Factory() :																					\
				_name(#ConcreteProductType)																						\
			{																													\
			}																													\
			gsl::owner<AbstractProductType*> Create() const override															\
			{																													\
				return new ConcreteProductType();																				\
			}																													\
			virtual ~ConcreteProductType##Factory()																			\
			{																													\
			}																													\
			const std::string& ClassName() const override																		\
			{																													\
				return _name;																									\
			}																													\
		private:																												\
			const std::string _name;	                                                                                        \
		};																										
}
#include "Factory.inl"