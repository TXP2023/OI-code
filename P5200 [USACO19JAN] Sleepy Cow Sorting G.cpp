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

template<typename T>
class binary_indexed_tree {
public:
    binary_indexed_tree(ll _size);

    inline void add(ll x, ll d);

    inline T sum(ll x);
private:
    static ll lowbit(ll x) {
        return x & -x;
    }

    std::vector< T > tree_;
    ll size_;
};

template<typename T>
binary_indexed_tree<T>::binary_indexed_tree(ll _size) {
    tree_.resize(_size, 0);
    size_ = _size;
    return;
}

template<typename T>
inline void binary_indexed_tree<T>::add(ll x, ll d) {
    for (size_t i = x; i < size_; i += lowbit(i)) {
        tree_[i] += d;
    }
    return;
}

template<typename T>
inline T binary_indexed_tree<T>::sum(ll x) {
    int sum = 0;
    while (x > 0) {
        sum = sum + tree_[x];
        x = x - lowbit(x);
    }
    return sum;
}


int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

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