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
#include <string>
#include <time.h>

#define READ          false
#define MAX_INF       1e18
#define MAX_NUM_SIZE  35
#define MAXN          (int64_t)(2e5 + 5)

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
    ll cnt[2];
    ll tag;
};

tree_node tree[MAXN << 2];
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

inline void push_up(ll _P) {
    tree[_P].cnt[0] = tree[ls(_P)].cnt[0] + tree[rs(_P)].cnt[0];
    tree[_P].cnt[1] = tree[ls(_P)].cnt[1] + tree[rs(_P)].cnt[1];
    return;
}

inline void add_tag(ll _P) {
    std::swap(tree[_P].cnt[0], tree[_P].cnt[1]);
    tree[_P].tag ^= 1;
    return;
}

inline void push_down(ll _P) {
    if (tree[_P].tag) {
        add_tag(ls(_P));
        add_tag(rs(_P));
        tree[_P].tag = 0;
    }
    return;
}

void build_tree(ll _P, ll _Lp, ll _Rp) {
    if (_Lp == _Rp) {
        tree[_P].cnt[array[_Lp]] = 1;
        tree[_P].cnt[array[_Lp] ^ 1] = 0;
        return;
    }

    ll mid = (_Lp + _Rp) >> 1;
    build_tree(ls(_P), _Lp, mid);
    build_tree(rs(_P), mid + 1, _Rp);
    push_up(_P);
    return;
}

void update(ll _P, ll _Lp, ll _Rp, ll _Left, ll _Right) {
    if (_Left <= _Lp && _Rp <= _Right) {
        add_tag(_P);
        return;
    }

    ll mid = (_Lp + _Rp) >> 1;
    push_down(_P);
    if (_Left <= mid) {
        update(ls(_P), _Lp, mid, _Left, _Right);
    }
    if (mid < _Right) {
        update(rs(_P), mid + 1, _Rp, _Left, _Right);
    }
    push_up(_P);
    return;
}

ll query(ll _P, ll _Lp, ll _Rp, ll _Left, ll _Right) {
    if (_Left <= _Lp && _Rp <= _Right) {
        return tree[_P].cnt[1];
    }

    ll mid = (_Lp + _Rp) >> 1, ret = 0;
    push_down(_P);
    if (_Left <= mid) {
        ret += query(ls(_P), _Lp, mid, _Left, _Right);
    }
    if (mid < _Right) {
        ret += query(rs(_P), mid + 1, _Rp, _Left, _Right);
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
    readf(&n), readf(&m);

    for (size_t i = 1; i <= n; i++){
        char ch;
        std::cin >> ch;
        array[i] = ch - '0';
    }

    build_tree(1, 1, n);
    for (size_t i = 0; i < m; i++) {
        ll opt = readf<short>(), left = readf<ll>(), right = readf<ll>();
        switch (opt) {
        case 0:
            update(1, 1, n, left, right);
            break;
        case 1:
            printf("%lld\n", query(1, 1, n, left, right));
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



/**
 *              ,----------------,              ,---------,
 *         ,-----------------------,          ,"        ,"|
 *       ,"                      ,"|        ,"        ,"  |
 *      +-----------------------+  |      ,"        ,"    |
 *      |  .-----------------.  |  |     +---------+      |
 *      |  |                 |  |  |     | -==----'|      |
 *      |  |  希望此代码无bug|  |  |     |         |      |
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