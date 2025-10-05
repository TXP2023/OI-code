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

struct Edge {
    ll v, next;

    Edge() = default;

    Edge(ll _v, ll _next) : v(_v), next(_next) {}
};

Edge edges[MAXN << 1];
ll size[MAXN], heavy[MAXN]; //以节点为根的子树的大小   重儿子
ll head[MAXN], edge_cnt = 0;
ll c[MAXN], sumId[MAXN], ans[MAXN], cnt[MAXN]; //颜色 出现次数的颜色编号和  答案  颜色出现次数
ll n, max_cnt = 0;

void add_edge(ll u, ll v) {
    ++edge_cnt;
    edges[edge_cnt] = Edge(v, head[u]);
    head[u] = edge_cnt;
}

void dfs_size(ll u, ll fa) {
    size[u] = 1;
    ll max_szie = -1;
    for (size_t i = head[u]; i; i = edges[i].next) {
        if (edges[i].v == fa) {
            continue;
        }
        dfs_size(edges[i].v, u);
        size[u] += size[edges[i].v];
        if (size[edges[i].v] > max_szie) {
            max_szie = size[edges[i].v];
            heavy[u] = edges[i].v;
        }
    }
    return;
}

void upd(ll u, ll fa, ll val, ll skip) {
    sumId[cnt[c[u]]] -= c[u];
    cnt[c[u]] += val;
    sumId[cnt[c[u]]] += c[u];

    if (val > 0 && cnt[c[u]] > max_cnt) {
        max_cnt = cnt[c[u]];
    }
    if (!sumId[max_cnt] && max_cnt) {
        --max_cnt;
    }
    for (size_t i = head[u]; i; i = edges[i].next) {
        if (edges[i].v == fa || edges[i].v == skip) {
            continue;
        }
        upd(edges[i].v, u, val, 0);
        //如果要跳过重儿子， 此时已经跳过完成了， 不用再跳了
    }
    return;
}

//节点 父节点 是否保存信息
void solve(ll u, ll fa, bool keep) {
    //先计算所有的轻儿子
    for (size_t i = head[u]; i; i = edges[i].next) {
        if (edges[i].v == fa || edges[i].v == heavy[u]) {
            continue;
        }
        solve(edges[i].v, u, false);
        //如果要跳过重儿子， 此时已经跳过完成了， 不用再跳了
    }

    //计算重儿子
    if (heavy[u]) {
        solve(heavy[u], u, true);
    }

    sumId[cnt[c[u]]] -= c[u];
    ++cnt[c[u]];
    sumId[cnt[c[u]]] += c[u];
    if (cnt[c[u]] > max_cnt) {
        max_cnt = cnt[c[u]];
    }


    //接下来是合并操作
    //合并所有轻儿子的贡献
    for (size_t i = head[u]; i; i = edges[i].next) {
        if (edges[i].v == fa || edges[i].v == heavy[u]) {
            continue;
        }
        upd(edges[i].v, u, 1, 0);
    }

    ans[u] = sumId[max_cnt];

    if (!keep) {
        upd(u, fa, -1, 0);
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

    fread(&n);

    for (size_t i = 1; i <= n; i++) {
        fread(&c[i]);
    }

    for (size_t i = 0; i < n - 1; i++) {
        ll u, v;
        fread(&u), fread(&v);
        add_edge(u, v);
        add_edge(v, u);
    }

    dfs_size(1, 0);
    max_cnt = 0;
    solve(1, 0, false);

    for (size_t i = 1; i <= n; i++) {
        printf("%lld ", ans[i]);
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