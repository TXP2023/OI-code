#pragma once
#include <string>
#include <iostream>
#include <vector>

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

    //����*
    unsigned_large_int operator *(const unsigned_large_int other);

    //Type ������ (unsigned)short/int/long
    template< typename Type >
    unsigned_large_int operator *(Type other);

private:
    std::string number;

    inline ll length();
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