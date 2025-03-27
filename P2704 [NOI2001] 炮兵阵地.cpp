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
#define MAXM          11
#define MAXN          101
#define SCHEME_NUM    ((1 << MAXM)+1)

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

Vector<uint64_t, SCHEME_NUM> legit_scheme;
uint32_t dp[2][SCHEME_NUM][SCHEME_NUM]; //Dp[i][j][k]为第i行的方案为j,上一行的方案为k
ll map[MAXN];
ll n, m, ans = LLONG_MIN;

inline uint32_t get_binary_1(uint64_t _Value) {
    ll cnt = 0;
    while (_Value) {
        if (_Value % 2) {
            ++cnt;
        }
        _Value >>= 1;
    }
    return cnt;
}

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    //TODO
    readf(&n), readf(&m);

    for (size_t i = 1; i <= n; ++i) {
        scanf("\n");
        for (size_t j = 1; j <= m; ++j) {
            if (getchar() == 'P') {
                ll val = (1 << (m - j));
                map[i] |= val;
                //map[i] |= (1 << (m - j));
            }
        }
    }

    for (size_t i = 0; i <= (1 << m); ++i) {
        if ((i & (i >> 1)) || (i & (i >> 2))) {
            continue;
        }
        legit_scheme.push_back(i);
    }

    for (uint64_t scheme : legit_scheme) {
        if ((scheme & map[1]) == scheme) {
            std::fill(dp[1][scheme], dp[1][scheme] + (1 << m), get_binary_1(scheme));
        }
    }

    for (size_t line = 2; line <= n; ++line) {
        size_t pos = line % 2;
        for (uint64_t scheme : legit_scheme) {
            if ((scheme & map[line]) != scheme) {
                continue;
            }
            for (uint64_t pre_scheme : legit_scheme) {
                if (scheme & pre_scheme) {
                    continue;
                }
                for (uint64_t pre_pre_scheme : legit_scheme) {
                    if (scheme & pre_pre_scheme) {
                        continue;
                    }
                    dp[pos][scheme][pre_scheme] = std::max(
                        dp[pos][scheme][pre_scheme],
                        dp[pos ^ 1][pre_scheme][pre_pre_scheme] + get_binary_1(scheme)
                    );
                    std::cout << "";
                }
            }
        }
    }

    for (uint64_t scheme : legit_scheme) {
        if ((scheme & map[n]) == scheme) {
            for (uint64_t pre_scheme : legit_scheme) {
                ans = std::max(ans, ll(dp[n % 2][scheme][pre_scheme]));
            }
        }
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