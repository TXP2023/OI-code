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

#define _FREAD        true
#define MAX_INF       1e18
#define MAX_NUM_SIZE  35
#define MAXN          105
#define MAXK          10

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

ll barn[MAXN], sum[MAXN];
ll dp[MAXK][MAXN][MAXN];
ll n, m;

inline ll get_sum(ll l, ll r) {
    if (l <= r) {
        return sum[r] - sum[l - 1];
    }
    return sum[n] - sum[l - 1] + sum[r];
}

int main() {

#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    fread(&n), fread(&m);

    for (size_t i = 1; i <= n; i++) {
        fread(&barn[i]);
        sum[i] = sum[i - 1] + barn[i];
    }

    for (size_t i = 1; i <= n; i++) {
        for (size_t j = 1; j <= n; j++) {
            if (i == j) {
                continue;
            }
            ll cnt = 0, k = i;
            do {
                ++k, ++cnt;
                if (k > n) {
                    k -= n;
                }
                dp[1][i][j] += cnt * barn[k];
            } while (k != j);
        }
    }

    for (size_t i = 2; i <= m; i++) {
        for (size_t len = i; len <= n; len++) {
            for (size_t l = 1; l <= n; l++) {
                ll r = l + len - 1;
                if (r > n) {
                    r -= n;
                }
                dp[i][l][r] = MAX_INF;
                if (l == r) {
                    continue;
                }
                ll k = l + i - 2;
                do {
                    ++k;
                    if (k > n) {
                        k -= n;
                    }
                    //dp[1][i][j] += cnt * barn[k];
                    ll temp = k - 1;
                    if (temp == 0) {
                        temp = n;
                    }
                    dp[i][l][r] = std::min(dp[i - 1][l][temp] + dp[1][k][r], dp[i][l][r]);
                } while (k != r);
            }
        }
    }

    ll ans = MAX_INF;
    for (size_t i = 1; i <= n; i++) {
        ll j = i + n - 1;
        if (j > n) {
            j -= n;
        }
        ans = std::min(dp[m][i][j], ans);
    }

    printf("%lld\n", ans);

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