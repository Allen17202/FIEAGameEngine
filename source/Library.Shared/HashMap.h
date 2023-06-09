#pragma once
#include "SList.h"
#include "HashFunction.h"
#include <functional>
#include <initializer_list>
#include "Vector.h"

namespace FIEAGameEngine
{
	template <typename T>
	class Vector;


	template <typename TKey, typename TData>
	class HashMap
	{
	public:
		using size_type = std::size_t;
		using pair_type = std::pair<const TKey, TData>;
		using chain_type = SList<pair_type>;
		using bucket_type = Vector<chain_type>;
		using EqualityFunctor = std::function<bool(const TKey& lhs, const TKey& rhs)>;
		using HashFunctor = std::function<size_type(const TKey& tKey)>;
		static const size_type defaultCapacity = 2;
		class Iterator;
		class ConstIterator;

		/// <summary>
		/// Initiaizer List
		/// </summary>
		/// <param name="list"></param>
		HashMap(std::initializer_list<pair_type> list);
		/// <summary>
		/// Copy Constructor: defaulted 
		/// </summary>
		/// <param name="rhs"></param>
		HashMap(const HashMap& rhs) = default;
		/// <summary>
		/// Move Constructor
		/// </summary>
		/// <param name="rhs"></param>
		/// <returns></returns>
		HashMap(HashMap&& rhs) noexcept;
		/// <summary>
		/// 
		/// </summary>
		/// <param name="numChains"></param>
		/// <param name="hash"></param>
		explicit HashMap(size_type chainCount = 2, HashFunctor hash = HashFunction<TKey>{});

		/// <summary>
		/// Destructor
		/// </summary>
		/// <param name="numChains"></param>
		/// <param name="hash"></param>
		virtual ~HashMap() = default;

		/// <summary>
		/// Index Operator
		/// </summary>
		/// <param name="key"></param>
		/// <returns></returns>
		TData& operator[](const TKey& key);
		const TData& operator[](const TKey& key) const;

		/// <summary>
		/// Assignment Operator
		/// </summary>
		/// <param name="rhs"></param>
		/// <returns></returns>
		HashMap& operator=(const HashMap& rhs) = default;
		HashMap& operator=(HashMap&& rhs) noexcept;

		class Iterator
		{
			friend HashMap;
			friend ConstIterator;

		public:
			/// <summary>
			/// Default Constructor: initializes values
			/// </summary>
			Iterator() = default;

			/// <summary>
			/// Copy Constructor: deep copy the list given as argument into "this" list
			/// </summary>
			/// <param name="container"> Iterator to be copied </param>
			Iterator(const Iterator& container) = default;

			/// <summary>
			/// Destructor
			/// </summary>
			~Iterator() = default;

			/// <summary>
			/// Assignment Operator: deep copies list given as argument into container
			/// </summary>
			/// <param name="container"> list to be copied</param>
			/// <returns> A reference to a copy</returns>
			Iterator& operator=(const Iterator& container) = default;

			/// <summary>
			/// Dereference Operator
			/// </summary>
			/// <returns> returns a non const reference to item contained by node the Iterator points to </returns>
			pair_type& operator*() const; 
			pair_type* operator->() const; 

			/// <summary>
			/// Not-Equal Operator
			/// </summary>
			/// <param name="other"></param>
			/// <returns> returns true when two Iterators do not point to the same Node </returns>
			bool operator!=(const Iterator& other) const; 
			/// <summary>
			/// Comparison Operator
			/// </summary>
			/// <param name="other"></param>
			/// <returns> returns true when two Iterators point to the same Node </returns>
			bool operator==(const Iterator& other) const; 
			/// <summary>
			/// Prefix Increment Operators: Assigns Iterator to next node in the list
			/// </summary>
			/// <returns> Iterator to the next node</returns>
			Iterator& operator++();
			/// <summary>
			/// Postfix Increment Operators: Assigns Iterator to next node in the list
			/// </summary>
			/// <returns> Iterator to the next node</returns>
			Iterator operator++(int);
		private:
			/*using size_type = std::size_t;
			using pair_type = std::pair<const TKey, TData>;
			using chain_type = SList<pair_type>;
			using bucket_type = Vector<chain_type>;*/
			HashMap<TKey, TData>* _container{ nullptr };
			size_type _containerIndex{ 0 };
			typename chain_type::Iterator _it;
			Iterator(HashMap<TKey, TData>& container, size_type containerIndex, typename chain_type::Iterator it);
		};

		class ConstIterator final
		{
			friend HashMap;

		public:
			/// <summary>
			/// Default Constructor: initializes values
			/// </summary>
			ConstIterator() = default;

			/// <summary>
			/// Copy Constructor: deep copy the list given as argument into "this" list
			/// </summary>
			/// <param name="container"> Iterator to be copied </param>
			ConstIterator(const ConstIterator& container) = default;


			ConstIterator(const Iterator& other); 

			/// <summary>
			/// Destructor
			/// </summary>
			~ConstIterator() = default;



			/// <summary>
			/// Assignment Operator: deep copies list given as argument into container
			/// </summary>
			/// <param name="container"> list to be copied</param>
			/// <returns> A reference to a copy</returns>
			ConstIterator& operator=(const ConstIterator& container) = default;

			/// <summary>
			/// Dereference Operator
			/// </summary>
			/// <returns> returns a non const reference to item contained by node the Iterator points to </returns>
			const pair_type& operator*() const;
			const pair_type* operator->() const;

			/// <summary>
			/// Not-Equal Operator
			/// </summary>
			/// <param name="other"></param>
			/// <returns> returns true when two Iterators do not point to the same Node </returns>
			bool operator!=(const ConstIterator& other) const;
			/// <summary>
			/// Comparison Operator
			/// </summary>
			/// <param name="other"></param>
			/// <returns> returns true when two Iterators point to the same Node </returns>
			bool operator==(const ConstIterator& other) const;
			/// <summary>
			/// Prefix Increment Operators: Assigns Iterator to next node in the list
			/// </summary>
			/// <returns> Iterator to the next node</returns>
			ConstIterator& operator++();
			/// <summary>
			/// Postfix Increment Operators: Assigns Iterator to next node in the list
			/// </summary>
			/// <returns> Iterator to the next node</returns>
			ConstIterator operator++(int);
		private:
			const HashMap<TKey, TData>* _container{ nullptr };
			size_type _containerIndex{ 0 };
			typename chain_type::ConstIterator _it;

			ConstIterator(const HashMap<TKey, TData>& container, size_type containerIndex, typename chain_type::ConstIterator it);
		};


		Iterator begin();
		Iterator end();
		ConstIterator begin() const;
		ConstIterator end() const;
		ConstIterator cbegin() const;
		ConstIterator cend() const;

		void Remove(const TKey& key, EqualityFunctor equals = DefaultEquality<TKey>{});
		//bool Remove(const TKey& key, EqualityFunctor equals = DefaultEquality<TKey>{});


		std::pair<Iterator, bool> Insert(const pair_type& pairToBeAdded, EqualityFunctor equals = DefaultEquality<TKey>{});
		Iterator Find(const TKey& keyToBeFound, EqualityFunctor equals = DefaultEquality<TKey>{});
		ConstIterator Find(const TKey& keyToBeFound, EqualityFunctor equals = DefaultEquality<TKey>{}) const;

		TData& At(const TKey& key);
		const TData& At(const TKey& key) const;
		bool ContainsKey(const TKey& key) const;
		size_type Capacity() const;
		size_type Size() const;
		void Clear();

	private:
		Iterator Find(const TKey& keyToBeFound, size_t& chainIndex, EqualityFunctor equals = DefaultEquality<TKey>{});
		ConstIterator Find(const TKey& keyToBeFound, size_t& chainIndex, EqualityFunctor equals = DefaultEquality<TKey>{}) const;
		bucket_type _table;
		size_type _size{ 0 }; // How many of those buckets have items
		HashFunctor _hash = HashFunction<TKey>{};
	};
}
#include "HashMap.inl"
