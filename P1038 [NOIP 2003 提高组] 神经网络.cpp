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
#include <queue>

#define MAX_INF       1e18
#define MAX_NUM_SIZE  35
#define MAXN          105

typedef long long int ll;
typedef unsigned long long int ull;

//快读函数声明
template< typename Type >
inline Type readf(Type* p = nullptr);

//快速输出函数
template<typename Type>
inline void writef(Type x);

struct Neuron {
    ll state, val; //状态和阈值
};

struct Edge {
    ll v, weight;
    size_t next;
};

Neuron neurons[MAXN];
Edge edges[MAXN * MAXN];
ll head[MAXN], indegree[MAXN], outdegree[MAXN];
ll n, p, edge_cnt;

inline void add_edge(ll u, ll v, ll weight) {
#ifdef _DEBUG
    printf("%lld %lld\n", u, v);
#endif // _DEBUG

    ++outdegree[u];
    ++indegree[v];
    edges[++edge_cnt].v = v;
    edges[edge_cnt].weight = weight;
    edges[edge_cnt].next = head[u];
    head[u] = edge_cnt;
    return;
}

inline void get_ans() {
    std::queue<ll> que;
    for (size_t i = 1; i <= n; i++) {
        if (!indegree[i]) {
            neurons[i].state += neurons[i].val;
            que.push(i);
        }
    }

    while (!que.empty()) {
        ll u = que.front();
        que.pop();
        neurons[u].state -= neurons[u].val;
        if (neurons[u].state > 0) {
            for (size_t i = head[u], v = edges[i].v; i; i = edges[i].next, v = edges[i].v) {
                --indegree[v];
                neurons[v].state += edges[i].weight * neurons[u].state;
                if (!indegree[v]) {
                    que.push(v);
                }
            }
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

    readf(&n), readf(&p);

    for (size_t i = 1; i <= n; i++) {
        readf(&neurons[i].state), readf(&neurons[i].val);
    }

    for (size_t i = 0; i < p; i++) {
        ll u, v, w;
        readf(&u), readf(&v), readf(&w);
        add_edge(u, v, w);
    }

    get_ans();

    bool flag = false;
    for (size_t i = 1; i <= n; i++) {
        if (neurons[i].state > 0 && !outdegree[i]) {
            printf("%lld %lld\n", i, neurons[i].state);
            flag = true;
        }
    }

    if (!flag) {
        puts("NULL");
    }

#ifdef _RUN_TIME
    printf("The running duration is not less than %ld ms\n", clock() - start);
#endif // _RUN_TIME
    return 0;
}

template< typename Type >
inline Type readf(Type* p) {
    Type ret = 0, sgn = 0, ch = getchar();
    while (!isdigit(ch)) {
        sgn |= ch == '-', ch = getchar();
    }
    while (isdigit(ch)) ret = ret * 10 + ch - '0', ch = getchar();
    if (p != nullptr) {
        *p = Type(sgn ? -ret : ret);
    }
    return sgn ? -ret : ret;
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