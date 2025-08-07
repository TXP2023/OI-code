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
#define MAXM          (size_t)(1e5+5)
#define MAXN          (size_t)(1e5+5)

typedef long long int ll;
typedef unsigned long long int ull;

//快读函数声明
template< typename Type >
inline Type fread(Type* p = nullptr);

//快速输出函数
template<typename Type>
inline void fwrite(Type x);

struct Edge {
    ll v, next;

    Edge(ll _v = 0, ll _next = 0) : v(_v), next(_next) {}
};


Edge edges[MAXM * 2];
ll head[MAXN];
ll deep[MAXN], fa[MAXN][20];
std::vector<ll> num[MAXN][20]; //记录每个城市到上跳2^j个城市所居住的人
std::vector<ll> cities[MAXN]; //记录每个城市所居住的人
ll n, m, q, edge_cnt = 0;

inline void add_edge(ll u, ll v) {
    ++edge_cnt;
    edges[edge_cnt] = Edge(v, head[u]);
    head[u] = edge_cnt;
    return;
}

inline std::vector<ll> merge(std::vector<ll>& a, std::vector<ll>& b) {
    std::vector<ll> _res;
    std::vector<ll>::iterator ita = a.begin(), itb = b.begin();
    while (ita != a.end() && itb != b.end() && _res.size() <= 10) {
        if (*ita < *itb) {
            _res.push_back(*ita);
            ++ita;
        }
        else {
            _res.push_back(*itb);
            ++itb;
        }
    }
    while (ita != a.end() && _res.size() <= 10) {
        _res.push_back(*ita);
        ++ita;
    }
    while (itb != b.end() && _res.size() <= 10) {
        _res.push_back(*itb);
        ++itb;
    }
    return _res;
}

void init_tree(ll _u, ll _fa, ll _deep) {
    deep[_u] = _deep;
    fa[_u][0] = _fa;
    fa[_u][1] = fa[_fa][0];
    num[_u][0] = cities[_u];
    num[_u][1] = merge(cities[_u], cities[_fa]);
    for (size_t i = head[_u], v; i; i = edges[i].next) {
        v = edges[i].v;
        if (v == _fa) {
            continue;
        }
        init_tree(v, _u, _deep + 1);
    }
    return;
}

inline void get_lca() {
    for (size_t j = 2; j <= 19; j++) {
        for (size_t i = 1; i <= n; i++) {
            fa[i][j] = fa[fa[i][j - 1]][j - 1];
            num[i][j] = merge(num[i][j - 1], num[fa[i][j - 1]][j - 1]);
        }
    }
    return;
}

int main() {

#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    fread(&n), fread(&m), fread(&q);

    for (size_t i = 0; i < n - 1; i++) {
        ll u, v;
        fread(&u), fread(&v);
        add_edge(u, v);
        add_edge(v, u);
    }

    for (size_t i = 1; i <= m; i++) {
        ll city;
        fread(&city);
        cities[city].push_back(i);
    }

    init_tree(1, 0, 1);

    get_lca();

    while (q--) {
        ll u, v, a;
        fread(&u), fread(&v), fread(&a);
        std::vector<ll> ans(0);
        if (deep[u] > deep[v]) {
            std::swap(u, v);
        }
        ll temp = deep[v] - deep[u];
        for (ll i = 19; i >= 0; --i) {
            if (temp & (1 << i)) {
                ans = merge(ans, num[v][i]);
                v = fa[v][i];
            }
        }
        if (u == v) {
            ans = merge(ans, num[v][0]);
            goto LOOP;
        }
        for (ll i = 19; i >= 0; i--) {
            if (fa[u][i] != fa[v][i]) {
                ans = merge(num[u][i], ans);
                ans = merge(num[v][i], ans);
                u = fa[u][i];
                v = fa[v][i];
            }
        }
        ans = merge(ans, num[u][0]);
        if (u != v) {
            ans = merge(ans, num[v][1]);
        }
    LOOP:
        ll size = std::min((ll)ans.size(), a);
        printf("%lld ", size);
        for (size_t i = 0; i < size; i++) {
            printf("%lld ", ans[i]);
        }
        puts("");
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