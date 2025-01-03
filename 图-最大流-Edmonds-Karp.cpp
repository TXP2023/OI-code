#if true
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
    for (size_t i = 0; i < m; i++){
        ll u = readf<ll>() - 1, v = readf<ll>() - 1, w = readf<ll>();
        graph[u][v] += w;
        
    }

    path.resize(n);
    dits.resize(n);
    printf("%lld\n", Edmonds_Karp(--s, --t));
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
    while (top) putchar(sta[--top] + 48);  // 48 是 '0'
    return;
}
#else
// correct code
#include<bits/stdc++.h>
using namespace std;
const int INF = 1e9;
const int N = 250;
#define ll long long
int n, m;
ll graph[N][N], pre[N];                  //graph[][]不仅记录图，还是残留网络
ll flow[N]/*flow[i]为从点s出发到点i路径中的最大流*/;
ll bfs(int s, int t) {                     //一次bfs找一条增广路
    memset(pre, -1, sizeof pre); //初始化路径记录
    flow[s] = INF;  pre[s] = 0;          //初始化起点
    queue<int> Q;  Q.push(s);            //起点入栈，开始bfs
    while (!Q.empty()) {
        int u = Q.front();  Q.pop();
        if (u == t) break;                  //搜到一个路径，这次bfs结束
        for (int i = 1; i <= n; i++) {         //bfs所有的点
            if (i != s/*不要往回走*/ && graph[u][i] > 0/*这个边可以走 剩余容量不为0*/ && pre[i] == -1/*这个点没有被遍历过*/) {
                pre[i] = u;  		     //记录路径
                Q.push(i);
                flow[i] = min(flow[u], graph[u][i]); //更新结点流量
            }
        }
    }
    if (pre[t] == -1) return -1;            //没有找到新的增广路
    return flow[t];                      //返回这个增广路的流量
}
ll maxflow(int s, int t) {
    ll Maxflow = 0;
    while (1) {
        ll flow = bfs(s, t);              //执行一次bfs，找到一条路径，返回路径的流量
        if (flow == -1) break;            //没有找到新的增广路，结束
        int cur = t;                     //更新路径上的残留网络
        while (cur != s) {                   //一直沿路径回溯到起点
            int father = pre[cur];       //pre[]记录路径上的前一个点
            graph[father][cur] -= flow;  //更新残留网络：正向边减
            graph[cur][father] += flow;  //更新残留网络：反向边加
            cur = father;
        }
        Maxflow += flow;
    }
    return Maxflow;
}
int main() {
    int s, t; scanf("%d%d%d%d", &n, &m, &s, &t);
    memset(graph, 0, sizeof graph);
    for (int i = 0; i < m; i++) {
        int u, v, w;  scanf("%d%d%d", &u, &v, &w);
        graph[u][v] += w;                //可能有重边
    }
    printf("%ld\n", maxflow(s, t));
    return 0;
}

#endif // learn
