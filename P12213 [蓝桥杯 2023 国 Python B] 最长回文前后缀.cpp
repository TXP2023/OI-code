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
#define MAX_STR_LENGTH  (uint64_t)(1e5+5)

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

char str1[MAX_STR_LENGTH * 2], str2[MAX_STR_LENGTH * 2];
ull radius1[MAX_STR_LENGTH * 2], radius2[MAX_STR_LENGTH * 2], first_length1[MAX_STR_LENGTH * 2], first_length2[MAX_STR_LENGTH * 2];
ull strLength, ans = 0;

inline size_t str_init(char* _Str) {
    char _s[MAX_STR_LENGTH * 2];
    _s[0] = '$';
    ull cnt = 0, _length = strlen(_Str + 1);
    for (size_t i = 1; i <= _length; i++) {
        _s[++cnt] = '#';
        _s[++cnt] = _Str[i];
    }
    _s[++cnt] = '#';
    _s[++cnt] = '@';
    _s[++cnt] = '\0';
    memcpy(_Str, _s, sizeof(_s));
    return strlen(_Str);
}

inline void _Manacher(const char* str, ull * radius, ull * first_length) {
    size_t len = strlen(str);
    std::fill(radius, radius + len, 0);
    radius[1] = 1;
    for (ull i = 2, right_pos = 1, left_pos; i < len; i++) {
        //依据以前计算好的数据拓展
        if (i <= right_pos) {
            radius[i] = std::min(
                radius[right_pos - i + left_pos],
                right_pos - i + 1
            );
        }
        //暴力往外拓展
        while (str[i - radius[i]] == str[i + radius[i]]) {
            ++radius[i];
        }
        if (i + radius[i] - 1 > right_pos) {
            right_pos = i + radius[i] - 1, left_pos = i - radius[i] + 1;
        }
        first_length[i - radius[i] + 1] = std::max(first_length[i - radius[i] + 1], radius[i] - 1);//求出以该点为左端点的最长饱和回文串 
    }
    for (int64_t i = 3; i < len; i += 2) {
        first_length[i] = std::max(first_length[i - 2] - 2, first_length[i]);
    } 
}

void Manacher(char* op, ull* r, ull* l) {
    int mr = 0, c;
    for (ull i = 1; i < strLength; i++) {
        if (i < mr) r[i] = std::min(r[2 * c - i], mr - i);
        else r[i] = 1;
        while (op[i + r[i]] == op[i - r[i]]) r[i]++;
        if (i + r[i] - 1 > mr) mr = i + r[i] - 1, c = i;
        l[i - r[i] + 1] = std::max(l[i - r[i] + 1], r[i] - 1);//求出以该点为左端点的最长饱和回文串 
    }
    for (ull i = 3; i < strLength; i += 2) l[i] = std::max(l[i - 2] - 2, l[i]);
    //求出以该点为左端点的最长回文串（含饱和回文串与不饱和回文串） 
}

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    scanf("%s\n", str1 + 1);
    strLength = strlen(str1 + 1);

    for (size_t i = 1; i <= strLength; i++) {
        str2[i] = str1[strLength - i + 1];
    } 

    strLength = str_init(str1);
    str_init(str2);

    _Manacher(str1, radius1, first_length1);
    _Manacher(str2, radius2, first_length2);
    
    for (size_t i = 2; i <= strLength; i += 2) {
        ans = std::max(std::max(i - 2 + first_length1[i - 1], i - 2 + first_length2[i - 1]), ans);
        if (str1[i] != str2[i]) {
            break;
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