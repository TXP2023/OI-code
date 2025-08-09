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
#include <math.h>
#include <cmath>
#include <stdint.h>
#include <bitset>

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

ull n, x, ans = MAX_INF;
clock_t start;

inline ull get_len(ull x) {
    ll res = 0;
    while (x) {
        ++res;
        x /= 10;
    }
    return res;
}

inline void dfs(short cnt, ull val) {
    if ((clock() - start) / CLOCKS_PER_SEC >= 0.99) {
        printf("%lld\n", ans);
        exit(0);
    }
    //memset(flag, 0, sizeof(flag));
    if (cnt >= ans) {
        return;
    }
    if (val >= n) {
        ans = cnt;
        return;
    }
    std::bitset<10> flag;
    ull temp = val, len = 0;
    while (temp) {
        ++len;
        flag[temp - (temp / 10) * 10] = 1;
        temp /= 10;
    }

    for (size_t i = 9; i >= 2; i--) {
        if (!flag[i]) {
            continue;
        }
        dfs(cnt + 1, val * i);
    }
    return;
}

inline void _debug_dfs(ull cnt, ull val, std::vector<ll> v) {
    std::bitset<10> flag;
    //memset(flag, 0, sizeof(flag));
    if (cnt >= ans) {
        //return;
    }
    ull temp = val, len = 0;
    if (val >= n) {
        ans = cnt;
        printf("[info] cost: %lld\n", cnt);
        for (auto& i : v) {
            printf("%lld ", i);
        }
        puts("");
        return;
    }
    while (temp) {
        ++len;
        flag[temp - (temp / 10) * 10] = 1;
        temp /= 10;
    }

    for (size_t i = 9; i >= 2; i--) {
        if (!flag[i]) {
            continue;
        }
        v.push_back(i);
        _debug_dfs(cnt + 1, val * i, v);
    }
    return;
}

int main() {
    start = clock();
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

    fread(&n), fread(&x);

    if (x == 1 || x == 0 || (get_len(x) > n)) {
        puts("-1");
        return 0;
    }
    n = std::pow(10, n - 1);

    //下面进入搜索
    dfs(0, x);

    printf("%lld\n", ans == MAX_INF ? -1 : ans);

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