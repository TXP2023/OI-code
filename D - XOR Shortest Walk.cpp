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
#include <cstdarg>
#include <climits>
#include <time.h>
#include <iostream>
#include <stdint.h>
#include <queue>

#define READ           false
#define MAX_INF        1e18
#define MAX_NUM_SIZE   35
#define MAXN           1005

#define GET_BINARE_BIT(x, index) (((x)>>(index - 1)) & 1)

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

struct Edge {
    size_t v, next;
    ll w;
};

Edge edges[MAXN];
ll head[MAXN], astrict[MAXN], dist[MAXN];
ll n, m, edge_cnt = 0, ans;

inline void add_edge(size_t u, size_t v, ll w) {
    ++edge_cnt;
    edges[edge_cnt].v = v;
    edges[edge_cnt].w = w;
    edges[edge_cnt].next = head[u];
    head[u] = edge_cnt;
    return;
}

inline void spfa(ll index) {
    std::queue<size_t> que;
    que.push(1);
    bool flag[MAXN][2]; //到达点u的第index位是否可以是1 or 0
    flag[1][0] = true;
    while (!que.empty()) {
        ll u = que.front();
        for (size_t i = head[u]; i; i = edges[i].next) {
            ll v = edges[i].v, w = edges[i].w;
            //if ((dist[u] >> (index - 1)) ^ (w >> (index - 1)) > astrict[v] >> (index - 1)) {
            //    continue; //超出已有限制
            //}
            if (GET_BINARE_BIT(dist[u], index) ^ GET_BINARE_BIT(w, index) > GET_BINARE_BIT(astrict[v], index)) {
                continue; //超出已有限制
            }
            bool tag = false;
            if (!flag[v][0] && (!GET_BINARE_BIT(w, index) ^ flag[u][0])) {
                flag[v][0] = true;
                tag = true;
            }
            if (!flag[v][1] && ((!(GET_BINARE_BIT(w, index)) && flag[u][1]) || (GET_BINARE_BIT(w, index) && flag[u][0]))) {
                flag[v][1] = true;
            }
        }
    }
    for (size_t i = 1; i <= n; i++) {
        astrict[i] |= 1 << (index - 1);
    }
    if (!flag[n][0]) {
        ans += 1 << (index - 1);
    }
}

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    readf(&n), readf(&m);

    for (size_t i = 0; i < m; i++) {
        ll u, v, w;
        readf(&u), readf(&v), readf(&w);
        add_edge(u, v, w);
    }

    for (size_t i = 10; i >= 1; i--) {
        spfa(i);
    }

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