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
#include <queue>
#include <ctype.h>
#include <cstdarg>
#include <climits>
#include <time.h>
#include <iostream>
#include <stdint.h>

#define _FREAD        true
#define MAX_INF       1e18
#define MAX_NUM_SIZE  35
#define MAXR          (size_t)(1e5+5)
#define MAXN          (size_t)(5005)

typedef long long int ll;
typedef unsigned long long int ull;

template<typename _T>
inline _T fpow(_T a, _T n, _T mod) {
    _T base = a, ret = 1;
    while (n) {
        if (n & 1) {
            ret = ret * base;
            ret %= mod;
        }
        base = base * base;
        base %= mod;
        n >>= 1;
    }
    return ret % mod;
}
//快读函数声明
template< typename Type >
inline Type fread(Type* p = nullptr);

//快速输出函数
template<typename Type>
inline void fwrite(Type x);

struct Edge {
    ll v, w, next;

    Edge() = default;

    Edge(ll _v, ll _w, ll _next) : v(_v), w(_w), next(_next) {}
};

struct heapData {
    ll u, w;
    bool operator <(const heapData& other)const {
        return w > other.w;
    }

    heapData() = default;

    heapData(ll _u, ll _w) : u(_u), w(_w) {}
};

ll head[MAXN];
Edge e[MAXR << 1];
ll dist[MAXN][2]; //0是最短路， 1是次短路
ll n, r, cnt = 0;

inline void add_edge(ll u, ll v, ll w) {
    ++cnt;
    e[cnt] = Edge(v, w, head[u]);
    head[u] = cnt;
    return;
}

void djstl() {
    memset(dist, 0x7f7f7f7f7f7f7f7f, sizeof(dist));
    dist[1][0] = 0;
    std::priority_queue<heapData> heap;
    heap.push({ 1, 0 });
    while (!heap.empty()) {
        heapData now = heap.top();
        heap.pop();
        for (size_t i = head[now.u]; i; i = e[i].next) {
            ll v = e[i].v, w = e[i].w;
            if (now.w + w < dist[v][0]) {
                dist[v][1] = dist[v][0];
                dist[v][0] = now.w + w;
                heap.push(heapData(v, dist[v][0]));
            }
            else {
                if (now.w + w < dist[v][1]) {
                    dist[v][1] = now.w + w;
                    heap.push(heapData(v, dist[v][1]));
                }
            }
        }
    }
}

int main() {

#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    fread(&n), fread(&r);

    for (size_t i = 0; i < r; i++) {
        ll u, v, w;
        fread(&u), fread(&v), fread(&w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }

    djstl();

    printf("%lld\n", dist[n][1]);

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