#include "BlockAllocator.h"
#pragma once

namespace FIEAGameEngine
{
	template<typename T>
	inline FIEAGameEngine::BlockAllocator<T>::BlockAllocator(std::size_t size, std::size_t count) : _blockSize(size), _freeListBlocks(nullptr), _memBuffer(nullptr), _memSize(0)
	{
		const std::size_t alignment = alignof(T);
		if (size % alignment != 0)
		{
			throw std::runtime_error("Block must be multiple");
		};

		_memBuffer = static_cast<std::byte*>(operator new(size * count + alignment));
		_memSize = size * count;
		for (std::size_t i = 0; i < count; ++i)
		{
			Block* newBlock = reinterpret_cast<Block*>(_memBuffer + (i * size));
			newBlock->next = _freeListBlocks;
			_freeListBlocks = newBlock;
		}
	}
	template<typename T>
	inline BlockAllocator<T>::~BlockAllocator()
	{
		std::free(_memBuffer);
	}
	template<typename T>
	inline void* BlockAllocator<T>::do_allocate(std::size_t bytes, std::size_t alignment)
	{
		std::size_t tempSize = _memSize - bytes;
		if (tempSize <= 0)
		{
			throw std::out_of_range("Requested bytes exceed block size or invalid alignment");
		}
		_memSize = _memSize - bytes;

		if (((bytes % _blockSize) != 0) || alignment > alignof(std::max_align_t))
		{
			throw std::out_of_range("Requested bytes exceed block size or invalid alignment");
		}

		if (_freeListBlocks)
		{
			Block* blockAllocated = _freeListBlocks;
			_freeListBlocks = _freeListBlocks->next;
			return blockAllocated;
		}
		return nullptr;
	}

	template<typename T>
	inline void BlockAllocator<T>::do_deallocate(void* ptr, std::size_t bytes, std::size_t alignment)
	{
		if (!ptr)
		{
			return;
		}

		if (bytes != _blockSize || alignment > alignof(std::max_align_t))
		{
			return;
		}

		Block* deallocateThisBlock = static_cast<Block*>(ptr);
		deallocateThisBlock->next = _freeListBlocks;
		_freeListBlocks = deallocateThisBlock;
	}

	template<typename T>
	inline bool BlockAllocator<T>::do_is_equal(const std::pmr::memory_resource& other) const noexcept
	{
		return this == &other;
	}
}