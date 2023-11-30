#pragma once
#include "FreeListAllocator.h"

namespace FIEAGameEngine
{
	template<typename T>
	inline FreeListAllocator<T>::FreeListAllocator(std::pmr::memory_resource* resource) : _resource(resource), _head(nullptr), _prevBestFitBlock(nullptr)
	{
	}

    template<typename T>
    inline FreeListAllocator<T>::~FreeListAllocator()
    {
        while (_head)
        {
            Block* nextBlock = _head->_next;
            _resource->deallocate(_head, _head->_size, alignof(Block));
            _head = nextBlock;
        }
    }

    template<typename T>
    void* FreeListAllocator<T>::do_allocate(std::size_t bytes, std::size_t align)
    {
            // Implement best-fit search algorithm
            Block* currentBlock = _head;
            Block* previousBlock = _head;

            while(currentBlock)
            {
                if (currentBlock->_size >= bytes)
                {
                    if (previousBlock)
                    {
                        previousBlock->_next = currentBlock->_next;
                    }
                    else
                    {
                        _head->_next = currentBlock->_next;
                    }
                    return currentBlock->_data;
                } 
                previousBlock = currentBlock;
                currentBlock = currentBlock->_next;
            }

            // If no suitable block is found, allocate a new one from the resource
            bytes = std::max(bytes, sizeof(Block));
            void* blockPtr = _resource->allocate(bytes, align);
            Block* newBlock = new (blockPtr) Block(bytes, blockPtr);

            // Used only once to add to head of list
            if (_head == nullptr)
            {
                _head = newBlock;
            }
            else if (_head && _head->_next == nullptr)
            {
                _head->_next = newBlock;
            }

            _prevBestFitBlock = newBlock;
            return newBlock->_data;
    }
    
    template<typename T>
    void FreeListAllocator<T>::do_deallocate(void* ptr, std::size_t, std::size_t)
    {
        if (!ptr)
        {
            return;
        }

        // Find the block that contains the given pointer
        Block* blockToDeallocate = nullptr;
        Block* previousBlock = nullptr;
        for (Block* current = _head; current; current = current->_next) {
            if (current && current->_data == ptr) {
                blockToDeallocate = current;
                break;
            }
            previousBlock = current;
        }

        if (blockToDeallocate) {
            // Add the block back to the free list
            if (previousBlock) {
                previousBlock->_next = blockToDeallocate;
            }
            else {
                if (_head->_next == nullptr && _head == blockToDeallocate)
                {
                    _head->_data = nullptr;
                }
                _head = blockToDeallocate;
            }

            blockToDeallocate->_data = nullptr;
        }
    }

    template<typename T>
    inline bool FreeListAllocator<T>::do_is_equal(const std::pmr::memory_resource& other) const noexcept
    {
        return this == &other;
    }


}
