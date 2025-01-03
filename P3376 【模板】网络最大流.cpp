// my code
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
//
//      By txp2024 www.luogu.com.cn  TXP2023 www.github.com
// 
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
#pragma once
#include <vector>
#include <queue>
#include <stdio.h>
#include <algorithm>
#include <ctype.h>
#include <cstdarg>
#include <climits>
#include <iostream>
#include <stdint.h>
#include <initializer_list>

#define READ false
#define MAX_INF 1e18
#define MAX_NUM_SIZE 35

typedef long long int ll;
typedef unsigned long long int unill;

//快读函数声明
#if READ
template< typename T >
inline T readf();
#else
template< typename Type >
inline Type readf(Type* p = NULL);
#endif

//快速输出函数
template<typename Type>
inline void writef(Type x);

std::vector<std::vector< ll >> graph;
std::vector<ll> dits;
std::vector<ll> path;
ll n, m, s, t;

inline ll new_path(ll _s, ll _t) {
    std::fill(path.begin(), path.end(), -1);
    dits[_s] = MAX_INF, path[_s] = 0;
    std::queue<ll> que;
    que.push(_s);
    while (!que.empty()) {
        ll u = que.front();
        que.pop();
        for (size_t i = 0; i < n; i++) {
            if (i != u && graph[u][i] > 0 && path[i] == -1) {
                path[i] = u;
                que.push(i);
                dits[i] = std::min(graph[u][i], dits[u]);
            }
        }
    }

    return (path[_t] == -1) ? -1 : dits[_t];
}

inline ll Edmonds_Karp(ll _s, ll _t) {
    ll sum = 0;
    while (true) {
        ll flow = new_path(_s, _t);
        if (flow == -1) {
            break;
        }
        ll cur = _t;
        while (cur != _s) {
            ll from = path[cur];
            graph[from][cur] -= flow;
            graph[cur][from] += flow;
            cur = from;
        }
        sum += flow;
    }
    return sum;
}

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

    readf(&n), readf(&m), readf(&s), readf(&t);

    graph.resize(n, std::vector< ll >(n, 0));
    for (size_t i = 0; i < m; i++) {
        ll u = readf<ll>() - 1, v = readf<ll>() - 1, w = readf<ll>();
        graph[u][v] += w;

    }

    path.resize(n);
    dits.resize(n);
    printf("%lld\n", Edmonds_Karp(--s, --t));
    return 0;
}
