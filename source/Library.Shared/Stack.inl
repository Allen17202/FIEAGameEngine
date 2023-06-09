#include "Stack.h"
#pragma once


namespace FIEAGameEngine
{
	template<typename T>
	inline void Stack<T>::Push(const_reference val)
	{
		_list.PushFront(val);
	}

	template<typename T>
	inline void Stack<T>::Push(rvalue_reference val)
	{
		_list.PushFront(val);
	}

	template<typename T>
	inline void Stack<T>::Pop()
	{
		_list.PopFront();
	}

	template<typename T>
	inline typename Stack<T>::reference Stack<T>::Top()
	{
		return _list.Front();
	}

	template<typename T>
	inline typename Stack<T>::const_reference Stack<T>::Top() const
	{
		return _list.Front();
	}
	template<typename T>
	inline typename Stack<T>::size_type Stack<T>::Size() const
	{
		return _list.Size();
	}
	template<typename T>
	inline bool Stack<T>::isEmpty() const
	{
		return _list.IsEmpty();
	}
	template<typename T>
	inline void Stack<T>::Clear()
	{
		return _list.Clear();
	}
}