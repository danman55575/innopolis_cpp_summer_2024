#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <memory>
#include "bigint.hpp"

BigInt::BigInt(const std::string& num) {
    if (num.size() == 0) {
        std::string msg = "Empty string cannot be converted to type BigInt";
        throw std::invalid_argument(msg);
    }
    int start_idx = num.size() - 1, end_idx = 0, size = num.size();
    if (start_idx == -1) return;
    if (num[0] == '-') {
        this->is_negative = true;
        end_idx += 1;
    } for (int i = end_idx; i < size; i += 1) {
        if (num[i] < '0' || num[i] > '9') {
            std::string msg = "Unexpected symbol at position ";
            msg += std::to_string(i + 1);
            throw std::out_of_range(msg);
        }
    } while ((end_idx < size - 1) && (num[end_idx] == '0')) {
        end_idx += 1;
    } for (int i = start_idx; i >= end_idx; i -= 9) {
        std::string str_unit = "";
        for (int j = std::max(end_idx, i - 8); j <= i; j += 1) {
            str_unit += num[j];
        }
        int32_t unit = std::stoi(str_unit);
        this->container.PushBack(unit);
    }
}

BigInt::BigInt(const BigInt& num) {
    this->container = num.container;
    this->is_negative = num.is_negative;
}

void BigInt::remove_leading_zeros() {
    while (this->container.getSize() > 1 && this->container.Back() == 0) {
        this->container.PopBack();
    }
    if (this->container.getSize() == 1 && this->container.Back() == 0) {
        this->is_negative = false;
    }
}

bool BigInt::equal_by_absolute_value_to(const BigInt& obj) const {
    if (this->container.getSize() != obj.container.getSize()) {
        return false;
    }
    std::shared_ptr<ListNode<int32_t>> node1 = this->container.getStart();
    std::shared_ptr<ListNode<int32_t>> node2 = obj.container.getStart();
    while (node1) {
        if (node1->getData() != node2->getData()) {
            return false;
        }
        node1 = node1->getNext();
        node2 = node2->getNext();
    }
    return true;
}

bool BigInt::less_by_absolute_value_to(const BigInt& obj) const {
    if (this->container.getSize() < obj.container.getSize()) {
        return true;
    } else if (this->container.getSize() > obj.container.getSize()) {
        return false;
    }
    int obj1_is_less = -1;
    std::shared_ptr<ListNode<int32_t>> node1 = this->container.getStart();
    std::shared_ptr<ListNode<int32_t>> node2 = obj.container.getStart();
    while (node1) {
        if (node1->getData() < node2->getData()) {
            obj1_is_less = 1;
        } else if (node1->getData() > node2->getData()) {
            obj1_is_less = 0;
        }
        node1 = node1->getNext();
        node2 = node2->getNext();
    }
    if (obj1_is_less == 1) {
        return true;
    } else {
        return false;
    }
}

BigInt BigInt::operator-() const {
    BigInt ans = *this;
    ans.is_negative = !ans.is_negative;
    return ans;
}

BigInt operator+(const BigInt& obj1, const BigInt& obj2) {
    if (obj1.less_by_absolute_value_to(obj2)) {
        return obj2 + obj1;
    }
    if (obj1.is_negative && !obj2.is_negative) {
        return -(-obj1 - obj2);
    }
    if (!obj1.is_negative && obj2.is_negative) {
        return obj1 - (-obj2);
    }
    int64_t num, carry = 0;
    MyList<int32_t> ans;
    int max_size = std::max(obj1.container.getSize(), obj2.container.getSize());
    std::shared_ptr<ListNode<int32_t>> node1 = obj1.container.getStart();
    std::shared_ptr<ListNode<int32_t>> node2 = obj2.container.getStart();
    for (int i = 0; i < max_size; i += 1) {
        if (node2 == nullptr) {
            num = node1->getData() + carry;
        } else {
            num = node1->getData() + node2->getData() + carry;
            node2 = node2->getNext();
        }
        node1 = node1->getNext();
        ans.PushBack(num % BigInt::UNIT);
        carry = num / BigInt::UNIT;
    }
    if (carry != 0) {
        ans.PushBack(carry);
    }
    return BigInt{ans, obj1.is_negative};
}

BigInt operator-(const BigInt& obj1, const BigInt& obj2) {
    if (obj1.less_by_absolute_value_to(obj2)) {
        return -obj2 + obj1;
    }
    if (!obj1.is_negative && obj2.is_negative) {
        return obj1 + -obj2;
    }
    if (obj1.is_negative && !obj2.is_negative) {
        return -(-obj1 + obj2);
    }
    int64_t num, carry = 0;
    MyList<int32_t> ans;
    int max_size = std::max(obj1.container.getSize(), obj2.container.getSize());
    std::shared_ptr<ListNode<int32_t>> node1 = obj1.container.getStart();
    std::shared_ptr<ListNode<int32_t>> node2 = obj2.container.getStart();
    for (int i = 0; i < max_size; i += 1) {
        if (node2 == nullptr) {
            num = node1->getData() - carry;
            if (num < 0) {
                num = BigInt::UNIT + num;
                carry = 1;
            } else {
                carry = 0;
            }
            ans.PushBack(num);
        } else {
            num = node1->getData() - node2->getData() - carry;
            if (num < 0) {
                num = BigInt::UNIT + num;
                carry = 1;
            } else {
                carry = 0;
            }
            ans.PushBack(num);
            node2 = node2->getNext();
        }
        node1 = node1->getNext();
    }
    BigInt res{ans, obj1.is_negative};
    res.remove_leading_zeros();
    return res;
}

BigInt operator*(const BigInt& obj1, const BigInt& obj2) {
    MyList<int32_t> ans;
    ans.PushBack(0);
    std::shared_ptr<ListNode<int32_t>> node1 = obj1.container.getStart();
    int degree = 0;
    while (node1) {
        auto ans_node = ans.getStart();
        for (int i = 0; i < degree; i += 1) {
            ans_node = ans_node->getNext();
        }
        auto node2 = obj2.container.getStart();
        int64_t carry = 0;
        while (node2) {
            int64_t num = node1->getData();
            num = num * node2->getData() + carry;
            if (ans_node) {
                num += ans_node->getData();
                carry = num / BigInt::UNIT;
                ans_node->setData(num % BigInt::UNIT);
                ans_node = ans_node->getNext();
            } else {
                ans.PushBack(num % BigInt::UNIT);
                carry = num / BigInt::UNIT;
            }
            node2 = node2->getNext();
        } while (carry != 0) {
            if (ans_node) {
                carry += ans_node->getData();
                ans_node->setData(carry % BigInt::UNIT);
                carry = carry / BigInt::UNIT;
                ans_node = ans_node->getNext();
            } else {
                ans.PushBack(carry % BigInt::UNIT);
                carry = carry / BigInt::UNIT;
            }
        }
        degree += 1;
        node1 = node1->getNext();
}
    bool is_negat = false;
    if (obj1.is_negative ^ obj2.is_negative) {
        is_negat = true;
    }
    BigInt res = BigInt{ans, is_negat};
    return res;
}

BigInt operator+(const BigInt& obj1, int32_t obj2) {
    std::string str_obj2 = std::to_string(obj2);
    BigInt num2{str_obj2};
    return obj1 + num2;
}

BigInt operator-(const BigInt& obj1, int32_t obj2) {
    std::string str_obj2 = std::to_string(obj2);
    BigInt num2{str_obj2};
    return obj1 - num2;
}

BigInt operator*(const BigInt& obj1, int32_t obj2) {
    std::string str_obj2 = std::to_string(obj2);
    BigInt num2{str_obj2};
    return obj1 * num2;
}

bool operator<(const BigInt& obj1, const BigInt& obj2) {
    if (obj1.is_negative && obj2.is_negative) {
        return obj2.less_by_absolute_value_to(obj1);
    } else if (!obj1.is_negative && !obj2.is_negative) {
        return obj1.less_by_absolute_value_to(obj2);
    } else if (obj1.is_negative && !obj2.is_negative) {
        return true;
    } else {
        return false;
    }
}

bool operator==(const BigInt& obj1, const BigInt& obj2) {
    if (obj1.is_negative != obj2.is_negative) {
        return false;
    }
    return obj1.equal_by_absolute_value_to(obj2);
}

bool operator!=(const BigInt& obj1, const BigInt& obj2) {
    return !(obj1 == obj2);
}

bool operator>(const BigInt& obj1, const BigInt& obj2) {
    return (!(obj1 < obj2) && (obj1 != obj2));
}

bool operator<=(const BigInt& obj1, const BigInt& obj2) {
    return ((obj1 < obj2) || (obj1 == obj2));
}

bool operator>=(const BigInt& obj1, const BigInt& obj2) {
    return !(obj1 < obj2);
}

std::ostream& operator<<(std::ostream& out, const BigInt& obj) {
    std::string output = "";
    auto node = obj.container.getStart();
    while (node) {
        std::string str_num = std::to_string(
            node->getData());
        std::reverse(str_num.begin(), str_num.end());
        while (str_num.size() < 9) {
            str_num.push_back('0');
        }
        output += str_num;
        node = node->getNext();
    } while (output.size() > 1 && output.back() == '0') {
        output.pop_back();
    }
    std::reverse(output.begin(), output.end());
    if (obj.is_negative) {
        out << '-';
    }
    out << output;
    return out;
}
