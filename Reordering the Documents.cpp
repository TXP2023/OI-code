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
#define MAXN          (5005)

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

ll seg[MAXN << 2];
ll arr[MAXN];
ll n, m, ans = 0;
clock_t start;

void build(ll p, ll lp, ll rp) {
    if (lp == rp) {
        seg[p] = arr[lp];
        return;
    }
    ll mid = (lp + rp) >> 1;
    build(p * 2, lp, mid);
    build(p * 2 + 1, mid + 1, rp);
    seg[p] = std::min(seg[p * 2], seg[p * 2 + 1]);
}

ll ask(ll p, ll lp, ll rp, ll l, ll r) {
    if (l <= lp && rp <= r) {
        return seg[p];
    }
    ll mid = (lp + rp) >> 1, res = 1e18;
    if (l <= lp) {
        res = std::min(res, ask(p * 2, lp, mid, l, r));
    }
    if (r > mid) {
        res = std::min(res, ask(p * 2 + 1, mid + 1, rp, l, r));
    }
    return res;
}

void dfs(ll cnt, std::vector<ll> a, std::vector<ll> b) {
    if (clock() - start > 3900) {
        puts("0");
        exit(0);
    }
    if (cnt == n + 1) {
        ++ans;
        return;
    }
    ll temp = ask(1, 1, n, cnt, n);
    if ((!a.empty() && temp < a.back()) && (!b.empty() && temp < b.back())) {
        return;
    }

    if ((a.empty() || arr[cnt] > a.back()) && a.size() < m) {
        a.push_back(arr[cnt]);
        dfs(cnt + 1, a, b);
        a.pop_back();
    }
    if ((b.empty() || arr[cnt] > b.back()) && b.size() < m) {
        b.push_back(arr[cnt]);
        dfs(cnt + 1, a, b);
        b.pop_back();
    }
    return;
}

int main() {

#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

    start = clock();

    fread(&n), fread(&m);

    for (size_t i = 1; i <= n; i++) {
        fread(&arr[i]);
    }

    build(1, 1, n);

    dfs(1, {}, {});



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