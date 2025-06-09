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

#define READ          false
#define MAX_INF       1e18
#define MAX_NUM_SIZE  35
#define MAXN          (uint64_t)(1e5+5)
#define LS(x)         ((x) << 1)
#define RS(x)         ((x) << 1 | 1)

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

std::map<ll, ll> mapping;
ll preSum[MAXN], arr[MAXN], segTree[MAXN << 2], disArr[MAXN];
ll n, valMax, valMin, dis_size, ans = 0;

inline size_t discretization() {
    memcpy(disArr + 1, preSum + 1, (n+1) * 8);
    std::sort(disArr + 1, disArr + n + 2);
    size_t cnt = std::unique(disArr + 1, disArr + n + 2) - disArr - 1;
    for (size_t i = 1; i <= cnt; i++) {
        mapping[disArr[i]] = i;
    }
    return cnt;
}

void insert(size_t pos, size_t left, size_t right, ll val) {
    ++segTree[pos];
    if (left == right) {
        return;
    }
    size_t mid = (left + right) >> 1;
    if (val <= mid) {
        insert(LS(pos), left, mid, val);
    }
    else {
        insert(RS(pos), mid + 1, right, val);
    }
    return;
}

ll query(size_t pos, size_t left, size_t right, ll valFirst, ll valLast) {
    if (valFirst > valLast) {
        return 0;
    }
    if (valFirst <= left && right <= valLast) {
        return segTree[pos];
    }
    ll sum = 0, mid = (left + right) >> 1;
    if (valFirst <= mid) {
        sum += query(LS(pos), left, mid, valFirst, valLast);
    }
    if (valLast > mid) {
        sum += query(RS(pos), mid + 1, right, valFirst, valLast);
    }
    return sum;
}

inline size_t small_bound(ll val) {
    int res = -1, left = 1, right = dis_size;
    while (left <= right) {
        int mid = (left + right) >> 1;
        if (disArr[mid] <= val) {
            res = mid;
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return res;
}

inline size_t big_bound(ll val) {
    int res = -1, left = 1, right = dis_size;
    while (left <= right) {
        int mid = (left + right) >> 1;
        if (disArr[mid] >= val) {
            res = mid;
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    return res;
}

#define DEBUG false

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    readf(&n), readf(&valMin), readf(&valMax);

    for (size_t i = 1; i <= n; i++) {
        readf(&arr[i]);
        preSum[i] = preSum[i - 1] + arr[i];
    }

    dis_size = discretization();

    insert(1, 1, dis_size, mapping[0]);
    //这个代码现在到9之前没问题
    for (size_t i = 1; i <= n; i++) {
        
#if DEBUG
        printf("%lld\n", mapping[preSum[i]]);
#endif // DEBUG

        ll max, min;
        max = small_bound(preSum[i] - valMin);
        min = std::lower_bound(disArr + 1, disArr + 1 + dis_size, preSum[i] - valMax) - disArr;
        if (max != -1 && min != -1) {
            ans += query(
                1, 1, dis_size,
                min,
                max
            );
        }
        
        insert(1, 1, dis_size, mapping[preSum[i]]);
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