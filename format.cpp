#include <iostream>
#include <string>
#include <list>
#include <stdexcept>
#include <utility>
#include <vector>
#include <sstream>
#include <memory>
#include <algorithm>
#include "base_substitution.hpp"
#include "format.hpp"
#include "format_exceptions.hpp"

template<typename Arg>
std::string substitute(
    std::shared_ptr<std::list<std::string>> parts, int number, Arg arg
) {
    auto iter = parts->begin();
    std::stringstream SS;
    SS << arg;
    std::string str_arg = SS.str();
    while (iter != parts->end()) {
        const std::string& elem = *iter;
        if (elem[0] == '{') {
            int num = 0;
            int size = elem.size();
            for (int i = 1; i < size - 1; i += 1) {
                num = 10 * num + (elem[i] - 48);
            }
            if (num == number) {
                *iter = str_arg;
            } else {
                std::string error_msg = "Number of arguments is less than "
                + std::to_string(num);
                throw ArgumentQuantityException(error_msg);
            }
        }
        iter++;
    }
    std::string ans = "";
    iter = parts->begin();
    while (iter != parts->end()) {
        ans += (*iter);
        iter++;
    }
    return ans;
}

template<typename Arg, typename... Args>
std::string substitute(
    std::shared_ptr<std::list<std::string>> parts,
    int number, Arg arg, Args... args
) {
    auto iter = parts->begin();
    std::stringstream SS;
    SS << arg;
    std::string str_arg = SS.str();
    while (iter != parts->end()) {
        const std::string& elem = *iter;
        if (elem[0] == '{') {
            int num = 0;
            int size = elem.size();
            for (int i = 1; i < size - 1; i += 1) {
                num = 10 * num + (elem[i] - 48);
            }
            if (num == number) {
                *iter = str_arg;
            }
        }
        iter++;
    }
    return substitute(parts, number + 1, args...);
}

template<typename... Args>
std::string format(const std::string& text, Args... args) {
    std::list<std::string> parts;
    std::string word;
    int i = 0, max_value = 0;
    std::vector<bool> used(1001, false);
    int size = text.size();
    while (i < size) {
        if (text[i] == '}') {
            throw SyntaxException("Unexpected symbol '}'");
        } else if (text[i] == '{') {
            parts.push_back(word);
            word.clear();
            bool f = false;
            int num = 0;
            i++;
            while (i < size) {
                if (text[i] == '}') {
                    if (text[i - 1] == '{') {
                        throw SyntaxException("Unexpected symbol '}'");
                    }
                    f = true;
                    break;
                }
                if (text[i] < '0' || text[i] > '9') {
                    std::string error_msg = "Unexpected symbol '";
                    error_msg.push_back(text[i]);
                    error_msg += "' in curly braces";
                    throw SyntaxException(error_msg);
                } else {
                    num = 10 * num + text[i] - 48;
                    if (num > 1000) {
                        throw ArgumentQuantityException(
                            "Amount of arguments cannot exceed 1000");
                    }
                }
                i++;
            }
            if (f == false) {
                throw SyntaxException("Expected symbol '}' is not found");
            }
            max_value = std::max(max_value, num);
            parts.push_back("{" + std::to_string(num) + "}");
            used[num] = 1;
            i++;
        } else {
            word += text[i];
            i++;
        }
    }
    if (!word.empty()) parts.push_back(word);
    for (int label = 0; label < max_value; label += 1) {
        if (!used[label]) {
            std::string error_msg = "Argument's label " +
                std::to_string(label) + " is not found";
            throw MissingArgumentValueException(error_msg);
        }
    }
    return substitute(
        std::make_shared<std::list<std::string>>(parts), 0, args...);
}
