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
#define MAXN          (size_t)(2e4+5)

typedef long long int ll;
typedef unsigned long long int ull;

//快读函数声明
template< typename Type >
inline Type fread(Type* p = nullptr);

//快速输出函数
template<typename Type>
inline void fwrite(Type x);

struct Edge {
    ll u, v, w;
};

Edge e[MAXN];
std::vector<Edge> graph[MAXN];
ll deep[MAXN], father[MAXN], heavy_son[MAXN], chain_top[MAXN], node_num[MAXN], id[MAXN];
ll weight[MAXN], sum[MAXN];
ll seg_tree[MAXN << 2];
ll n, cnt = 0, ans;

// 这个函数要初始化树的deep， father， heavy_son, node_num数组为有效值
inline void tree_init(ll _u, ll _father, ll _deep) {
    deep[_u] = _deep;
    father[_u] = _father;
    node_num[_u] = 1;
    for (size_t i = 0; i < graph[_u].size(); i++) {
        if (graph[_u][i].v == _father) {
            continue;
        }
        ll v = graph[_u][i].v;
        tree_init(v, _u, _deep + 1);
        node_num[_u] += node_num[v];
        if (heavy_son[_u] == -1 || node_num[heavy_son[_u]] < node_num[v]) {
            heavy_son[_u] = v;
        }
    }
    return;
}

inline void tree_init_heavy_chain(ll _u, ll _top, ll _father, ll& _cnt) {
    id[_u] = _cnt++;
    chain_top[_u] = _top; //记录这个点的链头
    //newSequence[id[_u]] = sequence[_u];
    if (heavy_son[_u] == -1) /*这个点为叶子节点 即这个点没有重儿子 即没有儿子*/ {
        return;
    }
    tree_init_heavy_chain(heavy_son[_u], _top, _u, _cnt); //先构建重链
    //遍历剩下的所有轻链
    ll v;
    for (size_t i = 0; i < graph[_u].size(); i++) {
        v = graph[_u][i].v;
        if (v != _father && v != heavy_son[_u]) /*这是一个轻儿子 轻儿子不是重儿子也不是父节点*/ {
            tree_init_heavy_chain(v, v, _u, _cnt); //遍历到这个轻儿子 由于这个点是轻儿子 故这将新建一个重链 这个重链的链头就是这个轻儿子
        }
    }
    return;
}

void build_tree(ll p, ll l, ll r) {
    if (l == r) {
        seg_tree[p] = weight[l];
        return;
    }
    ll mid = (l + r) >> 1;
    build_tree(p * 2, l, mid);
    build_tree(p * 2 + 1, mid + 1, r);
    seg_tree[p] = seg_tree[p * 2] + seg_tree[p * 2 + 1];
    return;
}

ll query(ll p, ll l, ll r, ll rL, ll rR) {
    if (rL <= l && r <= rR) {
        return seg_tree[p];
    }
    ll res = 0, mid = (l + r) >> 1;
    if (rL <= mid) {
        res += query(p * 2, l, mid, rL, rR);
    }
    if (mid < rR) {
        res += query(p * 2 + 1, mid + 1, r, rL, rR);
    }
    return res;
}

//针对树上_u ~ _v路径上的点的和
inline ll ask(ll _u, ll _v) {
    ll sum = 0;
    while (chain_top[_u] != chain_top[_v]) {
        //在跳的过程中 存在点u和点v不再一个树链上 故要将点u移动至点u所在树链的链头的父节点，即向上提一个重链
        if (deep[chain_top[_u]] < deep[chain_top[_v]]) {
            std::swap(_u, _v);
        }
        sum += query(id[chain_top[_u]] + 1, id[_u] + 1, 1, 1, n);
        //注意更新原来点u所在的重链
        _u = father[chain_top[_u]];
    }
    if (deep[_u] > deep[_v]) {
        std::swap(_u, _v);
    }
    sum += query(id[_u] + 2, id[_v] + 1, 1, 1, n); //此时u和v在同一条重链上 那就直接区间加
    return sum;
}



ll gcd(ll a, ll b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

int main() {

#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    fread(&n);

    for (size_t i = 0; i < n - 1; i++) {
        ll u, v, w;
        fread(&u), fread(&v), fread(&w);
        graph[u].push_back({ v, w });
        graph[v].push_back({ u, w });
        e[i] = { u, v, w };
    }

    tree_init(1, 0, 1);

    tree_init_heavy_chain(1, 1, 0, cnt);

    for (size_t i = 0; i < n - 1; i++) {
        ll u = e[i].u, v = e[i].v;
        if (deep[u] < deep[v]) {
            std::swap(u, v);
        }
        weight[id[u]] = e[i].w;
    }

    build_tree(1, 1, n);

    for (size_t i = 1; i <= n; i++) {
        for (size_t j = i + 1; j <= n; j++) {
            ll sum = ask(i, j);
            if (!(sum % 3)) {
                ++ans;
            }
        }
    }

    ans *= 2;
    ans += n;
    ll temp = gcd(ans, n * n);
    ans /= temp;
    printf("%lld/%lld\n", ans, n * n / temp);



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