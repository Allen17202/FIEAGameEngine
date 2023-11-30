#pragma once
#include "pch.h"
#include<cstddef>
#include <memory_resource>

namespace FIEAGameEngine
{
	template<typename T>
	class BlockAllocator : public std::pmr::memory_resource
	{
	public:
		BlockAllocator(std::size_t size, std::size_t count);
		~BlockAllocator() override;

		void* do_allocate(std::size_t bytes, std::size_t alignment) override;
		void do_deallocate(void*, std::size_t, std::size_t) override;
		bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;
	
	private:

		struct Block
		{
			Block* next;
		};
		const std::size_t _blockSize;
		Block* _freeListBlocks;
		std::byte* _memBuffer;
		std::size_t _memSize;
	};
}
#include "BlockAllocator.inl"
