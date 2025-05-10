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

//�������Ҫ��ʼ������deep�� father�� heavy_son, node_num����Ϊ��Чֵ
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
    chain_top[_u] = _top; //��¼��������ͷ
    //newSequence[id[_u]] = sequence[_u];
    if (heavy_son[_u] == -1) /*�����ΪҶ�ӽڵ� �������û���ض��� ��û�ж���*/ {
        return;
    }
    tree_init_heavy_chain(heavy_son[_u], _top, _u, _cnt); //�ȹ�������
    //����ʣ�µ���������
    for (size_t i = 0; i < graph[_u].size(); i++) {
        ll v = graph[_u][i];
        if (v != _father && v != heavy_son[_u]) /*����һ������� ����Ӳ����ض���Ҳ���Ǹ��ڵ�*/ {
            tree_init_heavy_chain(v, v, _u, _cnt); //�������������� ���������������� ���⽫�½�һ������ �����������ͷ������������
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
        //�����Ĺ����� ���ڵ�u�͵�v����һ�������� ��Ҫ����u�ƶ�����u������������ͷ�ĸ��ڵ㣬��������һ������
        if (deep[chain_top[_u]] < deep[chain_top[_v]]) {
            std::swap(_u, _v);
        }
        segment_updata_add(1, 1, n, id[chain_top[_u]] + 1, id[_u] + 1, _Value);
        //ע�����ԭ����u���ڵ�����
        _u = father[chain_top[_u]];
    }
    if (deep[_u] > deep[_v]) {
        std::swap(_u, _v);
    }
    if (_u == _v && _u == 0) {
        return;
    }
    segment_updata_add(1, 1, n, id[_u] + 2, id[_v] + 1, _Value); //��ʱu��v��ͬһ�������� �Ǿ�ֱ�������
    return;
}

inline void cover(ll _u, ll _v, ll _Value) {
    while (chain_top[_u] != chain_top[_v]) {
        //�����Ĺ����� ���ڵ�u�͵�v����һ�������� ��Ҫ����u�ƶ�����u������������ͷ�ĸ��ڵ㣬��������һ������
        if (deep[chain_top[_u]] < deep[chain_top[_v]]) {
            std::swap(_u, _v);
        }
        segment_updata_change(1, 1, n, id[chain_top[_u]] + 1, id[_u] + 1, _Value);
        //ע�����ԭ����u���ڵ�����
        _u = father[chain_top[_u]];
    }
    if (deep[_u] > deep[_v]) {
        std::swap(_u, _v);
    }
    if (_u == _v && _u == 0) {
        return;
    }
    segment_updata_change(1, 1, n, id[_u] + 2, id[_v] + 1, _Value); //��ʱu��v��ͬһ�������� �Ǿ�ֱ�������
    return;
}

inline void change(ll _k, ll _Value) {
    ll u = edges[_k].u, v = edges[_k].v;
    //deep[v]ҪС��deep[u]
    if (deep[v] > deep[u]) {
        std::swap(u, v);
    }
    segment_updata_change(1, 1, n, id[u] + 1, id[u] + 1, _Value); //��ʱu��v��ͬһ�������� �Ǿ�ֱ�������
    return;
}

inline ll query(ll _u, ll _v) {
    ll max = LLONG_MIN;
    while (chain_top[_u] != chain_top[_v]) {
        //�����Ĺ����� ���ڵ�u�͵�v����һ�������� ��Ҫ����u�ƶ�����u������������ͷ�ĸ��ڵ㣬��������һ������
        if (deep[chain_top[_u]] < deep[chain_top[_v]]) {
            std::swap(_u, _v);
        }
        max = std::max(max, segment_query(1, 1, n, id[chain_top[_u]] + 1, id[_u] + 1));
        //ע�����ԭ����u���ڵ�����
        _u = father[chain_top[_u]];
    }
    if (deep[_u] > deep[_v]) {
        std::swap(_u, _v);
    }
    if (_u == _v && _u == 0) {
        return max;
    }
    max = std::max(max, segment_query(1, 1, n, id[_u] + 2, id[_v] + 1)); //��ʱu��v��ͬһ�������� �Ǿ�ֱ�������
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

    //���ߵ�Ȩֵת�Ƶ�����������ӵ���Ƚ���Ľڵ���
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