#include "pch.h"
#include "HashFunction.h"
#include <cstddef>
#include <cstdint>

namespace FIEAGameEngine
{
	size_type Hashing(const uint8_t* valuePointer, size_type valueSize)
	{
		size_type returnedKey = 37;
		for (size_type i = 0; i < valueSize; i++)
		{
			returnedKey += valuePointer[i];
		}
		return returnedKey;
	}
}