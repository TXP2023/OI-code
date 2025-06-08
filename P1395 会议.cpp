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

#define READ          false
#define MAX_INF       1e18
#define MAX_NUM_SIZE  35
#define MAXN          (size_t)(5e4+5)

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
    size_t u, v;
    size_t next;
};

size_t head[MAXN];
Edge edges[MAXN * 2];
size_t edgeCnt = 0, n;
ll size[MAXN], maxSubTree[MAXN], ans, sum;

inline void addEdge(ll u, ll v) {
    edges[++edgeCnt].u = u;
    edges[edgeCnt].v = v;
    edges[edgeCnt].next = head[u];
    head[u] = edgeCnt;
    return;
}

void get_centroid(size_t u, size_t fa) {
    size[u] = 1;
    for (size_t i = head[u]; i; i = edges[i].next) {
        if (edges[i].v == fa) {
            continue;
        }
        get_centroid(edges[i].v, u);
        size[u] += size[edges[i].v];
        maxSubTree[u] = std::max(size[edges[i].v], maxSubTree[u]);
    }
    maxSubTree[u] = std::max((ll)n - size[u], maxSubTree[u]);
    if (maxSubTree[u] == maxSubTree[ans] && u < ans) {
        ans = u;
    }
    if (maxSubTree[u] < maxSubTree[ans]) {
        ans = u;
    }
    
    return;
}

void get_deep(ll u, ll fa, ll _deep) {
    sum += _deep;
    for (size_t i = head[u]; i; i = edges[i].next) {
        if (edges[i].v == fa) {
            continue;
        }
        get_deep(edges[i].v, u, _deep + 1);
    }
}

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    readf(&n);

    for (size_t i = 0; i < n-1; i++) {
        size_t u, v;
        readf(&u), readf(&v);
        addEdge(u, v);
        addEdge(v, u);
    }

    maxSubTree[0] = INT32_MAX;
    get_centroid(1, 0);
    get_deep(ans, 0, 0);

    printf("%lld %lld\n", ans, sum);
 
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