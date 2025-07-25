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
#define MAXN          (size_t)(5e4+5)
#define MAXQ          (size_t)(5e4+5)

typedef long long int ll;
typedef unsigned long long int ull;

//快读函数声明
template< typename Type >
inline Type readf(Type* p = nullptr);

//快速输出函数
template<typename Type>
inline void writef(Type x);

struct Task {
    ll l, r; //求get(1,l,x)*get(1, r,x)
    ll id, type; //是+(1)还是-(-1)
    Task() : l(0), r(0), id(0), type(0){}

    Task(ll _L, ll _R, ll _Id, ll _Type) {
        l = std::min(_L, _R);
        r = std::max(_L, _R);
        id = _Id;
        type = _Type;
        return;
    }
};

Task tasks[MAXQ * 4];
ll arr[MAXN], res[MAXQ], cntL[MAXN], cntR[MAXN];
ll n, q, block_size, cnt, sum;

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    readf(&n);

    block_size = std::sqrt(n);
    for (size_t i = 1; i <= n; i++) {
        readf(&arr[i]);
    }

    readf(&q);

    for (size_t i = 1; i <= q; i++) {
        ll L1, R1, L2, R2;
        readf(&L1), readf(&R1), readf(&L2), readf(&R2);
        //Get(x) = get(1, x)
        //Sigma(get(L1, R1)*get(L2, R2))
        // =Get(R1)*Get(R2) - Get(R1)*Get(L2-1) - Get(L1-1)*Get(R2) + Get(L1 - 1)*Get(L2 - 1)
        //下面强拆至4个子问题
        tasks[++cnt] = Task(R1, R2, i, 1);
        tasks[++cnt] = Task(R1, L2 - 1, i, -1);
        tasks[++cnt] = Task(L1 - 1, R2, i, -1);
        tasks[++cnt] = Task(L1 - 1, L2 - 1, i, 1);
    }

    std::sort(tasks + 1, tasks + 1 + 4 * q, [](const Task& a, const Task& b) {
        if ((a.l + 1)/block_size != (b.l + 1) / block_size) {
            return (a.l + 1) / block_size < (b.l + 1) / block_size;
        }
        if (((a.l + 1) / block_size) & 1) {
            return a.r < b.r;
        }
        else {
            return a.r > b.r;
        }
    });

    //如果cntL+1, 那么相当于加上cntR
    //反之

    for (ll i = 1, l = 0, r = -1; i <= cnt; i++) {
        ll rangeL = tasks[i].l, rangeR = tasks[i].r, id = tasks[i].id, type = tasks[i].type;
        while (l < rangeL) {
            ++l;
            sum += cntR[arr[l]];
            ++cntL[arr[l]];
        }
        while (l > rangeL) {
            --cntL[arr[l]];
            sum -= cntR[arr[l]];
            --l;
        }
        while (r > rangeR) {
            --cntR[arr[r]];
            sum -= cntL[arr[r]];
            --r;
        }
        while (r < rangeR) {
            ++r;
            ++cntR[arr[r]];
            sum += cntL[arr[r]];
        }
        res[id] += type * sum;
    }

    for (size_t i = 1; i <= q; i++) {
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