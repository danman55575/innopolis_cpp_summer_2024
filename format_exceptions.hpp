#pragma once
#include <string>

class FormatException {
 protected:
    std::string message_;
 public:
    explicit FormatException(const std::string& message);
    std::string what() const;
    std::string virtual info() const;
};

class SyntaxException: public FormatException {
 public:
    explicit SyntaxException(const std::string& message);
    std::string info() const override;
};

class ArgumentQuantityException: public FormatException {
 public:
    explicit ArgumentQuantityException(const std::string& message);
    std::string info() const override;
};

class MissingArgumentValueException: public FormatException {
 public:
    explicit MissingArgumentValueException(const std::string& message);
    std::string info() const override;
};
