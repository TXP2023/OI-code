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
#define inf 1e18
#define mod uint64_t(1000000007)

typedef long long int ll;
typedef unsigned long long int ull;

//快读函数声明
#if READ
template< typename T >
inline T readf();
#else
template< typename Type >
inline Type readf(Type* p = NULL);
#endif

struct one_limit {
    ll c, d;
    bool operator <(const one_limit other) const {
        return c < other.c;
    }
};

std::vector< one_limit > limits;
uint64_t t, n, m, v, ans;

uint64_t fast_pow(uint64_t a, uint64_t b) {
    b %= mod - 1;
    uint64_t s = 1;
    while (b) {
        if (b & 1)s *= a, s %= mod;
        a *= a;a %= mod;
        b >>= 1;
    }
    return s % mod;
}

inline uint64_t f(uint64_t i, uint64_t j) {
    return (fast_pow(v, 2 * (limits[j].c - limits[i].c)) - fast_pow(v, limits[j].c - limits[i].c - 1) * (v - 1) % mod + mod)%mod;
}

int main() {
    freopen("input.txt", "r", stdin);

    readf(&t);
    while (t--) {
        readf(&n), readf(&m), readf(&v);
        ans = 1;
        limits.resize(m);
        for (size_t i = 0; i < m; i++) {
            limits[i] = { readf< ll >(), readf< ll >() };
        }
        std::sort(limits.begin(), limits.end());
        for (size_t i = 0; i < m - 1; i++) {
            if (limits[i].c == limits[i + 1].c && limits[i].d != limits[i + 1].d) {
                puts("0");
                goto loop;
            }
        }

        //对于一元限制所影响的部分
        for (size_t i = 0; i < m - 1; i++) {
            if (limits[i].c != limits[i + 1].c) {
                ans *= f(i, i + 1);
                ans %= mod;
            }
        }

        //对于一元限制不影响的部分
        ans *= fast_pow(v, 2 * (limits.front().c - 1));
        ans %= mod;
        ans *= fast_pow(v, 2 * (n - limits.back().c));
        ans %= mod;

        printf("%llu\n", ans);
    loop:;
        limits.clear();
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