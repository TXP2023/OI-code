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
#include <cmath>

#define _FREAD        true
#define MAX_INF       1e18
#define MAX_NUM_SIZE  35
#define MAXN          (size_t)(1e5+5)
#define SQRTN         320

typedef long long int ll;
typedef unsigned long long int ull;

//快读函数声明
template< typename Type >
inline Type readf(Type* p = nullptr);

//快速输出函数
template<typename Type>
inline void writef(Type x);

struct Block {
    ll minNum, num; //块内最大的开平方指数 和整个块被开放数
    ll sum;
};

Block blocks[SQRTN];
ll belong[MAXN], arr[MAXN], cnt[MAXN]; //cnt 记录每个数被单独开了多少次方
ll n, m, block_size, sqrt_cnt, max_val;

//更新区间最小被开放数
inline void get_cnt(ll x) {
    blocks[x].minNum = INT32_MAX;
    for (size_t i = (x - 1) * block_size + 1; i <= std::min(x * block_size, n); i++) {
        blocks[x].minNum = std::min(blocks[x].minNum, cnt[i] + blocks[x].num);
    }
    return;
}

inline void update(ll l, ll r) {
    if (belong[l] == belong[r]) {
        if (blocks[belong[l]].minNum >= sqrt_cnt) {
            return;
        }
        for (size_t i = l; i <= r; i++) {
            blocks[belong[i]].sum -= arr[i];
            arr[i] = (ll)std::sqrt(arr[i]);
            blocks[belong[i]].sum += arr[i];
        }
        get_cnt(belong[l]);
        return;
    }
    if (blocks[belong[l]].minNum < sqrt_cnt) {
        for (size_t i = l; i <= belong[l] * block_size; i++) {
            ++cnt[i];
            blocks[belong[i]].sum -= arr[i];
            arr[i] = (ll)std::sqrt(arr[i]);
            blocks[belong[i]].sum += arr[i];
        }
        get_cnt(belong[l]);
    }

    for (size_t i = belong[l] + 1; i < belong[r]; i++) {
        if (blocks[i].minNum < sqrt_cnt) {
            ++blocks[i].num;
            ++blocks[i].minNum;
            for (size_t j = (i - 1) * block_size + 1; j <= i * block_size; j++) {
                blocks[i].sum -= arr[j];
                arr[j] = (ll)std::sqrt(arr[j]);
                blocks[i].sum += arr[j];
            }
        }
    }
    if (blocks[belong[r]].minNum < sqrt_cnt) {
        for (size_t i = (belong[r] - 1) * block_size + 1; i <= r; i++) {
            ++cnt[i];
            blocks[belong[i]].sum -= arr[i];
            arr[i] = (ll)std::sqrt(arr[i]);
            blocks[belong[i]].sum += arr[i];
        }
        get_cnt(belong[r]);
    }
    return;
}

inline ll query(ll l, ll r) {
    ll res = 0;
    if (belong[l] == belong[r]) {
        if (blocks[belong[l]].minNum >= sqrt_cnt) {
            return r - l + 1;
        }
        for (size_t i = l; i <= r; i++) {
            res += arr[i];
        }
        return res;
    }
    if (blocks[belong[l]].minNum < sqrt_cnt) {
        for (size_t i = l; i <= belong[l] * block_size; i++) {
            res += arr[i];
        }
    }
    else {
        res += belong[l] * block_size - l + 1;
    }

    for (size_t i = belong[l] + 1; i < belong[r]; i++) {
        if (blocks[i].minNum < sqrt_cnt) {
            res += blocks[i].sum;
        }
        else {
            res += block_size;
        }
    }
    if (blocks[belong[r]].minNum < sqrt_cnt) {
        for (size_t i = (belong[r] - 1) * block_size + 1; i <= r; i++) {
            res += arr[i];
        }
    }
    else {
        res += r - (belong[r] - 1) * block_size;
    }
    return res;
}

int main() {

#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    readf(&n);

    block_size = std::sqrt(n) + 1;
    for (size_t i = 1; i <= n; i++) {
        readf(&arr[i]);
        max_val = std::max(arr[i], max_val);
        belong[i] = (i - 1) / block_size + 1;
        blocks[belong[i]].sum += arr[i];
    }

    readf(&m);

    while (max_val != 1) {
        ++sqrt_cnt;
        max_val = (ll)std::sqrt(max_val);
    }

    while (m--) {
        ll k, l, r;
        readf(&k), readf(&l), readf(&r);
        if (l > r) {
            std::swap(l, r);
        }
        if (k == 0) {
            update(l, r);
        }
        else {
            printf("%lld\n", query(l, r));
        }
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