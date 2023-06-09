#pragma once
#include "SList.h"

namespace FIEAGameEngine
{
	template <typename T>
	class Stack final
	{
	public:
		using size_type = std::size_t;
		using value_type = T;
		using reference = value_type&;
		using const_reference = const value_type&;
		using rvalue_reference = value_type&&;

		void Push(const_reference val);
		void Push(rvalue_reference val);
		void Pop();
		[[nodiscard]] reference Top();
		[[nodiscard]] const_reference Top() const;
		[[nodiscard]] size_type Size() const;
		[[nodiscard]] bool isEmpty() const;
		void Clear();
	private:
		SList<value_type> _list;
	};
}
#include "Stack.inl"
