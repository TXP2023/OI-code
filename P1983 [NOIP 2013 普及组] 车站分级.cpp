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
#define MAXN          (size_t)(1005)

typedef long long int ll;
typedef unsigned long long int ull;

//快读函数声明
template< typename Type >
inline Type readf(Type* p = nullptr);

//快速输出函数
template<typename Type>
inline void writef(Type x);

struct Edge {
    ll v, next;
};

Edge edges[MAXN * MAXN];
ll head[MAXN], indegree[MAXN];
bool edge_flag[MAXN][MAXN]; //是否边i,j已经存在
ll dist[MAXN];
ll n, m, edge_cnt = 0, ans;

inline void add_edge(ll u, ll v) {
#ifdef  _DEBUG
    printf("%lld %lld\n", u, v);
#endif //  _DEBUG
    ++indegree[v];
    edges[++edge_cnt].v = v;
    edges[edge_cnt].next = head[u];
    head[u] = edge_cnt;
    return;
}

inline void get_ans() {
    std::queue<ll> que;
    for (size_t i = 1; i <= n; i++) {
        if (indegree[i]) {
            continue;
        }
        que.push(i);
        dist[i] = 1;
    }
    while (!que.empty()) {
        ll u = que.front();
        que.pop();
        if (!head[u]) {
            ans = std::max(ans, dist[u]);
            continue;
        }
        for (size_t i = head[u]; i; i = edges[i].next) {
            ll v = edges[i].v;
            --indegree[v];
            if (dist[u] + 1 > dist[v]) {
                dist[v] = dist[u] + 1;  
            }
            if (!indegree[v]) {
                que.push(v);
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

    readf(&n), readf(&m);

#ifdef _DEBUG
    puts("edges list:\n");
#endif // _DEBUG


    for (size_t i = 1; i <= m; i++) {
        bool flag[MAXN]; //标记每个停车的节点
        memset(flag, 0, sizeof(flag));
        ll station[MAXN];
        ll s = readf<ll>();
        for (size_t i = 1; i <= s; i++) {
            readf(&station[i]);
            flag[station[i]] = true;
        }

        for (size_t i = station[1]; i < station[s]; i++) {
            if (!flag[i]) {
                for (size_t j = 1; j <= s; j++) {
                    if (!edge_flag[station[j]][i]) {
                        edge_flag[station[j]][i] = true;
                        add_edge(station[j], i);
                    }
                }
            }
        }
        
        //for (size_t i = 1; i <= s; i++) {
        //    for (size_t j = station[1]; j < station[s]; j++) {
        //        if (!flag[j] && edge_flag[station[i]][j]) {
        //            edge_flag[station[i]][j] = true;
        //            add_edge(station[i], j);
        //        }
        //    }
        //}
    }

    get_ans();

    printf("%lld\n", ans);

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