#include <cstddef>
#include <cstdlib>
#include <iostream>
#include "allocator.hpp"

void Allocator::makeAllocator(size_t maxSize)
{
    delete[] this->ptr_to_start;
    this->ptr_to_start = new char[maxSize];
    this->size_used = 0;
    this->max_size = maxSize;
}

char* Allocator::alloc(size_t size)
{
    if (this->ptr_to_start == nullptr) return nullptr;
    if ((this->size_used + size) > this->max_size) return nullptr;
    this->size_used += size;
    return this->ptr_to_start + (this->size_used - size);
}

void Allocator::reset()
{
    this->size_used = 0;
}

Allocator::~Allocator() 
{
    delete[] this->ptr_to_start;
}