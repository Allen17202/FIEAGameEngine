#pragma once
#include "Allocator.h"


namespace FIEAGameEngine
{
	template<typename T>
	inline BumpAllocator<T>::BumpAllocator(std::size_t size, std::byte* memory): _mem(memory), _capacity(size), _offset(0)
	{
	}

	template<typename T>
	inline BumpAllocator<T>::~BumpAllocator()
	{
	}

	template<typename T>
	inline void* FIEAGameEngine::BumpAllocator<T>::allocateHelper(std::size_t bytes, std::size_t alignment)
	{
		if (bytes == 0)
		{
			return nullptr;
		}

		std::size_t adjust = alignment - (_offset % alignment);
		if (adjust == alignment)
		{
			//Memeorys alrody is aligned
			adjust = 0;
		}

		// Check if theres enough space to make the allocation
		// Throws exception if over capacity
		if (_offset + bytes + adjust > _capacity)
		{
			throw std::bad_alloc();
		}

		//Calculation for the aligned memeory address
		std::byte* addressAligned = _mem + _offset + adjust;

		//Updates the offset
		_offset += bytes + adjust;

		return static_cast<void*>(addressAligned);
	}

	template<typename T>
	inline void* BumpAllocator<T>::do_allocate(std::size_t bytes, std::size_t alignment)
	{
		return allocateHelper(bytes, alignment);
	}

	template<typename T>
	inline T* FIEAGameEngine::BumpAllocator<T>::allocate(std::size_t size)
	{
		return static_cast<T*>(allocateHelper(size * sizeof(T), alignof(T)));
	}

	template<typename T>
	inline void BumpAllocator<T>::do_deallocate(void*, std::size_t, std::size_t)
	{
	}

	template<typename T>
	inline bool BumpAllocator<T>::do_is_equal(const std::pmr::memory_resource& other) const noexcept
	{
		return this->operator==(other);
	}

	template<typename T>
	inline bool BumpAllocator<T>::operator==(const std::pmr::memory_resource& other) const noexcept
	{
		return this == &other;
	}

	template<typename T>
	inline bool BumpAllocator<T>::operator!=(const std::pmr::memory_resource& other) const noexcept
	{
		return !this.operator==(other);
	}
	
}
