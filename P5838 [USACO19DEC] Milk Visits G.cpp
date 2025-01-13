//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
//
//      By txp2024 www.luogu.com.cn  TXP2023 www.github.com
// 
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
#pragma once
#include <vector>
#include <set>
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

std::vector < std::vector< ll > > edge;
std::vector< ll > deep, father, chain_top, node_num, heavy_son, id;
std::vector< ll > breed, oldBreed;
ll n, m, num = 0;

inline void init() {
    deep.resize(n);
    deep.shrink_to_fit();
    father.resize(n);
    father.shrink_to_fit();
    chain_top.resize(n);
    chain_top.shrink_to_fit();
    node_num.resize(n);
    node_num.shrink_to_fit();
    heavy_son.resize(n, -1);
    heavy_son.shrink_to_fit();
    id.resize(n);
    id.shrink_to_fit();
    breed.resize(n);
    breed.shrink_to_fit();
    oldBreed.resize(n);
    oldBreed.shrink_to_fit();
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
    
    inline bool query_path(ll _u, ll _v, ll _b);
private:
    inline bool query(ll _left, ll _right, ll _x, ll _p, ll _lp, ll _rp);

    void build_tree(ll _p, ll _lp, ll _rp);

    inline void push_up(ll _p);

    std::vector< std::set< ll > >  tree_;
};
void Segnment_tree::build_tree(ll _p, ll _lp, ll _rp) {
    if (_lp == _rp ) {
        tree_[_p].insert(breed[_lp - 1]);
        return;
    }

    ll mid = (_lp + _rp) >> 1;
    build_tree(_p * 2, _lp, mid);
    build_tree(_p * 2 + 1, mid + 1, _rp);
    push_up(_p);

    return;
}

inline void Segnment_tree::push_up(ll _p) {
    std::set_union(
        tree_[_p * 2].begin(), tree_[_p * 2].end(), 
        tree_[_p * 2 + 1].begin(), tree_[_p * 2 + 1].end(), 
        std::inserter(tree_[_p], tree_[_p].begin())
    );
    return;
}

Segnment_tree::Segnment_tree(ll _size) {
    tree_.resize((_size << 2) + 1);

    build_tree(1, 1, n);

    return;
}

inline bool Segnment_tree::query_path(ll _u, ll _v, ll _b) {
    while (chain_top[_u] != chain_top[_v]) {
        if (deep[chain_top[_u]] < deep[chain_top[_v]]) {
            std::swap(_u, _v);
        }
        if (query(id[chain_top[_u]] + 1, id[_u] + 1, _b, 1, 1, n)) {
            return true;
        }
        _u = father[chain_top[_u]];
    }
    if (deep[_u] > deep[_v]) {
        std::swap(_u, _v);
    }
    
    return query(id[_u] + 1, id[_v] + 1, _b, 1, 1, n); 
}
inline bool Segnment_tree::query(ll _left, ll _right, ll _x, ll _p, ll _lp, ll _rp) {
    if (_left <= _lp && _right >= _rp) {
        return tree_[_p].count(_x);
    }

    ll mid = (_lp + _rp) >> 1;
    if (_left <= mid && query(_left, _right, _x, _p * 2, _lp, mid)) {
        return true;
    }
    if (_right > mid && query(_left, _right, _x, _p * 2 + 1, mid + 1, _rp)) {
        return true;
    }

    return false;
}

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

    readf(&n), readf(&m);
    
    init();

    for (size_t i = 0; i < n; i++) {
        oldBreed[i] = readf< ll >();
    }

    edge.resize(n);
    for (size_t i = 0; i < n - 1; i++) {
        ll u = readf< ll >() - 1, v = readf< ll >() - 1;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }

    

    tree_init(0, -1, 1);
    tree_init_chain(0, -1, 0);

    for (size_t i = 0; i < n; i++) {
        breed[id[i]] = oldBreed[i];
    }

    Segnment_tree farm(n);

    while (m--) {
        ll u = readf< ll >() - 1, v = readf< ll >() - 1, w = readf< ll >();
        printf("%d", farm.query_path(u, v, w));
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