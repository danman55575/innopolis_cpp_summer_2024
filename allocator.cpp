#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include "allocator.hpp"

class LackMemory {
private:
    std::string message_;
public:
    LackMemory(const std::string& message): message_(message) {}
    std::string what() const {
        return this->message_;
    }
};

Allocator::Allocator() {
    this->ptr_to_start = nullptr;
}

void Allocator::makeAllocator(size_t maxSize)
{
    delete[] this->ptr_to_start;
    try {
        this->ptr_to_start = new char[maxSize];
    } catch(const std::bad_alloc& err) {
        throw LackMemory("Error with memory allocation!");
    }
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
