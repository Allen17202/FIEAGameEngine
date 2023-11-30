#pragma once
#include "pch.h"
#include<cstddef>
#include <new>
#include <iostream>
#include <list>
#include <memory_resource>

namespace FIEAGameEngine
{
	template<typename T>
	class FreeListAllocator : public std::pmr::memory_resource
	{	
	public:
		FreeListAllocator(std::pmr::memory_resource* resource = std::pmr::get_default_resource());
		~FreeListAllocator() override;
		void* do_allocate(std::size_t bytes, std::size_t alignment = alignof(T)) override;
		void do_deallocate(void* ptr, std::size_t bytes, std::size_t align) override;
		bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;

	private:
		struct Block
		{
			std::size_t _size;
			void* _data;
			Block* _next;
			Block(std::size_t size, void* data) : _size(size), _data(data), _next(nullptr) {}
		};
		Block* _head;
		Block* _prevBestFitBlock;
		std::pmr::memory_resource* _resource;
	};
}
#include "FreeListAllocator.inl"