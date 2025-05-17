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
#define MAX_LENGTH    (uint64_t)(1e5+5)

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

char str[MAX_LENGTH], reverseStr[MAX_LENGTH], manacherStr[MAX_LENGTH * 2 + 3];
size_t firstLength[MAX_LENGTH], radius[MAX_LENGTH], lastLength[MAX_LENGTH];
size_t strLength, manacherLength, ans = 0;

inline size_t init() {
    strLength = strlen(str + 1);
    size_t cnt = 0;
    manacherStr[cnt++] = '@';
    for (size_t i = 1; i <= strLength; i++) {
        reverseStr[strLength - i + 1] = str[i];
        manacherStr[cnt++] = '#';
        manacherStr[cnt++] = str[i];
    }
    manacherStr[cnt++] = '#';
    manacherStr[cnt] = '$';
    return cnt;
}

inline void manacher() {
    radius[1] = 1;
    for (size_t i = 2, right_pos = 1, left_pos; i < manacherLength; i++) {
        size_t pre_length = i / 2;
        if (i <= right_pos) {
            radius[i] = std::min(
                radius[right_pos - i + left_pos],
                right_pos - i + 1
            );
           
        }
        //暴力往外拓展
        while (manacherStr[i - radius[i]] == manacherStr[i + radius[i]]) {
            ++radius[i];
        }
        if (manacherStr[i] == '#') {
            firstLength[pre_length - (radius[i] - 1) / 2 + 1] = std::max(firstLength[pre_length - (radius[i] - 1) / 2 + 1], radius[i] - 1);
            lastLength[pre_length + (radius[i] - 1) / 2] = std::max(lastLength[pre_length + (radius[i] - 1) / 2], radius[i] - 1 );
        }
        else {
            firstLength[pre_length - (radius[i] - 1) / 2] = std::max(firstLength[pre_length - (radius[i] - 1) / 2], radius[i] - 1);
            lastLength[pre_length + (radius[i] - 1) / 2] = std::max(lastLength[pre_length + (radius[i] - 1) / 2], radius[i] - 1);
        }
        if (i + radius[i] - 1 > right_pos) {
            right_pos = i + radius[i] - 1, left_pos = i - radius[i] + 1;
        }
    }
    return;
}

int main() {
#ifdef _FREOPEN
    freopen("D:\\bobi2\\development\\work spaces\\OI-code\\input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    scanf("%s", str + 1);

    manacherLength = init();

    manacher();

    lastLength[0] = 0;
    firstLength[strLength + 1] = 0;
    for (size_t i = 0; i <= strLength; i++) {
        if (str[i] != reverseStr[i] && i != 0) {
            break;
        }
        ans = std::max(ans, std::max(i * 2 + firstLength[i+1], i * 2 + lastLength[strLength - i]));
    }

    printf("%lld\n", ans);

#ifdef _RUN_TIME
    printf("The running duration is not less than %ld ms\n", clock() - start);
#endif // _RUN_TIME

    system("pause");
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