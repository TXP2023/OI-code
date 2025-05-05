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

#define READ          false
#define MAX_INF       1e18
#define MAX_NUM_SIZE  35
#define MAXN          (uint32_t)(1e6+5)
#define mod           19930726

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

uint32_t length[MAXN];
char str[MAXN];
uint32_t cnt[MAXN];
uint32_t n, k, max_length = 0, multiple = 1;


inline uint32_t fast_pow(uint32_t a, uint32_t n) {
    uint32_t base = a, ret = 1;
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

inline void _Manacher(const char* _str) {
    uint32_t len = strlen(_str), max_length = 0;
    length[1] = 1;
    for (uint32_t i = 2, right_pos = 1, left_pos; i < len; i++) {
        //依据以前计算好的数据拓展
        if (i <= right_pos) {
            length[i] = std::min(
                length[right_pos - i + left_pos],
                right_pos - i + 1
            );
        }
        //暴力往外拓展
        while (_str[i - length[i]] == _str[i + length[i]]) {
            ++length[i];
        }
        if (i + length[i] - 1 > right_pos) {
            right_pos = i + length[i] - 1, left_pos = i - length[i] + 1;
        }
        max_length = std::max(length[i], max_length);

    }
}


int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    //TODO
    readf(&n), readf(&k);

    str[0] = '@';
    scanf("%s", str + 1);
    str[n + 1] = '$';

    _Manacher(str);
    size_t len = strlen(str);

    for (uint32_t i = 1; i < len; i++) {
        max_length = std::max(max_length, length[i] * 2 - 1);
        ++cnt[length[i] * 2 - 1];
    }

    --cnt[1];

    for (ll i = max_length; i >=0 ; i--) {
        cnt[i] += cnt[i + 1];
    }
    for (size_t i = max_length; i > 0 && k > 0; i-=2) {
        if (k > cnt[i]) {
            multiple *= fast_pow(i, cnt[i]);
            multiple %= mod;
            k -= cnt[i];
        }
        else {
            multiple *= fast_pow(i, k);
            multiple %= mod;
            k = 0;
        }

    }

    if (k > 0) {
        puts("-1");
    }
    else {
        printf("%lld\n", multiple % mod);
    }
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