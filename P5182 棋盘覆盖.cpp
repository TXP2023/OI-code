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

#define _FREAD        true
#define MAX_INF       1e18
#define MAX_NUM_SIZE  35
#define MAXN          1005

typedef long long int ll;
typedef unsigned long long int ull;

inline int64_t fpow(int64_t a, int64_t n, int64_t mod) {
    int64_t base = a, ret = 1;
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

struct Point {
    ll x, y;

    Point() :x(0), y(0) {}

    Point(ll _x, ll _y) :x(_x), y(_y) {}

    Point operator +(const Point& other) {
        return Point(x + other.x, y + other.y);
    }

    bool operator !() {
        return x == 0 || y == 0;
    }
};

Point f[4] = { Point(0, 1), Point(0, -1), Point(1, 0), Point(-1, 0) };
bool flag[MAXN][MAXN], map[MAXN][MAXN];
Point used[MAXN][MAXN];
ll n, t, ans;

inline bool check(Point a) {
    return 1 <= a.x && a.x <= n && 1 <= a.y && a.y <= n && !map[a.x][a.y];
}

bool match(Point p) {
    for (auto& i : f) {
        Point temp = p + i;
        if (!check(temp) || flag[temp.x][temp.y]) {
            continue;
        }
        flag[temp.x][temp.y] = true;
        if (!used[temp.x][temp.y] || match(used[temp.x][temp.y])) {
            //原先写成match(temp)了
            used[temp.x][temp.y] = p;
            return true;
        }
    }
    return false;
}

int main() {

#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    fread(&n), fread(&t);

    for (size_t i = 0; i < t; i++) {
        ll x, y;
        fread(&x), fread(&y);
        map[x][y] = true;
    }

    for (size_t i = 1; i <= n; i++) {
        for (size_t j = 1; j <= n; j++) {
            memset(flag, 0, sizeof(flag));
            if (map[i][j]) {
                continue;
            }
            if (match(Point(i, j))) {
                ++ans;
#ifdef _DEBUG
                printf("[Log] i=%lld  j=%lld True\n", i, j);
#endif // _DEBUG
            }
            else {
#ifdef _DEBUG
                printf("[Log] i=%lld  j=%lld False\n", i, j);
#endif // _DEBUG
            }
        }
    }

    printf("%lld\n", ans / 2);



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