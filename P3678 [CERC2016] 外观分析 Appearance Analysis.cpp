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
#define MAX_SIZE      (uint64_t)(111+5)
#define BASE          131
#define MOD           (uint64_t)(1e9+7)

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

size_t length, width, window_length, window_width, ans, cnt1, cnt2;
std::map<uint64_t, bool> map;
char wall[MAX_SIZE][MAX_SIZE];

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    //TODO
    readf(&length), readf(&width);

    for (int i = 0; i < length; i++) {
        std::cin >> wall[i];
    }
    for (int i = 0; i < length; i++) {
        if (wall[i][1] == '#') cnt1++;
    }
    for (int i = 0; i < width; i++) {
        if (wall[1][i] == '#') cnt2++;
    }
    cnt1 = (length - cnt1) / (cnt1 - 1);
    cnt2 = (width - cnt2) / (cnt2 - 1); // 计算每幅画的长和宽

    for (int i = 1; i < length; i += cnt1 + 1) {
        for (int j = 1; j < width; j += cnt2 + 1) {
            uint64_t hash1 = 0, hash2 = 0, hash3 = 0, hash4 = 0;
            for (int k = 0; k < cnt1; k++) {
                for (int l = 0; l < cnt2; l++) {
                    hash1 = hash1 * BASE + wall[i + k][j + l]; // 计算哈希值，下同
                }
            }
            if (cnt1 == cnt2)
                for (int l = cnt2 - 1; l > -1; l--) {
                    for (int k = 0; k < cnt1; k++) {
                        hash2 = hash2 * BASE + wall[i + k][j + l];
                    }
                }
            for (int k = cnt1 - 1; k > -1; k--) {
                for (int l = cnt2 - 1; l > -1; l--) {
                    hash3 = hash3 * BASE + wall[i + k][j + l];
                }
            }
            if (cnt1 == cnt2)
                for (int l = 0; l < cnt2; l++) {
                    for (int k = cnt1 - 1; k > -1; k--) {
                        hash4 = hash4 * BASE + wall[i + k][j + l];
                    }
                }
            if (!map.count(hash1)) {
                ++ans;
                map[hash1] = map[hash2] = map[hash3] = map[hash4] = 1;
            }
            // cout << hex << "0x" << hash1 << " 0x" << hash2 << " 0x" << hash3 << " 0x" << hash4 << endl;
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