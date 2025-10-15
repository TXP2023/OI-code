//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
//
//      By txp2024 www.luogu.com.cn  TXP2023 www.github.com
// 
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

#pragma once
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <numeric>
#include <ctype.h>
#include <cstdarg>
#include <queue>
#include <climits>
#include <time.h>
#include <iostream>
#include <stdint.h>
#include <vector>

#define _FREAD        true
#define MAX_INF       0x7f7f7f7f7f7f7f7f
#define MAX_NUM_SIZE  35
#define MAXN          505

typedef long long int ll;
typedef unsigned long long int ull;

template<typename _T>
inline _T fpow(_T a, _T n, _T mod) {
    _T base = a, ret = 1;
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
//快读函数声明
template< typename Type >
inline Type fread(Type* p = nullptr);

//快速输出函数
template<typename Type>
inline void fwrite(Type x);

ll dp[MAXN][MAXN], f[MAXN][MAXN];
ll v[MAXN], pos[MAXN], sum[MAXN]; //village
ll n, m;

int main() {

#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    fread(&n), fread(&m);

    for (size_t i = 1; i < n; i++) {
        fread(&v[i]);
        pos[i + 1] = pos[i] + v[i];
        sum[i + 1] = sum[i] + pos[i + 1];
        f[i][i] = 0;
    }
    f[n][n] = 0;

    for (size_t i = 1; i < n; i++) {
        for (size_t j = i + 1; j <= n; j++) {
            ll len = j - i + 1;
            //取中点的位置
            ll k = (i + j) >> 1;
            //len是奇数
            //中点就位于某个村庄上
            //对于位于位置左边的情况
            f[i][j] = pos[k] * (k - i + 1) - sum[k] + sum[i - 1];
            //对于位于位置右边的情况
            f[i][j] += sum[j] - sum[k] - pos[k] * (j - k);
        }
    }

    memset(dp, 0x7f, sizeof dp);
    dp[0][0] = 0;
    std::fill(dp[0] + 1, dp[0] + 1 + m, 0);
    for (size_t i = 1; i <= n; i++) {
        for (size_t j = 1; j <= m; j++) {
            for (size_t k = 0; k < i; k++) {
                dp[i][j] = std::min(dp[k][j - 1] + f[k + 1][i], dp[i][j]);
            }
        }
    }

    printf("%lld\n", dp[n][m]);



#ifdef _RUN_TIME
    printf("The running duration is not less than %ld ms\n", clock() - start);
#endif // _RUN_TIME
    return 0;
}

template< typename Type >
inline Type fread(Type* p) {
#if _FREAD
    Type ret = 0, sgn = 0, ch = getchar();
    while (!isdigit(ch)) {
        sgn |= ch == '-', ch = getchar();
    }
    while (isdigit(ch)) ret = ret * 10 + ch - '0', ch = getchar();
    if (p != nullptr) {
        *p = Type(sgn ? -ret : ret);
    }
    return sgn ? -ret : ret;
#else
    if (p == nullptr) {
        Type temp;
        p = &temp;
    }
    scanf("%lld", p);
    return *p;


#endif // _FREAD
}


template<typename Type>
inline void fwrite(Type x) {
    int sta[MAX_NUM_SIZE];
    int top = 0;
    do {
        sta[top++] = x % 10, x /= 10;
    } while (x);
    while (top) {
        putchar(sta[--top] + '0');
    }  // 48 是 '0'
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