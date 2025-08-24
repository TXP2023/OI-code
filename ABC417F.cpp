//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
//
//      By txp2024 www.luogu.com.cn  TXP2023 www.github.com
// 
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

#pragma once
#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <numeric>
#include <ctype.h>
#include <cstdarg>
#include <climits>
#include <time.h>
#include <iostream>
#include <stdint.h>

#define _FREAD        true
#define MAX_INF       1e18
#define MAX_NUM_SIZE  35
#define MAXN          (size_t)(2e5+5)
#define LS(x)         ((x) << 1)
#define RS(x)         ((x) << 1 | 1)
#define MOD           998244353

typedef long long int ll;
typedef unsigned long long int ull;

//快读函数声明
template< typename Type >
inline Type fread(Type* p = nullptr);

//快速输出函数
template<typename Type>
inline void fwrite(Type x);

template<typename Type>
inline Type fpow(Type a, Type n, Type _Mod);

template<typename Type>
inline Type inv(Type val, Type mod) {
    return fpow(val, mod - 2, mod);
}

struct SegNode {
    ll sum;
    ll tag;//-1为无tag
    SegNode() : sum(0), tag(-1) {}
};

SegNode seg_tree[MAXN << 2];
ll arr[MAXN];
ll n, m;

inline void add_tag(ll pos, ll l, ll r, ll val) {
    seg_tree[pos].tag = val;
    seg_tree[pos].sum = (r - l + 1) * val % MOD;
    return;
}

inline void push_up(ll p) {
    seg_tree[p].sum = seg_tree[LS(p)].sum + seg_tree[RS(p)].sum;
    return;
}

inline void push_down(ll p, ll l, ll r) {
    if (seg_tree[p].tag == -1) {
        return;
    }
    ll mid = (l + r) >> 1;
    add_tag(LS(p), l, mid, seg_tree[p].tag);
    add_tag(RS(p), mid + 1, r, seg_tree[p].tag);
    seg_tree[p].tag = -1;
    return;
}

inline void build(ll pos = 1, ll l = 1, ll r = n) {
    if (l == r) {
        seg_tree[pos].sum = arr[l];
        return;
    }
    ll mid = (l + r) >> 1;
    build(LS(pos), l, mid);
    build(RS(pos), mid + 1, r);
    push_up(pos);
    return;
}

inline ll query(ll rangeL, ll rangeR, ll pos = 1, ll l = 1, ll r = n) {
    if (rangeL <= l && r <= rangeR) {
        return seg_tree[pos].sum % MOD;
    }
    push_down(pos, l, r);
    ll mid = (l + r) >> 1, res = 0;
    if (rangeL <= mid) {
        res += query(rangeL, rangeR, LS(pos), l, mid);
        res %= MOD;
    }
    if (mid + 1 <= rangeR) {
        res += query(rangeL, rangeR, RS(pos), mid + 1, r);
        res %= MOD;
    }
    return res;
}

inline void modify(ll rangeL, ll rangeR, ll val, ll pos = 1, ll l = 1, ll r = n) {
    if (rangeL <= l && r <= rangeR) {
        add_tag(pos, l, r, val);
        return;
    }
    push_down(pos, l, r);
    ll mid = (l + r) >> 1, res = 0;
    if (rangeL <= mid) {
        modify(rangeL, rangeR, val, LS(pos), l, mid);
    }
    if (mid + 1 <= rangeR) {
        modify(rangeL, rangeR, val, RS(pos), mid + 1, r);
    }
    push_up(pos);
    return;
}

int main() {

#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    fread(&n), fread(&m);

    for (size_t i = 1; i <= n; i++) {
        fread(&arr[i]);
    }

    build();
    while (m--) {
        ll l, r;
        fread(&l), fread(&r);
        ll sum = query(l, r), len = r - l + 1;
        ll temp = sum * inv(len, (ll)MOD) % MOD;
        modify(l, r, temp);
    }

    for (size_t i = 1; i <= n; i++) {
        printf("%lld ", query(i, i));
    }
    puts("");

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

template<typename Type>
inline Type fpow(Type a, Type n, Type _Mod) {
    Type base = a, ret = 1;
    while (n) {
        if (n & 1) {
            ret = ret * base;
            ret %= _Mod;
        }
        base = base * base;
        base %= _Mod;
        n >>= 1;
    }
    return ret % _Mod;
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