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
#define MAX_NUM_SIZE 35

typedef long long int ll;
typedef long long int* llp;
typedef unsigned long long int unill;

//快读函数声明
#if READ
template< typename T >
inline T readf();
#else
template< typename Type >
inline Type readf(Type* p = NULL);
#endif

//快速输出函数
template<typename Type>
inline void writef(Type x);

std::vector<std::vector<ll>> graph;
ll* deep, * father, * heavy_son, * node_num, * top;
ll n, m, s;//n个节点

inline ll/*返回值是节点p为根节点的子树的节点数量*/ tree_init(ll _p, ll _deep, ll _father) {
    deep[_p] = _deep;
    father[_p] = _father;
    if (graph[_p].size() == 1 && _p != s) {
        node_num[_p] = 1;
        return 1;
    }
    ll sum = 0;
    ll num = -1;
    for (size_t i = 0; i < graph[_p].size(); i++) {
        if (graph[_p][i] != _father) {
            sum += tree_init(graph[_p][i], _deep + 1, _p);
        }
    }
    heavy_son[_p] = graph[_p].front();
    for (size_t i = 1; i < graph[_p].size(); i++) {
        if (graph[_p][i] != _father && node_num[heavy_son[_p]] < node_num[graph[_p][i]]) {
            heavy_son[_p] = graph[_p][i];
        }
    }

    return node_num[_p] = sum + 1;
}

inline void tree_init_2(ll _p, ll _father) {
    top[_p] = _father;
    if (heavy_son[_p] == -1) {
        return;
    }
    tree_init_2(heavy_son[_p], _father);
    for (size_t i = 0; i < graph[_p].size(); i++) {
        if (graph[_p][i] != father[_p] && heavy_son[_p] != graph[_p][i]) {
            tree_init_2(graph[_p][i], graph[_p][i]);
        }
    }
    return;
}

inline ll lca(ll _u, ll _v) {
    while (top[_u] != top[_v]) {
        if (deep[top[_u]] < deep[top[_v]]) {
            std::swap(_u, _v);
        }
        _u = father[top[_u]];
    }
    return (deep[_u] < deep[_v]) ? _u : _v;
}

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

    readf(&n), readf(&m), readf(&s);

    graph.resize(n);
    for (size_t i = 0; i < n - 1; i++) {
        ll u, v;
        readf(&u), readf(&v);
        graph[--u].push_back(--v);
        graph[v].push_back(u);
    }

    top = new ll[n];
    deep = new ll[n];
    father = new ll[n];
    node_num = new ll[n];
    heavy_son = new ll[n];
    std::fill(heavy_son, heavy_son + n, -1);

    tree_init(--s, 1, s);
    tree_init_2(s, s);

    for (size_t i = 0; i < m; i++) {
        ll u, v;
        readf(&u), readf(&v);
        printf("%lld\n", lca(--u, --v) + 1);
    }
    delete[] top;
    delete[] deep;
    delete[] father;
    delete[] node_num;
    delete[] heavy_son;
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
    while (top) putchar(sta[--top] + 48);  // 48 是 '0'
    return;
}