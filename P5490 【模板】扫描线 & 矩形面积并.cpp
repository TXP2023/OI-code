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

struct line {
    ll y;
    ll left_x, right_x;
    int in_out;

    bool operator <(const line other) const {
        return y > other.y;
    }
};

class Segnment_tree {
public:
    Segnment_tree(ll _size);
    
    inline ll sum();

    void updata(ll _left, ll _right, ll _change, ll _p, ll _lp, ll _rp);

private:
    std::vector< ll > tree;
    std::vector< bool > tag;
};

std::vector< line > lines;
std::vector< ll > x;
ll n, num, ans;

Segnment_tree::Segnment_tree(ll _size) {
    tree.resize((_size << 2) + 1, 0);
    tag.resize((_size << 2) + 1);

}

inline ll Segnment_tree::sum() {
    return tree[1];
}

void Segnment_tree::updata(ll _left, ll _right, ll _change, ll _p, ll _lp, ll _rp) {
    
}

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

    readf(&n);

    lines.resize((n << 1) + 1);
    lines[0].y = 0;

    for (size_t i = 0; i < n; i++) {
        ll x1 = readf< ll >(), y1 = readf< ll >(), x2 = readf< ll >(), y2 = readf< ll >();
        lines[(i+1) * 2] = line{ y1, x1, x2, 1 };
        x[(i + 1) * 2] = x1;
        lines[(i + 1) * 2 + 1] = line{ y2, x1, x2, -1 };
        x[(i + 1) * 2 + 1] = x2;
    }

    std::sort(x.begin(), x.end());
    std::sort(lines.begin(), lines.end());

    x.erase(std::unique(x.begin(), x.end()), x.end());
    num = x.size();

    Segnment_tree tree(num);

    for (size_t i = 1; i <= num; i++) {
        ans += tree.sum() * (lines[i].y - lines[i - 1].y);
        int l = std::lower_bound(x.begin(), x.end(), lines[i].left_x) - x.begin(),
            r = std::lower_bound(x.begin(), x.end(), lines[i].right_x) - x.begin();


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