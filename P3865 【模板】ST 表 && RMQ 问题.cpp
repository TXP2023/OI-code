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
#include <time.h>
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

template<typename T, typename _RanIt>
class Sparse_table {
public:
    Sparse_table(size_t _size ,_RanIt _First, _RanIt _Last, T (*_func)(const T, const T));
    
    T query(size_t _Left, size_t _Right);
private:
    T (*func_)(const T, const T);
    size_t size_;
    std::vector< std::vector< T > > dp_;
};


std::vector< ll > v;
ll n, m;

template<typename T, typename _RanIt>
Sparse_table<T, _RanIt>::Sparse_table(size_t _size, _RanIt _First, _RanIt _Last, T(*_func)(const T, const T)) {
    func_ = _func;
    size_ = _size;
    ll* LOG = new ll[size_ + 1];
    LOG[0] = -1;
    for (size_t i = 1; i <= size_; i++) {
        LOG[i] = LOG[i >> 1] + 1;
    }
    ll p = (int)(log(double(size_)) / log(2.0));
    dp_.resize(n + 2, std::vector< ll >(p + 1, 0));
    _RanIt it = _First;
    for (size_t i = 1; i <= size_; i++, it++) {
        dp_[i][0] = *it;
    }
    for (size_t i = 1; i <= p; i++) {
        for (size_t j = 1; j + (1 << i) <= n + 1; j++) {
            dp_[j][i] = (*func_)(dp_[j][i - 1], dp_[j + (1 << (i - 1))][i - 1]);
        }
    }
    delete[] LOG;
    return;

}

template<typename T, typename _RanIt>
T Sparse_table<T, _RanIt>::query(size_t _Left, size_t _Right) {
    int k = (int)(log(double(_Right - _Left + 1)) / log(2.0));
    return (*func_)(dp_[_Left][k], dp_[_Right - (1 << k) + 1][k]);  //
}

ll max(ll a, ll b) {
    return (a > b) ? a : b;
}

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
    
#endif // _FREOPEN

    freopen("C:\\Users\\bobi2\\source\\repos\\OI-code\\output.txt", "w", stdout);

    clock_t start = clock();

    readf(&n), readf(&m);

    v.resize(n);
    for (size_t i = 0; i < n; i++) {
        readf(&v[i]);
    }
    
    Sparse_table<ll, std::vector< ll >::iterator> st(size_t(n), v.begin(), v.end(), max);

    for (size_t i = 0; i < m; i++) {
        size_t l = readf<size_t>(), r = readf<size_t>();
        printf("%lld\n", st.query(l, r));
        //writef(st.query(l, r));
       // puts("");
    }

    freopen("CON", "w", stdout);
    printf("%lld\n", clock() - start);
    
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