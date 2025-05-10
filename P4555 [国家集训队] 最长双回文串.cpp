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
#define MAX_STR_LENGTH  (ull)(1e5+2)

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

char str[MAX_STR_LENGTH * 2];
ull radius[MAX_STR_LENGTH * 2]; //以字符i为中心的回文串半径
ull first_length[MAX_STR_LENGTH * 2], last_length[MAX_STR_LENGTH * 2];//  以字符i为左(右)端点的回文串长度  存储的长度是不统计输入字符集外的字符的
ull length, ans = 0;

inline ull str_init(char* _Str) {
    char _s[MAX_STR_LENGTH * 2];
    _s[0] = '$';
    ull _strLength = strlen(_Str + 1), cnt = 1;
    for (size_t i = 1; i <= _strLength; i++) {
        _s[cnt++] = '#';
        _s[cnt++] = _Str[i];
    }
    _s[cnt++] = '#';
    _s[cnt++] = '@';
    _s[cnt] = '\0';
    memcpy(_Str, _s, sizeof(_s));
    return strlen(_Str);
}

inline void manacher() {
    radius[1] = 1;
    ull _strLength = strlen(str);
    for (ull i = 2, right_pos = 1, left_pos; i < _strLength; i++) {
        if (i <= right_pos) {
            radius[i] = std::min(
                radius[right_pos - i + left_pos],
                right_pos - i + 1
            );
            first_length[i - radius[i] + 1] = std::max(first_length[i - radius[i] + 1], radius[i] - 1);
            last_length[i + radius[i] - 1] = std::max(last_length[i + radius[i] - 1], radius[i] - 1);
        }
        //暴力往外拓展
        while (str[i - radius[i]] == str[i + radius[i]]) {
            ++radius[i];
            first_length[i - radius[i] + 1] = std::max(first_length[i - radius[i] + 1], radius[i] - 1);
            last_length[i + radius[i] - 1] = std::max(last_length[i + radius[i] - 1], radius[i] - 1);
        }
        if (i + radius[i] - 1 > right_pos) {
            right_pos = i + radius[i] - 1, left_pos = i - radius[i] + 1;
        }
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
    scanf("%s\n", str + 1);

    length = str_init(str);

    manacher();

    for (size_t i = 1; i < length; i+=2) {
        if (first_length[i] && last_length[i]) {
            ans = std::max(ans, last_length[i] + first_length[i]);
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