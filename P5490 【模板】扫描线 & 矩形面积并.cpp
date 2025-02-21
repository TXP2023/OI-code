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
#include <iostream>
#include <stdint.h>
#include <initializer_list>

#define READ          false
#define MAX_INF       1000005
#define MAX_NUM_SIZE  35
//#define ls(x)         x << 1
//#define rs(x)         x << 1 | 1
#define DEBUG         true

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

struct line {
    ll y;
    ll left_x, right_x;
    ll in_out;
};

struct tree_node {
    ll l, r;
    ll sum; //被覆盖的次数
    ll lenght; //所代表区间的长度
};

line lines[(MAX_INF * 2)];
tree_node seg_tree[(MAX_INF * 2) << 2];
ll x[MAX_INF * 2];
ll n, size, ans = 0, cnt = 0;

inline ll ls(ll x) {
    return x << 1;
}

inline ll rs(ll x) {
    return x << 1 | 1;
}

inline void discretization(ll &_cnt) {
    std::sort(x + 1, x + _cnt + 1);
    _cnt = std::unique(x + 1, x + _cnt + 1) - x;
    for (size_t i = 1; i < n * 2; i++) {
        lines[i].left_x = std::lower_bound(x, x + _cnt, lines[i].left_x) - x;
        lines[i].right_x = std::lower_bound(x, x + _cnt, lines[i].right_x) - x - 1;
    }
    return;
}

inline void push_up(ll _P) {
    if (seg_tree[_P].sum) {
        seg_tree[_P].lenght = x[seg_tree[_P].r + 1] - x[seg_tree[_P].l];
    }
    else {
        seg_tree[_P].lenght = seg_tree[ls(_P)].lenght + seg_tree[rs(_P)].lenght;
    }
    return;
}

void build_tree(ll _P, ll _Lp, ll _Rp) {
    seg_tree[_P].l = _Lp;
    seg_tree[_P].r = _Rp;
    if (_Lp == _Rp) {
        return;
    }
    ll mid = (_Lp + _Rp) >> 1;
    build_tree(ls(_P), _Lp, mid);
    build_tree(rs(_P), mid + 1, _Rp);
    return;
}

void updata(ll _P, ll _Left, ll _Right, ll _Value) {
    if (_Left <= seg_tree[_P].l && seg_tree[_P].r <= _Right) {
        seg_tree[_P].sum += _Value;
        push_up(_P);
        return;
    }

    ll mid = (seg_tree[_P].l + seg_tree[_P].r) >> 1;
    if (_Left <= mid) {
        updata(ls(_P), _Left, _Right, _Value);
    }
    if (_Right > mid) {
        updata(rs(_P), _Left, _Right, _Value);
    }
    push_up(_P);
    return;
}

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

    readf(&n);

    //lines.resize(n * 2 + 1);
    //x.resize(n * 2 + 1);

    for (size_t i = 1; i <= n; i++) {
        ll x1 = readf<ll>(), y1 = readf<ll>(), x2 = readf<ll>(), y2 = readf<ll>();
        lines[i * 2 - 1] = { y1, x1, x2, 1 };
        lines[i * 2] = { y2, x1, x2, -1 };
        x[i * 2 - 1] = x1;
        x[i * 2] = x2;
    }
    cnt = n * 2;


    std::sort(lines + 1, lines + 2 * n + 1, [](const line a, const line b) ->bool {return a.y < b.y; });
    discretization(cnt);

    lines[0] = { 0, 0, 0 };
    //seg_tree.resize(((x.size() - 1) << 2) + 1);
    build_tree(1, 1, cnt - 1);
    for (size_t i = 1; i < n * 2; i++) {
        updata(
            1,
            lines[i].left_x,
            lines[i].right_x,
            lines[i].in_out
        );
        ans += seg_tree[1].lenght * (lines[i + 1].y - lines[i].y);
    }


    printf("%lld\n", ans);
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