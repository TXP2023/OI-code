//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
//
//      By txp2024 www.luogu.com.cn  TXP2023 www.github.com
// 
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
#pragma once
#include <vector>
#include <queue>
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

#define REVISE 1
#define QUERY  2

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

class Persistent_data_structure {
public:
    Persistent_data_structure(ll _size, ll _m);
    
    size_t updata(ll _pre, ll _lp, ll _rp, ll _loc, ll _x);

    ll query(ll _pre, ll _lp, ll _rp, ll _loc);

    std::vector< ll > root;
private:
    size_t build_tree(ll _lp, ll _rp);
    
    struct tree_node {
        size_t ls, rs;
        ll data;
    };

    std::deque< tree_node > tree;

    
};

std::vector< ll > vec;
ll n, m;

Persistent_data_structure::Persistent_data_structure(ll _size, ll _m) {
    root.resize(_m + 1, 0);
    build_tree(1, _size);
    return;
}

size_t Persistent_data_structure::build_tree(ll _lp, ll _rp) {
    tree.push_back(tree_node{0, 0, 0});
    ll _p = tree.size() - 1;

    if (_lp == _rp) {
        tree[_p].data = vec[_lp - 1];
        return _p;
    }

    ll mid = (_lp + _rp) >> 1;
    tree[_p].ls = build_tree(_lp, mid);
    tree[_p].rs = build_tree(mid + 1, _rp);
    return _p;
}

size_t  Persistent_data_structure::updata(ll _pre, ll _lp, ll _rp, ll _loc, ll _x) {
    tree.push_back({ 0, 0, 0 });
    ll _p = tree.size() - 1;

    if (_lp == _rp) {
        tree[_p].data = _x;
        return _p;
    }

    ll mid = (_lp + _rp) >> 1;
    tree[_p] = tree[_pre];
    if (_loc <= mid) {
        tree[_p].ls = updata(tree[_pre].ls, _lp, mid, _loc, _x);
    }
    else {
        tree[_p].rs = updata(tree[_pre].rs, mid + 1, _rp, _loc, _x);
    }
    return _p;
}

ll Persistent_data_structure::query(ll _pre, ll _lp, ll _rp, ll _loc) {
    if (_lp == _rp) {
        return tree[_pre].data;
    }

    ll mid = (_lp + _rp) >> 1;
    if (_loc <= mid) {
        return query(tree[_pre].ls, _lp, mid, _loc);
    }
    else {
        return query(tree[_pre].rs, mid + 1, _rp, _loc);
    }
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

    vec.resize(n);
    for (size_t i = 0; i < n; i++) {
        readf(&vec[i]);
    }

    Persistent_data_structure tree(n, m);
    for (size_t i = 1; i <= m; i++) {
        ll version = readf<ll>(), operate = readf<ll>(), loc = readf<ll>(), x;
        switch (operate) {
        case REVISE:
            x = readf<ll>();
            tree.root[i] = tree.updata(tree.root[version], 1, n, loc, x);
            break;
        case QUERY:
            tree.root[i] = tree.root[version];
            printf("%lld\n", tree.query(tree.root[version], 1, n, loc));
            //writef(tree.query(tree.root[version], 1, n, loc));
            //puts("");
            break;
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