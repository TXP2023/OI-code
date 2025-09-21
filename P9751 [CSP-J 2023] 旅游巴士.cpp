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
#include <queue>
#include <iostream>
#include <stdint.h>

#define _FREAD        true
#define MAX_INF       0x7f7f7f7f7f7f7f7f
#define MAX_NUM_SIZE  35
#define MAXN          (size_t)(1e4+5)
#define MAXM          (size_t)(2e4+5)
#define MAXK          105

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
    ll u, t, next;

    Edge() = default;

    Edge(ll _u, ll _t, ll _next) : u(_u), t(_t), next(_next) {}
};

struct heapData {
    ll u, w;

    heapData() = default;

    heapData(ll _u, ll _w) : u(_u), w(_w) {}

    bool operator <(const heapData& other)const {
        return w > other.w;
    }
};

ll head[MAXN], dist[MAXN][MAXK];
bool flag[MAXN][MAXK];
Edge e[MAXM << 1];
ll n, m, k, cnt = 0;

void add_edge(ll u, ll v, ll t) {
    ++cnt;
    e[cnt] = Edge(v, t, head[u]);
    head[u] = cnt;
    return;
}

inline void djstl() {
    memset(dist, 0x7f, sizeof(dist));
    dist[1][0] = 0;
    std::priority_queue<heapData> heap;
    heap.push(heapData(1, 0));
    while (!heap.empty()) {
        ll u = heap.top().u, w = heap.top().w;
        heap.pop();
        if (flag[u][w % k]) {
            continue;
        }
        flag[u][w % k] = 1;
        for (size_t i = head[u]; i; i = e[i].next) {
            ll temp;
            if (w >= e[i].t) {
                temp = w;
            }
            else {
                temp = ((e[i].t - w + k - 1) / k) * k + w;
            }
            if (temp + 1 < dist[e[i].u][(temp + 1) % k]) {
                dist[e[i].u][(temp + 1) % k] = temp + 1;
                heap.push(heapData(e[i].u, temp + 1));
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

    fread(&n), fread(&m), fread(&k);

    for (size_t i = 0; i < m; i++) {
        ll u, v, t;
        fread(&u), fread(&v), fread(&t);
        add_edge(u, v, t);
    }

    djstl();

    printf("%lld\n", dist[n][0] != MAX_INF ? dist[n][0] : -1);



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