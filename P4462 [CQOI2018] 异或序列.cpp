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
#include <cmath>
#include <stdint.h>

#define _FREAD        true
#define MAX_INF       1e18
#define MAX_NUM_SIZE  35
#define MAXN          (size_t)(1e5+5)
#define MAX_VAL       (size_t)(1e5+5)

typedef long long int ll;
typedef unsigned long long int ull;

//快读函数声明
template< typename Type >
inline Type readf(Type* p = nullptr);

//快速输出函数
template<typename Type>
inline void writef(Type x);

struct Task {
    ll l, r, id;
};

ll arr[MAXN], preSum[MAXN], cnt[MAX_VAL];
Task tasks[MAXN];
ll res[MAXN];
ll n, m, k, blocks_size, ans;


int main() {

#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    readf(&n), readf(&m), readf(&k);

    blocks_size = std::sqrt(n);
    for (size_t i = 1; i <= n; i++) {
        readf(&arr[i]);
        preSum[i] = preSum[i - 1] ^ arr[i];
    }

    for (size_t i = 1; i <= m; i++) {
        readf(&tasks[i].l), readf(&tasks[i].r);
        tasks[i].id = i;
    }

    std::sort(tasks + 1, tasks + 1 + m, [](const Task& a, const Task& b) {
        if ((a.l + 1) / blocks_size != (b.l + 1) / blocks_size) {
            return (a.l + 1) / blocks_size < (b.l + 1) / blocks_size;
        }
        if ((b.l + 1) / blocks_size & 1) {
            return a.r < b.r;
        }
        return a.r > b.r;
    });

    //cnt[0] = 1;
    for (size_t i = 1, l = 1, r = 0; i <= m; i++) {
        ll rangeL = tasks[i].l - 1, rangeR = tasks[i].r, id = tasks[i].id;
        while (l < rangeL) {
            --cnt[preSum[l]];
            ans -= cnt[preSum[l] ^ k];
            ++l;
        }
        while (l > rangeL) {
            --l;
            ans += cnt[preSum[l] ^ k];
            ++cnt[preSum[l]];
        }
        while (r < rangeR) {
            ++r;
            ans += cnt[preSum[r] ^ k];
            ++cnt[preSum[r]];
        }
        while (r > rangeR) {
            --cnt[preSum[r]];
            ans -= cnt[preSum[r] ^ k];
            --r;
        }
        res[id] = ans;
    }

    for (size_t i = 1; i <= m; i++) {
        printf("%lld\n", res[i]);
    }


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