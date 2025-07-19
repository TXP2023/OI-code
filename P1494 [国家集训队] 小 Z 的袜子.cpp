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
#include <cmath>
#include <iostream>
#include <stdint.h>

#define _FREAD     true
#define MAX_INF       1e18
#define MAX_NUM_SIZE  35
#define MAXN          (size_t)(5e4+5)
#define MAXM          (size_t)(5e4+5)

typedef long long int ll;
typedef unsigned long long int ull;

//快读函数声明
template< typename Type >
inline Type readf(Type* p = nullptr);

//快速输出函数
template<typename Type>
inline void writef(Type x);

struct Task {
    ll l, r, id;
};

struct Results {
    ll num, den; //颜色相同num， 组合数量den

    Results() {
        num = 0;
        den = 1;
        return;
    }
};

Task tasks[MAXM];
ll color[MAXN], arr[MAXN];
Results res[MAXM];
ll n, m, block_size, sum = 0;

inline ll gcd(ll a, ll b) {
    if (!b) {
        return a;
    }
    return gcd(b, a % b);
}

int main() {

#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    readf(&n), readf(&m);

    block_size = (ll)std::sqrt(n);

    for (size_t i = 1; i <= n; i++) {
        readf(&arr[i]);
    }

    for (size_t i = 1; i <= m; i++) {
        readf(&tasks[i].l), readf(&tasks[i].r);
        tasks[i].id = i;
    }

    std::sort(tasks + 1, tasks + 1 + m, [](const Task& a, const Task& b) {
        if ((a.l + 1) / block_size != (b.l + 1) / block_size) {
            //如果2个询问不在同一块内，则按照所处块位置排序
            return (a.l + 1) / block_size < (b.l + 1) / block_size;
        }
        //这里有一个优化，在左端点位于同一块内，如果是奇数块的话让r小于排序, 否则大于排序。这样可以省去每次跨块时，右指针复原位置的操作
        if (((a.l + 1) / block_size) & 1) {
            return a.r < b.r;
        }
        else {
            return a.r > b.r;
        }
    });

    //接下来处理询问
    for (size_t i = 1, l = 1, r = 0; i <= m; i++) {
        ll rangeL = tasks[i].l, rangeR = tasks[i].r;
        while (l < rangeL) {
            --color[arr[l]];
            sum -= color[arr[l]];
            ++l;
        }
        while (l > rangeL) {
            --l;
            sum += color[arr[l]];
            ++color[arr[l]];
        }
        while (r < rangeR) {
            ++r;
            sum += color[arr[r]];
            ++color[arr[r]];
        }
        while (r > rangeR) {
            --color[arr[r]];
            sum -= color[arr[r]];
            --r;
        }
        if (sum) {
            ll GCD = gcd(sum, (r - l + 1) * (r - l) / 2);
            res[tasks[i].id].num = sum / GCD;
            res[tasks[i].id].den = (r - l + 1) * (r - l) / 2 / GCD;
        }
    }

    for (size_t i = 1; i <= m; i++) {
        printf("%lld/%lld\n", res[i].num, res[i].den);
    }


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
    scanf("%lld", p);

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