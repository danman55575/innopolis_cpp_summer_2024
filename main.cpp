#include <iostream>
#include <cstddef>
#include "allocator.hpp"
#include <gtest/gtest.h>


TEST(testCase, overflow_test_1)
{
    Allocator allocator{};
    allocator.makeAllocator(100);
    char* ptr1 = allocator.alloc(50);
    char* ptr2 = allocator.alloc(49);
    char* ptr3 = allocator.alloc(2);
    EXPECT_NE(ptr1, nullptr);
    EXPECT_NE(ptr2, nullptr);
    EXPECT_EQ(ptr3, nullptr);
}

TEST(testCase, overflow_test_2)
{
    Allocator allocator{};
    allocator.makeAllocator(50);
    char* ptr1 = allocator.alloc(60);
    char* ptr2 = allocator.alloc(25);
    allocator.reset();
    char* ptr3 = allocator.alloc(35);
    EXPECT_EQ(ptr1, nullptr);
    EXPECT_NE(ptr2, nullptr);
    EXPECT_NE(ptr3, nullptr);
}

TEST(testCase, overflow_test_3)
{
    Allocator allocator{};
    allocator.makeAllocator(50);
    char* ptr1 = allocator.alloc(50);
    char* ptr2 = allocator.alloc(0);
    allocator.makeAllocator(20);
    char* ptr3 = allocator.alloc(19);
    char* ptr4 = allocator.alloc(1);
    char* ptr5 = allocator.alloc(1);
    EXPECT_NE(ptr1, nullptr);
    EXPECT_NE(ptr2, nullptr);
    EXPECT_NE(ptr3, nullptr);
    EXPECT_NE(ptr4, nullptr);
    EXPECT_EQ(ptr5, nullptr);
}

TEST(testCase, reuse_allocator_test_1)
{
    Allocator allocator{};
    allocator.makeAllocator(2);
    char* ptr1 = allocator.alloc(2);
    *(ptr1++) = 'O';
    *(ptr1) = 'K';
    allocator.reset();
    char* ptr2 = allocator.alloc(2);
    EXPECT_EQ(*ptr2, 'O');
    EXPECT_EQ(*(++ptr2), 'K');
}

TEST(testCase, reuse_allocator_test_2)
{
    Allocator allocator{};
    allocator.makeAllocator(50);
    char* ptr1 = allocator.alloc(30);
    char* ptr2 = allocator.alloc(15);
    for (int i = 100; i < 115; i += 1) {
        *(ptr2++) = (char) i;
    }
    allocator.reset();
    char* ptr3 = allocator.alloc(40);
    char* ptr4 = allocator.alloc(5);
    for (int i = 110; i < 115; i += 1) {
        EXPECT_EQ(*(ptr4++), (char) i);
    }
}

TEST(testCase, allocation_completeness_test_1)
{
    Allocator allocator{};
    allocator.makeAllocator(2);
    char* ptr1 = allocator.alloc(2);
    *(ptr1++) = 'O';
    *ptr1 = 'K';
    EXPECT_EQ(*(ptr1--), 'K');
    EXPECT_EQ(*ptr1, 'O');
}

TEST(testCase, allocation_error_test_1)
{
    Allocator allocator{};
    ASSERT_ANY_THROW(allocator.makeAllocator(9951234567890));
}

TEST(testCase, no_make_allocator_test_1)
{
    Allocator allocator{};
    char* ptr1 = allocator.alloc(5);
    EXPECT_EQ(ptr1, nullptr);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
