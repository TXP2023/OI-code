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
#include <math.h>
#include <cmath>
#include <time.h>
#include <iostream>
#include <stdint.h>
#include <vector>

#define _FREAD        true
#define MAX_INF       0x7f7f7f7f7f7f7f7f
#define MAX_NUM_SIZE  35
#define MAXN          (size_t)(3005)

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

struct Circle {
    ll x, y, r;
};

struct  Edge {
    ll v, next;
};

struct queData {
    ll u, w;

    bool operator <(const queData& other)const {
        return w > other.w;
    }
};

Circle c[MAXN];
Edge e[MAXN * MAXN];
ll head[MAXN], cnt;
ll dist[MAXN];
bool flag[MAXN];
Point s, t;
std::priority_queue<queData> que;
ll n;

void add_edge(ll u, ll v) {
    ++cnt;
    e[cnt] = { v, head[u] };
    head[u] = cnt;
    return;
}

ll f(Point a, Point b) {
    return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
}

void djstl() {

    while (!que.empty()) {
        ll u = que.top().u, w = que.top().w;
        que.pop();
        flag[u] = true;
        for (size_t i = head[u]; i; i = e[i].next) {
            if (w + 1 < dist[e[i].v]) {
                dist[e[i].v] = w + 1;
                que.push({ e[i].v , dist[e[i].v] });
            }
        }
    }
    return;
}



bool isCos
(ll x1, ll y1, ll r1, ll x2, ll y2, ll r2) {

    ll dx = x1 - x2;
    ll dy = y1 - y2;
    ll distanceSq = dx * dx + dy * dy;
    ll radiusSum = r1 + r2;
    ll radiusDiff = fabs(r1 - r2);

    return distanceSq <= radiusSum * radiusSum &&
        distanceSq >= radiusDiff * radiusDiff;
}

// 判断两个圆是否相交（包括相切）
bool circlesIntersect(ll x1, ll y1, ll r1,
                     ll x2, ll y2, ll r2) {
    // 计算圆心距离
    ll dx = x1 - x2;
    ll dy = y1 - y2;
    ll distance = sqrt(dx * dx + dy * dy);

    // 判断是否相交
    // 相交条件：|r1 - r2| <= distance <= r1 + r2
    return (distance <= r1 + r2) && (distance >= fabs(r1 - r2));
}


int main() {

#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    fread(&n);

    fread(&s.x), fread(&s.y), fread(&t.x), fread(&t.y);

    for (size_t i = 1; i <= n; i++) {
        ll x, y, r;
        fread(&x), fread(&y), fread(&r);
        c[i] = { x, y, r };
    }

    for (size_t i = 2; i <= n; i++) {
        for (size_t j = 1; j < i; j++) {
            if (isCos(c[i].x, c[i].y, c[i].r, c[j].x, c[j].y, c[j].r)) {
                add_edge(i, j);
                add_edge(j, i);
            }
        }
    }

    memset(dist, 0x7f, sizeof dist);
    //判断s处于那个圆上
    for (size_t i = 1; i <= n; i++) {
        if (c[i].r == f({ c[i].x,c[i].y }, s)) {
            dist[i] = 0;
            que.push(queData{ (ll)i, 0 });
        }
    }

    djstl();

    //判断是否到达终点
    for (size_t i = 1; i <= n; i++) {
        if (c[i].r == f({ c[i].x,c[i].y }, t)) {
            if (dist[i] != MAX_INF) {
                puts("Yes");
                return 0;
            }
        }
    }

    puts("No");
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