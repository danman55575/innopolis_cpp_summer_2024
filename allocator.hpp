#include <cstddef>

class Allocator
{
private:
    char* ptr_to_start;
    size_t size_used;
    size_t max_size;
public:
    void makeAllocator(size_t maxSize);
    char* alloc(size_t size);
    void reset();
    ~Allocator();
};