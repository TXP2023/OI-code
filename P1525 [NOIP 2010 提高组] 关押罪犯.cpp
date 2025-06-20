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
#include <ctype.h>
#include <numeric>
#include <iterator>
#include <cstdarg>
#include <climits>
#include <time.h>
#include <iostream>
#include <stdint.h>

#define READ          false
#define MAX_INF       1e18
#define MAX_NUM_SIZE  35
#define MAXN          20000
#define MAXM          100000

typedef long long int ll;
typedef unsigned long long int ull;

//快读函数声明
#if READ
template< typename T >
inline T readf();
#else
template< typename Type >
inline Type readf(Type* p = nullptr);
#endif

//快速输出函数
template<typename Type>
inline void writef(Type x);

struct War {
    ll u, v;
    ll w;
};

War wars[MAXM];
ll enemy[MAXN], set[MAXN];
ll n, m;

ll find(ll x) {
    if (set[x] == x) {
        return x;
    }
    else {
        return set[x] = find(set[x]);
    }
}

inline bool same_set(ll x, ll y) {
    return find(x) == find(y);
}

inline void merge(ll x, ll y) {
    set[find(x)] = set[find(y)];
    return;
}

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME
        
    readf(&n), readf(&m);

    for (size_t i = 1; i <= m; i++) {
        ll u, v, w;
        readf(&wars[i].u), readf(&wars[i].v), readf(&wars[i].w);
    }

    std::iota(set + 1, set + 1 + n, 1);

    std::sort(wars + 1, wars + 1 + m, [](const War& a, const War& b) {
        return a.w > b.w;
        }
    );
    
    //贪心的， 我就尽量让2个仇恨大的人位于不同的监狱里头
    for (size_t i = 1; i <= m; i++) {
        ll u = wars[i].u, v = wars[i].v, w = wars[i].w;
        if (same_set(u, v)) {
            printf("%lld\n", w);
            return 0;
        }
        else {
            if (!enemy[u]) {
                enemy[u] = v;
            }
            else {
                merge(enemy[u], v);
            }
            if (!enemy[v]) {
                enemy[v] = u;
            }
            else {
                merge(enemy[v], u);
            }
        }
    }

    puts("0");


#ifdef _RUN_TIME
    printf("The running duration is not less than %ld ms\n", clock() - start);
#endif // _RUN_TIME
    return 0;
}

#if READ
template< typename T >
inline T readf() {
#if false
    T sum = 0;
    char ch = getchar();
    while (ch > '9' || ch < '0') ch = getchar();
    while (ch >= '0' && ch <= '9') sum = sum * 10 + ch - 48, ch = getchar();
    return sum;
#else
    T ret = 0, sgn = 0, ch = getchar();
    while (!isdigit(ch)) {
        sgn |= ch == '-', ch = getchar();
    }
    while (isdigit(ch)) ret = ret * 10 + ch - '0', ch = getchar();
    return sgn ? -ret : ret;
#endif
}
#else
template< typename Type >
inline Type readf(Type* p) {
    Type ret = 0, sgn = 0, ch = getchar();
    while (!isdigit(ch)) {
        sgn |= ch == '-', ch = getchar();
    }
    while (isdigit(ch)) ret = ret * 10 + ch - '0', ch = getchar();
    if (p != NULL) {
        *p = Type(sgn ? -ret : ret);
    }
    return sgn ? -ret : ret;
}
#endif

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
 *      |  |  By txp2024     |  |  |     |         |      |
 *      |  |                 |  |  |     |`---=    |      |
 *      |  |  C:\>_          |  |  |     |==== ooo |      ;
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