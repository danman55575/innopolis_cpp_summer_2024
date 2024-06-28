#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>
#include "tknparser.hpp"

void write_to_file(const std::string& line) {
    std::ofstream out_file("test.txt", std::ios_base::app | std::ios_base::out);
    if (!out_file.is_open()) {
        throw std::runtime_error("Cannot open file!");
    }
    out_file << line << "\n";
    out_file.close();
}

void clear_file() {
    std::ofstream out_file("test.txt");
    if (!out_file.is_open()) {
        throw std::runtime_error("Cannot open file!");
    }
    out_file.close();
}

TEST(ParseCorrectness, correct_split_test_1) {
    TokenParser tokenParser{};
    tokenParser.SetStringTokenCallback(
        [](const std::string& token){write_to_file("String:" + token);});
    tokenParser.SetDigitTokenCallback(
        [](uint64_t num){write_to_file("Number:" + std::to_string(num));});
    std::string line = "Innopolis \n\nrobot\n\n\n\t345\t\t";
    tokenParser.Parse(line);

    std::ifstream in_file;
    in_file.open("test.txt");
    if (!in_file.is_open()) {
        throw std::runtime_error("Cannot open file!");
    }

    std::string word;
    in_file >> word;
    EXPECT_EQ(word, "String:Innopolis");
    in_file >> word;
    EXPECT_EQ(word, "String:robot");
    in_file >> word;
    EXPECT_EQ(word, "Number:345");

    in_file.close();
    clear_file();
}

TEST(ParseCorrectness, correct_split_test_2) {
    TokenParser tokenParser{};
    tokenParser.SetStringTokenCallback(
        [](const std::string& token){write_to_file("String:" + token);});
    tokenParser.SetDigitTokenCallback(
        [](uint64_t num){write_to_file("Number:" + std::to_string(num));});
    std::string line = "\n\n \t N1umber\t\t 108\n i5s \n magic902 \t\t";
    tokenParser.Parse(line);

    std::ifstream in_file;
    in_file.open("test.txt");
    if (!in_file.is_open()) {
        throw std::runtime_error("Cannot open file!");
    }

    std::string word;
    in_file >> word;
    EXPECT_EQ(word, "String:N1umber");
    in_file >> word;
    EXPECT_EQ(word, "Number:108");
    in_file >> word;
    EXPECT_EQ(word, "String:i5s");
    in_file >> word;
    EXPECT_EQ(word, "String:magic902");

    in_file.close();
    clear_file();
}

TEST(ParseCorrectness, correct_split_test_3) {
    TokenParser tokenParser{};
    tokenParser.SetStringTokenCallback(
        [](const std::string& token){write_to_file("String:" + token);});
    tokenParser.SetDigitTokenCallback(
        [](uint64_t num){write_to_file("Number:" + std::to_string(num));});
    std::string line = "\t\n12 012 003r4 \n\n\ttour8p\t\n";
    tokenParser.Parse(line);

    std::ifstream in_file;
    in_file.open("test.txt");
    if (!in_file.is_open()) {
        throw std::runtime_error("Cannot open file!");
    }

    std::string word;
    in_file >> word;
    EXPECT_EQ(word, "Number:12");
    in_file >> word;
    EXPECT_EQ(word, "Number:12");
    in_file >> word;
    EXPECT_EQ(word, "String:003r4");
    in_file >> word;
    EXPECT_EQ(word, "String:tour8p");

    in_file.close();
    clear_file();
}

TEST(CallbackFunctioning, correct_callback_functioning_test_1) {
    TokenParser tokenParser{};
    tokenParser.SetStartCallback(
        [](){write_to_file("Start_Parsing...\n");});
    tokenParser.SetStringTokenCallback(
        [](const std::string& token){write_to_file("String:" + token);});
    tokenParser.SetDigitTokenCallback(
        [](uint64_t num){write_to_file("Number:" + std::to_string(num));});
    tokenParser.SetEndCallback(
        [](){write_to_file("Finish_Parsing\n");});
    std::string line = "\n\nInnoParty\n\n";
    tokenParser.Parse(line);

    std::ifstream in_file;
    in_file.open("test.txt");
    if (!in_file.is_open()) {
        throw std::runtime_error("Cannot open file!");
    }

    std::string word;
    in_file >> word;
    EXPECT_EQ(word, "Start_Parsing...");
    in_file >> word;
    EXPECT_EQ(word, "String:InnoParty");
    in_file >> word;
    EXPECT_EQ(word, "Finish_Parsing");

    in_file.close();
    clear_file();
}

TEST(CallbackFunctioning, correct_callback_functioning_test_2) {
    TokenParser tokenParser{};
    tokenParser.SetStartCallback(
        [](){write_to_file("Start_callback_only");});
    tokenParser.SetStringTokenCallback(
        [](const std::string& token){write_to_file("String:" + token);});
    tokenParser.SetDigitTokenCallback(
        [](uint64_t num){write_to_file("Number:" + std::to_string(num));});
    std::string line = "Bar \t\t \n 108";
    tokenParser.Parse(line);

    std::ifstream in_file;
    in_file.open("test.txt");
    if (!in_file.is_open()) {
        throw std::runtime_error("Cannot open file!");
    }

    std::string word;
    in_file >> word;
    EXPECT_EQ(word, "Start_callback_only");
    in_file >> word;
    EXPECT_EQ(word, "String:Bar");
    in_file >> word;
    EXPECT_EQ(word, "Number:108");

    in_file.close();
    clear_file();
}

TEST(DigitParsing, correct_digit_parsing_test_1) {
    TokenParser tokenParser{};
    tokenParser.SetStringTokenCallback(
        [](const std::string& token){write_to_file("String:" + token);});
    tokenParser.SetDigitTokenCallback(
        [](uint64_t num){write_to_file("Number:" + std::to_string(num));});
    std::string line = "12934 0019234  489u9039 -39485";
    tokenParser.Parse(line);

    std::ifstream in_file;
    in_file.open("test.txt");
    if (!in_file.is_open()) {
        throw std::runtime_error("Cannot open file!");
    }

    std::string word;
    in_file >> word;
    EXPECT_EQ(word, "Number:12934");
    in_file >> word;
    EXPECT_EQ(word, "Number:19234");
    in_file >> word;
    EXPECT_EQ(word, "String:489u9039");
    in_file >> word;
    EXPECT_EQ(word, "String:-39485");

    in_file.close();
    clear_file();
}

TEST(DigitParsing, correct_digit_parsing_test_2) {
    TokenParser tokenParser{};
    tokenParser.SetStringTokenCallback(
        [](const std::string& token){write_to_file("String:" + token);});
    tokenParser.SetDigitTokenCallback(
        [](uint64_t num){write_to_file("Number:" + std::to_string(num));});
    std::string line = "0018446744073709551615\n00018446744073709551620\n-0 0";
    tokenParser.Parse(line);

    std::ifstream in_file;
    in_file.open("test.txt");
    if (!in_file.is_open()) {
        throw std::runtime_error("Cannot open file!");
    }

    std::string word;
    in_file >> word;
    EXPECT_EQ(word, "Number:18446744073709551615");
    in_file >> word;
    EXPECT_EQ(word, "String:00018446744073709551620");
    in_file >> word;
    EXPECT_EQ(word, "String:-0");
    in_file >> word;
    EXPECT_EQ(word, "Number:0");

    in_file.close();
    clear_file();
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
