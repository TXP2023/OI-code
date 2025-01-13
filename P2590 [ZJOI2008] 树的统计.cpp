//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
//
//      By txp2024 www.luogu.com.cn  TXP2023 www.github.com
// 
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
#pragma once
#include <vector>
#include <string>
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

typedef long long int ll;
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

std::vector< std::vector< ll > > edge;
std::vector< ll > deep, father, chain_top, id, heavy_son, node_num;
std::vector< ll > weight, newWeight;
ll n, q, num = 0;

inline void init() {
    edge.resize(n);
    id.resize(n);
    id.shrink_to_fit();
    deep.resize(n);
    deep.shrink_to_fit();
    father.resize(n);
    father.shrink_to_fit();
    node_num.resize(n);
    node_num.shrink_to_fit();
    heavy_son.resize(n, -1);
    heavy_son.shrink_to_fit();
    chain_top.resize(n);
    chain_top.shrink_to_fit();
    weight.resize(n);
    weight.shrink_to_fit();
    newWeight.resize(n);
    newWeight.shrink_to_fit();
    return;
}

void tree_init(ll _u, ll _father, ll _deep) {
    deep[_u] = _deep;
    node_num[_u] = 1;
    father[_u] = _father;
    for (ll v : edge[_u]) {
        if (v != _father) {
            tree_init(v, _u, _deep + 1);
            node_num[_u] += node_num[v];
            if (heavy_son[_u] == -1 || node_num[heavy_son[_u]] < node_num[v]) {
                heavy_son[_u] = v;
            }
        }
    }
    return;
}

void tree_init_chain(ll _u, ll _father, ll _top) {
    chain_top[_u] = _top;
    id[_u] = num++;
    newWeight[id[_u]] = weight[_u];
    if (heavy_son[_u] == -1) {
        return;
    }
    tree_init_chain(heavy_son[_u], _u, _top);
    for (ll v : edge[_u]) {
        if (v != heavy_son[_u] && v != _father) {
            tree_init_chain(v, _u, v);
        }
    }
    return;
}

class Segnment_tree {
public:
    Segnment_tree(ll _size);

    ll query_lca_path_sum(ll _u, ll _v);

    ll query_lca_path_max(ll _u, ll _v);

    ll query_sum(ll _left, ll _right, ll _p, ll _lp, ll _rp);

    ll query_max(ll _left, ll _right, ll _p, ll _lp, ll _rp);

    void updata(ll _u, ll _t, ll _p, ll _lp, ll _rp);

    ll max_query(ll _p);

    ll sum_query(ll _p);
private:
    void build_tree(ll _p, ll _lp, ll _rp);

    inline void push_up(ll _p);

    //inline void push_down(ll _p, ll _lp, ll _rp);

    inline void add_tag(ll _p, ll _lp, ll _rp, ll _t);

    struct tree_data {
        ll max_w, sum_w;
    };

    struct tag_data {
        ll value;
        bool t;
    };
    
    std::vector< tree_data > tree_;
    //std::vector< tag_data > tag;

};

Segnment_tree::Segnment_tree(ll _size) {
    tree_.resize((_size << 2) + 1);
    //tag.resize((_size << 2) + 1, { 0, false });

    build_tree(1, 1, _size);

    return;
}

inline void Segnment_tree::push_up(ll _p) {
    tree_[_p].sum_w = tree_[_p * 2].sum_w + tree_[_p * 2 + 1].sum_w;
    tree_[_p].max_w = std::max(tree_[_p * 2].max_w, tree_[_p * 2 + 1].max_w);
    return;
}

ll Segnment_tree::max_query(ll _p) {
    return tree_[_p].max_w;
}

ll Segnment_tree::sum_query(ll _p) {
    return tree_[_p].sum_w;
}

inline void Segnment_tree::add_tag(ll _p, ll _lp, ll _rp, ll _t) {
    //tag[_p].t = true;
    //tag[_p].value = _t;
    tree_[_p] = { _t, (_rp - _lp + 1) * _t };
    return;
}

//inline void Segnment_tree::push_down(ll _p, ll _lp, ll _rp) {
//    if (tag[_p].t) {
//        tag[_p * 2] = tag[_p];
//        tag[_p * 2 + 1] = tag[_p];
//        
//        ll mid = (_lp + _rp) >> 1;
//        tree_[_p * 2] = { tag[_p].value, (mid - _lp + 1) * tag[_p].value };
//        tree_[_p * 2 + 1] = { tag[_p].value, (_rp - mid) * tag[_p].value };
//        tag[_p].t = false;
//    }
//    return;
//}

void Segnment_tree::build_tree(ll _p, ll _lp, ll _rp) {
    if (_lp == _rp) {
        tree_[_p].max_w = newWeight[_lp - 1];
        tree_[_p].sum_w = newWeight[_lp - 1];
        return;
    }

    ll mid = (_lp + _rp) >> 1;
    build_tree(_p * 2, _lp, mid);
    build_tree(_p * 2 + 1, mid + 1, _rp);
    push_up(_p);

    return;
}

ll Segnment_tree::query_lca_path_max(ll _u, ll _v) {
    ll ret = LLONG_MIN;
    while (chain_top[_u] != chain_top[_v]) {
        if (deep[chain_top[_u]] < deep[chain_top[_v]]) {
            std::swap(_u, _v);
        }
        ret = std::max(ret, query_max(id[chain_top[_u]] + 1, id[_u] + 1, 1, 1, n));
        _u = father[chain_top[_u]];
    }
    if (deep[_u] > deep[_v]) {
        std::swap(_u, _v);
    }

    return std::max(ret, query_max(id[_u] + 1, id[_v] + 1, 1, 1, n));
}

ll Segnment_tree::query_lca_path_sum(ll _u, ll _v) {
    ll ret = 0;
    while (chain_top[_u] != chain_top[_v]) {
        if (deep[chain_top[_u]] < deep[chain_top[_v]]) {
            std::swap(_u, _v);
        }
        ret += query_sum(id[chain_top[_u]] + 1, id[_u] + 1, 1, 1, n);
        _u = father[chain_top[_u]];
    }
    if (deep[_u] > deep[_v]) {
        std::swap(_u, _v);
    }

    return ret + query_sum(id[_u] + 1, id[_v] + 1, 1, 1, n);
}

ll Segnment_tree::query_sum(ll _left, ll _right, ll _p, ll _lp, ll _rp) {
    if (_left <= _lp && _right >= _rp) {
        return tree_[_p].sum_w;
    }

    //push_down(_p, _lp, _rp);
    ll mid = (_lp + _rp) >> 1, ret = 0;

    if (_left <= mid) {
        ret += query_sum(_left, _right, _p * 2, _lp, mid);
    }
    if (_right > mid) {
        ret += query_sum(_left, _right, _p * 2 + 1, mid + 1, _rp);
    }
    return ret;
}

ll Segnment_tree::query_max(ll _left, ll _right, ll _p, ll _lp, ll _rp) {
    if (_left <= _lp && _right >= _rp) {
        return tree_[_p].max_w;
    }

    //push_down(_p, _lp, _rp);
    ll mid = (_lp + _rp) >> 1, ret = LLONG_MIN;

    if (_left <= mid) {
        ret = std::max(query_max(_left, _right, _p * 2, _lp, mid), ret);
    }
    if (_right > mid) {
        ret = std::max(query_max(_left, _right, _p * 2 + 1, mid + 1, _rp), ret);
    }
    return ret;
}

void Segnment_tree::updata(ll _u, ll _t, ll _p, ll _lp, ll _rp) {
    if (_lp == _rp && _lp == _u) {
        add_tag(_p, _lp, _rp, _t);
        return;
    }

    //push_down(_p, _lp, _rp);
    ll mid = (_lp + _rp) >> 1;

    if (_u <= mid) {
        updata(_u, _t, _p * 2, _lp, mid);
    }
    if (_u > mid) {
        updata(_u, _t, _p * 2 + 1, mid + 1, _rp);
    }
    push_up(_p);
    return;
}

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

    readf(&n);

    init();

    edge.resize(n);
    for (size_t i = 0; i < n - 1; i++) {
        ll u = readf< ll >() - 1, v = readf< ll >() - 1;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }

    for (size_t i = 0; i < n; i++) {
        weight[i] = readf< ll >();
    }

    tree_init(0, 0, 1);
    tree_init_chain(0, 0, 0);

    Segnment_tree tree(n);

    readf(&q);
    while (q--) {
        //printf("num: %lld\n", q);
        std::string str;
        std::cin >> str;
        if (str == "CHANGE") {
            ll u = readf< ll >(), t = readf< ll >();
            tree.updata(id[u - 1] + 1, t, 1, 1, n);
        }
        else if (str == "QMAX") {
            ll u = readf< ll >() - 1, v = readf< ll >() - 1;
            printf("%lld\n", tree.query_lca_path_max(u, v));
        }
        else if(str == "QSUM") {
            ll u = readf< ll >() - 1, v = readf< ll >() - 1;
            printf("%lld\n", tree.query_lca_path_sum(u, v));
        }
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
    while (top) putchar(sta[--top] + '0');  // 48 是 '0'
    return;
}