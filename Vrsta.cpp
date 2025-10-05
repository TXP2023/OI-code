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
#include <map>

#define _FREAD        true
#define MAX_INF       0x7f7f7f7f7f7f7f7f
#define MAX_NUM_SIZE  35
#define MAX_VAL       (ll)(200005)
#define MAXN          (ll)(200005)
#define LS(x)         ((x) << 1)
#define RS(x)         ((x) << 1 | 1)

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

ll seg[MAX_VAL << 2];
ll n, cnt;
std::map<ll, ll> map, reMap;

struct Task {
    ll h, tot;
};

Task tasks[MAXN];
ll size;

void dis() {
    ll arr[MAXN] = { 0 };
    for (size_t i = 1; i <= n; i++) {
        arr[i] = tasks[i].h;
    }

    std::sort(arr + 1, arr + 1 + n);
    size = std::unique(arr + 1, arr + 1 + n) - (arr + 1);
    for (size_t i = 1; i <= size; i++) {
        map[arr[i]] = i;
        reMap[i] = arr[i];
    }

    for (size_t i = 1; i <= n; i++) {
        tasks[i].h = map[tasks[i].h];
    }
    return;
}

void ins(ll p, ll lp, ll rp, ll pos, ll val) {
    if (lp == rp) {
        seg[p] += val;
        return;
    }
    ll mid = (lp + rp) >> 1;
    if (pos <= mid) {
        ins(LS(p), lp, mid, pos, val);
    }
    else {
        ins(RS(p), mid + 1, rp, pos, val);
    }
    seg[p] = seg[LS(p)] + seg[RS(p)];
}

ll query(ll p, ll lp, ll rp, ll pos) {
    if (lp == rp) {
        return lp;
    }
    ll mid = (lp + rp) >> 1;
    if (pos <= seg[LS(p)]) {
        return query(LS(p), lp, mid, pos);
    }
    else {
        return query(RS(p), mid + 1, rp, pos - seg[LS(p)]);
    }
}

int main() {

#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    fread(&n);

    for (size_t i = 1; i <= n; i++) {
        ll h, tot;
        fread(&h), fread(&tot);
        tasks[i] = { h, tot };
    }

    dis();

    for (size_t i = 1; i <= n; i++) {
        ll h = tasks[i].h, tot = tasks[i].tot;
        cnt += tot;
        ins(1, 1, size, h, tot);
        if (cnt & 1) {
            // 存在奇数个人
            printf("%lld\n", reMap[query(1, 1, size, (cnt >> 1) + 1)]);
        }
        else {
            printf("%lld\n", reMap[query(1, 1, size, (cnt >> 1))]);
        }
    }



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
