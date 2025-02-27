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
#include <time.h>
#include <iostream>
#include <stdint.h>
#include <time.h>

#define READ          false
#define MAX_INF       1e18
#define MAX_NUM_SIZE  35
#define MAXN          100005
#define ls(x)         (x) << 2
#define rs(x)         (x) << 2 | 1

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

struct edge{
    ll u, v, w;
};

struct Tag {
    int b;
    ll value;
};

struct tree_data {
    ll sum;
    Tag tag = {0, 0};
};

std::vector<ll> graph[MAXN];
edge edges[MAXN - 1];
ll deep[MAXN], father[MAXN], heavy_son[MAXN], chain_top[MAXN], node_num[MAXN], id[MAXN];
ll array[MAXN]; //array[id] value
tree_data tree[MAXN << 2];
ll n, chain_cnt = 0;

//这个函数要初始化树的deep， father， heavy_son, node_num数组为有效值
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

inline void add_tag(ll _P, ll _Lp, ll _Rp,  Tag _Tag) {
    if (tree[_P].tag.b && _Lp != _Rp) {
        push_down(_P, _Lp, _Rp);
        return;
    }
    tree[_P].tag = _Tag;
    if (tree[_P].tag.b == 1) {
        tree[_P].sum = (_Rp - _Lp + 1) * tree[_P].tag.value;
    }
    else {
        tree[_P].sum += (_Rp - _Lp + 1) * tree[_P].tag.value;
    }
    return;
}

inline void push_up(ll _P) {
    tree[_P].sum = tree[ls(_P)].sum + tree[rs(_P)].sum;
    return;
}

inline void push_down(ll _P, ll _Lp, ll _Rp) {
    ll mid = (_Lp + _Rp) >> 1;
    if (!tree[_P].tag.b) {
        return;
    }

    add_tag(ls(_P), _Lp, mid, tree[_P].tag);
    add_tag(rs(_P), mid + 1, _Rp, tree[_P].tag);
    tree[_P].tag.b = 0;
    return;
}

void build_tree(ll _P, ll _Lp, ll _Rp) {
    if (_Lp = _Rp) {
        tree[_P].sum = array[_Lp - 1];
        return;
    }

    ll mid = (_Lp + _Rp) >> 1;
    build_tree(ls(_P), _Lp, mid);
    build_tree(rs(_P), mid + 1, _Rp);
    push_up(_P);
    return;
}

ll segment_query(ll _P, ll _Lp, ll _Rp, ll _Left, ll _Right) {
    if (_Left <= _Lp && _Rp <= _Right) {
        return tree[_P].sum;
    }

    push_down(_P, _Lp, _Rp);
    ll mid = (_Lp + _Rp) >> 1, ret = 0;
    if (_Left <= mid) {
        ret += segment_query(ls(_P), _Lp, mid, _Left, _Right);
    }
    if (_Right > mid) {
        ret += segment_query(rs(_P), mid, _Rp, _Left, _Right);
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

    //TODO
    readf(&n);
    for (size_t i = 0; i < n - 1; i++) {
        edges[i] = edge{ readf<ll>() - 1, readf<ll>() - 1, readf<ll>() };
        graph[edges[i].u].push_back(edges[i].v);
        graph[edges[i].v].push_back(edges[i].u);
    }

    tree_init(-1, 1, 0);
    tree_init_heavy_chain(0, 0, -1, chain_cnt);

    //将边的权值转移到这个边所连接的深度较深的节点上
    for (size_t i = 0; i < n - 1; i++) {
        if (father[edges[i].u] = edges[i].v) {
            array[id[edges[i].u]] = edges[i].w;
        }
        else {
            array[id[edges[i].v]] = edges[i].w;
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
 *      |  |  希望此代码无bug|  |  |     |         |      |
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