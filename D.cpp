#pragma GCC optimize(3,"Ofast","inline")
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
#include <queue>
#include <iostream>
#include <stdint.h>

#define READ          false
#define MAX_INF       1e18
#define MAX_NUM_SIZE  35

typedef long long int ll;
typedef unsigned long long int unill;

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

struct Road {
    char direction;
    ll weight = LLONG_MAX;
};

struct que_node {
    ll x, y;
    ll weight;
    bool operator <(const que_node& other)const {
        return weight > other.weight;
    }
};

struct point {
    ll x, y;
};

Road road[1002][1002];
char map[1002][1002];
point exits[1000000];
ll h, w, exits_cnt = 0;
std::queue<que_node> que;

inline void get_path() {
    while (!que.empty()) {
        que_node now = que.front();
        que.pop();
        if (now.x - 1 >= 1 && map[now.x - 1][now.y] != '#' && road[now.x - 1][now.y].weight > now.weight + 1) {
            road[now.x - 1][now.y].direction = 'v';
            road[now.x - 1][now.y].weight = now.weight + 1;
            que.push({ now.x - 1 , now.y, now.weight + 1 });
        }
        if (now.x + 1 <= h && map[now.x + 1][now.y] != '#' && road[now.x + 1][now.y].weight > now.weight + 1) {
            road[now.x + 1][now.y].direction = '^';
            road[now.x + 1][now.y].weight = now.weight + 1;
            que.push({ now.x + 1 , now.y, now.weight + 1 });
        }
        if (now.y - 1 >= 1 && map[now.x][now.y - 1] != '#' && road[now.x][now.y - 1].weight > now.weight + 1) {
            road[now.x][now.y - 1].direction = '>';
            road[now.x][now.y - 1].weight = now.weight + 1;
            que.push({ now.x , now.y - 1, now.weight + 1 });
        }
        if (now.y + 1 <= w && map[now.x][now.y + 1] != '#' && road[now.x][now.y + 1].weight > now.weight + 1) {
            road[now.x][now.y + 1].direction = '<';
            road[now.x][now.y + 1].weight = now.weight + 1;
            que.push({ now.x , now.y + 1, now.weight + 1 });
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

    readf(&h), readf(&w);

    for (ll i = 1; i <= h; i++) {
        for (ll j = 1; j <= w; j++) {
            char ch;
            std::cin >> ch;
            map[i][j] = ch;
            if (ch == 'E') {
                exits[exits_cnt++] = (point{i, j});
            }
        }
    }
    
    for (size_t i = 0; i < exits_cnt; i++) {
        que.push({ exits[i].x, exits[i].y, 1 });
    }
    get_path();

    for (size_t i = 1; i <= h; i++) {
        for (size_t j = 1; j <= w; j++) {
            if (map[i][j] == '.') {
                putchar(road[i][j].direction);
            }
            else {
                putchar(map[i][j]);
            }
        }
        putchar('\n');
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