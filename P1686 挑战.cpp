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
#include <math.h>
#include <cmath>
#include <time.h>
#include <iostream>
#include <stdint.h>

#define _FREAD        true
#define MAX_INF       1e18
#define MAX_NUM_SIZE  35
#define MAXN          (size_t)(2.5e5 + 10)

typedef long long int ll;
typedef unsigned long long int ull;

//快读函数声明
template< typename Type >
inline Type fread(Type* p = nullptr);

//快速输出函数
template<typename Type>
inline void fwrite(Type x);

struct Point {
    ll x, y;
    ll dist, id;

    Point() : x(0), y(0), dist(0) {}
    Point(ll _x, ll _y, ll _dist, ll _id) : x(_x), y(_y), dist(_dist), id(_id) {}
};

Point p[MAXN], s, t;
ll n, ans = INT_MAX;
char res;

inline ll get_path(const Point& a, const Point& b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

int main() {

#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    fread(&n);

    ll x = 0, y = 0;
    for (size_t i = 1; i <= n; i++) {
        char ch;
        std::cin >> ch;
        switch (ch) {
        case 'N':
            ++y;
            break;
        case 'S':
            --y;
            break;
        case 'E':
            ++x;
            break;
        case 'W':
            --x;
            break;
        }
        p[i] = Point(x, y, i, i);
    }

    std::sort(p, p + n + 1, [](const Point& a, const Point& b) {
        if (a.x == b.x) {
            return a.y < b.y;
        }
        return a.x < b.x;
    });

    for (size_t i = 0; i < n; i++) {
        if (p[i].x == p[i + 1].x && std::abs(p[i].dist - p[i + 1].dist) > 1) {
            //ans = std::min(get_path(p[i], p[i + 1]), ans);
            ll temp = get_path(p[i], p[i + 1]);
            Point temp_s = p[i].id < p[i + 1].id ? p[i] : p[i + 1];
            Point temp_t = p[i].id < p[i + 1].id ? p[i + 1] : p[i];
            if (temp < ans || (temp == ans && (temp_s.id < s.id || (temp_s.id == s.id && temp_t.id > t.id)))) {
                s = temp_s;
                t = temp_t;
                ans = temp;
                res = s.y > t.y ? 'S' : 'N';
            }
        }
    }

    std::sort(p, p + n + 1, [](const Point& a, const Point& b) {
        if (a.y == b.y) {
            return a.x < b.x;
        }
        return a.y < b.y;
    });

    for (size_t i = 0; i < n; i++) {
        if (p[i].y == p[i + 1].y && std::abs(p[i].dist - p[i + 1].dist) > 1) {
            //ans = std::min(get_path(p[i], p[i + 1]), ans);
            ll temp = get_path(p[i], p[i + 1]);
            Point temp_s = p[i].id < p[i + 1].id ? p[i] : p[i + 1];
            Point temp_t = p[i].id < p[i + 1].id ? p[i + 1] : p[i];
            if (temp < ans || (temp == ans && (temp_s.id < s.id || (temp_s.id == s.id && temp_t.id > t.id)))) {
                s = temp_s;
                t = temp_t;
                ans = temp;
                res = s.x > t.x ? 'W' : 'E';
            }
        }
    }

    printf(
        "%lld %lld %lld %c\n",
        ans, s.id, t.id, res
    );

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