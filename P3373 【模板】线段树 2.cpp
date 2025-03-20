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
    ll sum;
    ll add;
    ll mul;

    tree_node() {
        add = 0;
        mul = 0;
        return;
    }
};

tree_node tree[MAXN << 2];
ll array[MAXN];
ll n, q, mode;

template<typename Type>
inline Type ls(Type _X) {
    return _X << 1;
}

template<typename Type>
inline Type rs(Type _X) {
    return _X << 1 | 1;
}

inline void Mode(ll _Index) {
    tree[_Index].sum %= mode;
    tree[_Index].mul %= mode;
    tree[_Index].add %= mode;
    return;
}

inline void add_multiply_tag(ll _Index, ll _Value) {
    _Value %= mode;
    tree[_Index].sum *= _Value;
    tree[_Index].mul *= _Value;
    tree[_Index].add *= _Value;
    return;
}

inline void add_add_tag(ll _Index, ll _Range_Left, ll _Rane_Right, ll _Value) {
    tree[_Index].sum += (_Rane_Right - _Range_Left + 1) * _Value;
    tree[_Index].add += _Value;
    Mode(_Index);
    return;
}

inline void push_up(ll _Index) {
    tree[_Index].sum = tree[ls(_Index)].sum + tree[rs(_Index)].sum;
    Mode(_Index);
    return;
}



inline void push_down(ll _Index, ll _RangeL, ll _RangeR) {
    if (tree[_Index].mul) {
        add_multiply_tag(ls(_Index), tree[_Index].mul);
        add_multiply_tag(rs(_Index), tree[_Index].mul);
        tree[_Index].mul = 0;
    }
    if (tree[_Index].add) {
        ll mid = (_RangeL + _RangeR) >> 1;
        add_add_tag(ls(_Index), _RangeL, mid, tree[_Index].add);
        add_add_tag(rs(_Index), mid + 1, _RangeR, tree[_Index].add);
        tree[_Index].add = 0;
    }
    return;
}

void build_tree(ll _Index, ll _RangeL, ll _RangeR) {
    if (_RangeL == _RangeR) {
        tree[_Index].sum = array[_RangeL];
        return;
    }
    ll mid = (_RangeL + _RangeR) >> 1;
    build_tree(ls(_Index), _RangeL, mid);
    build_tree(rs(_Index), mid + 1, _RangeR);
    push_up(_Index);
    return;
}

ll query(ll _Index, ll _RangeL, ll _RangeR, ll _Left, ll _Right) {
    if (_Left <= _RangeL && _RangeR <= _Right) {
        return tree[_Index].sum;
    }

    push_down(_Index, _RangeL, _RangeR);
    ll mid = (_RangeL + _RangeR) >> 1, sum = 0;
    if (_Left <= mid) {
        sum += query(ls(_Index), _RangeL, mid, _Left, _Right);
    }
    if (mid < _Right) {
        sum += query(rs(_Index), mid + 1, _RangeR, _Left, _Right);
    }
    return sum;
}

void update_add(ll _Index, ll _RangeL, ll _RangeR, ll _Left, ll _Right, ll _value) {
    if (_Left <= _RangeL && _RangeR <= _Right) {
        add_add_tag(_Index, _RangeL, _RangeR, _value);
        return;
    }

    push_down(_Index, _RangeL, _RangeR);
    ll mid = (_RangeL + _RangeR) >> 1, sum = 0;
    if (_Left <= mid) {
        update_add(ls(_Index), _RangeL, mid, _Left, _Right, _value);
    }
    if (mid < _Right) {
        update_add(rs(_Index), mid + 1, _RangeR, _Left, _Right, _value);
    }
    return;
}

void update_multiply(ll _Index, ll _RangeL, ll _RangeR, ll _Left, ll _Right, ll _value) {
    if (_Left <= _RangeL && _RangeR <= _Right) {
        add_multiply_tag(_Index, _value);
        return;
    }

    push_down(_Index, _RangeL, _RangeR);
    ll mid = (_RangeL + _RangeR) >> 1, sum = 0;
    if (_Left <= mid) {
        update_multiply(ls(_Index), _RangeL, mid, _Left, _Right, _value);
    }
    if (mid < _Right) {
        update_multiply(rs(_Index), mid + 1, _RangeR, _Left, _Right, _value);
    }
    return;
}

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    //TODO
    readf(&n), readf(&q), readf(&mode);

    for (size_t i = 1; i <= n; i++) {
        array[i] = readf<ll>() % mode;
    }

    build_tree(1, 1, n);

    while (q--) {
        ll ope = readf<short>(), left = readf<ll>(), right = readf<ll>(), value;
        switch (ope) {
        case 3:
            printf("%lld\n", query(1, 1, 1, left, right));
            break;
            value = readf<ll>();
        case 1:
            update_multiply(1, 1, n, left, right, value);
            break;
        case 2:
            update_add(1, 1, n, left, right, value);
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