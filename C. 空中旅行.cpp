//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
//
//      By txp2024 www.luogu.com.cn  TXP2023 www.github.com
// 
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

#pragma once
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <numeric>
#include <ctype.h>
#include <cstdarg>
#include <queue>
#include <climits>
#include <time.h>
#include <iostream>
#include <stdint.h>
#include <vector>

#define _FREAD        true
#define MAX_INF       0x7f7f7f7f7f7f7f7f
#define MAX_NUM_SIZE  35
#define MAXN          20

typedef long long int ll;
typedef unsigned long long int ull;

template<typename _T>
inline _T fpow(_T c, _T n, _T mod) {
    _T base = c, ret = 1;
    while (n) {
        if (n & 1) {
            ret = ret * base;
            ret %= mod;
        }
        base = base * base;
        base %= mod;
        n >>= 1;
    }
    return ret % mod;
}
//快读函数声明
template< typename Type >
inline Type fread(Type* p = nullptr);

//快速输出函数
template<typename Type>
inline void fwrite(Type x);

struct City {
    ll x, y, z;
};

#pragma once
#include <stdint.h>
template<typename Type, size_t _MAX_SIZE>
class Vector {
public:

    Vector() {
        size_ = 0;
        return;
    }

    template<typename T>
    inline Type& operator [] (T _Pos) {
        return arr_[_Pos];
    }

    inline void push_back(Type _Value) {
        arr_[size_++] = _Value;
        return;
    }

    inline size_t size() {
        return size_;
    }

    inline Type* begin() {
        return arr_;
    }

    inline Type* end() {
        return &arr_[size_];
    }

    inline void clera() {
        size_ = 0;
        return;
    }

private:
    Type arr_[_MAX_SIZE];
    size_t size_;
};

struct queData {
    ll tag, end, val; //状态和权值

    bool operator <(const queData& other)const {
        //return val > other.val;
        if (tag == other.tag) {
            return val > other.val;
        }
        return tag < other.tag;
    }
};

City c[MAXN];
ll dp[(1 << MAXN)][MAXN];
bool flag[(1 << MAXN)][MAXN];
Vector<ll, MAXN> v, v1, v2;
ll n;

ll get_path(City a, City b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y) + std::max(0ll, b.z - a.z);
}

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN
    ll n;
    fread(&n);
    for (ll i = 0; i < n; i++) {
        fread(&c[i].x), fread(&c[i].y), fread(&c[i].z);
    }

    memset(dp, 0x7f, sizeof dp);
    dp[1][0] = 0;
    for (size_t i = 1; i < (1 << n); i++) {
        for (size_t u = 0; u < n; u++) {
            if (dp[i][u] == MAX_INF || !(i & (1 << u))) {
                continue;
            }
            for (size_t v = 0; v < n; v++) {
                if (i & (1 << v)) {
                    continue;
                }
                ll temp = i | (1 << v);
                ll w = get_path(c[u], c[v]);
                if (dp[temp][v] > dp[i][u] + w) {
                    dp[temp][v] = dp[i][u] + w;
                }
            }
        }
    }
    ll ans = MAX_INF;
    ll temp = (1 << n) - 1;

    for (size_t u = 1; u < n; u++) {
        if (dp[temp][u] != MAX_INF) {
            ans = std::min(ans, dp[temp][u] + get_path(c[u], c[0]));
        }
    }

    printf("%lld\n", ans);
}

template< typename Type >
inline Type fread(Type* p) {
#if _FREAD
    Type ret = 0, sgn = 0, ch = getchar();
    while (!isdigit(ch)) {
        sgn |= ch == '-', ch = getchar();
    }
    while (isdigit(ch)) ret = ret * 10 + ch - '0', ch = getchar();
    if (p != nullptr) {
        *p = Type(sgn ? -ret : ret);
    }
    return sgn ? -ret : ret;
#else
    if (p == nullptr) {
        Type temp;
        p = &temp;
    }
    scanf("%lld", p);
    return *p;


#endif // _FREAD
}


template<typename Type>
inline void fwrite(Type x) {
    ll sta[MAX_NUM_SIZE];
    ll top = 0;
    do {
        sta[top++] = x % 10, x /= 10;
    } while (x);
    while (top) {
        putchar(sta[--top] + '0');
    }  // 48 是 '0'
    return;
}



/**
 *              ,----------------,              ,---------,
 *         ,-----------------------,          ,"        ,"|
 *       ,"                      ,"|        ,"        ,"  |
 *      +-----------------------+  |      ,"        ,"    |
 *      |  .-----------------.  |  |     +---------+      |
 *      |  |                 |  |  |     | -==----'|      |
 *      |  |                 |  |  |     |         |      |
 *      |  |  C:\>rp++       |  |  |     |`---=    |      |
 *      |  |                 |  |  |     |==== ooo |      ;
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