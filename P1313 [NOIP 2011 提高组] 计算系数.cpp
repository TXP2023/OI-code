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
#define MAXK          1005
#define MOD           10007

typedef long long int ll;
typedef unsigned long long int ull;

//快读函数声明
template< typename Type >
inline Type readf(Type* p = nullptr);

//快速输出函数
template<typename Type>
inline void writef(Type x);

ll c[MAXK][MAXK]; //c[n][m]在n中选m
ll a, b, k, n, m;
ll ans = 1;

inline int64_t fpow(int64_t a, int64_t n, int64_t mod = MOD) {
    int64_t base = a, ret = 1;
    while (n) {
        if (n & 1) {
            ret = ret * base;
            ret %= mod;
        }
        base = base * base;
        base %= mod;
        n >>= 1;
    }
    return ret % mod;
}

ll get_combinations(ll _n, ll _m) {
    if (!_m) {
        //子集大小为m=0时, 子集只能是空的1种情况
        return c[_n][_m] = 1;
    }
    if (_m == 1) {
        //子集大小为m=1时，n个元素中每个各有1中可能
        return c[_n][_m] = _n;
    }
    if (c[_n][_m]) {
        return c[_n][_m];
    }
    //利用 帕斯卡/杨辉三角公式 计算
    if (_n - _m < _m) {
        _m = _n - _m;
    }
    return c[_n][_m] = (get_combinations(_n - 1, _m) + get_combinations(_n - 1, _m - 1)) % MOD;
}

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    scanf("%lld%lld%lld%lld%lld", &a, &b, &k, &n, &m);

    c[1][0] = 1, c[1][1] = 1;

    a %= MOD, b %= MOD;

    ans *= (fpow(a, n) * fpow(b, m)) % MOD;

    if (n > m) {
        n = m;
    }

    ans *= get_combinations(k, n) % MOD;
    ans %= MOD;

    printf("%lld\n", ans);



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