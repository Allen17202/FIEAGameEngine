#pragma once
#include <cstdint>
#include <cstddef>
#include <stdexcept>
#include <initializer_list>

namespace FIEAGameEngine
{
	template<typename T>
	class Vector final
	{
	public:
		using size_type = std::size_t;
		using value_type = T;
		using reference = value_type&;
		using const_reference = const value_type&;
		using rvalue_reference = T&&;

		/// <summary>
		/// Default Constructor: Initialize the list to be empty
		/// </summary>
		//Vector() = default;

		Vector(std::size_t capacity = 0);

		/// <summary>
		/// Initializer List: 
		/// </summary>
		/// <param name="list"> initializes the container with the list</param>
		Vector(std::initializer_list<T> list);

		/// <summary>
		/// Move Constructor: shallow copies the vector and invalidates other
		/// </summary>
		/// <param name="other"> list to be copied</param>
		Vector(Vector&& other) noexcept;

		/// <summary>
		/// Move Assignment Operator: shallow copies the vector and invalidates other
		/// </summary>
		/// <param name="other"> list to be copied</param>
		Vector<T>& operator=(Vector&& other) noexcept;

		/// <summary>
		///  Array Index Operator
		/// </summary>
		/// <exception cref="Run Time Error"> Thrown when array is out of bounds </exception>
		/// <param name="indexOfArray"> index of the array requested</param>
		/// <returns> Returns a reference to the item at the given index</returns>
		reference operator[](size_type indexOfArray);
		/// <summary>
		///  Array Index Operator
		/// </summary>
		/// <exception cref="Run Time Error"> Thrown when array is out of bounds </exception>
		/// <param name="indexOfArray"> index of the array requested</param>
		/// <returns> Returns a reference to the item at the given index</returns>
		const_reference operator[](size_type indexOfArray) const;
		/// <summary>
		/// Assignment Operator: deep copies list given into "this" list
		/// </summary>
		/// <param name="other"> list to be deep copied</param>
		/// <returns></returns>
		Vector& operator=(const Vector& other);
		/// <summary>
		/// Copy Constructor: deep copies the list given into *this
		/// </summary>
		/// <param name="rhs">list to be deep copied</param>
		Vector(const Vector& rhs);
		~Vector();
		class Iterator 
		{
			friend class Vector<T>;
			friend class ConstIterator;

		public:
			using size_type = std::size_t;
			using value_type = T;
			using reference = value_type&;
			using const_reference = const value_type&;
			using rvalue_reference = T&&;
			using iterator_category = std::bidirectional_iterator_tag;
			using difference_type = std::ptrdiff_t;
			using pointer = value_type*;

			/// <summary>
			/// Default Constructor: initializes _container to nullptr and _containerIndex to 0
			/// </summary>
			Iterator() = default;
			/// <summary>
			/// Copy Constructor: deep copy the list given as argument into "this" list
			/// </summary>
			/// <param name="container"> Iterator to be copied </param>
			Iterator(const Iterator& container) = default;
			/// <summary>
			/// Assignment Operator: deep copies list given as argument into container
			/// </summary>
			/// <param name="container"> list to be copied</param>
			/// <returns> A reference to a copy</returns>
			Iterator& operator=(const Iterator& container) = default;

			/// <summary>
			/// Constructor: takes a reference to a vector and an index 
			/// </summary>
			/// <param name="container"> reference to vector container</param>
			/// <param name="containerIndex"> index referenced</param>
			Iterator(Vector& container, size_type containerIndex);

			/// <summary>
			/// Dereference Operator
			/// </summary>
			/// <returns> returns a non const reference to item contained by node the Iterator points to </returns>
			reference operator*() const;
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
			Iterator& operator++(int);
			/// <summary>
			/// Prefix Increment Operators: Assigns Iterator to next node in the list
			/// </summary>
			/// <returns> Iterator to the next node</returns>
			Iterator& operator--();
			/// <summary>
			/// Postfix Increment Operators: Assigns Iterator to next node in the list
			/// </summary>
			/// <returns> Iterator to the next node</returns>
			Iterator& operator--(int);


		private:
			Vector<T>* _container{ nullptr };
			size_type _containerIndex{ 0 };
		};
		class ConstIterator 
		{
			friend class Vector<T>;
			using size_type = std::size_t;
			using value_type = T;
			using reference = value_type&;
			using const_reference = const value_type&;
			using rvalue_reference = T&&;
			using iterator_category = std::bidirectional_iterator_tag;
			using difference_type = std::ptrdiff_t;
			using pointer = value_type*;

		public:
			/// <summary>
			/// Default Constructor: initializes _container to nullptr and _containerIndex to 0
			/// </summary>
			ConstIterator() = default;
			/// <summary>
			/// Copy Constructor: deep copy the list given as argument into "this" list
			/// </summary>
			/// <param name="container"> ConstIterator to be copied </param>
			ConstIterator(const ConstIterator& container) = default;
			/// <summary>
			/// Constructor: takes an Iterator and converts to ConstIterator
			/// </summary>
			/// <param name="other"></param>
			ConstIterator(const Iterator& other);
			/// <summary>
			/// Constructor: takes a reference to a vector and an index 
			/// </summary>
			/// <param name="container"> reference to vector container</param>
			/// <param name="containerIndex"> index referenced</param>
			ConstIterator(const Vector& container, size_type containerIndex);
			/// <summary>
			/// Assignment Operator: deep copies list given as argument into container
			/// </summary>
			/// <param name="container"> list to be copied</param>
			/// <returns> A reference to a copy</returns>
			ConstIterator& operator=(const ConstIterator& container) = default;
			/// <summary>
			/// Dereference Operator
			/// </summary>
			/// <returns> returns a non const reference to item contained by node the ConstIterator points to </returns>
			const_reference operator*() const;
			/// <summary>
			/// Not-Equal Operator
			/// </summary>
			/// <param name="other"></param>
			/// <returns> returns true when two ConstIterators do not point to the same Node </returns>
			bool operator!=(const ConstIterator& other) const;
			/// <summary>
			/// Comparison Operator
			/// </summary>
			/// <param name="other"></param>
			/// <returns> returns true when two ConstIterators point to the same Node </returns>
			bool operator==(const ConstIterator& other) const;
			/// <summary>
			/// Prefix Increment Operators: Assigns ConstIterator to next node in the list
			/// </summary>
			/// <returns> ConstIterator to the next node</returns>
			ConstIterator& operator++();
			/// <summary>
			/// Postfix Increment Operators: Assigns ConstIterator to next node in the list
			/// </summary>
			/// <returns> ConstIterator to the next node</returns>
			ConstIterator& operator++(int);
			/// <summary>
			/// Prefix Decrement Operators: Assigns ConstIterator to next node in the list
			/// </summary>
			/// <returns> ConstIterator to the next node</returns>
			ConstIterator& operator--();
			/// <summary>
			/// Postfix Decrement Operators: Assigns ConstIterator to next node in the list
			/// </summary>
			/// <returns> ConstIterator to the next node</returns>
			ConstIterator& operator--(int);



		private:
			const Vector* _container{ nullptr };
			size_type _containerIndex{ 0 };
		};
	public:
		/// <summary>
		/// Reserve: takes unsigned int indicating capacity of the array
		/// </summary>
		/// <param name="capacity"> Amount to increase capacity by</param>
		void Reserve(size_type capacity);
	//oid Resize(size_type capacity);

		/// <summary>
		/// Size: Returns the current size of the container as unsigned int
		/// </summary>
		/// <returns> _size: number of items in the list currently </returns>
		[[nodiscard]] size_type Size() const;
		/// <summary>
		/// Capacity: Returns the number of items allocated in memory for the container
		/// </summary>
		/// <returns> _capacity: number of irems allocated in memory </returns>
		[[nodiscard]] size_type Capacity() const;
		/// <summary>
		/// IsEmpty: bool method
		/// </summary>
		/// <returns>Returns a bool indicating whether the list has any items</returns>
		[[nodiscard]] bool IsEmpty() const;
		/// <summary>
		/// Front: retrieves the first item in the container
		/// </summary>
		/// <exception cref="Run Time Error"> Thrown when _size = 0 </exception>
		/// <returns> returns the first item in the container</returns>
		[[nodiscard]] reference Front();
		/// <summary>
		/// Front: retrieves the first item in the container
		/// </summary>
		/// <exception cref="Run Time Error"> Thrown when _size = 0 </exception>
		/// <returns> Returns the first item in the container</returns>
		[[nodiscard]] const_reference Front() const;
		/// <summary>
		/// Back: retries the last item in container
		/// </summary>
		/// <exception cref="Run Time Error"> Thrown when _size = 0 </exception>
		/// <returns> Returns the last item in the container</returns>
		[[nodiscard]] reference Back();
		/// <summary>
		/// Back: retrieves the last item in container
		/// </summary>
		/// <exception cref="Run Time Error"> Thrown when _size = 0 </exception>
		/// <returns> Returns the last item in the container</returns>
		[[nodiscard]] const_reference Back() const;
		/// <summary>
		/// PopBack: Removes the last item in the container without changing capacity
		/// </summary>
		void PopBack();
		/// <summary>
		/// Clear: empties the container of all items
		/// </summary>
		void Clear();
		/// <summary>
		/// PushBack: Appends given item to the end of the list.
		/// </summary>
		/// <param name="dataToBeAdded"> Item to be added to end of list</param>
		void PushBack(rvalue_reference dataToBeAdded);
		/// <summary>
		/// PushBack: Appends given item to the end of the list.
		/// </summary>
		/// <param name="dataToBeAdded"> Item to be added to end of list</param>
		void PushBack(const_reference dataToBeAdded);
		/// <summary>
		/// ShrinkToFit reduces capacity of the container to match its size
		/// </summary>
		void ShrinkToFit();
		/// <summary>
		/// Begin: returns a Iterator pointing to the first element in the contianer
		/// </summary>
		[[nodiscard]] Iterator begin();
		/// <summary>
		/// End: returns a Iterator inidicating not to be in the container
		/// </summary>
		[[nodiscard]] Iterator end();
		/// <summary>
		/// Begin: returns a ConstIterator pointing to the first element in the container
		/// </summary>
		[[nodiscard]] ConstIterator begin() const;
		/// <summary>
		/// Begin: returns a ConstIterator pointing to the first element in the container
		/// </summary>
		[[nodiscard]] ConstIterator cbegin() const;
		/// <summary>
		/// End: returns a Iterator pointing to the element not in the container
		/// </summary>
		[[nodiscard]] ConstIterator end() const;
		/// <summary>
		/// End: returns a ConstIterator pointing to the element not in the container
		/// </summary>
		[[nodiscard]] ConstIterator cend() const;
		/// <summary>
		/// At: returns a reference to the object at the given index given item to the end of the list.
		/// </summary>
		/// <param name="indexOfData"> index to search vector</param>
		[[nodiscard]] reference At(size_type indexofData);
		/// <summary>
		/// At: returns a reference to the object at the given index given item to the end of the list.
		/// </summary>
		/// <param name="indexOfData"> index to search vector</param>
		[[nodiscard]] const_reference At(size_type indexofData) const;
		/// <summary>
		/// Find: returns a Iterator pointing to first item in container that matches key
		/// </summary>
		/// <param name="key"> value that is being looked for</param>
		/// <returns></returns>
		[[nodiscard]] Iterator Find(const_reference key);
		/// <summary>
		/// Find: returns a ConstIterator pointing to first item in container that matches key
		/// </summary>
		/// <param name="key"> value that is being looked for</param>
		/// <returns></returns>
		[[nodiscard]] ConstIterator Find(const_reference key) const;
		/// <summary>
		/// Remove: Allows the removal of any element in the list
		/// </summary>
		/// <param name="it"> Takes an Iterator</param>
		/// <returns></returns>
		
		bool Remove(const Iterator& it);
		bool Remove(const_reference it);
		bool Remove(const Iterator& start, const Iterator& end);
		void Resize(std::size_t size);
		bool Contains(const T& val) const;
	private:
		T* _data{ nullptr };
		size_type _capacity{ 0 };
		size_type _size{ 0 };
	};
}
#include "Vector.inl"
