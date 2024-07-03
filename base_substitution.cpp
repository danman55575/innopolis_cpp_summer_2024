#include <string>
#include <list>
#include <stdexcept>
#include <memory>
#include "base_substitution.hpp"

std::string substitute(
    std::shared_ptr<std::list<std::string>> parts, int number
) {
    if (parts->size() > 1) {
        throw std::invalid_argument("Lack of arguments!");
    }
    if (number == -1e9) {
        return "number";
    }
    return parts->front();
}
