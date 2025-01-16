//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
//
//      By txp2024 www.luogu.com.cn  TXP2023 www.github.com
// 
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
#pragma once
#include <vector>
#include <set>
#include <map>
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

struct operate {
    ll x;
    short opt;
};

class Segnment_tree {
public:
    Segnment_tree(ll _size);

    void insert(ll _x, ll _p = 1, ll _lp = 1, ll _rp = -1);

    void remove(ll _x, ll _p = 1, ll _lp = 1, ll _rp = -1);

private:
    static inline ll ls(ll x);

    static inline ll rs(ll x);

    inline void push_up(ll _p);

    std::vector< ll > tree;

    ll value_cnt = 1, size;
};

std::vector< operate > operates;
std::vector< ll > dis_value;
ll n, cnt = 0, num;

inline void Discretization() /*离散化*/ {
    std::sort(dis_value.begin(), dis_value.end());
    dis_value.erase(std::unique(dis_value.begin(), dis_value.end()), dis_value.end());
    for (size_t i = 0; i < n; i++) {
        if (operates[i].opt != 4) {
            operates[i].x = std::lower_bound(dis_value.begin(), dis_value.end(), operates[i].x) - dis_value.begin();
        }
    }
    num = dis_value.size();
    return;
}

Segnment_tree::Segnment_tree(ll _size) {
    tree.resize((_size << 2) + 1, 0);
    size = _size;
}

inline void Segnment_tree::push_up(ll _p) {
    tree[_p] = tree[ls(_p)] + tree[rs(_p)];
    return;
}


inline void Segnment_tree::insert(ll _x, ll _p, ll _lp, ll _rp) {
    _rp = (_rp == -1) ? size : _rp;

    if (_lp == _x && _lp == _rp) {
        ++tree[_p];
        return;
    }

    ll mid = (_lp + _rp) >> 1;
    if (_x <= mid) {
        insert(_x, ls(_p), _lp, mid);
    }
    else {
        insert(_x, rs(_p), mid + 1, _rp);
    }

    push_up(_p);
    return;
}

inline void Segnment_tree::remove(ll _x, ll _p, ll _lp, ll _rp) {
    _rp = (_rp == -1) ? size : _rp;

    if (_lp == _x && _lp == _rp) {
        --tree[_p];
        return;
    }

    ll mid = (_lp + _rp) >> 1;
    if (_x <= mid) {
        remove(_x, ls(_p), _lp, mid);
    }
    else {
        remove(_x, rs(_p), mid + 1, _rp);
    }

    push_up(_p);
    return;
}

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

    readf(&n);

    operates.resize(n);
    dis_value.resize(n);
    for (operate &i : operates) {
        readf(&i.opt), readf(&i.x);
        if (i.opt != 4) {
            //dis_value.push_back(i.x);
            dis_value[cnt++] = i.x;
        }
    }

    dis_value.erase(dis_value.begin() + cnt, dis_value.end());
    Discretization();

    for (const operate ope : operates) {
        switch (ope.opt) {
        case 1:

            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
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