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
#define MAXE          (size_t)(1e5+5)
#define MAXN          (size_t)(5e4+5)
#define WHITE         0

typedef long long int ll;
typedef unsigned long long int ull;

//快读函数声明
template< typename Type >
inline Type readf(Type* p = nullptr);

//快速输出函数
template<typename Type>
inline void writef(Type x);

struct Edge {
    int color;
    ll u, v, weight;
};

Edge edges[MAXE];
ll set[MAXN];
ll n, m, need;

inline ll find_set(ll x) {
    if (set[x] == x) {
        return x;
    }
    else {
        return set[x] = find_set(set[x]);
    }
}

inline bool same_set(ll x, ll y) {
    x = find_set(x), y = find_set(y);
    return x == y;
}

inline void merge_set(ll x, ll y) {
    x = find_set(x), y = find_set(y);
    set[x] = y;
    return;
}

//first权值 second白色边数量
inline std::pair<ll, ll> Kruskal() {
    std::iota(set + 1, set + 1 + n, 1);
    ll cnt = 0, tot = 0, sum = 0;
    std::sort(edges + 1, edges + 1 + m, [](const Edge& a, const Edge& b) {
        if (a.weight == b.weight) {
            return a.color < b.color;
        }
        return a.weight < b.weight;
    });
    for (size_t i = 1; i <= m; i++) {
        if (!same_set(edges[i].u, edges[i].v)) {
            cnt += (edges[i].color == WHITE);
            sum += edges[i].weight;
            ++tot;
            merge_set(edges[i].u, edges[i].v);
        }
        if (tot == n - 1) {
            break;
        }
    }
    return std::make_pair(sum, cnt);
}

inline void add_weight(ll x) {
    for (size_t i = 1; i <= m; i++) {
        if (edges[i].color == WHITE) {
            edges[i].weight += x;
        }
    }
}

inline bool check(ll x) {
    add_weight(x);
    bool ret = (Kruskal().second >= need);
    add_weight(-x);
    return ret;
}

int main() {

#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    readf(&n), readf(&m), readf(&need);

    for (size_t i = 1; i <= m; i++) {
        readf(&edges[i].u);
        readf(&edges[i].v); 
        readf(&edges[i].weight);
        readf(&edges[i].color);
        ++edges[i].u;
        ++edges[i].v;
    }

    ll res = 0;
    for (ll l = -100, r = 100; l <= r; ) {
        ll mid = (l + r) >> 1;
        if (check(mid)) {
            l = mid + 1;
            res = mid;
        }
        else {
            r = mid - 1;
        }
    }
    add_weight(res);
    ll ans = Kruskal().first - need * res;
    printf("%lld\n", ans);
    

#ifdef _RUN_TIME
    printf("The running duration is not less than %ld ms\n", clock() - start);
#endif // _RUN_TIME
    return 0;
}

template< typename Type >
inline Type readf(Type* p) {
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
inline void writef(Type x) {
    int sta[MAX_NUM_SIZE];
    int top = 0;
    do {
        sta[top++] = x % 10, x /= 10;
    } while (x);
    while (top) putchar(sta[--top] + '0');  // 48 是 '0'
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