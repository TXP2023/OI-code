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

#define READ          false
#define MAX_INF       1e18
#define MAX_NUM_SIZE  35
#define MAXN          (int64_t)(5e4 + 5)

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

struct _tree {
    ll lmax, rmax, max, sum;

    _tree(ll _value) {
        lmax = _value;
        rmax = _value;
        max = _value;
        sum = _value;
        return;
    }
    _tree() {
        return;
    }
};

_tree seg_tree[MAXN << 2];
ll array[MAXN];
ll n, m;

template<typename Type>
inline Type ls(Type _X) {
    return _X << 1;
}

template<typename Type>
inline Type rs(Type _X) {
    return _X << 1 | 1;
}

inline _tree push_up(_tree _ltree, _tree _rtree) {
    _tree ret;
    ret.sum = _ltree.sum + _rtree.sum;
    ret.lmax = std::max(_ltree.lmax, _ltree.sum + _rtree.lmax);
    ret.rmax = std::max(_rtree.rmax, _rtree.sum + _ltree.rmax);
    ret.max = std::max(
        std::max(
            std::max(ret.rmax, ret.lmax), //位于左子节点的左边或右子节点的右边
            std::max(_ltree.max, _rtree.max)),
        _ltree.rmax + _rtree.lmax
    );
    return ret;
}

void build_tree(ll _P, ll _Lp, ll _Rp) {
    if (_Lp == _Rp) {
        seg_tree[_P] = _tree(array[_Lp]);
        return;
    }

    ll mid = (_Lp + _Rp) >> 1;
    build_tree(ls(_P), _Lp, mid);
    build_tree(rs(_P), mid + 1, _Rp);
    seg_tree[_P] = push_up(seg_tree[ls(_P)], seg_tree[rs(_P)]);
    return;
}

void update(ll _P, ll _Lp, ll _Rp, ll _Index, ll _Value) {
    if (_Lp == _Rp) {
        seg_tree[_P] = _tree(_Value);
        return;
    }

    ll mid = (_Lp + _Rp) >> 1;
    if (_Index <= mid) {
        update(ls(_P), _Lp, mid, _Index, _Value);
    }
    else {
        update(rs(_P), mid + 1, _Rp, _Index, _Value);
    }
    seg_tree[_P] = push_up(seg_tree[ls(_P)], seg_tree[rs(_P)]);
    return;
}

_tree query(ll _P, ll _Lp, ll _Rp, ll _Left, ll _Right) {
    if (_Left <= _Lp && _Rp <= _Right) {
        return seg_tree[_P];
    }

    ll mid = (_Lp + _Rp) >> 1;
    bool tag = false;
    _tree ret;
    if (_Left <= mid) {
        tag = true;
        ret = query(ls(_P), _Lp, mid, _Left, _Right);
    }
    if (mid < _Right) {
        if (!tag) {
            ret = query(rs(_P), mid + 1, _Rp, _Left, _Right);
        }
        else {
            _tree right_ret = query(rs(_P), mid + 1, _Rp, _Left, _Right);
            return push_up(ret, right_ret);
        }
    }
    return ret;
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

    for (size_t i = 1; i <= n; i++) {
        readf(&array[i]);
    }

    build_tree(1, 1, n);

    readf(&m);

    for (size_t i = 0; i < m; i++) {
        short ope = readf<short>();
        if (ope == 0) {
            ll x = readf<ll>(), y = readf<ll>();
            update(1, 1, n, x, y);
        }
        else {
            ll left = readf<ll>(), right = readf<ll>();
            printf("%lld\n", query(1, 1, n, left, right).max);
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