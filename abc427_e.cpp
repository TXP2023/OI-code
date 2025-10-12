//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
//
//      By txp2024 www.luogu.com.cn  TXP2023 www.github.com
// 
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

#pragma once
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <numeric>
#include <ctype.h>
#include <cstdarg>
#include <queue>
#include <climits>
#include <time.h>
#include <iostream>
#include <stdint.h>
#include <vector>

#define _FREAD        true
#define MAX_INF       0x7f7f7f7f7f7f7f7f
#define MAX_NUM_SIZE  35
#define MAXH          20

typedef long long int ll;
typedef unsigned long long int ull;

template<typename _T>
inline _T fpow(_T a, _T n, _T mod) {
    _T base = a, ret = 1;
    while (n) {
        if (n & 1) {
            ret = ret * base;
            ret %= mod;
        }
        base = base * base;
        base %= mod;
        n >>= 1;
    }
    return ret % mod;
}
//快读函数声明
template< typename Type >
inline Type fread(Type* p = nullptr);

//快速输出函数
template<typename Type>
inline void fwrite(Type x);

struct Point {
    ll x, y;
};

//记录状态
struct Sta {
    ll lowx, upx, lowy, upy; //边界坐标相对于原地图的位置ll 
    ll x, y, dist; //高桥目前的位置和移动的次数
};

ll sum[MAXH][MAXH];
char map[MAXH][MAXH];
bool vis[14][14][14][14][28][28];
int dx[4] = { 0,0,1,-1 }, dy[4] = { 1,-1,0,0 };
Point s;
ll h, w;

int main() {

#ifdef _FREOPEN     
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    fread(&h), fread(&w);

    for (size_t i = 1; i <= h; i++) {
        for (size_t j = 1; j <= w; j++) {
            std::cin >> map[i][j];
            sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + (map[i][j] == '#');
            if (map[i][j] == 'T') {
                s.x = i;
                s.y = j;
            }
        }
    }

    std::queue<Sta> que;
    que.push({ 1, h, 1, w, h, w });
    vis[1][h][1][w][h][w] = true;

    while (!que.empty()) {
        Sta u = que.front();
        que.pop();
        for (int i = 0; i < 4; i++) {
            Sta v = u;
            v.dist++;
            v.x += dx[i];
            v.y += dy[i];

            v.lowx = std::max(v.lowx, v.x - h + 1);
            v.upx = std::min(v.upx, v.x);
            v.lowy = std::max(v.lowy, v.y - w + 1);
            v.upy = std::min(v.upy, v.y);

            int X = v.x - h + s.x, Y = v.y - w + s.y; // 高桥当前位置对应原地图的实际坐标

            // 排除非法情况
            if (v.x < 0 || v.x > 2 * h || v.y < 0 || v.y > 2 * w)
                continue;
            if (X >= v.lowx && X <= v.upx && Y >= v.lowy && Y <= v.upy && map[X][Y] == '#') // 还在地图内且与垃圾位置重合
                continue;
            if (vis[v.lowx][v.upx][v.lowy][v.upy][v.x][v.y] == true) {
                continue;
            }

            if (sum[v.upx][v.upy] - sum[v.upx][v.lowy - 1] - sum[v.lowx - 1][v.upy] + sum[v.lowx - 1][v.lowy - 1] == 0) // 剩余位置无垃圾
            {
                std::cout << v.dist;
                return 0;
            }

            que.push(v);
            vis[v.lowx][v.upx][v.lowy][v.upy][v.x][v.y] = true;
        }
    }

    puts("-1");

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