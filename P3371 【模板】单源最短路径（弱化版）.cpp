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
#include <queue>
#include <stdint.h>

#define READ          false
#define MAX_INF       1e18
#define MAX_NUM_SIZE  35
#define MAXN          (size_t)(1e4+5)
#define MAXM          (size_t)(5e5+5)

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
    ll v, w;
    size_t next;

    inline bool operator <(const Edge &other)const {
        return w > other.w;
    }

    Edge() {
        return;
    }

    Edge(ll v, ll w) {
        this->v = v;
        this->w = w;
        return;
    }
    
};

Edge edges[MAXM];
size_t head[MAXN];
ll dist[MAXN];
ll n, m, s, edges_cnt = 0;

//添加一条有向边
inline void add_edge(ll u, ll v, ll w) {
    ++edges_cnt;
    edges[edges_cnt].v = v;
    edges[edges_cnt].w = w;
    edges[edges_cnt].v = v;
    edges[edges_cnt].next = head[u];
    head[u] = edges_cnt;
}

inline void djstl(ll _start) {
    std::priority_queue<Edge> que;
    bool flag[MAXN]; //记录每个点是否被访问过
    std::fill(dist + 1, dist + 1 + n, INT32_MAX);
    std::fill(flag + 1, flag + 1 + n, 0);
    dist[_start] = 0;
    que.push(Edge(_start, 0));
    while (!que.empty()) {
        ll u = que.top().v;
        que.pop();
        flag[u] = true;
        for (size_t i = head[u]; i; i=edges[i].next) {
            if (dist[edges[i].v] > dist[u] + edges[i].w) {
                dist[edges[i].v] = dist[u] + edges[i].w;
                que.push(Edge(edges[i].v, dist[edges[i].v]));
            }
        }
    }
    return;
}

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    readf(&n), readf(&m), readf(&s);

    for (size_t i = 0; i < m; i++) {
        ll u, v, w;
        readf(&u), readf(&v), readf(&w);
        add_edge(u, v, w);
    }

    djstl(s);

    for (size_t i = 1; i <= n; i++) {
        printf("%lld ", dist[i]);
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