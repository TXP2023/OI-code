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
#include <cmath>
#include <math.h>
#include <ctype.h>
#include <cstdarg>
#include <climits>
#include <time.h>
#include <iostream>
#include <stdint.h>

#define MAX_INF       1e18
#define MAX_NUM_SIZE  35
#define MAXN          (size_t)(155)

typedef long long int ll;
typedef unsigned long long int ull;

//快读函数声明
template< typename Type >
inline Type readf(Type* p = nullptr);

//快速输出函数
template<typename Type>
inline void writef(Type x);

struct Farm {
    ll x, y;
    Farm() {
        x = 0;
        y = 0;
        return;
    }

    Farm(ll _x, ll _y) {
        x = _x;
        y = _y;
        return;
    }
};

Farm farms[MAXN];
double graph[MAXN][MAXN], dist[MAXN], diameter[MAXN];
ll head[MAXN], id[MAXN];
ll n, blocks_id = 0;

inline double get_dist(const Farm& a, const Farm& b) {
    return std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2));
}

inline void get_block(size_t _u, ll _id) {
    id[_u] = _id;
    for (size_t i = 1; i <= n; ++i) {
        if (graph[_u][i] == MAX_INF) {
            continue;
        }
        if (id[i]) {
            continue;
        }
        get_block(i, _id);
    }
    return;
}

inline void Floyd() {
    for (size_t k = 1; k <= n; k++) {
        for (size_t i = 1; i <= n; i++) {
            for (size_t j = 1; j <= n; j++) {
                if (graph[i][k] + graph[k][j] < graph[i][j]) {
                    graph[i][j] = graph[i][k] + graph[k][j];
                }
                    
                //graph[i][j] = std::min(graph[i][j], graph[i][k] + graph[k][j]);
            }
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
    
    readf(&n);
    for (size_t i = 1; i <= n; i++) {
        ll x, y;
        readf(&x), readf(&y);
        farms[i] = Farm(x, y);
        std::fill(graph[i] + 1, graph[i] + 1 + n, MAX_INF);
    }
    
#if true
    for (size_t i = 1; i <= n; i++) {
        char str[MAXN];
        scanf("%s", str + 1);
        for (size_t j = 1; j <= n; j++) {
            if (str[j] == '1' || i == j) {
                graph[i][j] = get_dist(farms[i], farms[j]);
            }
        }
    }
#else
    for (size_t i = 1; i <= n; ++i) {
        char s[MAXN];
        scanf("%s", s);
        for (size_t j = 1; j <= n; ++j)
            if (s[j - 1] == '1' || i == j) {
                graph[i][j] = get_dist(farms[i], farms[j]);
            } 
            else {
                graph[i][j] = MAX_INF;
            }     
    }
#endif // true

    

    for (size_t i = 1; i <= n; i++) {
        if (!id[i]) {
            get_block(i, ++blocks_id);
        }
    }

    Floyd();

    for (size_t i = 1; i <= n; ++i) {
        dist[i] = 0.0;
        for (size_t j = 1; j <= n; ++j) {
            if (graph[i][j] < MAX_INF) {
                dist[i] = std::max(dist[i], graph[i][j]);
            }
        }
        diameter[id[i]] = std::max(diameter[id[i]], dist[i]);
    }

    double min_dist = MAX_INF, max_dist;
    for (size_t i = 1; i <= n; ++i) {
        for (size_t j = i + 1; j <= n; ++j) {
            if (id[i] != id[j]) {
                max_dist = std::max(
                    std::max(diameter[id[i]], diameter[id[j]]),
                    dist[i] + get_dist(farms[i], farms[j]) + dist[j]
                );
                min_dist = std::min(min_dist, max_dist);
            }
        }
    }
        

    printf("%.6lf\n", min_dist);

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