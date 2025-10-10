//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
//
//      By txp2024 www.luogu.com.cn  TXP2023 www.github.com
// 
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

#pragma once
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <numeric>
#include <ctype.h>
#include <cstdarg>
#include <queue>
#include <climits>
#include <time.h>
#include <iostream>
#include <stdint.h>
#include <vector>

#define _FREAD        true
#define MAX_INF       0x7f7f7f7f7f7f7f7f
#define MAX_NUM_SIZE  35
#define MAXM          (size_t)(2e5+5)
#define MAXN          (size_t)(2e5+5)

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

struct Graph {
    struct Edge {
        ll v, next;
    };

    Edge e[MAXM];
    ll head[MAXN], cnt;

    Graph() {
        cnt = 0;
        memset(head, 0, sizeof head);
        return;
    }

    void add_edge(ll u, ll v) {
        ++cnt;
        e[cnt] = { v, head[u] };
        head[u] = cnt;
        return;
    }
};

struct queData {
    ll u, w, tag; //tag = 0 正图 1反图

    queData() = default;

    queData(ll _u, ll _w, ll _tag) : u(_u), w(_w), tag(_tag) {}

    bool operator <(const queData& other)const {
        return w > other.w;
    }
};

Graph g, suf;
ll dist[MAXN][2];
ll flag[MAXN][2];
ll n, m, x;

void djstl() {
    memset(dist, 0x7f, sizeof dist);
    dist[1][0] = 0;
    std::priority_queue<queData> que;
    que.push(queData(1, 0, 0));
    while (!que.empty()) {
        ll u = que.top().u, w = que.top().w, tag = que.top().tag;
        que.pop();
        flag[u][tag] = true;
        //走正图
        for (size_t i = g.head[u]; i; i = g.e[i].next) {
            if (w + 1 + (tag == 0 ? 0 : x) < dist[g.e[i].v][0]) {
                dist[g.e[i].v][0] = w + 1 + (tag == 0 ? 0 : x);
                que.push({ g.e[i].v , dist[g.e[i].v][0], 0 });
            }
        }
        //走返图
        for (size_t i = suf.head[u]; i; i = suf.e[i].next) {
            if (w + 1 + (tag == 1 ? 0 : x) < dist[suf.e[i].v][1]) {
                dist[suf.e[i].v][1] = w + 1 + (tag == 1 ? 0 : x);
                que.push({ suf.e[i].v , dist[suf.e[i].v][1], 1 });
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

    fread(&n), fread(&m), fread(&x);

    for (size_t i = 0; i < m; i++) {
        ll u, v;
        fread(&u), fread(&v);
        g.add_edge(u, v);
        suf.add_edge(v, u);
    }

    djstl();

    printf("%lld\n", std::min(dist[n][0], dist[n][1]));

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
