//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
//
//      By txp2024 www.luogu.com.cn  TXP2023 www.github.com
// 
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
/*
����һ����,��ʼÿһ�����ȨֵΪ0
��2�ֲ���
1. �����u~v��·����Ȩֵ����max_value�ĵ����������u~v·���Ͻڵ�����
2. ����T��Ȩֵ��1

Ȩֵ����Ϊ2*1e5

*/
#pragma once
#include <vector>
#include <set>
#include <stdio.h>
#include <algorithm>
#include <ctype.h>
#include <cstdarg>
#include <climits>
#include <cstring>
#include <time.h>
#include <iostream>
#include <stdint.h>
#include <time.h>

#define READ          false
#define MAX_INF       1e18
#define MAX_NUM_SIZE  35
#define MAXN          (int64_t)(2e5 + 5)

typedef int ll;
typedef unsigned long long int unill;

//�����������
#if READ
template< typename T >
inline T readf();
#else
template< typename Type >
inline Type readf(Type* p = nullptr);
#endif

//�����������
template<typename Type>
inline void writef(Type x);

//�ɳ־û�Ȩֵ�߶���

struct node {
    ll ls, rs;
    ll cnt; //���ֵ�Ĵ���

    node() {
        ls = 0;
        rs = 0;
        cnt = 0;
        return;
    }

};

struct operate {
    ll u, v, max_value;
    ll id;

    operate(ll _id, ll _u, ll _v, ll _max_value) {
        id = _id;
        u = _u;
        v = _v;
        max_value = _max_value;
        return;
    }
    operate() {
        return;
    }
};

std::vector<ll> graph[MAXN];
std::vector<operate> operates;
uint64_t root[MAXN];
ll deep[MAXN], father[MAXN], heavy_son[MAXN], chain_top[MAXN], node_num[MAXN], id[MAXN];
ll value[MAXN];
node tree[MAXN * 50];
ll n, q, tree_root, tree_cnt = 1, cnt = 0;

namespace Tree {
    //��ʼ��������Ҫ�Ľڵ�id���
    ll id_cnt = 1;

    //��ʼ����
    inline void init();

    //��ʼ��������ȣ����ڵ㣬�ڵ��������ض���
    inline void _init(ll _u, ll _father, ll _deep);

    //��ʼ����������
    inline void _init_have_chain(ll _u, ll _father, ll _top, ll& _cnt);

    //����ֵΪһ��pair��firstΪ;����������� secondΪȨֵ����_max_value������
    inline uint64_t query(ll _u, ll _v, ll _max_value);

    inline uint64_t get_lca(ll _u, ll _v);
}

namespace Persistent_data_structure {
    inline ll update(ll _pre, ll _lp, ll _rp, ll _Index);
    inline ll query(ll root_left, ll root_right, ll _lp, ll _rp, ll _max_value);
}

inline void Tree::init() {
    memset(heavy_son, -1, sizeof(heavy_son));
    Tree::_init(tree_root, 0, 1);
    Tree::_init_have_chain(tree_root, tree_root, tree_root, id_cnt);
    return;
}

inline void Tree::_init(ll _u, ll _father, ll _deep) {
    deep[_u] = _deep;
    father[_u] = _father;
    node_num[_u] = 1;
    for (size_t i = 0; i < graph[_u].size(); i++) {
        if (graph[_u][i] == _father) {
            continue;
        }
        ll v = graph[_u][i];
        _init(v, _u, _deep + 1);
        node_num[_u] += node_num[v];
        if (heavy_son[_u] == -1 || node_num[heavy_son[_u]] < node_num[v]) {
            heavy_son[_u] = v;
        }
    }
    return;
}

inline void Tree::_init_have_chain(ll _u, ll _father, ll top, ll& _cnt) {
    id[_u] = _cnt++;
    chain_top[_u] = top;
    if (heavy_son[_u] == -1) {
        return;
    }
    Tree::_init_have_chain(heavy_son[_u], _u, top, _cnt);
    for (size_t i = 0; i < graph[_u].size(); i++) {
        if (graph[_u][i] != _father && graph[_u][i] != heavy_son[_u]) {
            Tree::_init_have_chain(graph[_u][i], _u, graph[_u][i], _cnt);
        }
    }
    return;
}

uint64_t Tree::query(ll _u, ll _v, ll _max_value) {
    ll ret = 0;
    while (chain_top[_u] != chain_top[_v]) {
        if (deep[chain_top[_u]] < deep[chain_top[_v]]) {
            std::swap(_u, _v);
        }
        ret += std::max(Persistent_data_structure::query(root[id[father[chain_top[_u]]]], root[id[_u]], 0, MAXN, _max_value), 0);
        _u = father[chain_top[_u]];
    }
    if (deep[_u] > deep[_v]) {
        std::swap(_u, _v);
    }
    ret += Persistent_data_structure::query(root[id[father[_u]]], root[id[_v]], 0, MAXN, _max_value);
    return ret;
}

uint64_t Tree::get_lca(ll _u, ll _v) {
    ll ret = 0;
    while (chain_top[_u] != chain_top[_v]) {
        if (deep[chain_top[_u]] < deep[chain_top[_v]]) {
            std::swap(_u, _v);
        }
        _u = father[chain_top[_u]];
    }
    if (deep[_u] > deep[_v]) {
        std::swap(_u, _v);
    }
    return _u;
}

inline ll Persistent_data_structure::update(ll _pre, ll _lp, ll _rp, ll _Index) {
    ll p = tree_cnt++;
    tree[p] = tree[_pre];
    tree[p].cnt++;
    if (_lp != _rp) {
        ll mid = (_lp + _rp) >> 1;
        if (_Index <= mid) {
            tree[p].ls = update(tree[_pre].ls, _lp, mid, _Index);
        }
        else {
            tree[p].rs = update(tree[_pre].rs, mid + 1, _rp, _Index);
        }
    }
    return p;
}

inline ll Persistent_data_structure::query(ll root_left, ll root_right, ll _lp, ll _rp, ll _max_value) {
    //��ǰ�ڵ�����ʾ�����ֵ����С��_max_value
    if (_rp < _max_value) {
        return tree[root_right].cnt - tree[root_left].cnt;
    }
    if (_lp >= _max_value || tree[root_right].cnt - tree[root_left].cnt == 0) {
        return 0;
    }

    ll mid = (_lp + _rp) >> 1;
    //���ڽ������������ ��ô���_max_value����λ����������ڻ������������Сֵ��С
    //����������Сֵ����С��_max_value
    ll ret = query(tree[root_left].ls, tree[root_right].ls, _lp, mid, _max_value);

    if (mid + 1 < _max_value) {
        //����������Сֵ��_max_value
        //����������
        ret += query(tree[root_left].rs, tree[root_right].rs, mid + 1, _rp, _max_value);
    }
    return ret;
}

inline void build_tree(ll _u, ll _father) {
    root[id[_u]] = Persistent_data_structure::update(root[id[father[_u]]], 0, MAXN, value[_u]);
    for (size_t i = 0; i < graph[_u].size(); i++) {
        //if (g_size != graph[1521].size()) {
        //    printf(" error debug :  _u: %lld  i: %lld graph[_1521].size()�� %lld \n", _u, i, graph[1521].size());
        //    printf("debug: graph[_u][i]��%lld  \n", graph[_u][i]);
        //}
        if (graph[_u][i] != _father) {
            build_tree(graph[_u][i], _u);
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

    //TODO
    readf(&n);

    //graph.resize(n + 5);

    for (size_t i = 1; i <= n; i++) {
        ll u = readf<ll>();
        if (u) {
            graph[i].push_back(u);
            graph[u].push_back(i);
        }
        else {
            tree_root = i;
        }
    }
    //g_size = graph[1521].size();
    Tree::init();
    //g_size = graph[1521].size();

    operates.resize(readf(&q));
    std::fill(value, value + n + 1, q);
    for (size_t i = 0; i < q; i++) {
        ll u, v, max_value;
        switch (readf<short>()) {
        case 2:
            readf(&u);
            if (value[u] == q) {
                value[u] = i;
            }
            break;
        case 1:
            readf(&u), readf(&v), readf(&max_value);
            operates[cnt++] = operate(i, u, v, max_value);
        }
    }

    //printf("%lld\n", graph[1521][3]);
    build_tree(tree_root, -1);
    for (size_t i = 0; i < cnt; i++) {
        ll id = operates[i].id, u = operates[i].u, v = operates[i].v, max_value = operates[i].max_value;
        ll lca = Tree::get_lca(u, v);
        printf("%lld ", deep[u] + deep[v] - 2 * deep[father[lca]] - 1);
        if (ll(id - max_value - 1) <= 0) {
            puts("0");
            continue;
        }

        printf("%lld\n", Tree::query(u, v, id - max_value));
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
    while (top) putchar(sta[--top] + '0');  // 48 �� '0'
    return;
}



/**
 *              ,----------------,              ,---------,
 *         ,-----------------------,          ,"        ,"|
 *       ,"                      ,"|        ,"        ,"  |
 *      +-----------------------+  |      ,"        ,"    |
 *      |  .-----------------.  |  |     +---------+      |
 *      |  |                 |  |  |     | -==----'|      |
 *      |  |  ϣ���˴�����bug|  |  |     |         |      |
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