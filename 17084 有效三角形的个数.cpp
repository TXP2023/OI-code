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
#define MAXN          1005

typedef long long int ll;
typedef unsigned long long int ull;

//快读函数声明
template< typename Type >
inline Type readf(Type* p = nullptr);

//快速输出函数
template<typename Type>
inline void writef(Type x);

void read(ll& x) {
    bool neg = false;
    x = 0;
    char ch = 0;
    while (ch < '0' || ch > '9') {
        if (ch == '-') neg = true;
        ch = getchar();
    }
    if (neg) {
        while (ch >= '0' && ch <= '9') {
            x = x * 10 + ('0' - ch);
            ch = getchar();
        }
    }
    else {
        while (ch >= '0' && ch <= '9') {
            x = x * 10 + (ch - '0');
            ch = getchar();
        }
    }
}


ll edges[MAXN]; //离散化去重数组
ll n, ans;

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME


    std::cin >> n;

    for (size_t i = 1; i <= n; i++) {
        //readf(&edges[i]);
        //std::cin >> edges[i];
        //edges[i] = readf<ll>();
        read(edges[i]);
    }

    std::sort(edges + 1, edges + 1 + n);

    for (size_t i = 1; i <= n; i++) {
        for (size_t j = i + 1; j <= n; j++) {
            for (size_t k = j + 1; k <= n; k++) {
                if (edges[i] + edges[j] > edges[k]) {
                    ++ans;
                }
                else {
                    break;
                }
            }
        }
    }

	printf("%lld\n", ans);

#ifdef _RUN_TIME
    printf("The running duration is not less than %ld ms\n", clock() - start);
#endif // _RUN_TIME
    return 0;
}


template< typename Type >
inline Type readf(Type* p) {
#if true
    bool neg = false;
    Type x = 0;
    char ch = 0;
    while (ch < '0' || ch > '9') {
        if (ch == '-') neg = true;
        ch = getchar();
    }
    if (neg) {
        while (ch >= '0' && ch <= '9') {
            x = x * 10 + ('0' - ch);
            ch = getchar();
        }
    }
    else {
        while (ch >= '0' && ch <= '9') {
            x = x * 10 + (ch - '0');
            ch = getchar();
        }
    }
    if (p != nullptr) {
        *p = x;
    }
    return x;
#else

    Type ret = 0, sgn = 0, ch = getchar();
    while (!isdigit(ch)) {
        sgn |= ch == '-', ch = getchar();
    }
    while (isdigit(ch)) ret = ret * 10 + ch - '0', ch = getchar();
    if (p != nullptr) {
        *p = Type(sgn ? -ret : ret);
    }
    return sgn ? -ret : ret;
#endif // READ
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