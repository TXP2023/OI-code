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
#define N_TAG         -1

typedef int ll;
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
    int l, r;
    short ope; //0为升序 1为降序
};

struct tree_node {
    ll sum[2];
    ll tag;

    tree_node() {
        sum[0] = 0;
        sum[1] = 0;
        tag = N_TAG;
    }
};

std::vector< tree_node > tree;
std::vector< operate > operates;
std::vector< ll > array;
ll n, m, q;

template<typename Type>
inline Type ls(Type x) {
    return x << 1;
}

template<typename Type>
inline Type rs(Type x) {
    return x << 1 | 1;
}

inline void push_up(ll _P) {
    tree[_P].sum[0] = tree[ls(_P)].sum[0] + tree[rs(_P)].sum[0];
    tree[_P].sum[1] = tree[ls(_P)].sum[1] + tree[rs(_P)].sum[1];
    return;
}

inline void push_down(ll _P, ll _Lp, ll _Rp) {
    if (tree[_P].tag != N_TAG) {
        ll mid = (_Lp + _Rp) >> 1;
        tree[ls(_P)].sum[tree[_P].tag] = mid - _Lp + 1;
        tree[ls(_P)].sum[tree[_P].tag ^ 1] = 0;
        tree[rs(_P)].sum[tree[_P].tag] = _Rp - mid;
        tree[rs(_P)].sum[tree[_P].tag ^ 1] = 0;
        tree[ls(_P)].tag = tree[_P].tag;
        tree[rs(_P)].tag = tree[_P].tag;
        tree[_P].tag = N_TAG;
    }
    return;
}

void build(ll _P, ll _Lp, ll _Rp, ll _Value) {
    tree[_P].sum[0] = 0;
    tree[_P].sum[1] = 0;
    tree[_P].tag = N_TAG;
    if (_Lp == _Rp) {
        ++tree[_P].sum[array[_Lp - 1] >= _Value];
        return;
    }

    ll mid = (_Lp + _Rp) >> 1;
    build(ls(_P), _Lp, mid, _Value);
    build(rs(_P), mid + 1, _Rp, _Value);
    push_up(_P);
    return;
}

ll query(ll _Left, ll _Right, ll _P, ll _Lp, ll _Rp, ll _Value) {
    if (_Left <= _Lp && _Right >= _Rp) {
        return tree[_P].sum[_Value];
    }

    push_down(_P, _Lp, _Rp);
    ll mid = (_Lp + _Rp) >> 1, sum = 0;
    if (_Left <= mid) {
        sum += query(_Left, _Right, ls(_P), _Lp, mid, _Value);
    }
    if (_Right > mid) {
        sum += query(_Left, _Right, rs(_P), mid + 1, _Rp, _Value);
    }
    return sum;
}

void updata(ll _Left, ll _Right, ll _P, ll _Lp, ll _Rp, ll _Value) {
    if (_Left > _Right) {
        return;
    }
    if (_Left <= _Lp && _Rp <= _Right) {
        tree[_P].tag = _Value;
        tree[_P].sum[_Value] = _Rp - _Lp + 1;
        tree[_P].sum[_Value ^ 1] = 0;
        return;
    }

    push_down(_P, _Lp, _Rp);
    ll mid = (_Lp + _Rp) >> 1;
    if (_Left <= mid) {
        updata(_Left, _Right, ls(_P), _Lp, mid, _Value);
    }
    if (_Right > mid) {
        updata(_Left, _Right, rs(_P), mid + 1, _Rp, _Value);
    }
    push_up(_P);
    return;
}

inline bool check(ll _Value) {
    build(1, 1, n, _Value);

    for (int i = 0; i < m; i++) {
        if (operates[i].ope == 0) {
            ll sum = query(operates[i].l, operates[i].r, 1, 1, n, 0);
            updata(operates[i].l, operates[i].l + sum - 1, 1, 1, n, 0);
            updata(operates[i].l + sum, operates[i].r, 1, 1, n, 1);
        }
        else {
            ll sum = query(operates[i].l, operates[i].r, 1, 1, n, 1);
            updata(operates[i].l, operates[i].l + sum - 1, 1, 1, n, 1);
            updata(operates[i].l + sum, operates[i].r, 1, 1, n, 0);
        }
    }
    return query(q, q, 1, 1, n, 1) > 0;
}

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    
    readf(&n), readf(&m);

    array.resize(n);
    for (int i = 0; i < n; i++) {
        readf(&array[i]);
    }

    operates.resize(m);
    for (int i = 0; i < m; i++) {
        int l, r, ope;
        readf(&ope), readf(&l), readf(&r);
        operates[i] = operate{ l, r, short(ope) };
    }
    readf(&q);

    tree.resize((n << 2) + 1);
    ll Left = 1, Right = n;
    while (Left <= Right) {
        ll mid = (Left + Right) >> 1;
        if (check(mid)) {
            Left = mid + 1;
        }
        else {
            Right = mid - 1;
        }
    }

    printf("%lld\n", Right);

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
