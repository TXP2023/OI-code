#pragma once
#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <numeric>
#include <ctype.h>
#include <cstdarg>
#include <climits>
#include <time.h>
#include <iostream>
#include <stdint.h>

typedef long long int ll;

class unsigned_large_int {
public:
    unsigned_large_int() {
        number = "0";
    }

    inline const char* show_to_const_char();

    inline std::string show_to_string();

    inline void input();

    static inline unsigned_large_int max(unsigned_large_int a, unsigned_large_int b);

    static inline unsigned_large_int min(unsigned_large_int a, unsigned_large_int b);

    //运算符重载部分
    //重载 =
    //对于一个 unsigned_large_int 对象
    void operator =(const unsigned_large_int other);
    //对于一个无符号整数对象 
    //Type 可以是 (unsigned)short/int/long
    template< typename Type >
    void operator =(Type other);

    //重载+
    unsigned_large_int operator +(const unsigned_large_int other);

    unsigned_large_int operator -(const unsigned_large_int& other);

    unsigned_large_int operator /(const unsigned_large_int& other);

    template<typename Type>
    unsigned_large_int operator /(Type other);

    //重载*
    unsigned_large_int operator *(const unsigned_large_int other);

    //Type 可以是 (unsigned)short/int/long
    template< typename Type >
    unsigned_large_int operator *(Type other);

private:
    std::string number;

    inline ll length();

    // 私有辅助函数：比较两个数的大小
   // 返回: 1 (this > other), 0 (相等), -1 (this < other)
    int compare(const unsigned_large_int& other) const {
        if (number.length() > other.number.length()) return 1;
        if (number.length() < other.number.length()) return -1;
        for (int i = number.length() - 1; i >= 0; --i) {
            if (number[i] > other.number[i]) return 1;
            if (number[i] < other.number[i]) return -1;
        }
        return 0;
    }
};

inline ll unsigned_large_int::length() {
    return number.length();
}

//输入一个高精度类
inline void unsigned_large_int::input() {
    std::string s;
    std::cin >> s;
    ll length = s.length();
    number.resize(length);
    for (size_t i = 0; i < s.length(); i++) {
        number[i] = s[length - i - 1];
    }
    return;
}

//对两个高精度类比较， 返回较大的那个
inline unsigned_large_int unsigned_large_int::max(unsigned_large_int a, unsigned_large_int b) {
    if (a.length() == b.length()) {
        for (ll i = a.length(); i >= 0; i--) {
            if (a.number[i] != b.number[i]) {
                return (a.number[i] > b.number[i]) ? a : b;
            }
        }
        return a;
    }
    return (a.length() > b.length()) ? a : b;
}

inline unsigned_large_int unsigned_large_int::min(unsigned_large_int a, unsigned_large_int b) {
    if (a.length() == b.length()) {
        for (ll i = a.length(); i >= 0; i--) {
            if (a.number[i] != b.number[i]) {
                return (a.number[i] < b.number[i]) ? a : b;
            }
        }
        return a;
    }
    return (a.length() < b.length()) ? a : b;
}

//这个高精度类所代表的数字转化为字符串格式
inline const char* unsigned_large_int::show_to_const_char() {
    const char* p = number.data();
    return p;
}

inline std::string unsigned_large_int::show_to_string() {
    std::string s;
    s.resize(number.length());
    for (size_t i = 0; i < number.length(); i++) {
        s[i] = number[number.length() - i - 1];
    }
    return s;
}

void unsigned_large_int::operator=(const unsigned_large_int other) {
    (*this).number = other.number;
    return;
}

template< typename Type >
inline void unsigned_large_int::operator=(Type other) {
    unsigned_large_int num;
    ll other_num = 0; //other对象的位数
    (*this).number.clear();

    if (other == 0) {

        (*this).number.resize(1, '0');
        return;
    }

    while (other) {
        (*this).number.push_back((other % 10) + '0');
        other /= 10;
    }
    return;
}

unsigned_large_int unsigned_large_int::operator+(const unsigned_large_int other) {
    unsigned_large_int num1 = *this, num2 = other, summation;

    if (num1.length() < num2.length()) {
        std::swap(num1, num2);
    }
    summation.number.resize(num1.length() + 1);
    summation.number = num1.number;

    //加和
    for (size_t i = 0; i < num2.length(); i++) {
        summation.number[i] += num2.number[i] - '0';
    }

    //进位
    for (size_t i = 0; i < summation.length() - 1; i++) {
        if (summation.number[i] - '0' >= 10) {
            summation.number[i + 1]++;
            summation.number[i] -= 10;
        }
    }
    if (summation.number.back() > '9') {
        summation.number.resize(summation.number.length() + 1);
        *(summation.number.end() - 1) = '1';
        *(summation.number.end() - 2) -= 10;
    }
    return summation;
}

//一个 unsigned_large_int 类和一个 unsigned_large_int 类相乘
inline unsigned_large_int unsigned_large_int::operator*(unsigned_large_int other) {
    unsigned_large_int product, num1 = *this;
    if (num1.length() < other.length()) {
        std::swap(num1, other);
    }

    std::vector< int > vproduct(other.length() + num1.length() + 1, 0);
    for (size_t i = 0; i < other.number.length(); i++) {
        for (size_t j = 0; j < num1.length(); j++) {
            vproduct[i + j] += (num1.number[j] - '0') * (other.number[i] - '0');
        }
    }

    for (size_t i = 0; i < vproduct.size() - 1; i++) {
        if (vproduct[i] > 9) {
            vproduct[i + 1] += vproduct[i] / 10;
            vproduct[i] %= 10;
        }
    }

    //std::string::iterator it = product.number.end() - 1;
    std::vector< int >::iterator it = vproduct.end() - 1;
    while (*it == 0) {
        if (it == vproduct.begin()) {
            product.number.resize(1, '0');
            return product;
        }
        it--;
    }

    vproduct.erase(it + 1, vproduct.end());
    product.number.resize(vproduct.size());
    for (size_t i = 0; i < vproduct.size(); i++) {
        product.number[i] = '0' + vproduct[i];
    }

    return product;
}

//一个 unsigned_large_int 类和一个无符号整数相乘
template< typename Type >
unsigned_large_int unsigned_large_int::operator*(Type other) {
    unsigned_large_int num;
    num.number = "";
    ll other_num = 0; //other对象的位数
    while (other) {
        num.number.push_back((other % 10) + '0');
        other /= 10;
    }

    return *this * num;
}

unsigned_large_int unsigned_large_int::operator -(const unsigned_large_int& other) {
    unsigned_large_int result;
    // 检查被减数是否小于减数
    if (this->compare(other) < 0) {
        std::cerr << "Error: Minuend is less than subtrahend." << std::endl;
        result.number = "0";
        return result;
    }

    result.number = this->number; // 复制当前对象
    int borrow = 0;
    size_t i;

    // 逐位减法
    for (i = 0; i < other.number.size(); ++i) {
        int digit_this = (result.number[i] - '0') - borrow;
        int digit_other = other.number[i] - '0';
        borrow = 0;

        if (digit_this < digit_other) {
            digit_this += 10;
            borrow = 1;
        }
        result.number[i] = '0' + (digit_this - digit_other);
    }

    // 处理剩余借位
    while (borrow && i < result.number.size()) {
        if (result.number[i] > '0') {
            result.number[i]--;
            borrow = 0;
        }
        else {
            result.number[i] = '9';
            ++i;
        }
    }

    // 移除前导零（从末尾开始）
    while (result.number.size() > 1 && result.number.back() == '0') {
        result.number.pop_back();
    }

    return result;
}

// 高精度除以高精度实现
unsigned_large_int unsigned_large_int::operator/(const unsigned_large_int& other) {
    unsigned_large_int quotient;
    // 除零检查
    if (other.number == "0") {
        std::cerr << "Error: Division by zero." << std::endl;
        quotient.number = "0";
        return quotient;
    }

    int cmp = this->compare(other);
    if (cmp < 0) { // 被除数小于除数
        quotient.number = "0";
        return quotient;
    }
    if (cmp == 0) { // 被除数等于除数
        quotient.number = "1";
        return quotient;
    }

    // 转换为正序字符串（高位在前）
    std::string dividend = this->show_to_string();
    unsigned_large_int temp = other;
    std::string divisor_str = temp.show_to_string();
    std::string quotient_str;

    unsigned_large_int current;
    current.number = "0";

    for (size_t i = 0; i < dividend.size(); ++i) {
        // 将当前数字加入current
        if (current.number == "0") {
            current.number[0] = dividend[i];
        }
        else {
            current.number.push_back(dividend[i]);
        }

        // 移除可能的前导零（在正序中）
        size_t start = 0;
        while (start < current.number.size() - 1 && current.number[start] == '0') {
            start++;
        }
        current.number = current.number.substr(start);

        // 试商
        int digit = 0;
        unsigned_large_int temp = other;
        while (current.compare(temp) >= 0) {
            digit++;
            temp = temp + other; // 使用加法模拟乘法
        }

        if (digit > 0) {
            // 更新current
            temp = temp - other; // 回退到最后一次小于等于current的值
            current = current - temp;
        }

        quotient_str.push_back('0' + digit);
    }

    // 移除商的前导零
    size_t start = 0;
    while (start < quotient_str.size() - 1 && quotient_str[start] == '0') {
        start++;
    }
    quotient_str = quotient_str.substr(start);

    // 转换为逆序存储
    std::reverse(quotient_str.begin(), quotient_str.end());
    quotient.number = quotient_str;

    return quotient;
}

// 高精度除以整数模板实现
template<typename Type>
unsigned_large_int unsigned_large_int::operator/(Type other) {
    unsigned_large_int quotient;
    // 除零检查
    if (other == 0) {
        std::cerr << "Error: Division by zero." << std::endl;
        quotient.number = "0";
        return quotient;
    }

    std::string quotient_str;
    Type remainder = 0;
    ll n = number.size();

    // 从最高位（逆序存储的末尾）开始处理
    for (ll i = n - 1; i >= 0; --i) {
        Type current = remainder * 10 + (number[i] - '0');
        Type digit = current / other;
        remainder = current % other;
        quotient_str.push_back('0' + digit);
    }

    // 移除前导零（正序字符串的开头）
    size_t start = 0;
    while (start < quotient_str.size() && quotient_str[start] == '0') {
        start++;
    }

    if (start == quotient_str.size()) {
        quotient.number = "0";
    }
    else {
        quotient_str = quotient_str.substr(start);
        std::reverse(quotient_str.begin(), quotient_str.end());
        quotient.number = quotient_str;
    }

    return quotient;
}