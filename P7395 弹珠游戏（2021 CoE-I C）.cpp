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

typedef long long int ll;
typedef unsigned long long int ull;

//快读函数声明
template< typename Type >
inline Type fread(Type* p = nullptr);

//快速输出函数
template<typename Type>
inline void fwrite(Type x);

ll dp[1 << 16];
ll  offset[4][2] = { {0, 1}, {1, 0}, {1, 1}, {1, -1} }, t;
ll matrix[16] = { 0, 4, 1, 8, 5, 2, 12, 9, 6, 3, 13, 10, 7, 14, 11, 15 };

inline ll dfs(ll x) {
    if (~dp[x]) {
        return dp[x];
    }
    for (size_t i = 0; i < 16; i++) {
        if (x & (1 << i)) {
            continue;
        }
        ll r = i / 4, c = i % 4;
        for (size_t j = 0; j < 4; j++) {
            ll bit = 0;
            for (size_t k = 0; k < 3; k++) {
                ll rr = r + offset[j][0] * k, cc = c + offset[j][1] * k;
                if (rr < 0 || rr > 3 || cc < 0 || cc > 3) {
                    break;
                }
                if (x & (1 << (rr * 4 + cc))) {
                    break;
                }
                bit |= (1 << (rr * 4 + cc));
                if (!dfs(x ^ bit)) {
                    return dp[x] = 1;
                }
            }
        }
    }
    return dp[x] = 0;
}

int main() {

#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME


    memset(dp, -1, sizeof(dp));
    dp[(1 << 16) - 1] = 0;

    fread(&t);
    for (int cs = 1; cs <= t; cs++) {
        ll mask = 0, cnt = 0;
        char ch;
        while (cnt < 16) {
            std::cin >> ch;
            if (ch == '*' || ch == '.') {
                if (ch == '*')
                    mask |= (1 << matrix[cnt]);
                cnt++;
            }
        }
        printf(dfs(mask) ? "Possible.\n" : "Impossible.\n");
    }




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