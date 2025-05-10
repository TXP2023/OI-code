//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
//
//      By txp2024 www.luogu.com.cn  TXP2023 www.github.com
// 
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
#pragma once
#include <climits>
#include <stdint.h>
#include <ctype.h>
#include <vector>
#include <set>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <time.h>
#include <cstdarg>

#define READ          false
#define MAX_INF       1e18
#define MAX_NUM_SIZE  35
#define MAXN          (int64_t)(1e5 + 1)

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

struct tree_node {
    ll biggest, next_biggest;

    tree_node() {
        biggest = -1;
        next_biggest = -1;
        return;
    }
};

std::vector<ll> graph[MAXN];
ll deep[MAXN], father[MAXN], node_num[MAXN], heavy_son[MAXN], dfn_id[MAXN], chain_top[MAXN];
tree_node seg_tree[MAXN << 2];
ll value[MAXN];
ll n, m, dfn_cnt = 0;
std::multiset<ll, std::greater<ll>> value_set;

inline void _get_tree_value(ll _u, ll _father, ll _deep) {
    deep[_u] = _deep;
    father[_u] = _father;
    node_num[_u] = 1;
    for (ll v : graph[_u]) {
        if (v == _father) {
            continue;
        }
        _get_tree_value(v, _u, _deep + 1);
        node_num[_u] += node_num[v];
        if (heavy_son[_u] == -1 || node_num[v] > node_num[heavy_son[_u]]) {
            heavy_son[_u] = v;
        }
    }
    return;
}

inline void _get_heavy_chain(ll _u, ll _father, ll _chain_top) {
    chain_top[_u] = _chain_top;
    dfn_id[_u] = ++dfn_cnt;
    if (!heavy_son[_u]) {
        return;
    }
    _get_heavy_chain(heavy_son[_u], _u, _chain_top);
    for (auto& v : graph[_u]) {
        if (v != _father && v != heavy_son[_u]) {
            _get_heavy_chain(v, _u, v);
        }
    }
    return;
}

inline void init_tree() {
    _get_tree_value(1, 0, 1);
    _get_heavy_chain(1, 0, 1);
    return;
}

template<typename Type>
inline Type ls(Type _X) {
    return _X << 1;
}

template<typename Type>
inline Type rs(Type _X) {
    return _X << 1 | 1;
}

inline tree_node push_up(tree_node a, tree_node b) {
    tree_node ret;
    std::set<ll, std::greater<ll>> value_s;
    value_s.insert(a.biggest);
    value_s.insert(a.next_biggest);
    value_s.insert(b.biggest);
    value_s.insert(b.next_biggest);
    ret.biggest = *value_s.begin();
    value_s.erase(ret.biggest);
    if (value_s.size()) {
        ret.next_biggest = *value_s.begin();
    }
    return ret;
}

void add(ll _Index, ll _RangeL, ll _RangeR, ll _Pos, ll _Value) {
    if (_RangeL == _RangeR) {
        seg_tree[_Index].biggest += _Value;
        return;
    }

    ll mid = (_RangeL + _RangeR) >> 1;
    if (_Pos <= mid) {
        add(ls(_Index), _RangeL, mid, _Pos, _Value);
    }
    else {
        add(rs(_Index), mid + 1, _RangeR, _Pos, _Value);
    }
    //push_up(_Index);
    seg_tree[_Index] = push_up(seg_tree[ls(_Index)], seg_tree[rs(_Index)]);
}

tree_node seg_query(ll _Index, ll _RangeL, ll _RangeR, ll _Left, ll _Right) {
    if (_Left <= _RangeL && _RangeR <= _Right) {
        return seg_tree[_Index];
    }

    tree_node Lret, Rret;
    ll mid = (_RangeL + _RangeR) >> 1;
    if (_Left <= mid) {
        Lret = seg_query(ls(_Index), _RangeL, mid, _Left, _Right);
    }
    if (mid < _Right) {
        Rret = seg_query(rs(_Index), mid + 1, _RangeR, _Left, _Right);
    }
    return push_up(Lret, Rret);
}

tree_node query(ll _u, ll _v) {
    std::set<ll, std::greater<ll>> s;
    while (chain_top[_u] != chain_top[_v]) {
        if (deep[chain_top[_u]] < deep[chain_top[_v]]) {
            std::swap(_u, _v);
        }
//        ret = push_up(ret, seg_query(1, 1, n, dfn_id[_u], dfn_id[chain_top[_u]]));
        tree_node ans = seg_query(1, 1, n, dfn_id[chain_top[_u]], dfn_id[_u]);
        s.insert(ans.biggest);
        s.insert(ans.next_biggest);
        _u = father[chain_top[_u]];
    }
    if (deep[_u] < deep[_v]) {
        std::swap(_u, _v);
    }
    tree_node ans = seg_query(1, 1, n, dfn_id[_v], dfn_id[_u]);
    s.insert(ans.biggest);
    s.insert(ans.next_biggest);
    ans.biggest = *s.begin();
    s.erase(s.begin());
    if (s.size()) {
        ans.next_biggest = *s.begin();
    }
    else {
        ans.next_biggest = -1;
    }
    return ans;
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
        ll u = readf<ll>(), v = readf<ll>();
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    init_tree();

    for (size_t i = 1; i <= n; i++) {
        readf(&value[i]);
        value_set.insert(value[i]);
        add(1, 1, n, dfn_id[i], value[i] + 1); //因为tree每个节点的初始化为-1，所以要+1
    }

    readf(&m);

    for (size_t i = 0; i < m; i++) {
        ll opt = readf<short>(), x = readf<ll>(), y = readf<ll>();
        if (opt == 0) {
            add(1, 1, n, dfn_id[x], y);
            value_set.erase(value_set.find(value[x]));
            value[x] += y;
            value_set.insert(value[x]);
        }
        else {
            tree_node ans = query(x, y);
            if (ans.next_biggest == -1) {
                puts("-1");
                continue;
            }
            value_set.erase(value_set.find(ans.biggest));
            value_set.erase(value_set.find(ans.next_biggest));
            ll max = *value_set.begin();
            ll sec_max = *(value_set.upper_bound(max));
            printf("%lld %lld\n", ans.next_biggest, sec_max);
            value_set.insert(ans.biggest);
            value_set.insert(ans.next_biggest);
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