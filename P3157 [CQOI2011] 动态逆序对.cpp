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
#define MAX_NUM_SIZE 3e5
#define MAXN         100000 
#define lowbit(x)    x&-x

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

struct tree_node {
    ll l, r;
    ll data;
};

tree_node segment_tree[MAXN];
std::vector< ll > root;
std::vector< ll > array;
std::vector< ll > value_index;
ll tree_cnt = 0;
ll n, m, ans = 0;

inline void init() {
    array.resize(n);
    value_index.resize(n, -1);
    root.resize(n + 1, 0);
    segment_tree[tree_cnt++] = { 0, 0, 0 };
    return;
}

void Segment_tree_add(ll _Index, ll _Value, ll &_Pre, ll _Left, ll _Right) {
    if (!_Pre) {
        _Pre = tree_cnt++;
    }
    
    segment_tree[_Pre].data += _Value;
    if (_Left != _Right) {
        ll mid = (_Left + _Right) >> 1;
        if (_Index <= mid) {
            Segment_tree_add(_Index, _Value, segment_tree[_Pre].l, _Left, mid);
        }
        else {
            Segment_tree_add(_Index, _Value, segment_tree[_Pre].r, mid + 1, _Right);
        }
    }
    return;
}



//找比_Index小的数的个数
ll segment_query(ll _P, ll _Lp, ll _Rp, ll _value_Begin, ll _value_End) {
    if (segment_tree[_P].data == 0 ) {
        return 0;
    }
    if (_Lp >= _value_Begin && _Rp <= _value_End) {
        return segment_tree[_P].data;
    }

    ll sum = 0, mid = (_Lp + _Rp) >> 1;
    if (_value_Begin <= mid) {
        sum += segment_query(segment_tree[_P].l, _Lp, mid, _value_Begin, _value_End);
    }
    if (_value_End > mid) {
        sum += segment_query(segment_tree[_P].r, mid + 1, _Rp, _value_Begin, _value_End);
    }
    return sum;
}

//查询位置区间range_Left ~ range_Right  中值位于value_Begin ~ value_End 区间的元素的数量
inline ll query(ll range_Left, ll range_Rright, ll value_Begin, ll value_End) {
    //现在在查询的是序列1~ (Value-1) 中比value大的和value+1 ~ n中比value小的
    if (range_Left > range_Rright || value_Begin > value_End) {
        return 0;
    }

    ll sum = 0;
    for (ll i = range_Rright; i > 0; i-=lowbit(i)) {
        sum += segment_query(root[i], 1, n, value_Begin, value_End);
    }
    for (ll i = range_Left - 1; i > 0; i -= lowbit(i)) {
        sum -= segment_query(root[i], 1, n, value_Begin, value_End);
    }

    return sum;
}

inline void add(ll _Index, ll _Value) {
    ans += query(1, _Index - 1, _Value + 1, n);
    for (ll i = _Index; i <= n; i += lowbit(i)) {
        Segment_tree_add(_Value, 1, root[i], 1, n);
    }
    return;
}

inline void remove(ll _Index, ll _Value) {
    ans -= query(1, _Index, _Value + 1, n);
    ans -= query(_Index + 2, n, 1, _Value - 1);
    for (size_t i = _Index + 1; i <= n; i += lowbit(i)) {
        Segment_tree_add(_Value, -1, root[i], 1, n);
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
    readf(&n), readf(&m);
    
    init();

    for (size_t i = 0; i < n; i++) {
        readf(&array[i]);
        value_index[array[i] - 1] = i;
        add(i + 1, array[i]);
    }

    for (size_t i = 0; i < m; i++) {
        printf("%lld\n", ans);
        ll value = readf<ll>();
        remove(value_index[value - 1], value);
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