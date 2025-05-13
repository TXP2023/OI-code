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
#define MAX_LENGTH    (uint64_t)(1e7+5)

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

char text[MAX_LENGTH], mod[MAX_LENGTH];
uint64_t Next[MAX_LENGTH], lastMod[MAX_LENGTH];
uint64_t textLength, modLength, ans = 0;


inline void get_next(uint64_t* _Arr, const char* _Str) {
    _Arr[1] = 0;
    ll _strLength = strlen(_Str + 1);
    for (size_t i = 2, length = 0/*lenght表示已经比较过的长度*/; i <= _strLength; ++i) {
        while (length && _Str[i] != _Str[length + 1]) {
            length = _Arr[length];
        }
        if (_Str[i] == _Str[length + 1]) {
            _Arr[i] = ++length;
        }
    }
    return;
}
inline std::vector<size_t> kmp(const uint64_t* _Next, const char* _Text, const char* _Mod) {
    std::vector<size_t> ret;
    size_t _textLength = strlen(_Text + 1), _modLength = strlen(_Mod + 1);
    for (size_t textIndex = 0, modIndex = 0/*已经比较过的合法长度*/; textIndex <= textLength; textIndex++) {
        while (modIndex && _Text[textIndex + 1] != _Mod[modIndex + 1]) {
            modIndex = _Next[modIndex];
        }
        if (_Text[textIndex + 1] == _Mod[modIndex + 1]) {
            ++modIndex;
        }
        if (modIndex == _modLength) {
            ret.push_back(textIndex - modIndex + 2);
            modIndex = _Next[modIndex];
        }
    }
    return ret;
}

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    readf(&modLength), readf(&textLength);

    scanf("%s\n%s", mod + 1, text + 1);

    get_next(Next, mod);

    std::vector<size_t> mod_pos = kmp(Next, text, mod);
    std::vector<size_t>::iterator it = mod_pos.begin();

    for (size_t i = 1, pos ; i <= textLength; i++) {
        if (*it == i) {
            pos = i;
            ++it;
        }
        lastMod[i] = pos;
    }

    for (size_t i = 1; i < modLength; i++) {

    }

    

    for (size_t i = 1, old_pos = -1; i <= textLength; ) {
        if (lastMod[i] != old_pos) {
            old_pos = lastMod[i];
        }
        i += modLength;
        ++ans;
        if (i > textLength) {
            puts("Fake");
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