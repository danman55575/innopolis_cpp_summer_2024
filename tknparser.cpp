#include <string>
#include <iostream>
#include <cstdarg>
#include <optional>
#include <numeric>
#include "tknparser.hpp"

void TokenParser::SetStartCallback(void(*callback_for_start)()) {
    this->start_callback = callback_for_start;
}

void TokenParser::SetEndCallback(void(*callback_for_end)()) {
    this->end_callback = callback_for_end;
}

void TokenParser::SetDigitTokenCallback(void(*callback_for_digit)(uint64_t)) {
    this->number_callback = callback_for_digit;
}

void TokenParser::SetStringTokenCallback(
    void(*callback_for_str)(const std::string&)) {
    this->string_callback = callback_for_str;
}

std::optional<uint64_t> TokenParser::convert_to_number(
    const std::string& token) const {
    std::string max_num = "18446744073709551615";
    std::string num = "";
    bool is_zero = true;
    for (char sym : token) {
        if ((sym < '0') || (sym > '9')) return {};
        if (sym > '0') is_zero = false;
        if (!is_zero) num += sym;
    }
    if (num.size() > max_num.size()) return {};
    if ((num.size() == max_num.size()) && (num > max_num)) return {};

    uint64_t number = std::accumulate(token.begin(), token.end(), 0,
    [](uint64_t a, char b){return (uint64_t) (a * 10 + b - 48);});
    return number;
}

void TokenParser::process_token(std::string token) const {
    std::optional<uint64_t> digit_token = this->convert_to_number(token);
    if (digit_token) {
        this->number_callback(digit_token.value());
    } else {
        this->string_callback(token);
    }
}

void TokenParser::Parse(const std::string& line) {
    this->start_callback();

    std::string max_num = "18446744073709551615";
    std::string word = "";
    for (char sym : line) {
        if ((sym == ' ') || (sym == '\n') || (sym == '\t')) {
            if (!word.empty()) {
                process_token(word);
            }

            word.clear();
            continue;
        }
        word += sym;
    }
    if (!word.empty()) process_token(word);

    this->end_callback();
}
