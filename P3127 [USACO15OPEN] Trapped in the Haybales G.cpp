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
#include <iostream>
#include <stdint.h>
#include <map>
#include <set>

#define READ          false
#define MAX_INF       1e18
#define MAX_NUM_SIZE  35
#define MAXN          100005

typedef long long int ll;
typedef unsigned long long int ull;

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

struct HayStack {
    ll pos, weight;
};

std::map<ll, int> mapping;
std::set<ll> set;
HayStack hays[MAXN];
ll pos[MAXN];
bool flag[MAXN];
ll n, ans;

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    readf(&n);

    for (size_t i = 1; i <= n; i++) {
        readf(&hays[i].weight), readf(&hays[i].pos);
        pos[i] = hays[i].pos;
    }

    std::sort(pos + 1, pos + 1 + n, 
        [](const ll &a, const ll &b) {
            return a < b; 
        }
    );

    for (size_t i = 1; i <= n; i++) {
        mapping[pos[i]] = i;
    }

    std::sort(hays + 1, hays + 1 + n,
        [](const HayStack &a, const HayStack &b) {
            return a.weight > b.weight;
        }
    );

    set.insert(hays[1].pos);

    for (size_t i = 2; i <= n; i++) {
        if (*(set.begin()) < hays[i].pos) {
            //二分查找第一个大于hays[i].pos的位置
            std::set<ll>::iterator it = --set.upper_bound(hays[i].pos);
            ll left = mapping[*it], right = mapping[hays[i].pos];
            if (pos[right] - pos[left] <= hays[i].weight && !flag[left]) {
                for (size_t i = left; i < right; i++) {
                    flag[i] = true;
                }
            }
        }
        if (*(--set.end()) > hays[i].pos) {
            //二分查找第一个大于hays[i].pos的位置
            std::set<ll>::iterator it = set.upper_bound(hays[i].pos);
            ll left = mapping[hays[i].pos], right = mapping[*it];
            if (pos[right] - pos[left] <= hays[i].weight && !flag[left]) {
                for (size_t i = left; i < right; i++) {
                    flag[i] = true;
                }
            }
        }
    }

    for (int i = 1; i < n; i++) {
        if (flag[i]) {
            ans += pos[i + 1] - pos[i];
        }    
    }

    printf("%lld\n", ans);

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