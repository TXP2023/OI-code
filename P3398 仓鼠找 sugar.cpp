//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
//
//      By txp2024 www.luogu.com.cn  TXP2023 www.github.com
// 
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
#pragma once
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <ctype.h>
#include <cstdarg>
#include <climits>
#include <iostream>
#include <stdint.h>
#include <initializer_list>

#define READ false
#define MAX_INF 1e18

typedef long long int ll;
typedef unsigned long long int unill;

//快读函数声明
#if READ
template< typename T >
inline T readf();
#else
template< typename Type >
inline Type readf(Type* p = NULL);
#endif

std::vector< std::vector< ll > > graph;
std::vector< std::vector< ll > > father;
std::vector< ll > depth;
ll n, q;

void dfs_depth(ll u, ll v) {
    for (size_t i = 0; i < graph[u].size(); i++) {
        ll child = graph[u][i];
        if (child == v) {
            continue;
        }
        depth[child] = depth[u] + 1;
        father[child][0] = u;
        dfs_depth(child, u);
    }
    return;
}

inline ll LCA(ll u, ll v) {
    //如果两个是同一个点的话，那就是这个点本身
    if (u == v) {
        return u;
    }
    //让u成为深度更大的那个点
    if (depth[u] < depth[v]) {
        std::swap(u, v);
    }

    for (ll i = 18; i >= 0; i--) {
        if (depth[u] - depth[v] >= (1 << i)) //如果目前的差距大于2的i次方，那么要更新u，并计算2的i+1次方
        {
            u = father[u][i]; //往上提
        }
    }

    if (u == v) {
        return u;
    }

    for (ll i = 18; i >= 0; i--) {
        if (father[u][i] != father[v][i]) {
            u = father[u][i], v = father[v][i]; //往上提
        }
    }
    return father[u][0];
}

inline void init() {
    for (size_t j = 1; j <= 18; j++) {
        for (size_t i = 0; i < n; i++) {
            father[i][j] = father[father[i][j - 1]][j - 1];
        }
    }
    return;
}

int main() {
    freopen("input.txt", "r", stdin);

    readf(&n), readf(&q);

    graph.resize(n);
    for (size_t i = 0; i < n; i++) {
        ll u = readf< ll >() - 1, v = readf< ll >() - 1;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    depth.resize(n);
    father.resize(n, std::vector< ll >(19, 0));
    depth[0] = 1;
    dfs_depth(0, -1);

    for (size_t i = 0; i < q; i++) {
        ll a = readf< int >(), b = readf< int >(), c = readf< int >(), d = readf< int >();
        ll lca1 = LCA(--a, --b), lca2 = LCA(--c, --d);
        if ((depth[lca1] >= depth[lca2]/*lca1在lca2的路径上*/ && (LCA(lca1, c) == lca1 &&  LCA(lca1, d) == lca1)) && 
            (depth[lca2] >= depth[lca1]/*lca2在lca1的路径上*/ && (LCA(lca2, a) == lca2 && LCA(lca2, b) == lca1))
            ) {
            puts("Y");
        }
        else {
            puts("N");
        }
    }

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