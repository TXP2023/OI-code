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
#define MAXN          (size_t)(1e5+5)

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

struct shop {
    ll cost, weigh;


};

shop shops[MAXN];
ll farm[MAXN];
ll c[MAXN];
ll farm_cnt = 1, shop_cnt = 1;
ll n, m, r, ans = 0;

ll get_shop(ll val) {
    if (val <= shops[shop_cnt].weigh) {
        return val * shops[shop_cnt].weigh;
    }
    else {
        ll res = 0, cnt = shop_cnt;
        while (val && cnt <= m) {
            res += std::min(val, shops[cnt].weigh) * shops[cnt].cost;
            val -= std::min(val, shops[cnt].weigh);
            ++cnt;
        }
        return res;
    }
}

int main() {

#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    fread(&n), fread(&m), fread(&r);

    for (size_t i = 1; i <= n; i++) {
        fread(&c[i]);
    }

    for (size_t i = 1; i <= m; i++) {
        fread(&shops[i].weigh), fread(&shops[i].cost);
    }

    for (size_t i = 1; i <= r; i++) {
        fread(&farm[i]);
    }

    std::sort(c + 1, c + 1 + n);

    std::sort(farm + 1, farm + 1 + r, [](const ll& a, const ll& b) {
        return a > b;
    });

    std::sort(shops + 1, shops + 1 + m, [](const shop& a, const shop& b) {
        return a.cost > b.cost;
    });

    for (size_t i = 1; i <= n; i++) {
        //处理第i头牛

        if (get_shop(c[i]) < farm[farm_cnt]) {
            ans += farm[farm_cnt];
            ++farm_cnt;
        }
        else {
            while (c[i]) {
                ans += std::min(c[i], shops[shop_cnt].weigh) * shops[shop_cnt].cost;
                if (c[i] > shops[shop_cnt].weigh) {
                    c[i] -= shops[shop_cnt].weigh;
                    shops[shop_cnt].weigh -= shops[shop_cnt].weigh;
                    ++shop_cnt;
                }
                else {
                    shops[shop_cnt].weigh -= c[i];
                    c[i] = 0;
                }
            }
        }
    }

    printf("%lld\n", ans);



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