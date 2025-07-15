//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
//
//      By txp2024 www.luogu.com.cn  TXP2023 www.github.com
// 
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

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

#define MAX_INF       1e18
#define MAX_NUM_SIZE  35
#define MAXN          51

typedef long long int ll;
typedef unsigned long long int ull;

//快读函数声明
template< typename Type >
inline Type readf(Type* p = nullptr);

//快速输出函数
template<typename Type>
inline void writef(Type x);

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

    //重载*
    unsigned_large_int operator *(const unsigned_large_int other);

    //Type 可以是 (unsigned)short/int/long
    template< typename Type >
    unsigned_large_int operator *(Type other);

private:
    std::string number;

    inline ll length();
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

unsigned_large_int mul[MAXN], ans;
ll n;

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    readf(&n);

    ans = 0;
    mul[1] = 1;
    for (size_t i = 2; i <= n; i++) {
        mul[i] = mul[i - 1] * i;
    }

    for (size_t i = 1; i <= n; i++) {
        ans = ans + mul[i];
    }

    std::cout << ans.show_to_string() << '\n';

#ifdef _RUN_TIME
    printf("The running duration is not less than %ld ms\n", clock() - start);
#endif // _RUN_TIME
    return 0;
}

template< typename Type >
inline Type readf(Type* p) {
    Type ret = 0, sgn = 0, ch = getchar();
    while (!isdigit(ch)) {
        sgn |= ch == '-', ch = getchar();
    }
    while (isdigit(ch)) ret = ret * 10 + ch - '0', ch = getchar();
    if (p != nullptr) {
        *p = Type(sgn ? -ret : ret);
    }
    return sgn ? -ret : ret;
}


template<typename Type>
inline void writef(Type x) {
    int sta[MAX_NUM_SIZE];
    int top = 0;
    do {
        sta[top++] = x % 10, x /= 10;
    } while (x);
    while (top) putchar(sta[--top] + '0');  // 48 是 '0'
    return;
}



/**
 *              ,----------------,              ,---------,
 *         ,-----------------------,          ,"        ,"|
 *       ,"                      ,"|        ,"        ,"  |
 *      +-----------------------+  |      ,"        ,"    |
 *      |  .-----------------.  |  |     +---------+      |
 *      |  |                 |  |  |     | -==----'|      |
 *      |  |                 |  |  |     |         |      |
 *      |  |  C:\>rp++       |  |  |     |`---=    |      |
 *      |  |                 |  |  |     |==== ooo |      ;
 *      |  |                 |  |  |     |(((( [33]|    ,"
 *      |  `-----------------'  | /      |((((     |  ,"
 *      +-----------------------+/       |         |,"
 *         /_)______________(_/          +---------+
 *    _______________________________
 *   /  oooooooooooooooo  .o.  oooo /,   /-----------
 *  / ==ooooooooooooooo==.o.  ooo= //   /\--{)B     ,"
 * /_==__==========__==_ooo__ooo=_/'   /___________,"
 *
 */