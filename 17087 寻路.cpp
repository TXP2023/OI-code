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
#define MAXN          1005

typedef long long int ll;
typedef unsigned long long int ull;

//快读函数声明
template< typename Type >
inline Type readf(Type* p = nullptr);

//快速输出函数
template<typename Type>
inline void writef(Type x);

struct point {
    size_t x, y;
    ll w;

    inline bool operator <(const point& other)const {
        return w > other.w;
    }
};

int map[MAXN][MAXN], dist[MAXN][MAXN];
bool flag[MAXN][MAXN];
point s;
ll n, m;

inline bool in_map(size_t x, size_t y) {
    return 1 <= x && x <= n && 1 <= y && y <= m;
}

inline void get_path() {
    const short trendx[4] = { 0, 0, 1, -1 }, trendy[4] = { -1, 1, 0, 0 };
    s.w = 0;
    std::priority_queue<point> que;
    que.push(s);
    dist[s.x][s.y] = 0;
    while (!que.empty()) {
        point now = que.top();
        que.pop();
        flag[now.x][now.y] = true;
        for (size_t i = 0; i < 4; i++) {
            size_t x = now.x + trendx[i], y = now.y + trendy[i];
            if (!in_map(x, y) || flag[x][y] || map[x][y] == -1) {
                continue;
            }
            if (map[x][y] <= map[now.x][now.y] && dist[x][y] > dist[now.x][now.y] + 1) {
                dist[x][y] = dist[now.x][now.y] + 1;
                que.push(point{ x, y, dist[x][y] });
                continue;
            }
            if (map[x][y] > map[now.x][now.y] && dist[x][y] > dist[now.x][now.y] + map[x][y] - map[now.x][now.y] + 1) {
                dist[x][y] = dist[now.x][now.y] + map[x][y] - map[now.x][now.y] + 1;
                que.push(point{ x, y, dist[x][y] });
                continue;
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

    scanf("%lld%lld", &n, &m);

    for (size_t i = 1; i <= n; i++) {
        char str[MAXN];
        scanf("%s", str + 1);
        for (size_t j = 1; j <= m; j++) {
            map[i][j] = str[j] == '#' ? -1 : str[j] - '0';
            dist[i][j] = INT32_MAX;
        }
    }

    scanf("%lld%lld", &s.x, &s.y);

    get_path();

    for (size_t i = 1; i <= n; i++) {
        for (size_t j = 1; j <= m; j++) {
            if (map[i][j] == -1) {
                printf("-1 ");
                continue;
            }
            printf("%lld ",  dist[i][j] != INT32_MAX? dist[i][j] : (ll)- 1);
        }
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