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
#define MAXN          (size_t)(6e5+5)
#define MOD           (size_t)(1e9+7)

typedef long long int ll;
typedef unsigned long long int ull;

//快读函数声明
template< typename Type >
inline Type readf(Type* p = nullptr);

//快速输出函数
template<typename Type>
inline void writef(Type x);

ll arrA[MAXN], preSumA[MAXN];
ll arrB[MAXN], preSumB[MAXN];
ll res[MAXN];
ull n, sum;

int main() {

#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    readf(&n);

    for (size_t i = 1; i <= n; i++) {
        readf(&arrA[i]);
        preSumA[i] = preSumA[i - 1] + arrA[i] + MOD;
        preSumA[i] %= MOD;
    }

    for (size_t i = 1; i <= n; i++) {
        readf(&arrB[i]);
        preSumB[i] = preSumB[i - 1] + arrB[i] + MOD;
        preSumB[i] %= MOD;
    }

    for (size_t r = 1, sumAl = 0, sumBl = 0, mul = 0; r <= n; r++) {
        res[r] = ((((r * preSumA[r])%MOD) * preSumB[r]) % MOD) - ((preSumB[r] * sumAl) % MOD) - ((preSumA[r] * sumBl) % MOD) + mul;
        while (res[r] < 0) {
            res[r] += MOD;
        }
        res[r] %= MOD;
        mul += preSumA[r] * preSumB[r] + MOD + MOD;
        mul %= MOD;
        sumAl += preSumA[r] + MOD + MOD;
        sumAl %= MOD;
        sumBl += preSumB[r] + MOD + MOD;
        sumBl %= MOD;
    }

    for (size_t i = 1; i <= n; i++) {
        sum += (res[i] % MOD + MOD) % MOD;
    }

    printf("%lld\n", sum % MOD);



#ifdef _RUN_TIME
    printf("The running duration is not less than %ld ms\n", clock() - start);
#endif // _RUN_TIME
    return 0;
}

template< typename Type >
inline Type readf(Type* p) {
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