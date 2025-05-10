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
#define MAXN          200000

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

struct tree_data {
    ll max;
    bool add_bool = false, change_bool = false;
    ll tag_add, tag_change;
    tree_data() {
        add_bool = false;
        change_bool = false;
        tag_add = 0;
        tag_change = 0;
        max = 0;
        return;
    }
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

template<typename Type>
inline Type ls(Type _x) {
    return _x << 1;
}

template<typename Type>
inline Type rs(Type _x) {
    return _x << 1 | 1;
}

inline void push_up(ll _P) {
    tree[_P].max = std::max(tree[ls(_P)].max, tree[rs(_P)].max);
    return;
}

inline void push_down(ll _P, ll _Lp, ll _Rp) {
    if (tree[_P].change_bool || tree[_P].add_bool) {
        ll mid = (_Lp + _Rp) >> 1;
        if (tree[_P].change_bool) {
            tree[ls(_P)].max = tree[_P].tag_change;
            tree[ls(_P)].change_bool = true;
            tree[ls(_P)].tag_change = tree[_P].tag_change;
            tree[ls(_P)].add_bool = false;
            tree[ls(_P)].tag_add = 0;
            tree[rs(_P)].max = tree[_P].tag_change;
            tree[rs(_P)].change_bool = true;
            tree[rs(_P)].tag_change = tree[_P].tag_change;
            tree[rs(_P)].add_bool = false;
            tree[rs(_P)].tag_add = 0;
        }
        if (tree[_P].add_bool) {
            tree[ls(_P)].max += tree[_P].tag_add;
            tree[ls(_P)].add_bool = true;
            tree[ls(_P)].tag_add += tree[_P].tag_add;
            tree[rs(_P)].max += tree[_P].tag_add;
            tree[rs(_P)].add_bool = true;
            tree[rs(_P)].tag_add += tree[_P].tag_add;
        }
        tree[_P].add_bool = false;
        tree[_P].change_bool = false;
        tree[_P].tag_add = 0;
        tree[_P].tag_change = 0;
    }
    return;
}

void build_tree(ll _P, ll _Lp, ll _Rp) {
    if (_Lp == _Rp) {
        tree[_P].max = array[_Lp - 1];
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
        return tree[_P].max;
    }

    push_down(_P, _Lp, _Rp);
    ll mid = (_Lp + _Rp) >> 1, ret = LLONG_MIN;
    if (_Left <= mid) {
        ret = std::max(segment_query(ls(_P), _Lp, mid, _Left, _Right), ret);
    }
    if (_Right > mid) {
        ret = std::max(segment_query(rs(_P), mid + 1, _Rp, _Left, _Right), ret);
    }
    push_up(_P);
    return ret;
}

void segment_updata_add(ll _P, ll _Lp, ll _Rp, ll _Left, ll _Right, ll _Value) {
    if (_Left <= _Lp && _Rp <= _Right) {
        tree[_P].tag_add += _Value;
        tree[_P].add_bool = true;
        tree[_P].max += _Value;
        return;
    }

    push_down(_P, _Lp, _Rp);
    ll mid = (_Lp + _Rp) >> 1;
    if (_Left <= mid) {
        segment_updata_add(ls(_P), _Lp, mid, _Left, _Right, _Value);
    }
    if (_Right > mid) {
        segment_updata_add(rs(_P), mid + 1, _Rp, _Left, _Right, _Value);
    }
    push_up(_P);
    return;
}

void segment_updata_change(ll _P, ll _Lp, ll _Rp, ll _Left, ll _Right, ll _Value) {
    if (_Left <= _Lp && _Rp <= _Right) {
        tree[_P].tag_add = 0;
        tree[_P].add_bool = false;
        tree[_P].tag_change = _Value;
        tree[_P].change_bool = true;
        tree[_P].max = _Value;
        return;
    }

    push_down(_P, _Lp, _Rp);
    ll mid = (_Lp + _Rp) >> 1;
    if (_Left <= mid) {
        segment_updata_change(ls(_P), _Lp, mid, _Left, _Right, _Value);
    }
    if (_Right > mid) {
        segment_updata_change(rs(_P), mid + 1, _Rp, _Left, _Right, _Value);
    }
    push_up(_P);
    return;
}

inline void add(ll _u, ll _v, ll _Value) {
    while (chain_top[_u] != chain_top[_v]) {
        //在跳的过程中 存在点u和点v不再一个树链上 故要将点u移动至点u所在树链的链头的父节点，即向上提一个重链
        if (deep[chain_top[_u]] < deep[chain_top[_v]]) {
            std::swap(_u, _v);
        }
        segment_updata_add(1, 1, n, id[chain_top[_u]] + 1, id[_u] + 1, _Value);
        //注意更新原来点u所在的重链
        _u = father[chain_top[_u]];
    }
    if (deep[_u] > deep[_v]) {
        std::swap(_u, _v);
    }
    if (_u == _v && _u == 0) {
        return;
    }
    segment_updata_add(1, 1, n, id[_u] + 2, id[_v] + 1, _Value); //此时u和v在同一条重链上 那就直接区间加
    return;
}

inline void cover(ll _u, ll _v, ll _Value) {
    while (chain_top[_u] != chain_top[_v]) {
        //在跳的过程中 存在点u和点v不再一个树链上 故要将点u移动至点u所在树链的链头的父节点，即向上提一个重链
        if (deep[chain_top[_u]] < deep[chain_top[_v]]) {
            std::swap(_u, _v);
        }
        segment_updata_change(1, 1, n, id[chain_top[_u]] + 1, id[_u] + 1, _Value);
        //注意更新原来点u所在的重链
        _u = father[chain_top[_u]];
    }
    if (deep[_u] > deep[_v]) {
        std::swap(_u, _v);
    }
    if (_u == _v && _u == 0) {
        return;
    }
    segment_updata_change(1, 1, n, id[_u] + 2, id[_v] + 1, _Value); //此时u和v在同一条重链上 那就直接区间加
    return;
}

inline void change(ll _k, ll _Value) {
    ll u = edges[_k].u, v = edges[_k].v;
    //deep[v]要小于deep[u]
    if (deep[v] > deep[u]) {
        std::swap(u, v);
    }
    segment_updata_change(1, 1, n, id[u] + 1, id[u] + 1, _Value); //此时u和v在同一条重链上 那就直接区间加
    return;
}

inline ll query(ll _u, ll _v) {
    ll max = LLONG_MIN;
    while (chain_top[_u] != chain_top[_v]) {
        //在跳的过程中 存在点u和点v不再一个树链上 故要将点u移动至点u所在树链的链头的父节点，即向上提一个重链
        if (deep[chain_top[_u]] < deep[chain_top[_v]]) {
            std::swap(_u, _v);
        }
        max = std::max(max, segment_query(1, 1, n, id[chain_top[_u]] + 1, id[_u] + 1));
        //注意更新原来点u所在的重链
        _u = father[chain_top[_u]];
    }
    if (deep[_u] > deep[_v]) {
        std::swap(_u, _v);
    }
    if (_u == _v && _u == 0) {
        return max;
    }
    max = std::max(max, segment_query(1, 1, n, id[_u] + 2, id[_v] + 1)); //此时u和v在同一条重链上 那就直接区间加
    return max;
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
        ll u = readf<ll>() - 1, v = readf<ll>() - 1, w = readf<ll>();
        edges[i] = edge{ u, v, w };
        graph[edges[i].u].push_back(edges[i].v);
        graph[edges[i].v].push_back(edges[i].u);
    }

    std::fill(heavy_son, heavy_son + n, -1);
    tree_init(0, -1, 0);
    tree_init_heavy_chain(0, 0, -1, chain_cnt);

    //将边的权值转移到这个边所连接的深度较深的节点上
    for (size_t i = 0; i < n - 1; i++) {
        if (deep[edges[i].u] > deep[edges[i].v]) {
            array[id[edges[i].u]] = edges[i].w;
        }
        else {
            array[id[edges[i].v]] = edges[i].w;
        }
    }

    build_tree(1, 1, n);
    std::string str;
    std::cin >> str;    
    while (str != "Stop") {
        if (str == "Change") {
            ll x = readf<ll>() - 1, value = readf<ll>();
            change(x, value);
        }
        else if(str == "Cover") {
            ll u = readf<ll>() - 1, v = readf<ll>() - 1, value = readf<ll>();
            cover(u, v, value);
        }
        else if(str == "Add") {
            ll u = readf<ll>() - 1, v = readf<ll>() - 1, value = readf<ll>();
            add(u, v, value);
        }
        else {
            ll u = readf<ll>() - 1, v = readf<ll>() - 1;
            printf("%lld\n", query(u, v));
        }
        
        std::cin >> str;
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