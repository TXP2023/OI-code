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
#include <cstdarg>
#include <climits>
#include <time.h>
#include <iostream>
#include <stdint.h>

#define READ          false
#define MAX_INF       1e18
#define MAX_NUM_SIZE  35
#define MAXN          (uint64_t)(1e6+5)
#define MODE          (uint64_t)(89999794200117649LL)

typedef long long int ll;
typedef unsigned long long int unill;

//快读函数声明
#if READ
template< typename T >
inline T readf();
#else
template< typename Type >
inline Type readf(Type* p = nullptr);
#endif

//快速输出函数
template<typename Type>
inline void writef(Type x);

struct tree_node {
    ll w;
    ll ls, rs;
    tree_node() {
        return;
    }

    tree_node(size_t _Ls, size_t _Rs) {
        ls = _Ls;
        rs = _Rs;
        return;
    }
};


tree_node tree[MAXN];
ll node_num[MAXN];
ll n, ans = LLONG_MIN;
std::pair<uint64_t, uint64_t> Hash[MAXN];
const uint64_t Base1 = 999999751, Base2 = 299999827, Base3 = 1e9 + 7;

void dfs(size_t _u) {
    if (tree[_u].ls) {
        dfs(tree[_u].ls);
    }
    if (tree[_u].rs) {
        dfs(tree[_u].rs);
    }

    node_num[_u] = node_num[tree[_u].ls] + node_num[tree[_u].rs] + 1;
    Hash[_u].first = (Hash[tree[_u].ls].first * Base1 + tree[_u].w * Base2 + Hash[tree[_u].rs].first * Base3) % MODE;
    Hash[_u].second = (Hash[tree[_u].ls].second * Base3 + tree[_u].w * Base2 + Hash[tree[_u].rs].second * Base1) % MODE;

    if (node_num[tree[_u].ls] == node_num[tree[_u].rs] && Hash[_u].second == Hash[_u].first) {
        ans = std::max(ans, node_num[_u]);
    }
}

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    
    readf(&n);

    for (size_t i = 1; i <= n; i++) {
        readf(&tree[i].w);
    }

    for (size_t i = 1; i <= n; i++) {
        ll ls = readf<ll>(), rs = readf<ll>();
        if (ls == -1) {
            ls = 0;
        }
        if (rs == -1) {
            rs = 0;
        }
        tree[i].ls = ls;
        tree[i].rs = rs;
    }

    dfs(1);
    printf("%lld\n", ans);


#ifdef _RUN_TIME
    printf("The running duration is not less than %ld ms\n", clock() - start);
#endif // _RUN_TIME
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



/**
 *              ,----------------,              ,---------,
 *         ,-----------------------,          ,"        ,"|
 *       ,"                      ,"|        ,"        ,"  |
 *      +-----------------------+  |      ,"        ,"    |
 *      |  .-----------------.  |  |     +---------+      |
 *      |  |                 |  |  |     | -==----'|      |
 *      |  |  By txp2024     |  |  |     |         |      |
 *      |  |                 |  |  |     |`---=    |      |
 *      |  |  C:\>_          |  |  |     |==== ooo |      ;
 *      |  |                 |  |  |     |(((( [33]|    ,"
 *      |  `-----------------'  | /      |((((     |  ,"
 *      +-----------------------+/       |         |,"s
 *         /_)______________(_/          +---------+
 *    _______________________________
 *   /  oooooooooooooooo  .o.  oooo /,   /-----------
 *  / ==ooooooooooooooo==.o.  ooo= //   /\--{)B     ,"
 * /_==__==========__==_ooo__ooo=_/'   /___________,"
 *
 */
