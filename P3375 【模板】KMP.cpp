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
#include <ctype.h>
#include <string>
#include <cstdarg>
#include <climits>
#include <time.h>
#include <iostream>
#include <stdint.h>

#define READ          false
#define MAX_INF       1e18
#define MAX_NUM_SIZE  35
#define MAX_S1        (uint64_t)(1e6+5)
#define MAX_S2        (uint64_t)(1e6 + 5)

typedef long long int ll;
typedef unsigned long long int unill;

//快读函数声明
#if READ
template< typename T >
inline T readf();
#else
template< typename Type >
inline Type readf(Type* p = nullptr);
#endif

//快速输出函数
template<typename Type>
inline void writef(Type x);

std::string s1, s2;
uint64_t next[MAX_S1];
std::vector<size_t> ans;

inline void get_next(uint64_t* _Arr, std::string _Str) {
    _Arr[1] = 0;
    for (size_t i = 1, length = 0; i < _Str.length(); ++i) {
        while (length && _Str[i] != _Str[length]) {
            length = _Arr[length];
        }
        if (_Str[i] == _Str[length]) {
            _Arr[i + 1] = ++length;
        }
    }
    return;
}

inline std::vector<size_t> kmp(const uint64_t* _Next, std::string _Str1, std::string _Str2) {
    std::vector<size_t> ret;
    for (size_t s1Index = 0, s2Index = 0; s1Index < _Str1.length(); s1Index++) {
        while (s2Index && _Str1[s1Index] != _Str2[s2Index]) {
            s2Index = _Next[s2Index];
        }
        if (_Str1[s1Index] == _Str2[s2Index]) {
            ++s2Index;
        }
        if (s2Index == _Str2.length()) {
            ret.push_back(s1Index - s2Index + 2);
            s2Index = _Next[s2Index];
        }
    }
    return ret;
}

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    //TODO
    std::cin >> s1 >> s2;

    get_next(next, s2);
    ans = kmp(next, s1, s2);

    for (size_t i : ans) {
        printf("%llu\n", i);
    }

    for (size_t i = 1; i <= s2.length(); i++) {
        printf("%lld ", next[i]);
    }

#ifdef _RUN_TIME
    printf("\nThe running duration is not less than %ld ms\n", clock() - start);
#endif // _RUN_TIME
    return 0;
}

#if READ
template< typename T >
inline T readf() {
#if false
    T sum = 0;
    char ch = getchar();
    while (ch > '9' || ch < '0') ch = getchar();
    while (ch >= '0' && ch <= '9') sum = sum * 10 + ch - 48, ch = getchar();
    return sum;
#else
    T ret = 0, sgn = 0, ch = getchar();
    while (!isdigit(ch)) {
        sgn |= ch == '-', ch = getchar();
    }
    while (isdigit(ch)) ret = ret * 10 + ch - '0', ch = getchar();
    return sgn ? -ret : ret;
#endif
}
#else
template< typename Type >
inline Type readf(Type* p) {
    Type ret = 0, sgn = 0, ch = getchar();
    while (!isdigit(ch)) {
        sgn |= ch == '-', ch = getchar();
    }
    while (isdigit(ch)) ret = ret * 10 + ch - '0', ch = getchar();
    if (p != NULL) {
        *p = Type(sgn ? -ret : ret);
    }
    return sgn ? -ret : ret;
}
#endif

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
 *      |  |  By txp2024     |  |  |     |         |      |
 *      |  |                 |  |  |     |`---=    |      |
 *      |  |  C:\>_          |  |  |     |==== ooo |      ;
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