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

//�����������
#if READ
template< typename T >
inline T readf();
#else
template< typename Type >
inline Type readf(Type* p = NULL);
#endif

//�����������
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
    while (top) putchar(sta[--top] + 48);  // 48 �� '0'
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
ll graph[N][N], pre[N];                  //graph[][]������¼ͼ�����ǲ�������
ll flow[N]/*flow[i]Ϊ�ӵ�s��������i·���е������*/;
ll bfs(int s, int t) {                     //һ��bfs��һ������·
    memset(pre, -1, sizeof pre); //��ʼ��·����¼
    flow[s] = INF;  pre[s] = 0;          //��ʼ�����
    queue<int> Q;  Q.push(s);            //�����ջ����ʼbfs
    while (!Q.empty()) {
        int u = Q.front();  Q.pop();
        if (u == t) break;                  //�ѵ�һ��·�������bfs����
        for (int i = 1; i <= n; i++) {         //bfs���еĵ�
            if (i != s/*��Ҫ������*/ && graph[u][i] > 0/*����߿����� ʣ��������Ϊ0*/ && pre[i] == -1/*�����û�б�������*/) {
                pre[i] = u;  		     //��¼·��
                Q.push(i);
                flow[i] = min(flow[u], graph[u][i]); //���½������
            }
        }
    }
    if (pre[t] == -1) return -1;            //û���ҵ��µ�����·
    return flow[t];                      //�����������·������
}
ll maxflow(int s, int t) {
    ll Maxflow = 0;
    while (1) {
        ll flow = bfs(s, t);              //ִ��һ��bfs���ҵ�һ��·��������·��������
        if (flow == -1) break;            //û���ҵ��µ�����·������
        int cur = t;                     //����·���ϵĲ�������
        while (cur != s) {                   //һֱ��·�����ݵ����
            int father = pre[cur];       //pre[]��¼·���ϵ�ǰһ����
            graph[father][cur] -= flow;  //���²������磺����߼�
            graph[cur][father] += flow;  //���²������磺����߼�
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
        graph[u][v] += w;                //�������ر�
    }
    printf("%ld\n", maxflow(s, t));
    return 0;
}

#endif // learn
