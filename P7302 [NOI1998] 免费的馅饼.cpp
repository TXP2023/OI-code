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
#define MAXN          (size_t)(1e5+5)

typedef long long int ll;
typedef unsigned long long int ull;

template<typename _T>
inline _T fpow(_T a, _T n, _T mod) {
    _T base = a, ret = 1;
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

struct Cookie {
    ll t, p, v, x; //掉落的时间 位置 分值

    Cookie() = default;

    Cookie(ll _t, ll _p, ll _v) : t(_t), p(_p), v(_v) {}
};

Cookie c[MAXN];
ll dp[MAXN], f[MAXN], tree[MAXN]; //dp[i] 表示在第i张馅饼落下时的最大收益
ll w, n, ans;

ll lowbit(ll x) {
    return x & (-x);
}

void dis() {
    ll temp[MAXN];
    memset(temp, 0, sizeof temp);
    for (size_t i = 1; i <= n; i++) {
        temp[i] = c[i].p + 2 * c[i].t;
    }

    std::sort(temp + 1, temp + 1 + n);
    for (size_t i = 1; i <= n; i++) {
        c[i].x = std::lower_bound(temp + 1, temp + 1 + n, c[i].p + 2 * c[i].t) - temp;
    }
    return;
}

void upd(ll x, ll a) {
    for (ll i = x; i <= n; i += lowbit(i)) {
        tree[i] = std::max(tree[i], a);
    }
}

ll ask(ll x) {
    ll res = 0;
    for (ll i = x; i; i = i - lowbit(i)) {
        res = std::max(res, tree[i]);
    }
    return res;
}

int main() {

#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    fread(&w), fread(&n);

    for (size_t i = 1; i <= n; i++) {
        ll t, p, v;
        fread(&t), fread(&p), fread(&v);
        c[i] = Cookie(t, p, v);
    }

    dis();

    std::sort(c + 1, c + 1 + n, [](const Cookie& a, const Cookie& b) {
        return  a.p - 2 * a.t >= b.p - 2 * b.t;
    });

    ans = c[1].v;
    for (size_t i = 1; i <= n; i++) {
        dp[i] = ask(c[i].x) + c[i].v;
        upd(c[i].x, dp[i]);
        ans = std::max(dp[i], ans);
    }

    printf("%lld\n", ans);


#ifdef _RUN_TIME
    printf("The running duration is not less than %ld ms\n", clock() - start);
#endif // _RUN_TIME
    return 0;
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
    int sta[MAX_NUM_SIZE];
    int top = 0;
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