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

#define READ         false
#define MAX_INF      1e18
#define MAX_NUM_SIZE 35
#define MAXN         100000
//#define ls(x)        (x) << 2
//#define rs(x)        (x) << 2 | 1

typedef int ll;
typedef unsigned long long int unill;

//�����������
#if READ
template< typename T >
inline T readf();
#else
template< typename Type >
inline Type readf(Type* p = NULL);
#endif

//�����������
template<typename Type>
inline void writef(Type x);

struct tree_node {
    ll lc, rc;// "left color" and "right_color"
    ll sum;
    ll tag = 0;
};

ll deep[MAXN], father[MAXN], heavy_son[MAXN], chain_top[MAXN], node_num[MAXN], id[MAXN];
tree_node tree[MAXN << 2];
std::vector< ll > graph[MAXN];
ll colors[MAXN];
ll m, n, cnt = 0;

// �������Ҫ��ʼ������deep�� father�� heavy_son, node_num����Ϊ��Чֵ
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

inline ll ls(ll x) {
    return x << 1;
}

inline ll rs(ll x) {
    return x << 1 | 1;
}

inline void add_tag(ll _P, ll _Color) {
    tree[_P].lc = _Color;
    tree[_P].rc = _Color;
    tree[_P].sum = 1;
    tree[_P].tag = _Color;
}

inline void push_up(ll _P) {
    tree[_P].lc = tree[ls(_P)].lc;
    tree[_P].rc = tree[rs(_P)].rc;
    tree[_P].sum = tree[ls(_P)].sum + tree[rs(_P)].sum - (tree[ls(_P)].rc == tree[rs(_P)].lc);
    return;
}

inline void push_down(ll _P) {
    if (tree[_P].tag) {
        //tree[ls(_P)].tag = tree[_P].tag;
        //tree[rs(_P)].tag = tree[_P].tag;
        //tree[ls(_P)].sum = 1;
        //tree[rs(_P)].sum = 1;
        //tree[ls(_P)].lc = tree[_P].tag;
        //tree[ls(_P)].rc = tree[_P].tag;
        //tree[rs(_P)].lc = tree[_P].tag;
        //tree[rs(_P)].rc = tree[_P].tag;
        add_tag(ls(_P), tree[_P].tag);
        add_tag(rs(_P), tree[_P].tag);
        tree[_P].tag = 0;
    }
    return;
}

void build_tree(ll _P, ll _Lp, ll _Rp) {
    if (_Lp == _Rp) {
        ll p = std::find(id, id + n, _Lp - 1) - id;
        tree[_P].lc = colors[p];
        tree[_P].rc = colors[p];
        tree[_P].sum = 1;
        return;
    }

    ll mid = (_Lp + _Rp) >> 1;
    build_tree(ls(_P), _Lp, mid);
    build_tree(rs(_P), mid + 1, _Rp);
    push_up(_P);
    return;
}

void seg_updata(ll _Left, ll _Right, ll _Color, ll _P, ll _Lp, ll _Rp) {
    if (_Left <= _Lp && _Rp <= _Right) {
        add_tag(_P, _Color);
        return;
    }

    push_down(_P);
    ll mid = (_Lp + _Rp) >> 1;
    if (_Left <= mid) {
        seg_updata(_Left, _Right, _Color, ls(_P), _Lp, mid);
    }
    if (_Right > mid) {
        seg_updata(_Left, _Right, _Color, rs(_P), mid + 1, _Rp);
    }
    push_up(_P);
    return;
}

inline void updata(ll _u, ll _v, ll _Color) {
    while (chain_top[_u] != chain_top[_v]) {
        //�����Ĺ����� ���ڵ�u�͵�v����һ�������� ��Ҫ����u�ƶ�����u������������ͷ�ĸ��ڵ㣬��������һ������
        if (deep[chain_top[_u]] < deep[chain_top[_v]]) {
            std::swap(_u, _v);
        }
        seg_updata(id[chain_top[_u]] + 1, id[_u] + 1, _Color, 1, 1, n);
        //ע�����ԭ����u���ڵ�����
        _u = father[chain_top[_u]];
    }
    if (deep[_u] > deep[_v]) {
        std::swap(_u, _v);
    }
    seg_updata(id[_u] + 1, id[_v] + 1, _Color, 1, 1, n); //��ʱu��v��ͬһ�������� �Ǿ�ֱ�������
    return;
}

ll seg_query(ll _Left, ll _Right, ll _P, ll _Lp, ll _Rp) {
    if (_Left <= _Lp && _Rp <= _Right) {
        return tree[_P].sum;
    }

    push_down(_P);
    ll mid = (_Lp + _Rp) >> 1, sum = 0;
    if (_Left <= mid) {
        sum += seg_query(_Left, _Right, ls(_P), _Lp, mid);
    }
    if (_Right > mid) {
        if (sum > 0 && tree[ls(_P)].rc == tree[rs(_P)].lc) {
            --sum;
        }
        sum += seg_query(_Left, _Right, rs(_P), mid + 1, _Rp);
    }
    return sum;
}

ll seg_point_color_query(ll _Index, ll _P, ll _Lp, ll _Rp) {
    if (_Index == _Lp && _Lp == _Rp) {
        return tree[_P].lc;
    }

    push_down(_P);
    ll mid = (_Lp + _Rp) >> 1;
    if (_Index <= mid) {
        return seg_point_color_query(_Index, ls(_P), _Lp, mid);
    }
    else {
        return seg_point_color_query(_Index, rs(_P), mid + 1, _Rp);
    }
}

inline ll query(ll _u, ll _v) {
    ll sum = 0;
    while (chain_top[_u] != chain_top[_v]) {
        //�����Ĺ����� ���ڵ�u�͵�v����һ�������� ��Ҫ����u�ƶ�����u������������ͷ�ĸ��ڵ㣬��������һ������
        if (deep[chain_top[_u]] < deep[chain_top[_v]]) {
            std::swap(_u, _v);
        }
        sum += seg_query(id[chain_top[_u]] + 1, id[_u] + 1, 1, 1, n);
        if (id[father[chain_top[_u]]] + 1 != 0 &&
            seg_point_color_query(id[chain_top[_u]] + 1, 1, 1, n) == seg_point_color_query(id[father[chain_top[_u]]] + 1, 1, 1, n)) {
            --sum;
        }
        //ע�����ԭ����u���ڵ�����
        _u = father[chain_top[_u]];
    }
    if (deep[_u] > deep[_v]) {
        std::swap(_u, _v);
    }
    //sum += seg_query(id[_u] + 2, id[_v] + 1, 1, 1, n); //��ʱu��v��ͬһ�������� �Ǿ�ֱ�������
    return sum += seg_query(id[_u] + 1, id[_v] + 1, 1, 1, n); //��ʱu��v��ͬһ�������� �Ǿ�ֱ�������;
}

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    //TODO
    readf(&n), readf(&m);

    for (size_t i = 0; i < n; i++) {
        readf(&colors[i]);
    }

    for (size_t i = 0; i < n - 1; i++) {
        ll u = readf<ll>(), v = readf<ll>();
        graph[--u].push_back(--v);
        graph[v].push_back(u);
    }

    std::fill(heavy_son, heavy_son + n, -1);
    tree_init(0, -1, 1);
    tree_init_heavy_chain(0, 0, -1, cnt);

    build_tree(1, 1, n);

    for (size_t i = 0; i < m; i++) {
        char ch[5];
        scanf("%s", &ch);
        if (ch[0] == 'C') {
            ll u = readf<ll>() - 1, v = readf<ll>() - 1, color = readf<ll>();
            updata(u, v, color);
        }
        else {
            ll u = readf<ll>() - 1, v = readf<ll>() - 1;
            //printf("%lld\n", query(u, v));
            writef(query(u, v));
            puts("");
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