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
#include <stdint.h>

#define _FREAD        true
#define MAX_INF       1e18
#define MAX_NUM_SIZE  35
#define MAXN          2005
#define MAXK          2005

typedef long long int ll;
typedef unsigned long long int ull;

//快读函数声明
template< typename Type >
inline Type fread(Type* p = nullptr);

//快速输出函数
template<typename Type>
inline void fwrite(Type x);

struct Edge {
    ll v, w, next;

    Edge() : v(0), next(0), w(0) {}

    Edge(ll _v, ll _w, ll _next) : v(_v), w(_w), next(_next) {}
};


Edge edges[MAXN << 1];
ll dp[MAXN][MAXK];
ll head[MAXN], size[MAXN];
ll n, m, edge_cnt = 0;

inline void add_edge(ll u, ll v, ll w) {
    ++edge_cnt;
    edges[edge_cnt] = Edge(v, w, head[u]);
    head[u] = edge_cnt;

    ++edge_cnt;
    edges[edge_cnt] = Edge(u, w, head[v]);
    head[v] = edge_cnt;
    return;
}

inline void fill_dp(ll _u, ll _fa) {
    size[_u] = 1;
    dp[_u][0] = 0;
    dp[_u][1] = 0;
    for (size_t i = head[_u]; i; i = edges[i].next) {
        ll v = edges[i].v;
        if (v == _fa) {
            continue;
        }
        fill_dp(v, _u);
        size[_u] += size[v];
        for (ll j = std::min(m, size[_u]); j >= 0; --j) {   //此处倒序枚举是为了避免重复选取
            if (dp[_u][j] != -1) {
                dp[_u][j] += dp[v][0] + (ll)size[v] * (n - m - size[v]) * edges[i].w;
            }   //在DP前应先加上当前子节点的子树纯白色的情况，这是下面也倒序枚举的前提

            for (ll k = std::min(ll(j), size[v]); k; --k) {
                if (dp[_u][j - k] == -1) {
                    continue;
                }
                ll temp = (ll)(k * (m - k) + (size[v] - k) * (n - m - size[v] + k)) * edges[i].w;   //当前情况下连接子节点的边的贡献
                dp[_u][j] = std::max(dp[_u][j], dp[_u][j - k] + dp[v][k] + temp);
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

    fread(&n), fread(&m);

    if (n - m < m) {
        m = n - m;
    }
    for (size_t i = 0; i < n - 1; i++) {
        ll u, v, w;
        fread(&u), fread(&v), fread(&w);
        add_edge(u, v, w);
    }

    memset(dp, -1, sizeof(dp));

    fill_dp(1, 0);


    printf("%lld", dp[1][m]);

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