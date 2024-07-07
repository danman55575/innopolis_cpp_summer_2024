#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <sstream>
#include <utility>
#include "bigint.hpp"

TEST(ResultCorrectness, operation_plus_correctness_test_1) {
    BigInt num1{"10000000000000000000000000009"};
    BigInt num2{"8000000000000000000000000008519"};
    BigInt num3{"1999999999999999929999999999"};
    BigInt num4{"34444444444666666666666666660000000000002"};
    BigInt num5{"-00000000000000000000000000000000000000098989845754321"};
    BigInt res1 = num1 + num2;
    BigInt res2 = num3 + num4;
    BigInt res3 = num1 + num5;
    std::string correct_res1 = "8010000000000000000000000008528\n";
    std::string correct_res2 = "34444444444668666666666666659930000000001\n";
    std::string correct_res3 = "9999999999999901010154245688\n";
    std::string correct_res = correct_res1 + correct_res2 + correct_res3;
    std::stringstream SS;
    SS << res1 << "\n";
    SS << res2 << "\n";
    SS << res3 << "\n";
    EXPECT_EQ(SS.str(), correct_res);
}

TEST(ResultCorrectness, operation_plus_correctness_test_2) {
    BigInt num1{"0000000000000000000000000000"};
    BigInt num2{"05000000000"};
    BigInt num3{"-4055"};
    BigInt res1 = num1 + num2;
    BigInt res2 = num3 + num2;
    BigInt res3 = num1 + num3;
    std::string correct_res = "5000000000\n4999995945\n-4055\n";
    std::stringstream SS;
    SS << res1 << "\n" << res2 << "\n" << res3 << "\n";
    EXPECT_EQ(SS.str(), correct_res);
}

TEST(ResultCorrectness, operation_plus_correctness_test_3) {
    BigInt num1{"108108108108108108108108108108108"};
    BigInt num2{"-152"};
    int32_t num3 = 1379737935;
    BigInt res1 = num1 + -num2;
    BigInt res2 = num2 + num3;
    BigInt res3 = num1 + num3;
    std::string correct_res = "108108108108108108108108108108260\n";
    correct_res += "1379737783\n108108108108108108108109487846043\n";
    std::stringstream SS;
    SS << res1 << "\n" << res2 << "\n" << res3 << "\n";
    EXPECT_EQ(SS.str(), correct_res);
}

TEST(ResultCorrectness, operation_minus_correctness_test_1) {
    BigInt num1{"314159265358979323846264"};
    BigInt num2{"444444444444444444444444"};
    int32_t num3 = 1000000007;
    BigInt res1 = num1 - num2;
    BigInt res2 = -num2 - num3;
    BigInt res3 = num1 - num3;
    std::string correct_res = "-130285179085465120598180\n";
    correct_res += "-444444444444445444444451\n314159265358978323846257\n";
    std::stringstream SS;
    SS << res1 << "\n" << res2 << "\n" << res3 << "\n";
    EXPECT_EQ(SS.str(), correct_res);
}

TEST(ResultCorrectness, operation_minus_correctness_test_2) {
    BigInt num1{"2718281828459045235"};
    BigInt num2{"-0000000000000005"};
    int32_t num3 = -45893;
    BigInt res1 = num2 - num1;
    BigInt res2 = num1 - num3;
    BigInt res3 = num2 - num3;
    std::string correct_res = "-2718281828459045240\n";
    correct_res += "2718281828459091128\n45888\n";
    std::stringstream SS;
    SS << res1 << "\n" << res2 << "\n" << res3 << "\n";
    EXPECT_EQ(SS.str(), correct_res);
}

TEST(ResultCorrectness, operation_mul_correctness_test_1) {
    BigInt num1{"3959395939593"};
    BigInt num2{"-790985"};
    int32_t num3 = 50035;
    BigInt res1 = num1 * num2;
    BigInt res2 = num1 * num3;
    BigInt res3 = num2 * num3;
    std::string correct_res = "-3131822797278969105\n";
    correct_res += "198108375837535755\n-39576934475\n";
    std::stringstream SS;
    SS << res1 << "\n" << res2 << "\n" << res3 << "\n";
    EXPECT_EQ(SS.str(), correct_res);
}

TEST(ResultCorrectness, operation_mul_correctness_test_2) {
    BigInt num1{"989758453984"};
    BigInt num2{"909234545"};
    int32_t num3 = 0;
    BigInt res1 = num1 * num2;
    BigInt res2 = num1 * num3;
    BigInt res3 = num2 * num3;
    std::string correct_res = "899922577568045677280\n0\n0\n";
    std::stringstream SS;
    SS << res1 << "\n" << res2 << "\n" << res3 << "\n";
    EXPECT_EQ(SS.str(), correct_res);
}

TEST(ResultCorrectness, operation_mul_correctness_test_3) {
    BigInt num1{"-00000005000000"};
    BigInt num2{"-0001282565121024"};
    int32_t num3 = 392781243;
    BigInt res1 = num1 * num2;
    BigInt res2 = num2 * num3;
    BigInt res3 = num1 * num3;
    std::string correct_res = "6412825605120000000\n";
    correct_res += "-503767522464252152832\n-1963906215000000\n";
    std::stringstream SS;
    SS << res1 << "\n" << res2 << "\n" << res3 << "\n";
    EXPECT_EQ(SS.str(), correct_res);
}

TEST(ExceptionCorrectness, invalid_string_test_1) {
    try {
        BigInt num{""};
    } catch (const std::invalid_argument& err) {
        std::string msg = "Empty string cannot be converted to type BigInt";
        EXPECT_EQ(err.what(), msg);
    } catch(...) {
        EXPECT_EQ("exception", "invalid_argument");
    }
}

TEST(ExceptionCorrectness, invalid_string_test_2) {
    try {
        BigInt num{"389t8"};
    } catch (const std::out_of_range& err) {
        std::string msg = "Unexpected symbol at position 4";
        EXPECT_EQ(err.what(), msg);
    } catch (...) {
        EXPECT_EQ("exception", "invalid_argument");
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
