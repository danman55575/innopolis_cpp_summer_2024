#pragma once
#include <string>
#include <iostream>
#include <optional>

class TokenParser {
 private:
    void (*start_callback)() = [](){};
    void (*end_callback)() = [](){};
    void (*number_callback)(uint64_t) = [](uint64_t num){num+=1;};
    void (*string_callback)(const std::string&) = [](
      const std::string& word){std::string token = word;};

    std::optional<uint64_t> convert_to_number(const std::string& token) const;

    void process_token(std::string token) const;

 public:
    TokenParser() = default;

    // Устанавливаем callback-функцию перед стартом парсинга.
    void SetStartCallback(void (*)());

    // Устанавливаем callback-функцию после окончания парсинга.
    void SetEndCallback(void (*)());

    // Устанавливаем callback-функцию для обработки чисел.
    void SetDigitTokenCallback(void (*)(uint64_t));

    // Устанавливаем callback-функцию для обработки строк
    void SetStringTokenCallback(void (*)(const std::string&));

    void Parse(const std::string &);
};
