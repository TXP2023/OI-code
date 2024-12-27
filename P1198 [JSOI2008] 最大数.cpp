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

class segment_tree {
public:
    segment_tree(int _size, int _mod);
    ~segment_tree();

    void updata(ll x, int p = 1, int lp = 1, int rp = -1);

    ll query(int left, int right, int p = 1, int lp = 1, int rp = -1);

    int t = 0, size = 0, length = 0, cnt = 1;
private:
    ll * tree;

    ll mod;

    inline void push_up(ll p);
};

segment_tree::segment_tree(int _size, int _mod) {
    //tree.resize((_size << 2) + 1, 0);
    //tree.shrink_to_fit();
    tree = new ll[(_size << 2) + 1];
    std::fill(tree, tree + (_size << 2) + 1, 0);
    mod = _mod;
    size = _size;
    return;
}

segment_tree::~segment_tree() {
    delete[] tree;
    return;
}

inline void segment_tree::push_up(ll p) {
    tree[p] = std::max(tree[p * 2], tree[p * 2 + 1]);
    tree[p] %= mod;
    return;
}

void segment_tree::updata(ll x, int p, int lp, int rp) {
    if (rp == -1) {
        rp = size;
    }

    if (lp == rp && lp == cnt) {
        tree[p] = x + t;
        tree[p] %= mod;
        length++;
        return;
    }

    int mid = (lp + rp) >> 1;
    if (cnt <= mid) {
        updata(x, p * 2, lp, mid);
    }
    if (cnt > mid) {
        updata(x, p * 2 + 1, mid + 1, rp);
    }

    push_up(p);
    return;
}

ll segment_tree::query(int left, int right, int p, int lp, int rp) {
    if (rp == -1) {
        rp = size;
    }

    if (left <= lp && right >= rp) {
        return tree[p];
    }

    ll max = LLONG_MIN;
    ll mid = (lp + rp) >> 1;
    if (mid >= left) {
        max = query(left, right, p * 2, lp, mid);
    }
    if (mid < right) {
        max = std::max(query(left, right, p * 2 + 1, mid + 1, rp), max);
    }

    return max;
}

ll n, m;

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

    readf(&n), readf(&m);

    segment_tree tree(2e5, m);

    while (n--) {
        char ch[5];
        scanf("%s", &ch);
        int l, n;
        switch (ch[0]) {
        case 'Q':
            if (tree.cnt == 1) {
                puts("0");
                continue;
            }
            l = readf<int>();
            tree.t = tree.query(tree.length - l + 1, tree.length);
            printf("%lld\n", tree.t);
            break;
        case 'A':
            n = readf<int>();
            tree.updata(n);
            ++tree.cnt;
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
    while (top) putchar(sta[--top] + 48);  // 48 是 '0'
    return;
}