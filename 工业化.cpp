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
#define FAST_READ     true
#define MAXN          (size_t)(1e4+5)
#define MAXM          (size_t)(2e4+5)
#define MAXG          (105)

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

Edge edges[MAXM * 2];
int head[MAXN], dist[MAXN][2][MAXN], pre[MAXG];
bool flag[MAXN];
ll n, m, g, q, edges_cnt = 0;

inline void add_edge(ll u, ll v) {
    ++edges_cnt;
    edges[edges_cnt].v = v;
    edges[edges_cnt].next = head[u];
    head[u] = edges_cnt;
    return;
}

inline void get_path(ll s) {
    for (size_t i = 1; i <= n; i++) {
        dist[s][0][i] = -1;
        dist[s][1][i] = -1;
    }
    dist[s][0][s] = 0;
    std::queue<std::pair<ll, bool>> que;
    que.push({ s, 0 });
    while (!que.empty()) {
        std::pair<ll, bool> u = que.front();
        que.pop();
        for (size_t i = head[u.first]; i; i = edges[i].next) {
            ll v = edges[i].v;
            if (dist[s][u.second ^ 1][v] == -1) {
                dist[s][u.second ^ 1][v] = dist[s][u.second][u.first] + 1;
                que.push({ v, u.second ^ 1 });
            }
        }
    }
    return;
}

int main() {


#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
#endif // _FREOPEN


#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    //scanf("%lld%lld", &n, &m);
    readf(&n), readf(&m);

    for (size_t i = 0; i < m; i++) {
        ll u, v;
        //scanf("%lld%lld", &u, &v);
        readf(&u), readf(&v);
        add_edge(u, v);
        add_edge(v, u);
    }

    //for (size_t i = 1; i <= n; i++) {
    //    get_path(i);
    //}

#ifdef _RUN_TIME
    printf("The running duration is not less than %ld ms\n", clock() - start);
#endif // _RUN_TIME

    scanf("%lld", &g);

    for (size_t i = 1; i <= g; i++) {
        scanf("%lld", &pre[i]);
        //readf(&pre[i]);
    }

    scanf("%lld", &q);
    //readf(&q);

    while (q--) {
        ll x, s, t, val = 0, temp;

        scanf("%lld%lld%lld", &x, &s, &t);
        //readf(&x), readf(&s), readf(&t);
        if (!flag[x]) {
            flag[x] = true;
            get_path(x);
        }
        while (s != t) {
            s = pre[s];
            ++val;
            if (s == 0) {
                for (size_t i = 0; i < n; i++) {
                    putchar('0');
                    putchar(' ');
                }
                goto LOOP;
            }
        }
        temp = val % 2;
        for (size_t i = 1; i <= n; i++) {
            if (dist[x][temp][i] <= val) {
                putchar('1');
                putchar(' ');
            }
            else {
                putchar('0');
                putchar(' ');
            }
        }
    LOOP:
        puts("");
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