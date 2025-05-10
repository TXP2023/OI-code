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
#include <cstring>
#include <cstdarg>
#include <climits>
#include <time.h>
#include <iostream>
#include <stdint.h>
#include <time.h>

#define READ          false
#define MAX_INF       1e18
#define MAX_NUM_SIZE  35
#define MAXN          (int64_t)(1e5 + 5)

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
    ll value[2];
    ll left, right;

    std::pair< bool, int > tag;

    tree_node() {
        tag = std::pair< bool, int >{ false, 0 };
        return;
    }
};

std::vector<ll> graph[MAXN];
ll deep[MAXN], father[MAXN], heavy_son[MAXN], chain_top[MAXN], node_num[MAXN], id[MAXN];
const short int tree_root = 1;
tree_node tree[MAXN << 2];
ll n, id_cnt = 1, q;

inline void _init(ll _u, ll _father, ll _deep) {
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

inline void _init_have_chain(ll _u, ll _father, ll top, ll& _cnt) {
    id[_u] = _cnt++;
    chain_top[_u] = top;
    if (heavy_son[_u] == -1) {
        return;
    }
    _init_have_chain(heavy_son[_u], _u, top, _cnt);
    for (size_t i = 0; i < graph[_u].size(); i++) {
        if (graph[_u][i] != _father && graph[_u][i] != heavy_son[_u]) {
            _init_have_chain(graph[_u][i], _u, graph[_u][i], _cnt);
        }
    }
    return;
}

inline void init() {
    memset(heavy_son, -1, sizeof(heavy_son));
    _init(tree_root, 0, 1);
    _init_have_chain(tree_root, tree_root, tree_root, id_cnt);
    return;
}

template<typename Type>
Type ls(Type x) {
    return x << 1;
}

template<typename Type>
inline Type rs(Type x) {
    return x << 1 | 1;
}

inline void add_tag(ll _P, ll _value) {
    tree[_P].value[_value] = tree[_P].right - tree[_P].left + 1;
    tree[_P].value[_value ^ 1] = 0;
    tree[_P].tag = std::pair< bool, int >(true, _value);
    return;
}

inline void push_up(ll _P) {
    tree[_P].value[0] = tree[ls(_P)].value[0] + tree[rs(_P)].value[0];
    tree[_P].value[1] = tree[ls(_P)].value[1] + tree[rs(_P)].value[1];
    return;
}

inline void push_down(ll _P) {
    if (tree[_P].tag.first) {
        add_tag(ls(_P), tree[_P].tag.second);
        add_tag(rs(_P), tree[_P].tag.second);
        tree[_P].tag = { false, 0 };
    }
    return;
}

void build_tree(ll _P, ll _Lp, ll _Rp) {
    tree[_P].left = _Lp;
    tree[_P].right = _Rp;
    tree[_P].value[0] = _Rp - _Lp + 1;
    tree[_P].value[1] = 0;
    if (_Lp == _Rp) {
        return;
    }
    ll mid = (_Lp + _Rp) >> 1;
    build_tree(ls(_P), _Lp, mid);
    build_tree(rs(_P), mid + 1, _Rp);
    return;
}

void updata(ll _P, ll _Left, ll _Right, ll _Value) {
    if (_Left <= tree[_P].left && tree[_P].right <= _Right) {
        add_tag(_P, _Value);
        return;
    }

    push_down(_P);
    ll mid = (tree[_P].left + tree[_P].right) >> 1;
    if (_Left <= mid) {
        updata(ls(_P), _Left, _Right, _Value);
    }
    if (_Right > mid) {
        updata(rs(_P), _Left, _Right, _Value);
    }
    push_up(_P);
    return;
}

ll query(ll _P, ll _Left, ll _Right, ll _Value) {
    if (_Left <= tree[_P].left && tree[_P].right <= _Right) {
        return tree[_P].value[_Value];
    }

    push_down(_P);
    ll mid = (tree[_P].left + tree[_P].right) >> 1, ret = 0;
    if (_Left <= mid) {
        ret += query(ls(_P), _Left, _Right, _Value);
    }
    if (_Right > mid) {
        ret += query(rs(_P), _Left, _Right, _Value);
    }
    return ret;
}

inline ll install(ll _x) {
    ll ret = 0, _u = _x, _v = 1;
    while (chain_top[_u] != chain_top[_v]) {
        if (deep[chain_top[_u]] < deep[chain_top[_v]]) {
            std::swap(_u, _v);
        }
        ret += query(1, id[chain_top[_u]], id[_u], 0);
        updata(1, id[chain_top[_u]], id[_u], 1);
        _u = father[chain_top[_u]];
    }
    if (deep[_u] > deep[_v]) {
        std::swap(_u, _v);
    }
    ret += query(1, id[_u], id[_v], 0);
    updata(1, id[_u], id[_v], 1);
    return ret;
}

inline ll uninstall(ll _x) {
    ll ret = query(1, id[_x], id[_x] + node_num[_x] - 1, 1);
    updata(1, id[_x], id[_x] + node_num[_x] - 1, 0);
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

    for (size_t i = 2; i <= n; i++) {
        ll u = readf<ll>() + 1;
        graph[i].push_back(u);
        graph[u].push_back(i);
    }
    init();
    build_tree(1, 1, n);

    readf(&q);
    for (size_t i = 0; i < q; i++) {
        std::string str;
        ll x;
        std::cin >> str;
        readf(&x);
        ++x;
        if (str == "install") {
            printf("%lld\n", install(x));
        }
        else {
            printf("%lld\n", uninstall(x));
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