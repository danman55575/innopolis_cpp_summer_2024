#pragma once
#include <string>
#include <list>
#include <memory>

std::string substitute(
    std::shared_ptr<std::list<std::string>> parts, int number
);
