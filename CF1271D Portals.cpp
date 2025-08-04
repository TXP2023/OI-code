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
#include <queue>
#include <iostream>
#include <stdint.h>

#define _FREAD        true
#define MAX_INF       1e18
#define MAX_NUM_SIZE  35
#define MAXN          (size_t)(5e3+5)
#define MAXM          (size_t)(3e5+5)

typedef long long int ll;
typedef unsigned long long int ull;

//快读函数声明
template< typename Type >
inline Type readf(Type* p = nullptr);

//快速输出函数
template<typename Type>
inline void writef(Type x);

struct City {
    int id;
    std::vector<size_t> road;
    ll attack, add, weight;
    City() : attack(0), add(0), weight(0), id(0), road({}) {}

    City(ll _Attack, ll _Defend, ll _Weight) : attack(_Attack), add(_Defend), weight(_Weight), id(0), road({}) {}

    inline bool operator <(const City& other)const {
        return this->weight < other.weight;
    }
};

struct Path {
    ll u, v;//u -> v
};

Path paths[MAXN];
City cities[MAXN];
bool flag[MAXN];
ll n, m, k, ans;

inline void slove() {
    //一个个的攻占
    std::priority_queue<City> heap;
    for (size_t i = 1; i <= n; i++) {
        //攻占分为2个阶段
        //准备士兵
        //部署防御

        //先是准备士兵
        if (k < cities[i].attack) {
            //目前的兵力不足以攻占这个城市
            ll temp = cities[i].attack - k;
            if (heap.size() < k) {
                puts("-1");
                exit(0);
            }
            while (k < cities[i].attack) {
                City temp = heap.top();
                heap.pop();
                k++;
                ans -= temp.weight;
            }
        }

        k += cities[i].add;
        //现在进攻完成，部署防御
        for (auto& j : cities[i].road) {
            if (!k) {
                br      eak;
            }
            ans += cities[j].weight;
            --k;
            heap.push(City(cities[j]));
        }
    }
    return;
}

int main() {

#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    readf(&n), readf(&m), readf(&k);

    for (size_t i = 1; i <= n; i++) {
        readf(&cities[i].attack), readf(&cities[i].add), readf(&cities[i].weight);
        cities[i].id = i;
    }

    for (size_t i = 1; i <= m; i++) {
        readf(&paths[i].u), readf(&paths[i].v);
    }

    std::sort(paths + 1, paths + 1 + m, [](const Path& a, const Path& b) {
        return a.u > b.u;
    });

    for (size_t i = 1; i <= m; i++) {
        if (flag[paths[i].v] || paths[i].v > paths[i].u) {
            continue;
        }
        flag[paths[i].v] = true;
        cities[paths[i].u].road.push_back(paths[i].v);
    }

    for (size_t i = 1; i <= n; i++) {
        if (!flag[i]) {
            cities[i].road.push_back(i);
        }
        std::sort(cities[i].road.begin(), cities[i].road.end(), [](const size_t& a, const size_t& b) {
            return cities[a].weight > cities[b].weight;
        });
    }

    slove();

    printf("%lld\n", ans);

#ifdef _RUN_TIME
    printf("The running duration is not less than %ld ms\n", clock() - start);
#endif // _RUN_TIME
    return 0;
}

template< typename Type >
inline Type readf(Type* p) {
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