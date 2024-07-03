#include <string>
#include "format_exceptions.hpp"

FormatException::FormatException(const std::string& message) {
    this->message_ = message;
}

std::string FormatException::what() const {
    return this->message_;
}

std::string FormatException::info() const {
    return "Exception is to the the format() function";
}

SyntaxException::SyntaxException(
    const std::string& message
): FormatException(message) {}

std::string SyntaxException::info() const {
    return "Exception is related to incorrect string syntax for substitution";
}

ArgumentQuantityException::ArgumentQuantityException(
    const std::string& message
): FormatException(message) {}

std::string ArgumentQuantityException::info() const {
    return "Exception is related to unexpected amount of arguments";
}

MissingArgumentValueException::MissingArgumentValueException(
    const std::string& message
): FormatException(message) {}

std::string MissingArgumentValueException::info() const {
    return "Exception is related to unexpected labelling of the arguments";
}
