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
#define MAX_MOD_NUM   205
#define MAX_MOD_LEN   15
#define MAX_TEXT_LEN  (size_t)(2e5+5)

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

char modStrs[MAX_MOD_NUM][MAX_MOD_LEN], text[MAX_TEXT_LEN];
bool modTag[MAX_MOD_NUM][MAX_TEXT_LEN]; //modTag[i][j]表示文本串的第j位是不是第个模式串的起点
size_t modLen[MAX_MOD_NUM], dp[MAX_TEXT_LEN];
size_t modNum = 0, textLength;

inline void __get_next(uint64_t* _Arr, const char* _Str) {
    ll _strLength = strlen(_Str + 1);
    _Arr[1] = 0;
    memset(_Arr, 0, (_strLength + 1) * 8);
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
inline void __kmp(const uint64_t* _Next, const char* _Text, const char* _Mod, size_t id) {
    std::vector<size_t> ret;
    size_t _textLength = strlen(_Text + 1), _modLength = strlen(_Mod + 1);
    for (size_t textIndex = 0, modIndex = 0/*已经比较过的合法长度*/; textIndex <= _textLength; textIndex++) {
        while (modIndex && _Text[textIndex + 1] != _Mod[modIndex + 1]) {
            modIndex = _Next[modIndex];
        }
        if (_Text[textIndex + 1] == _Mod[modIndex + 1]) {
            ++modIndex;
        }
        if (modIndex == _modLength) {
            //ret.push_back(textIndex - modIndex + 2);
            modTag[id][textIndex - modIndex + 2] = true;
            modIndex = _Next[modIndex];
        }
    }
    return;
}

inline void kmp(size_t id) {
    uint64_t Next[MAX_MOD_LEN];
    __get_next(Next, modStrs[id]);
    __kmp(Next, text, modStrs[id], id);
    return;
}

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    while (scanf("%s", modStrs[modNum+1] + 1), modStrs[modNum + 1][1] != '.') {
        ++modNum;
        modLen[modNum] = strlen(modStrs[modNum] + 1);
    }

    //scanf("%s", text + 1);

    ll cnt = 1;
    while (1) {
        char s[80];
        if (~scanf("%s", s + 1)) {
            size_t len = strlen(s + 1);
            for (size_t i = 1; i <= len; i++) {
                text[cnt++] = s[i];
            }
        }
        else {
            break;
        }
    }
    textLength = strlen(text + 1);

    for (size_t i = 1; i <= modNum; i++) {
        kmp(i);
    }
    
    dp[0] = 1;
    for (size_t i = 1; i <= textLength; i++) {
        for (size_t j = 1; j <= modNum && !dp[i]; j++) {
            if (i - modLen[j] >= 0) {
                dp[i] = dp[i - modLen[j]] && modTag[j][i - modLen[j] + 1];
            }
        }
    }

    for (ll i = textLength; i >= 0 ; --i) {
        if (dp[i]) {
            printf("%lld\n", i);
            return 0;
        }
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