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
#define MAXN          (int64_t)(15)
#define MODE          (int64_t)(1e8)

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

template<typename Type, size_t _max_size>
class Vector {
public:
    template<typename T>
    inline Type & operator [] (T _Index) {
        return _que[_Index];
    }
    
    inline void push_back(Type val) {
        _que[cnt++] = val;
    }

    ll size = 0;

private:
    Type _que[_max_size];
};

Vector<ll, 1 << MAXN>  legit_scheme;
ll farm[MAXN];
ll dp[MAXN + 2][1 << MAXN]; //dp[i][j]为dp的第i行排列为j时的方案数
ll n, m, ans = 0;

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    //TODO
    readf(&n), readf(&m);

    for (size_t i = 1; i <= n; i++) {
        for (size_t j = 0; j < m; j++) {
            ll value = readf<ll>();
            if (value) {
                farm[i] |= (value << j);
            }
        }
    }

    for (size_t i = 0; i < (1 << MAXN); i++) {
        if (i & (i >> 1) ) {
            continue;
        }
        legit_scheme.push_back(i);
    }

    for (size_t i = 0; i < legit_scheme.size; i++) {
        //legit_scheme[i] 为 farm[1] 的子集
        if ((legit_scheme[i] & farm[1]) == farm[1]) {
            dp[1][legit_scheme[i]] = 1;
        }
    }

    for (size_t i = 2; i <= n; i++) {
        for (size_t j = 0; j < legit_scheme.size; j++) {
            ll scheme = legit_scheme[j];
            //当前考虑的方案 scheme 不为当前所考虑的行 farm[i] 的子集 
            if (!(scheme & farm[i])) {
                continue;
            }
            //考虑上一行的状态
            for (size_t k = 0; k < legit_scheme.size; k++) {
                ll pre_scheme = legit_scheme[i];
                if (!dp[i - 1][pre_scheme] && (scheme & pre_scheme)) {
                    continue;
                }
                dp[i][scheme] = (dp[i - 1][pre_scheme] + dp[i][scheme]) % MODE;
            }
        }
    }

    for (size_t i = 0; i <= legit_scheme.size; i++) {
        ans = (ans + dp[n][legit_scheme[i]]) % MODE;
    }

    writef(ans);

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