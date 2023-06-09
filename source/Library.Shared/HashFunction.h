#pragma once

namespace FIEAGameEngine
{
	using size_type = std::size_t;
	using string_type = std::string;
	size_type Hashing(const uint8_t* valuePointer, size_type valueSize);

	template <typename T>
	struct HashFunction final
	{
		size_type operator()(const T& tkey) const;
	};

	template <>
	struct HashFunction<char*> final
	{
		size_type operator()(const char* tkey) const;
	};

	template <>
	struct HashFunction<const char*> final
	{
		size_type operator()(const char* tkey) const;
	};
	
	template <>
	struct HashFunction<string_type> final
	{
		size_type operator()(const string_type& tkey) const;
	};

	template <>
	struct HashFunction<const string_type> final
	{
		size_type operator()(const string_type& tkey) const;
	};
}
#include "HashFunction.inl"
