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
#define MAXP          (size_t)(2e5+10)

typedef long long int ll;
typedef unsigned long long int ull;

//快读函数声明
template< typename Type >
inline Type fread(Type* p = nullptr);

//快速输出函数
template<typename Type>
inline void fwrite(Type x);

std::vector<std::vector<ll>> map, dp;
ll p[MAXP];
ll h, w, ans;

inline bool check(ll x) {
    for (size_t i = 0; i <= h; i++) {
		dp[i][0] = -1e18;
    }
    for (size_t i = 0; i <= w; i++) {
		dp[0][i] = -1e18;
    }
    dp[1][1] = map[1][1] + x - p[1];
    for (size_t i = 1; i <= h; i++) {
        for (size_t j = 1; j <= w; j++) {
            if (i == 1 && j == 1) {
                continue;
            }
            dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]) + map[i][j];
            if (dp[i][j] < p[i + j - 1]) {
                dp[i][j] = -1e18;
            }
            else {
                dp[i][j] -= p[i + j - 1];
            }
        }
    }
	return dp[h][w] >= 0;
}
int main() {

#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

	fread(&h), fread(&w);

	map.resize(h + 1, std::vector<ll>(w + 1, 0));

    for (size_t i = 1; i <= h; i++) {
        for (size_t j = 1; j <= w; j++) {
			fread(&map[i][j]);
        }
    }

    for (size_t i = 1; i <= h + w - 1; i++) {
		fread(&p[i]);
    }

    dp.resize(h + 1, std::vector<ll>(w + 1, 0));

	

    for (ll l = 0, r = 2e14 + 1, mid; l <= r; ) {
		mid = (l + r) >> 1;
        if (check(mid)) {
            ans = mid;
            r = mid - 1;
        }
        else {
            l = mid + 1;
        }
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