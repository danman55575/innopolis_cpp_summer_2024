#pragma once
#include <string>
#include <list>
#include <memory>

template<typename Arg>
std::string substitute(
    std::shared_ptr<std::list<std::string>> parts,
    int number, Arg arg
);

template<typename Arg, typename... Args>
std::string substitute(
    std::shared_ptr<std::list<std::string>> parts,
    int number, Arg arg, Args... args
);

template<typename... Args>
std::string format(const std::string& text, Args... args);
