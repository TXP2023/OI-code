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
#define MAXN         (size_t)(5e5+5)

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

std::vector<ll> graph[MAXN];
ll deep[MAXN], father[MAXN], heavy_son[MAXN], node_num[MAXN], chain_top[MAXN];
ll n, m, s;//n个节点

//dppe[u]为节点u的深度， father[u]为节点u的父节点, node_num[u]为以节点u为根节点的子树的节点数量， 
// chain_top[u]为节点u的重链的头节点

//heavy_son[u]为节点u的重子节点，对于一个节点的重子节点为这个节点的所有子节点
//中，以该子节点为根的子树最大的的点

// 这个函数要初始化树的deep， father， heavy_son, node_num数组为有效值
inline void tree_init(ll _u, ll _father, ll _deep) {
    deep[_u] = _deep;
    father[_u] = _father;
    node_num[_u] = 1;
    for (size_t i = 0; i < graph[_u].size(); i++) {
        if (graph[_u][i] == _father) {
            continue;
        }
        ll v = graph[_u][i];
        tree_init(v, _u, _deep + 1);
        node_num[_u] += node_num[v];
        if (!heavy_son[_u] || node_num[heavy_son[_u]] < node_num[v]) {
            heavy_son[_u] = v;
        }
    }
    return;
}

inline void tree_init_heavy_chain(ll _u, ll _top, ll _father) {
    chain_top[_u] = _top; //记录这个点的链头
    //newSequence[id[_u]] = sequence[_u];
    if (!heavy_son[_u]) /*这个点为叶子节点 即这个点没有重儿子 即没有儿子*/ {
        return;
    }
    tree_init_heavy_chain(heavy_son[_u], _top, _u); //先构建重链
    //遍历剩下的所有轻链
    for (size_t i = 0; i < graph[_u].size(); i++) {
        ll v = graph[_u][i];
        if (v != _father && v != heavy_son[_u]) {
            /*这是一个轻儿子 轻儿子不是重儿子也不是父节点*/
            tree_init_heavy_chain(v, v, _u); 
            //遍历到这个轻儿子 由于这个点是轻儿子 故这将新建一个重链 这个重链的链头就是这个轻儿子
        }
    }
    return;
}

//如何借助树剖求lca，对于点u，v的lca分类讨论
//1）点u，v在一条重链上 节点深度低的就是
//2）点u，v不在一条重链上 让深度低的往上跳，直到 1）

inline ll lca(ll _u, ll _v) {
    while (chain_top[_u] != chain_top[_v]) {
        //在跳的过程中 存在点u和点v不再一个树链上 故要将点u移动至点u所在树链的链头的父节点，即向上提一个重链
        if (deep[chain_top[_u]] < deep[chain_top[_v]]) {
            std::swap(_u, _v);
        }
        //注意更新原来点u所在的重链
        _u = father[chain_top[_u]];
    }
    
    return (deep[_u] < deep[_v]) ? _u : _v;
}

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

    readf(&n), readf(&m), readf(&s);

    for (size_t i = 0; i < n - 1; i++) {
        ll u, v;
        readf(&u), readf(&v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    std::fill(heavy_son + 1, heavy_son + n + 1, 0);

    tree_init(s, 0, 1);
    tree_init_heavy_chain(s, s, 1);

    for (size_t i = 0; i < m; i++) {
        ll u, v;
        readf(&u), readf(&v);
        printf("%lld\n", lca(u, v));
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