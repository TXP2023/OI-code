//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
//
//      By txp2024 www.luogu.com.cn  TXP2023 www.github.com
// 
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
#pragma once
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <ctype.h>
#include <cstdarg>
#include <climits>
#include <time.h>
#include <iostream>
#include <stdint.h>

#define READ          false
#define MAX_INF       1e18
#define MAX_NUM_SIZE  35
#define MAXN          11
#define MAXK          101
#define MAX_SCHEME    (1 << MAXN)

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

template<typename Type, size_t _MAX_SIZE>
class Vector {
public:

    Vector() {
        size_ = 0;
        return;
    }

    template<typename T>
    inline Type& operator [] (T _Pos) {
        return arr_[_Pos];
    }

    inline void push_back(Type _Value) {
        arr_[size_++] = _Value;
        return;
    }

    inline size_t size() {
        return size_;
    }

    inline Type* begin() {
        return arr_;
    }

    inline Type* end() {
        return &arr_[size_];
    }

private:
    Type arr_[_MAX_SIZE];
    size_t size_;
};

struct Scheme {
    ll s;
    ll cnt;
    Scheme(ll _S, ll _Cnt) {
        s = _S;
        cnt= _Cnt;
        return;
    }

    Scheme() {
        return;
    }
};

Vector<Scheme, (1 << MAXN) + 1> legit_scheme;
uint64_t dp[MAXN][MAXK][MAX_SCHEME]; //第i行，要摆放j个国王，这行摆放的方案为k
ll n, k, ans;

inline uint64_t get_binary_1(uint64_t _Value) {
    ll num = 0;
    while (_Value) {
        num += _Value % 2;
        _Value >>= 1;
    }
    return num;
}

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    //TODO
    readf(&n), readf(&k);

    for (size_t i = 0; i < (1 << n); i++) {
        if (i & (i >> 1)) {
            continue;
        }
        legit_scheme.push_back(Scheme(i, get_binary_1(i)));
    }

    for (auto& scheme : legit_scheme) {
        dp[1][scheme.cnt][scheme.s] = 1;
    }

    for (size_t line = 2; line <= n; ++line) {
        for (auto& scheme : legit_scheme) {
            for (auto& pre_scheme : legit_scheme) {
                if ((pre_scheme.s & scheme.s) || ((pre_scheme.s >> 1) & scheme.s) || ((pre_scheme.s << 1) & scheme.s)) {
                    continue;
                }
                for (size_t king_num = scheme.cnt + pre_scheme.cnt; king_num <= k; ++king_num) {
                    dp[line][king_num][scheme.s] = dp[line][king_num][scheme.s] + dp[line - 1][king_num - scheme.cnt][pre_scheme.s];
                }
            }
        }
    }

    for (auto& scheme : legit_scheme) {
        ans += dp[n][k][scheme.s];
    }

    printf("%lld\n", ans);

#ifdef _RUN_TIME
    printf("The running duration is not less than %ld ms\n", clock() - start);
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