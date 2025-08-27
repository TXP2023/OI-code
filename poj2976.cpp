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
#include <queue>
#include <time.h>
#include <iostream>
#include <stdint.h>

#define _FREAD        true
#define MAX_INF       1e18
#define MAX_NUM_SIZE  35
#define MAXN          1005

typedef long long int ll;
typedef unsigned long long int ull;

//快读函数声明
template< typename Type >
inline Type fread(Type* p = nullptr);

//快速输出函数
template<typename Type>
inline void fwrite(Type x);

struct Village {
    ll x, y, z;

	Village(ll _x, ll _y, ll _z) : x(_x), y(_y), z(_z) {}

	Village() : x(0), y(0), z(0) {}
};

struct Edge {
    ll length, cost, v, next;

	Edge(ll _lenght, ll _cost, ll _v, ll _next) : length(_lenght), cost(_cost), v(_v), next(_next) {}

	Edge() : length(0), cost(0) {}
};

Edge edges[MAXN * MAXN];
Village villages[MAXN];
ll head[MAXN];
ll n, edge_cnt = 0;

inline void add_edge(ll u, ll v, ll length, ll cost) {
	edges[++edge_cnt] = Edge(length, cost, v, head[u]);
	head[u] = edge_cnt;
    return;
}

inline bool check(double mid) {
	//std::iota(set + 1, set + n + 1, 1);
	Edge temp[MAXN * MAXN];
    memcpy(temp, edges, sizeof(edges));
	bool flag[MAXN] = { false };
    flag[1] = true;
    double sum = 0;
    std::priority_queue<std::pair<double, ll>> heap; //first 的权值， second是点的编号 大根堆
    for (size_t i = head[1]; i ; i = edges[i].next) {
		heap.push(std::make_pair((double)edges[i].cost - mid * edges[i].length, edges[i].v));
    }
    for (size_t cnt = 1; cnt < n; cnt++) {
        while (flag[heap.top().second]) {
			heap.pop();
        }
		sum += heap.top().first;
        flag[heap.top().second] = true;
        for (size_t i = head[heap.top().second]; i; i = edges[i].next) {
            if (!flag[edges[i].v]) {
                heap.push(std::make_pair(edges[i].cost - mid * edges[i].length, edges[i].v));
            }
        }
    }
    return sum >= 0;
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
        ll x, y, z;
		fread(&x), fread(&y), fread(&z);    
		villages[i] = Village(x, y, z);
    }

    for (size_t i = 2; i <= n; i++) {
        for (size_t j = i - 1; j > 0; --j) {
			ll length = abs(villages[i].x - villages[j].x) + abs(villages[i].y - villages[j].y);
			ll cost = abs(villages[i].z - villages[j].z);
            add_edge(i, j, length, cost);
            add_edge(j, i, length, cost);
        }
    }

    double res;
    for (double l = 0, r = 100000000; r - l >= (1e-5); ) {
		double mid = (l + r) / 2;
        if (check(mid)) {
            res = mid;
            l = mid;
        }
        else {
            r = mid;
        }
    }

	printf("%.3lf\n", res);

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