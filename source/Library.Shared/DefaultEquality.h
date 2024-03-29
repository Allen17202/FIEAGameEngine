#pragma once
#include <cstring>
namespace FIEAGameEngine
{
	template <typename T>
	struct DefaultEquality final
	{
		bool operator()(const T& lhs, const T& rhs) const;
	};

	template <>
	struct DefaultEquality<char*> final
	{
		bool operator()(const char* lhs, const char* rhs) const;
	};

	template <>
	struct DefaultEquality<const char*> final
	{
		bool operator()(const char* lhs, const char* rhs) const;
	};

	template <>
	struct DefaultEquality<char* const> final
	{
		bool operator()(const char* const lhs, const char* const rhs) const;
	};

	template <>
	struct DefaultEquality<const char* const> final
	{
		bool operator()(const char* const lhs, const char* const rhs) const;
	};
}
#include "DefaultEquality.inl"
