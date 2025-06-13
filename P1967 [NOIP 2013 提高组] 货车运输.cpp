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
#include <ctype.h>
#include <cstdarg>
#include <climits>
#include <time.h>
#include <iostream>
#include <stdint.h>

#define READ          false
#define MAX_INF       1e18
#define MAX_NUM_SIZE  35
#define MAXN          (size_t)(1e4+5)
#define MAXM          (size_t)(5e4+5)

typedef long long int ll;
typedef unsigned long long int ull;

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

struct Edge {
    size_t u, v, next;
    ll w;

    Edge() {
        u = 0;
		v = 0;
        next = 0;
		w = 0;
        return;
    }

    Edge(size_t u, size_t v, ll w) {
		this->u = u;
        this->v = v;
        this->w = w;
        this->next = 0;
        return;
	}

    bool operator <(const Edge& other) const {
        return w > other.w; // 大根堆
	}
};

Edge graph[MAXM], edges[MAXM], tree[MAXM];
ll head[MAXN], tree_head[MAXN], set[MAXN];
size_t graph_cnt = 0, tree_cnt;
ll n, m;

void add_edge(size_t u, size_t v, ll w, size_t &cnt, Edge* _Edges, ll* _Head) {
	cnt++;
    _Edges[cnt].u = u;
    _Edges[cnt].v = v;
    _Edges[cnt].w = w;
    _Edges[cnt].next = _Head[u];
	_Head[u] = cnt;
    return;
}

inline void set_init() {
    for (size_t i = 1; i <= n; i++) {
        set[i] = i;
    }
	return;
}

inline size_t find_set(size_t x) {
    if (set[x] == x) {
        return set[x];
    }
    return set[x] = find_set(set[x]);
}

inline void build_max_tree() {
    //kruskal
    ll cnt = 1;
    std::sort(edges + 1, edges + 1 + m);
	//一个树有 n - 1 条边
    for (size_t i = 1; i <= n - 1; i++) {
        if (find_set(edges[cnt].u) != find_set(edges[cnt].v)) {
            set[find_set(edges[cnt].u)] = set[find_set(edges[cnt].v)];
            
        }
    }

}

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    readf(&n), readf(&m);

    for (size_t i = 1; i <= m; i++) {
        ll u, v, w;
		readf(&u), readf(&v), readf(&w);    
        add_edge(u, v, w, graph_cnt, edges, head);
		add_edge(v, u, w, graph_cnt, edges, head); // 无向图
		edges[i] = Edge(u, v, w);
    }

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
 *      +-----------------------+/       |         |,"
 *         /_)______________(_/          +---------+
 *    _______________________________
 *   /  oooooooooooooooo  .o.  oooo /,   /-----------
 *  / ==ooooooooooooooo==.o.  ooo= //   /\--{)B     ,"
 * /_==__==========__==_ooo__ooo=_/'   /___________,"
 *
 */