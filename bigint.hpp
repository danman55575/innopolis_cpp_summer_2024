#pragma once
#include <iostream>
#include <string>
#include "mylist.cpp"

class BigInt {
 private:
    MyList<int32_t> container;
    bool is_negative = false;
    static const int64_t UNIT = 1e9;
    bool equal_by_absolute_value_to(const BigInt&) const;
    bool less_by_absolute_value_to(const BigInt&) const;
    void remove_leading_zeros();
    BigInt(const MyList<int32_t>& cont, bool is_negat):
    container(cont), is_negative(is_negat) {}

 public:
    explicit BigInt(const std::string& num);
    BigInt(const BigInt& num);
    BigInt(BigInt&& num): container(num.container),
    is_negative(num.is_negative) {
        num.container = MyList<int32_t>();
        num.is_negative = false;
    }
    BigInt operator-() const;
    friend BigInt operator+(const BigInt&, const BigInt&);
    friend BigInt operator-(const BigInt&, const BigInt&);
    friend BigInt operator*(const BigInt&, const BigInt&);
    friend BigInt operator+(const BigInt&, int32_t);
    friend BigInt operator-(const BigInt&, int32_t);
    friend BigInt operator*(const BigInt&, int32_t);
    friend std::ostream& operator<<(std::ostream&, const BigInt&);
    friend bool operator<(const BigInt&, const BigInt&);
    friend bool operator>(const BigInt&, const BigInt&);
    friend bool operator==(const BigInt&, const BigInt&);
    friend bool operator!=(const BigInt&, const BigInt&);
    friend bool operator<=(const BigInt&, const BigInt&);
    friend bool operator>=(const BigInt&, const BigInt&);
};
