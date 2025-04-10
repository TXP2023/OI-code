//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
//
//      By txp2024 www.luogu.com.cn  TXP2023 www.github.com
// 
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
// 这个题目非常神奇，你让hash值自然溢出就ac了，但是取余mode反而会wa
#pragma once
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <ctype.h>
#include <cstring>
#include <cstdarg>
#include <climits>
#include <time.h>
#include <iostream>
#include <stdint.h>

#define READ          false
#define MAX_INF       1e18
#define MAX_NUM_SIZE  35
#define MAX_LENGTH    (uint64_t)(200+1)
#define MAXN          (uint64_t)(30001)

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

const uint64_t base1 = 124355159, base2 = 14519, mode_1 = 1635173629, mode_2 = 100003;
char str[MAXN][MAX_LENGTH];
uint64_t Hash[MAXN][MAX_LENGTH], Reverse_Hash[MAXN][MAX_LENGTH];
ll n, lenght, ans;

inline void init(ll _Index) {
    for (size_t i = 1; i <= lenght; ++i) {
        Hash[_Index][i] = (Hash[_Index][i - 1] * base1 + str[_Index][i]);
    }
    for (size_t i = lenght; i >= 1; --i) {
        Reverse_Hash[_Index][i] = (Reverse_Hash[_Index][i + 1] * base2 + str[_Index][i]);
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

    //TODO
    readf(&n), readf(&lenght), readf<ll>();

    for (size_t i = 1; i <= n; i++) {
        scanf("\n%s", str[i] + 1);
        init(i);
    }

    for (size_t difference_Pos = 1; difference_Pos <= lenght; ++difference_Pos) {
        ll hash[MAXN];
        memset(hash, 0, sizeof(hash));
        for (size_t i = 1; i <= n; i++) {
            hash[i] = (Hash[i][difference_Pos - 1] * base1 + Reverse_Hash[i][difference_Pos + 1] * base2);
        }
        std::sort(hash + 1, hash + 1 + n);
        ll cnt = 1;
        for (size_t i = 2; i <= n; i++) {
            if (hash[i] == hash[i - 1]) {
                ans += cnt++;
            }
            else {
                cnt = 1;
            }
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