//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
//
//      By txp2024 www.luogu.com.cn  TXP2023 www.github.com
// 
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
#pragma once
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <ctype.h>
#include <cstdarg>
#include <climits>
#include <queue>
#include <time.h>
#include <iostream>
#include <stdint.h>

#define READ          false
#define MAX_INF       1e18
#define MAX_NUM_SIZE  35
#define MAXN          (uint64_t)(1e3)

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

struct point {
    uint16_t x, y;

    point() {
        return;
    }
    point(uint16_t _x, uint16_t _y) {
        x = _x;
        y = _y;
        return;
    }

    inline bool operator ==(const point& othere) const {
        return x == othere.x && y == othere.y;
    }
};

ll value[MAXN + 4][MAXN + 4];
char map[MAXN + 4][MAXN + 4];
ll H, W;
point beg, end;

inline void dfs(point start) {
    std::queue<point> que;
    que.push(start);
    while (!que.empty()) {
        point now = que.front();
        que.pop();
        if (map[now.x - 1][now.y]) {//头顶有墙
            value[now.x - 1][now.y] = std::min(value[now.x - 1][now.y], value[now.x][now.y] + 1);
            value[now.x - 2][now.y] = std::min(value[now.x - 2][now.y], value[now.x][now.y] + 1);
        }
        else {
            value[now.x - 1][now.y] = std::min(value[now.x - 1][now.y], value[now.x][now.y]);
            if (map[now.x - 2][now.y]) {//头顶顶有墙
                value[now.x - 2][now.y] = std::min(value[now.x - 2][now.y], value[now.x][now.y] + 1);
            }
            else {
                value[now.x - 2][now.y] = std::min(value[now.x - 2][now.y], value[now.x][now.y]);
            }
        }

        if (map[now.x + 1][now.y]) {//头顶有墙
            value[now.x + 1][now.y] = std::min(value[now.x + 1][now.y], value[now.x][now.y] + 1);
            value[now.x + 2][now.y] = std::min(value[now.x + 2][now.y], value[now.x][now.y] + 1);
        }
        else {
            value[now.x + 1][now.y] = std::min(value[now.x + 1][now.y], value[now.x][now.y]);
            if (map[now.x + 2][now.y]) {//头顶顶有墙
                value[now.x + 2][now.y] = std::min(value[now.x + 2][now.y], value[now.x][now.y] + 1);
            }
            else {
                value[now.x + 2][now.y] = std::min(value[now.x + 2][now.y], value[now.x][now.y]);
            }
        }
        if (map[now.x][now.y - 1]) {//头顶有墙
            value[now.x][now.y - 1] = std::min(value[now.x][now.y - 1], value[now.x][now.y] + 1);
            value[now.x][now.y - 2] = std::min(value[now.x][now.y - 2], value[now.x][now.y] + 1);
        }
        else {
            value[now.x][now.y - 1] = std::min(value[now.x][now.y - 1], value[now.x][now.y]);
            if (map[now.x][now.y - 2]) {//头顶顶有墙
                value[now.x][now.y - 2] = std::min(value[now.x][now.y - 2], value[now.x][now.y] + 1);
            }
            else {
                value[now.x][now.y - 2] = std::min(value[now.x][now.y], value[now.x][now.y]);
            }
        }
        if (map[now.x - 1][now.y]) {//头顶有墙
            value[now.x - 1][now.y] = std::min(value[now.x - 1][now.y], value[now.x][now.y] + 1);
            value[now.x - 2][now.y] = std::min(value[now.x - 2][now.y], value[now.x][now.y] + 1);
        }
        else {
            value[now.x - 1][now.y] = std::min(value[now.x - 1][now.y], value[now.x][now.y]);
            if (map[now.x - 2][now.y]) {//头顶顶有墙
                value[now.x - 2][now.y] = std::min(value[now.x - 2][now.y], value[now.x][now.y] + 1);
            }
            else {
                value[now.x - 2][now.y] = std::min(value[now.x - 2][now.y], value[now.x][now.y]);
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

    
    readf(&H), readf(&W);
    ll x = readf<uint16_t>(), y = readf<uint16_t>();
    beg = point(x, y);
    x = readf<uint16_t>(), y = readf<uint16_t>();
    end = point(x, y);
    for (size_t i = 2; i < H + 2; ++i) {
        scanf("\n");
        for (size_t j = 2; j < W+2; j++) {
            map[i][j] = getchar() == '#' ? 1 : 0;
        }
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