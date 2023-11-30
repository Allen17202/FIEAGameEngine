#pragma once
#include "pch.h"
#include<cstddef>
#include <new>
#include <iostream>
#include <list>
#include <memory_resource>

//Bump Allocator
namespace FIEAGameEngine
{
	template<typename T>
	class BumpAllocator : public std::pmr::memory_resource
	{
	public:
		BumpAllocator(std::size_t size, std::byte* memory);
		~BumpAllocator() override;
		void* do_allocate(std::size_t bytes, std::size_t alignment) override;
		T* allocate(std::size_t bytes = 1);
		void do_deallocate(void*,std::size_t,std::size_t) override;
		bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;
		bool operator==(const std::pmr::memory_resource& other) const noexcept;
		bool operator!=(const std::pmr::memory_resource& other) const noexcept;

	private:
		std::byte* _mem;
		std::size_t _capacity;
		std::size_t _offset;
		void* allocateHelper(std::size_t bytes, std::size_t alignment);
	};
}
#include "Allocator.inl"