#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <list>
#include <stdexcept>
#include <utility>
#include <vector>
#include <sstream>
#include "format.hpp"
#include "format.cpp"

TEST(ResultCorrectness, correct_format_string_result_test_1) {
    std::string res1 = format("I love {0}!", "Innopolis");
    std::string correct_res1 = "I love Innopolis!";
    std::string res2 = format("  I {0} Innopolis !", "love");
    std::string correct_res2 = "  I love Innopolis !";
    std::string res3 = format("{0} love Innopolis!", "I");
    std::string correct_res3 = "I love Innopolis!";
    EXPECT_EQ(res1, correct_res1);
    EXPECT_EQ(res2, correct_res2);
    EXPECT_EQ(res3, correct_res3);
}

TEST(ResultCorrectness, correct_format_string_result_test_2) {
    std::string correct_res = "Do you love Innopolis?";
    std::string res1 = format("Do {1} love {0}?",
    "Innopolis", "you");
    std::string res2 = format("{0} you{1} Innopolis?",
    "Do", " love");
    std::string res3 = format("D{0}{1}y{0}u{1}l{0}ve{1}Inn{0}p{0}lis?",
    "o", " ");
    EXPECT_EQ(res1, correct_res);
    EXPECT_EQ(res2, correct_res);
    EXPECT_EQ(res3, correct_res);
}

TEST(ResultCorrectness, correct_format_string_result_test_3) {
    std::string correct_res = "Have you heard about 108 bar?";
    std::string res1 = format("{3} you {2} {1} {0} bar?",
    108, "about", "heard", "Have");
    std::string res2 = format("Have you heard about {2}{0}{1} bar?",
    0, 8, 1);
    std::string res3 = format("Have{1}heard{2}10{0}",
    "8 bar?", " you ", " about ");
    EXPECT_EQ(res1, correct_res);
    EXPECT_EQ(res2, correct_res);
    EXPECT_EQ(res3, correct_res);
}

TEST(ExceptionsCorrectness, correct_exception_throw_test_1) {
    try {
        std::string res = format("What a wonde{1rful day!");
    } catch (const SyntaxException& se) {
        EXPECT_EQ(se.what(), "Unexpected symbol 'r' in curly braces");
    } catch (...) {
        EXPECT_EQ("Exception", "SyntaxException");
    }
}

TEST(ExceptionsCorrectness, correct_exception_throw_test_2) {
    try {
        std::string res = format("Segment t{1}ree is used often",
        13500, "r");
    } catch (const MissingArgumentValueException& mave) {
        EXPECT_EQ(mave.what(), "Argument's label 0 is not found");
    } catch(...) {
        EXPECT_EQ("Exception", "MissingArgumentValueException");
    }
}

TEST(ExceptionsCorrectness, correct_exception_throw_test_3) {
    try {
        std::string res = format("Compiler} does not understand me...", 5);
    } catch (const SyntaxException& se) {
        EXPECT_EQ(se.what(), "Unexpected symbol '}'");
    } catch(...) {
        EXPECT_EQ("Exception", "SyntaxException");
    }
}

TEST(ExceptionsCorrectness, correct_exception_throw_test_4) {
    try {
        std::string res = format("My secret is {}", 50, "I am");
    } catch (const SyntaxException& se) {
        EXPECT_EQ(se.what(), "Unexpected symbol '}'");
    } catch(...) {
        EXPECT_EQ("Exception", "SyntaxException");
    }
}

TEST(ExceptionsCorrectness, correct_exception_throw_test_5) {
    try {
        std::string res = format("{1001} of red roses are in Linux", "Yes");
    } catch (const ArgumentQuantityException& aqe) {
        EXPECT_EQ(aqe.what(), "Amount of arguments cannot exceed 1000");
    } catch(...) {
        EXPECT_EQ("Exception", "ArgumentQuantityException");
    }
}

TEST(ExceptionsCorrectness, correct_exception_throw_test_6) {
    try {
        std::string res = format("Good {0} over comprehensive {1}",
        "mind");
    } catch (const ArgumentQuantityException& aqe) {
        EXPECT_EQ(aqe.what(), "Number of arguments is less than 1");
    } catch(...) {
        EXPECT_EQ("Exception", "ArgumentQuantityException");
    }
}

TEST(ExceptionsCorrectness, correct_exception_throw_test_7) {
    try {
        std::string res = format("{0} {1} {2} {5} {7}?",
        "Do", "you", "have", "night", "work");
    } catch (const MissingArgumentValueException& mave) {
        EXPECT_EQ(mave.what(), "Argument's label 3 is not found");
        std::string res = "Exception is related";
        res += " to unexpected labelling of the arguments";
        EXPECT_EQ(mave.info(), res);
    } catch(...) {
        EXPECT_EQ("Exception", "MissingArgumentValueException");
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
