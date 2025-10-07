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
#define MAXN          105
#define MAXM          505

typedef long long ll;
typedef unsigned long long ull;

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

        Edge() = default;

        Edge(ll _v, ll _next) : v(_v), next(_next) {}
    };

    Edge e[MAXN];
    ll head[MAXN], cnt;

    Graph() {
        memset(head, 0, sizeof head);
        cnt = 0;
    }

    void add_edge(ll u, ll v) {
        ++cnt;
        e[cnt] = Edge(v, head[u]);
        head[u] = cnt;
        return;
    }
};

Graph g, tree;

ll dfn[MAXN], low[MAXN], fa[MAXN], stack[MAXN], deg[MAXN], val[MAXN], cost[MAXN], top = 0;
ll w[MAXN], v[MAXN], pre[MAXN], dp[MAXN][MAXM];
bool vis[MAXN];
ll n, m, cnt, tot, now;


void tarjan(ll u) {
    low[u] = dfn[u] = ++now;
    stack[++top] = u; vis[u] = 1;
    for (ll i = g.head[u]; i; i = g.e[i].next) {
        ll v = g.e[i].v;
        if (!dfn[v]) {
            tarjan(v);
            low[u] = std::min(low[u], low[v]);
        }
        else if (vis[v])low[u] = std::min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
        ++tot;
        vis[u] = 0;
        while (stack[top + 1] != u) {
            fa[stack[top]] = tot;
            vis[stack[top--]] = 0;
        }
    }
}

void solve(ll u) {
    for (ll i = cost[u]; i <= m; i++) {
        dp[u][i] = val[u];
    }
    for (ll i = tree.head[u]; i; i = tree.e[i].next) {
        solve(tree.e[i].v);
        for (ll j = m - cost[u]; j >= 0; j--) {
            for (ll q = 0; q <= j; q++) {
                dp[u][j + cost[u]] = std::max(dp[u][j + cost[u]], dp[u][j + cost[u] - q] + dp[tree.e[i].v][q]);
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

    fread(&n), fread(&m);


    for (size_t i = 1; i <= n; i++) {
        fread(&w[i]);
    }

    for (size_t i = 1; i <= n; i++) {
        fread(&v[i]);
    }

    for (size_t i = 1; i <= n; i++) {
        fread(&pre[i]);
        if (pre[i]) {
            g.add_edge(i, pre[i]);
        }
    }

    for (size_t i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }

    for (ll i = 1; i <= n; i++) {
        val[fa[i]] += v[i]; cost[fa[i]] += w[i];
        if (fa[i] != fa[pre[i]] && pre[i] != 0) {
            tree.add_edge(fa[pre[i]], fa[i]);
            deg[fa[i]]++;
        }
    }

    ll sys = tot + 1;
    for (ll i = 1; i <= tot; i++) {
        if (!deg[i]) {
            tree.add_edge(sys, i);
        }
    }
    cost[sys] = 0; val[sys] = 0;
    solve(sys);

    printf("%d", dp[sys][m]);

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
    ll sta[MAX_NUM_SIZE];
    ll top = 0;
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