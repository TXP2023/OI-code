#include <vector>
#include <stdio.h>
#include <algorithm>
#include <ctype.h>
#include <cstdarg>
#include <climits>
#include <iostream>
#include <stdint.h>
#include <set>
#include <initializer_list>

#define READ true

typedef int64_t ll;
typedef uint64_t unill;

#if READ
//函数前向声明
//快读函数
template< typename T >
inline T readf();
#else
template< typename T >
inline T readf(std::initializer_list< T* > li);
#endif

std::vector< std::vector< ll > > dp;
std::vector< std::vector< std::set< ll > > > cla;
std::vector< ll > v;
ll n;

int main() {
    freopen("input.txt", "r", stdin);

    n = readf< ll >();

    v.resize(n);
    dp.resize(n, std::vector< ll >(n));
    cla.resize(n, std::vector< std::set< ll > >(n));
    for (size_t i = 0; i < n; i++) {
        v[i] = readf< ll >();
        dp[i][i] = 1;
        cla[i][i].insert(i);
    }
    for (size_t length = 2; length < n; length++) {
        for (size_t brg = 0; brg + length < n; brg++) {

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
template< typename T >
inline T readf(std::initializer_list< T* > li) {
    T ret = 0, sgn = 0, ch = getchar();
    while (!isdigit(ch)) {
        sgn |= ch == '-', ch = getchar();
    }
    while (isdigit(ch)) ret = ret * 10 + ch - '0', ch = getchar();
    //va_list args;
    //va_start(args, num_arge);
    for (auto i = li.begin(); i != li.end(); i++) {
        *i = sgn ? -ret : ret;
    }
    //va_end(args);
    return sgn ? -ret : ret;
}
#endif