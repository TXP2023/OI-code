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

struct line {
    ll y;
    ll left_x, right_x;
    ll in_out;
};

class Segment_tree {
public:
    Segment_tree(ll _Size);
    
    inline void updata(ll _Left, ll _Right, ll _P, ll _Lp, ll _Rp, ll _InOut);

    inline ll sum();
private:
    struct tag_data {
        bool tag_bool;
        ll in_out;
    };
    
    std::vector< ll > tree;
    std::vector< tag_data > tag;

    inline ll ls(ll _P);

    inline ll rs(ll _P);

    inline void add_tag(ll _P, ll _Lp, ll _Rp, ll _InOut);

    inline void push_down(ll _P, ll _Lp, ll _Rp);

    inline void push_up(ll _P);
};

std::deque< line > lines;
std::vector< ll > x;
ll n, size, ans = 0;

inline void discretization() {
    std::sort(x.begin(), x.end());
    x.erase(std::unique(x.begin(), x.end()), x.end());
    //for (size_t i = 0; i < lines.size(); i++) {
    //    lines[i].left_x = std::lower_bound(x.begin(), x.end(), lines[i].left_x) - x.begin();
    //    lines[i].right_x = std::lower_bound(x.begin(), x.end(), lines[i].right_x) - x.begin();
    //}
    x.erase(x.begin());
    size = x.size();
    return;
}

Segment_tree::Segment_tree(ll _Size) {
    tree.resize((_Size << 2) + 1, 0);
    tag.resize((_Size << 2) + 1, { false, 0 });
}

inline ll Segment_tree::ls(ll _P) {
    return _P << 1;
}

inline ll Segment_tree::rs(ll _P) {
    return (_P << 1) + 1;
}

inline void Segment_tree::push_down(ll _P, ll _Lp, ll _Rp) {
    if (tag[_P].tag_bool) {
        ll mid = (_Lp + _Rp) >> 1;
        add_tag(ls(_P), _Lp, mid, tag[_P].in_out);
        add_tag(rs(_P), mid + 1, _Rp, tag[_P].in_out);
        tag[_P].tag_bool = false;
        tag[_P].in_out = 0;
    }
    return;
}

inline void Segment_tree::push_up(ll _P) {
    tree[_P] = tree[ls(_P)] + tree[rs(_P)];
    return;
}


inline void Segment_tree::updata(ll _Left, ll _Right, ll _P, ll _Lp, ll _Rp, ll _InOut) {
    if (_Left <= _Lp && _Right >= _Rp) {
        add_tag(_P, _Lp, _Rp, _InOut);
        return;
    }

    push_down(_P, _Lp, _Rp);
    ll mid = (_Lp + _Rp) >> 1;
    if (_Left <= mid) {
        updata(_Left, _Right, ls(_P), _Lp, mid, _InOut);
    }
    if (_Right > mid) {
        updata(_Left, _Right, rs(_P), mid + 1, _Rp, _InOut);
    }
    push_up(_P);
}

inline void Segment_tree::add_tag(ll _p, ll _Lp, ll _Rp, ll _InOut) {
    tag[_p].tag_bool = true;
    tag[_p].in_out += _InOut;
    if (tag[_p].in_out) {
        tree[_p] = x[_Rp] - x[_Lp - 1];
    }
    else {
        tree[_p] = 0;
    }
    return;
}

inline ll Segment_tree::sum() {
    return tree[1];
}


int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

    readf(&n);

    lines.resize(n * 2 + 1);
    x.resize(n * 2 + 1);

    for (size_t i = 1; i <= n; i++) {
        ll x1 = readf<ll>(), y1 = readf<ll>(), x2 = readf<ll>(), y2 = readf<ll>();
        lines[i * 2 - 1] = { y1, x1, x2, 1 };
        lines[i * 2] = { y2, x1, x2, -1 };
        x[i * 2 - 1] = x1;
        x[i * 2] = x2;
    }

    std::sort(lines.begin(), lines.end(), [](line a, line b) ->bool {return a.y < b.y; });
    discretization();
    

    Segment_tree tree(size);


    //开始扫描
    lines[0] = { 0,0,0 };
    for (size_t i = 1; i <= n * 2; i++) {
        ans += tree.sum() * (lines[i].y - lines[i - 1].y);
        ll L = std::lower_bound(x.begin(), x.end(), lines[i].left_x) - x.begin() + 1,
           R = std::lower_bound(x.begin(), x.end(), lines[i].right_x) - x.begin();

        tree.updata(L, R, 1, 1, size, lines[i].in_out);

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
