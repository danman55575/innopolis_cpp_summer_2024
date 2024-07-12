#include <gtest/gtest.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <memory>
#include <stdexcept>
#include <string>
#include "avl.hpp"

TEST(BalancingCorrectness, balanced_test_1) {
    avl<std::string, int> my_map(
        {
            {"banana", 9},
            {"apple", 5},
            {"apricot", 10},
            {"orange", 11},
            {"lemon", 20},
            {"pear", 50},
            {"cherry", 35},
            {"tomato", 38},
            {"plum", 32},
            {"tangerine", 33},
            {"almond", 34},
            {"walnut", 14},
            {"grapefruit", 100},
            {"pomegranate", 145}
        });
    EXPECT_EQ(true, my_map.is_balanced());
}

TEST(BalancingCorrectness, balancing_test_2) {
    avl<int, std::string> my_map(
        {
            {-100, "Python"},
            {100, "C++"},
            {80, "Java"},
            {90, "Rust"},
            {-25, "JavaScript"},
            {0, "Julia"},
            {200, "C"},
            {500, "B"},
            {1000, "A"},
            {5000, "Assembler"},
            {10000, "Binary code"},
            {3000, "Fortran"},
            {-50000, "HTML"},
            {20000, "CSS"},
            {-30, "Ruby"},
            {70, "Haskell"},
            {1001101, "Linux"}
        });
    EXPECT_EQ(true, my_map.is_balanced());
    EXPECT_EQ(false, my_map.empty());
    EXPECT_EQ(17, my_map.size());
}

TEST(InsertionCorrectness, insert_test_1) {
    avl<std::string, int> my_map(
        {
            {"banana", 9},
            {"apple", 5},
            {"apricot", 10},
            {"orange", 11},
            {"lemon", 20},
            {"pear", 50},
            {"cherry", 35},
            {"tomato", 38},
            {"plum", 32}
        });
    my_map.insert({"pomegranate", 145});
    my_map.insert({"grapefruit", 100});
    my_map.insert({"walnut", 14});
    my_map.insert({"almond", 34});
    my_map.insert({"tangerine", 33});
    EXPECT_EQ(my_map["walnut"], 14);
    EXPECT_EQ(my_map["grapefruit"], 100);
    EXPECT_EQ(my_map["pomegranate"], 145);
    EXPECT_EQ(my_map["tangerine"], 33);
    EXPECT_EQ(my_map["almond"], 34);
}

TEST(InsertionCorrectness, insert_test_2) {
    avl<int, std::string> my_map({});
    my_map.insert({0, "Julia"});
    my_map.insert({200, "C"});
    my_map.insert({100, "C++"});
    my_map.insert({70, "Haskell"});
    my_map.insert({1001101, "Linux"});
    EXPECT_EQ(my_map.find(0)->second, "Julia");
    EXPECT_EQ(my_map.find(100)->second, "C++");
    EXPECT_EQ(my_map.find(1001101)->second, "Linux");
}

TEST(EraseCorrectness, erase_test_1) {
    avl<std::string, int> my_map(
        {
            {"banana", 9},
            {"apple", 5},
            {"apricot", 10},
            {"orange", 11},
            {"lemon", 20},
            {"pear", 50},
            {"cherry", 35},
            {"tomato", 38},
            {"plum", 32},
            {"tangerine", 33},
            {"almond", 34},
            {"walnut", 14},
            {"grapefruit", 100},
            {"pomegranate", 145}
        });
    my_map.erase("banana");
    my_map.erase("pear");
    EXPECT_EQ(my_map.contains("banana"), false);
    EXPECT_EQ(my_map.contains("pear"), false);
    EXPECT_EQ(my_map.contains("orange"), true);
    my_map.erase("orange");
    EXPECT_EQ(my_map.contains("orange"), false);
    my_map.erase("apple");
    my_map.erase("almond");
    my_map.erase("tangerine");
    my_map.erase("cherry");
    my_map.erase("apple");
    EXPECT_EQ(my_map.size(), 7);
}

TEST(EraseCorrectness, erase_test_2) {
    avl<int, std::string> my_map(
        {
            {-100, "Python"},
            {100, "C++"},
            {80, "Java"},
            {90, "Rust"},
            {-25, "JavaScript"},
            {0, "Julia"},
            {200, "C"},
            {500, "B"},
            {1000, "A"},
            {5000, "Assembler"},
            {10000, "Binary code"},
            {3000, "Fortran"},
            {-50000, "HTML"},
            {20000, "CSS"},
            {-30, "Ruby"},
            {70, "Haskell"},
            {1001101, "Linux"}
        });
    my_map.erase(20000);
    my_map.erase(80);
    my_map.erase(-30);
    my_map.erase(70);
    my_map.erase(80);
    my_map.erase(-100);
    my_map.erase(80);
    EXPECT_EQ(my_map.size(), 12);
    EXPECT_EQ(my_map.find(80), my_map.end());
    EXPECT_EQ(my_map.find(20000), my_map.end());
    EXPECT_EQ(my_map.find(70), my_map.end());
    try {
        std::string value = my_map.at(-100);
    } catch (const std::out_of_range& err) {
        std::string msg = err.what();
        EXPECT_EQ(msg, "Key is not in the map!");
    } catch (...) {
        EXPECT_EQ("Exception", "Out of range");
    }
}

TEST(FindCorrectness, correct_find_operation_test_1) {
    avl<std::string, int> my_map(
        {
            {"banana", 9},
            {"apple", 5},
            {"apricot", 10},
            {"orange", 11},
            {"lemon", 20},
            {"pear", 50},
            {"cherry", 35},
            {"tomato", 38},
            {"plum", 32},
            {"tangerine", 33},
            {"almond", 34},
            {"walnut", 14},
            {"grapefruit", 100},
            {"pomegranate", 145}
        });
    {
        auto iter = my_map.find("lemon");
        EXPECT_EQ(iter->first, "lemon");
        EXPECT_EQ(iter->second, 20);
    }
    {
        auto iter = my_map.find("walnut");
        EXPECT_EQ(iter->first, "walnut");
        EXPECT_EQ(iter->second, 14);
    }
    {
        auto iter = my_map.find("pineapple");
        EXPECT_EQ(iter, my_map.end());
    }
}

TEST(FindCorrectness, correct_find_operation_test_2) {
    avl<int, std::string> my_map(
        {
            {-100, "Python"},
            {100, "C++"},
            {80, "Java"},
            {90, "Rust"},
            {-25, "JavaScript"},
            {0, "Julia"},
            {200, "C"},
            {500, "B"},
            {1000, "A"},
            {5000, "Assembler"},
            {10000, "Binary code"},
            {3000, "Fortran"},
            {-50000, "HTML"},
            {20000, "CSS"},
            {-30, "Ruby"},
            {70, "Haskell"},
            {1001101, "Linux"}
        });
    try {
        std::string value = my_map.at(50);
    } catch (const std::out_of_range& err) {
        std::string msg = err.what();
        EXPECT_EQ(msg, "Key is not in the map!");
    } catch (...) {
        EXPECT_EQ("Exception", "Out of range");
    }
    {
        auto iter = my_map.find(100);
        EXPECT_EQ(iter->first, 100);
        EXPECT_EQ(iter->second, "C++");
        ++iter;
        EXPECT_EQ(iter->first, 200);
        EXPECT_EQ(iter->second, "C");
    }
    {
        auto iter = my_map.find(10000);
        EXPECT_EQ(iter->first, 10000);
        EXPECT_EQ(iter->second, "Binary code");
        --iter;
        EXPECT_EQ(iter->first, 5000);
        EXPECT_EQ(iter->second, "Assembler");
    }
}

TEST(IterationCorrectness, iteration_correctness_test_1) {
    avl<std::string, int> my_map(
        {
            {"banana", 9},
            {"apple", 5},
            {"apricot", 10},
            {"orange", 11},
            {"lemon", 20},
            {"pear", 50},
            {"cherry", 35},
            {"tomato", 38},
            {"plum", 32},
            {"tangerine", 33},
            {"almond", 34},
            {"walnut", 14},
            {"grapefruit", 100},
            {"pomegranate", 145}
        });
    auto iter = my_map.find("banana");
    std::vector<std::string> key_sorted = {
        "banana",
        "cherry",
        "grapefruit",
        "lemon",
        "orange",
        "pear",
        "plum",
        "pomegranate",
        "tangerine",
        "tomato",
        "walnut"
    };
    int index = 0;
    while (iter != my_map.end()) {
        EXPECT_EQ(iter->first, key_sorted[index]);
        index += 1;
        ++iter;
    }
}

TEST(IterationCorrectness, iteration_correctness_test_2) {
    avl<int, std::string> my_map(
        {
            {-100, "Python"},
            {100, "C++"},
            {80, "Java"},
            {90, "Rust"},
            {-25, "JavaScript"},
            {0, "Julia"},
            {200, "C"},
            {500, "B"},
            {1000, "A"},
            {5000, "Assembler"},
            {10000, "Binary code"},
            {3000, "Fortran"},
            {-50000, "HTML"},
            {20000, "CSS"},
            {-30, "Ruby"},
            {70, "Haskell"},
            {1001101, "Linux"}
        });
    std::vector<std::string> values = {
        "Linux", "CSS", "Binary code", "Assembler", "Fortran",
        "A", "B", "C", "C++", "Rust", "Java", "Haskell",
        "Julia", "JavaScript", "Ruby", "Python", "HTML"
    };
    auto iter = my_map.rbegin();
    int index = 0;
    while (iter != my_map.rend()) {
        EXPECT_EQ(iter->second, values[index]);
        index += 1;
        ++iter;
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
