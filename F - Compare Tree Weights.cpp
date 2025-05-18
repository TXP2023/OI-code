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
#include <cmath>
#include <iostream>
#include <stdint.h>
#include <cstdlib>

#define READ          false
#define MAX_INF       1e18
#define MAX_NUM_SIZE  35
#define MAXN          (uint64_t)(3e5+5)
#define LS(x)         ((x) << 1)
#define RS(x)         ((x) << 1 | 1)

typedef long long int ll;
typedef unsigned long long int unill;

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

struct edge {
    size_t u, v;
};

ll deep[MAXN], father[MAXN], heavy_son[MAXN], chain_top[MAXN], node_num[MAXN], id[MAXN];
ll n, tree_cnt = 1, edge_cnt = 1, q;
ll seg_tree[MAXN << 2];
edge edges[MAXN];
std::vector<size_t> graph[MAXN];

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
    for (size_t i = 0; i < graph[_u].size(); i++) {
        ll v = graph[_u][i];
        if (v != _father && v != heavy_son[_u]) /*这是一个轻儿子 轻儿子不是重儿子也不是父节点*/ {
            tree_init_heavy_chain(v, v, _u, _cnt); //遍历到这个轻儿子 由于这个点是轻儿子 故这将新建一个重链 这个重链的链头就是这个轻儿子
        }
    }
    return;
}

void seg_tree_init(size_t pos, size_t range_l, size_t range_r) {
    seg_tree[pos] = range_r - range_l + 1;
    if (range_l == range_r) {
        return;
    }
    size_t mid = (range_l + range_r) >> 1;
    seg_tree_init(LS(pos), range_l, mid);
    seg_tree_init(RS(pos), mid + 1, range_r);
    return;
}

void update(size_t pos, size_t range_l, size_t range_r, size_t index, size_t w) {
    if (range_l == range_r) {
        seg_tree[pos] += w;
        return;
    }
    size_t mid = (range_l + range_r) >> 1;
    if (index <= mid) {
        update(LS(pos), range_l, mid, index, w);
    }
    else {
        update(RS(pos), mid + 1, range_r, index, w);
    }
    seg_tree[pos] = seg_tree[LS(pos)] + seg_tree[RS(pos)];
    return;
}

ll query(size_t pos, size_t range_l, size_t range_r, size_t left, size_t right) {
    if (left <= range_l && range_r <= right) {
        return seg_tree[pos];
    }
    ll mid = (range_l + range_r) >> 1, ret = 0;
    if (left <= mid) {
        ret += query(LS(pos), range_l, mid, left, right);
    }
    if (mid < right) {
        ret += query(RS(pos), mid + 1, range_r, left, right);
    }
    return ret;
}

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    readf(&n);

    for (size_t i = 0; i < n - 1; i++) {
        size_t u, v;
        readf(&u), readf(&v);
        graph[u].push_back(v);
        graph[v].push_back(u);
        edges[edge_cnt++] = { u,v };
    }

    memset(heavy_son, -1, (n + 1) * 8);
    tree_init(1, 0, 1);
    tree_init_heavy_chain(1, 1, 0, tree_cnt);

    seg_tree_init(1, 1, n);

    readf(&q);

    for (size_t i = 0; i < q; i++) {
        short opt;
        readf(&opt);
        if (opt == 1) {
            ll u = readf<size_t>(), w = readf<ll>();
            update(1, 1, n, id[u], w);
        }
        else {
            ll y = readf<ll>();
            if (deep[edges[y].u] > deep[edges[y].v]) {
                std::swap(edges[y].u, edges[y].v);
            }
            //此时u是v的父节点
            ll sub_tree_sum = query(1, 1, n, id[edges[y].v], id[edges[y].v] + node_num[edges[y].v] - 1), sum;
            sum = seg_tree[1] - sub_tree_sum;
            printf("%lld\n", (ll)std::fabs(sum - sub_tree_sum));
        }
    }


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