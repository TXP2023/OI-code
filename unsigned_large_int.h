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

    //��������ز���
    //���� =
    //����һ�� unsigned_large_int ����
    void operator =(const unsigned_large_int other);
    //����һ���޷����������� 
    //Type ������ (unsigned)short/int/long
    template< typename Type >
    void operator =(Type other);

    //����+
    unsigned_large_int operator +(const unsigned_large_int other);

    unsigned_large_int operator -(const unsigned_large_int& other);

    unsigned_large_int operator /(const unsigned_large_int& other);

    template<typename Type>
    unsigned_large_int operator /(Type other);

    //����*
    unsigned_large_int operator *(const unsigned_large_int other);

    //Type ������ (unsigned)short/int/long
    template< typename Type >
    unsigned_large_int operator *(Type other);

private:
    std::string number;

    inline ll length();

    // ˽�и����������Ƚ��������Ĵ�С
   // ����: 1 (this > other), 0 (���), -1 (this < other)
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

//����һ���߾�����
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

//�������߾�����Ƚϣ� ���ؽϴ���Ǹ�
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

//����߾����������������ת��Ϊ�ַ�����ʽ
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
    ll other_num = 0; //other�����λ��
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

    //�Ӻ�
    for (size_t i = 0; i < num2.length(); i++) {
        summation.number[i] += num2.number[i] - '0';
    }

    //��λ
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

//һ�� unsigned_large_int ���һ�� unsigned_large_int �����
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

//һ�� unsigned_large_int ���һ���޷����������
template< typename Type >
unsigned_large_int unsigned_large_int::operator*(Type other) {
    unsigned_large_int num;
    num.number = "";
    ll other_num = 0; //other�����λ��
    while (other) {
        num.number.push_back((other % 10) + '0');
        other /= 10;
    }

    return *this * num;
}

unsigned_large_int unsigned_large_int::operator -(const unsigned_large_int& other) {
    unsigned_large_int result;
    // ��鱻�����Ƿ�С�ڼ���
    if (this->compare(other) < 0) {
        std::cerr << "Error: Minuend is less than subtrahend." << std::endl;
        result.number = "0";
        return result;
    }

    result.number = this->number; // ���Ƶ�ǰ����
    int borrow = 0;
    size_t i;

    // ��λ����
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

    // ����ʣ���λ
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

    // �Ƴ�ǰ���㣨��ĩβ��ʼ��
    while (result.number.size() > 1 && result.number.back() == '0') {
        result.number.pop_back();
    }

    return result;
}

// �߾��ȳ��Ը߾���ʵ��
unsigned_large_int unsigned_large_int::operator/(const unsigned_large_int& other) {
    unsigned_large_int quotient;
    // ������
    if (other.number == "0") {
        std::cerr << "Error: Division by zero." << std::endl;
        quotient.number = "0";
        return quotient;
    }

    int cmp = this->compare(other);
    if (cmp < 0) { // ������С�ڳ���
        quotient.number = "0";
        return quotient;
    }
    if (cmp == 0) { // ���������ڳ���
        quotient.number = "1";
        return quotient;
    }

    // ת��Ϊ�����ַ�������λ��ǰ��
    std::string dividend = this->show_to_string();
    unsigned_large_int temp = other;
    std::string divisor_str = temp.show_to_string();
    std::string quotient_str;

    unsigned_large_int current;
    current.number = "0";

    for (size_t i = 0; i < dividend.size(); ++i) {
        // ����ǰ���ּ���current
        if (current.number == "0") {
            current.number[0] = dividend[i];
        }
        else {
            current.number.push_back(dividend[i]);
        }

        // �Ƴ����ܵ�ǰ���㣨�������У�
        size_t start = 0;
        while (start < current.number.size() - 1 && current.number[start] == '0') {
            start++;
        }
        current.number = current.number.substr(start);

        // ����
        int digit = 0;
        unsigned_large_int temp = other;
        while (current.compare(temp) >= 0) {
            digit++;
            temp = temp + other; // ʹ�üӷ�ģ��˷�
        }

        if (digit > 0) {
            // ����current
            temp = temp - other; // ���˵����һ��С�ڵ���current��ֵ
            current = current - temp;
        }

        quotient_str.push_back('0' + digit);
    }

    // �Ƴ��̵�ǰ����
    size_t start = 0;
    while (start < quotient_str.size() - 1 && quotient_str[start] == '0') {
        start++;
    }
    quotient_str = quotient_str.substr(start);

    // ת��Ϊ����洢
    std::reverse(quotient_str.begin(), quotient_str.end());
    quotient.number = quotient_str;

    return quotient;
}

// �߾��ȳ�������ģ��ʵ��
template<typename Type>
unsigned_large_int unsigned_large_int::operator/(Type other) {
    unsigned_large_int quotient;
    // ������
    if (other == 0) {
        std::cerr << "Error: Division by zero." << std::endl;
        quotient.number = "0";
        return quotient;
    }

    std::string quotient_str;
    Type remainder = 0;
    ll n = number.size();

    // �����λ������洢��ĩβ����ʼ����
    for (ll i = n - 1; i >= 0; --i) {
        Type current = remainder * 10 + (number[i] - '0');
        Type digit = current / other;
        remainder = current % other;
        quotient_str.push_back('0' + digit);
    }

    // �Ƴ�ǰ���㣨�����ַ����Ŀ�ͷ��
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