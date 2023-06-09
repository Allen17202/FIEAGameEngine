#pragma once
#include <cstdint>
#include <cstddef>
#include <stdexcept>
#include <functional>
#include <initializer_list>

namespace FIEAGameEngine
{
	
	template <typename T> 
	class SList final
	{
	public:
		using size_type = std::size_t;
		using value_type = T;
		using reference = value_type&;
		using const_reference = const value_type&;
		using rvalue_reference = T&&;
		using EqualityFunctor = std::function<bool(const T& lhs, const T& rhs)>;
	private:
		struct Node
		{
			T Data;
			Node* Next { nullptr };
			Node(const T& data, Node* next = nullptr); 
		};

	public:
		SList() = default; 
		/// <summary>
		/// 
		/// </summary>
		/// <param name="rhs"></param>
		SList(const SList& rhs); 
		/// <summary>
		/// 
		/// </summary>
		/// <param name="list"></param>
		SList(std::initializer_list<T> list);
		/// <summary>
		/// 
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		SList& operator=(const SList& other);
		
		/// <summary>
		/// 
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		~SList();  

		class Iterator final
		{
			friend SList;
			friend class ConstIterator;
		public:
			/// <summary>
			/// 
			/// </summary>
			Iterator() = default;
			/// <summary>
			/// 
			/// </summary>
			/// <param name="container"></param>
			Iterator(const SList& container);
			/// <summary>
			/// 
			/// </summary>
			/// <returns></returns>
			reference operator*() const;
			/// <summary>
			/// 
			/// </summary>
			/// <param name="other"></param>
			/// <returns></returns>
			bool operator!=(const Iterator& other) const; 
			/// <summary>
			/// 
			/// </summary>
			/// <param name="other"></param>
			/// <returns></returns>
			bool operator==(const Iterator& other) const;
			/// <summary>
			/// 
			/// </summary>
			/// <returns></returns>
			Iterator& operator++();
			/// <summary>
			/// 
			/// </summary>
			/// <param name=""></param>
			/// <returns></returns>
			Iterator& operator++(int);
		private:
			/// <summary>
			/// 
			/// </summary>
			/// <param name="container"></param>
			/// <param name="node"></param>
			/// Paul had this labeled Private; Why
			Iterator(const SList& container, Node* node);
			const SList* _container{ nullptr }; 
			Node* _node = { nullptr };
		};

		class ConstIterator final
		{
			friend SList;
		public:

			/// <summary>
			/// 
			/// </summary>
			ConstIterator() = default;

			/// <summary>
			/// 
			/// </summary>
			/// <param name="container"></param>
			/// <param name="node"></param>
			ConstIterator(const SList& container, Node* node);

			/// <summary>
			/// 
			/// </summary>
			/// <param name="container"></param>
			ConstIterator(const SList& container);

			/// <summary>
			/// 
			/// </summary>
			/// <param name="other"></param>
			ConstIterator(const Iterator& other);

			/// <summary>
			/// 
			/// </summary>
			/// <returns></returns>
			const_reference operator*() const; 

			/// <summary>
			/// 
			/// </summary>
			/// <param name="other"></param>
			/// <returns></returns>
			bool operator!=(const ConstIterator& other) const; 

			/// <summary>
			/// 
			/// </summary>
			/// <param name="other"></param>
			/// <returns></returns>
			bool operator==(const ConstIterator& other) const; 

			/// <summary>
			/// 
			/// </summary>
			/// <returns></returns>
			ConstIterator& operator++(); 

			/// <summary>
			/// 
			/// </summary>
			/// <param name=""></param>
			/// <returns></returns>
			ConstIterator& operator++(int); 
		private:
			const SList* _container{ nullptr }; 
			Node* _node{nullptr};
		};

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] size_t Size() const; 
		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] bool IsEmpty() const;
		/// <summary>
		/// 
		/// </summary>
		void Clear();
		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] reference Front();	
		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] const_reference Front() const; 
		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] reference Back();		
		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] const_reference Back() const;
		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		void PushFront(const_reference dataToBeAddded);
		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		void PopFront();	
		/// <summary>
		/// 
		/// </summary>
		/// <param name="dataToBeAdded"></param>
		/// <returns></returns>
		Iterator PushBack(const_reference dataToBeAdded);
		/// <summary>
		/// 
		/// </summary>
		void PopBack();
		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		Iterator begin();
		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		ConstIterator cbegin() const;
		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		ConstIterator begin() const;
		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		Iterator end();
		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		ConstIterator cend() const;
		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		ConstIterator end() const;
		/// <summary>
		/// 
		/// </summary>
		/// <param name="value"></param>
		/// <returns></returns>
		Iterator Find(const_reference value, EqualityFunctor equals = DefaultEquality<T>{});
		/// <summary>
		/// 
		/// </summary>
		/// <param name="value"></param>
		/// <returns></returns>
		ConstIterator Find(const_reference value, EqualityFunctor equals = DefaultEquality<T>{}) const;
		/// <summary>
		/// 
		/// </summary>
		/// <param name="it"></param>
		/// <param name="dataToBeInserted"></param>
		/// <returns></returns>
		Iterator InsertAfter(Iterator it, const T& dataToBeInserted);
		bool Remove(const_reference value);
		bool Remove(Iterator it);
	private:
		Node* _front{ nullptr };
		Node* _back{ nullptr };
		std::size_t _size{ 0 };
	};
}
#include "SList.inl"