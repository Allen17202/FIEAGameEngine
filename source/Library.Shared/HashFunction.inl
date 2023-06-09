#include "HashFunction.h"

namespace FIEAGameEngine
{
	template<typename T>
	inline size_type HashFunction<T>::operator()(const T& tkey) const
	{
		const uint8_t* value = reinterpret_cast<const uint8_t*>(&tkey);
		return Hashing(value, sizeof(T));
	}

	inline size_t HashFunction<char*>::operator()(const char* tkey) const
	{
		const uint8_t* value = reinterpret_cast<const uint8_t*>(tkey);
		return Hashing(value, strlen(tkey));
	}

	inline size_t HashFunction<const char*>::operator()(const char* tkey) const
	{
		const uint8_t* value = reinterpret_cast<const uint8_t*>(tkey);
		return Hashing(value, strlen(tkey));
	}

	inline size_type HashFunction<string_type>::operator()(const string_type& tkey) const
	{
		const uint8_t* value = reinterpret_cast<const uint8_t*>(tkey.c_str());
		return Hashing(value, tkey.length());
	}

	inline size_t HashFunction<string_type const>::operator()(const string_type& tkey) const
	{
		const uint8_t* value = reinterpret_cast<const uint8_t*>(tkey.c_str());
		return Hashing(value, tkey.length());
	}
}