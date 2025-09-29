//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
//
//      By txp2024 www.luogu.com.cn  TXP2023 www.github.com
// 
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

#pragma once
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <numeric>
#include <ctype.h>
#include <stack>
#include <cstdarg>
#include <queue>
#include <climits>
#include <time.h>
#include <iostream>
#include <stdint.h>
#include <vector>

#define _FREAD        true
#define MAX_INF       0x7f7f7f7f7f7f7f7f
#define MAX_NUM_SIZE  35
#define MAX_LEN       (size_t)(1e6+5)

typedef long long int ll;
typedef unsigned long long int ull;

template<typename _T>
inline _T fpow(_T a, _T n, _T mod) {
    _T base = a, ret = 1;
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
//快读函数声明
template< typename Type >
inline Type fread(Type* p = nullptr);

//快速输出函数
template<typename Type>
inline void fwrite(Type x);

ll next[MAX_LEN];
char text[MAX_LEN], mod[MAX_LEN];
ll pi[MAX_LEN];
ll modLen, textLen;

struct stackData {
    ll i, j;

    stackData() = default;

    stackData(ll _i, ll _j) : i(_i), j(_j) {}
};

void get_pi() {
    pi[1] = 0;
    for (size_t i = 2, j = 0; i <= modLen; i++) {
        while (j && mod[i] != mod[j + 1]) {
            j = pi[j];
        }
        if (mod[i] == mod[j + 1]) {
            pi[i] = ++j;
        }
    }
}

void kmp() {
    std::stack<stackData> s;
    s.push(stackData{ 0, 0 });
    for (; s.top().i <= textLen; s.top().i = next[s.top().i]) {

        while (s.top().j && text[next[s.top().i]] != mod[s.top().j + 1]) {
            s.push(stackData{ s.top().i, pi[s.top().j] });
        }
    LOOP:
        if (text[next[s.top().i]] == mod[s.top().j + 1]) {
            ++s.top().j;
        }
        if (s.top().j == modLen) {
            next[s.top().i - s.top().j + 1] = next[s.top().i] + 1;
            if (s.size() > 1) {
                s.pop();
                goto LOOP;
            }

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

    scanf("%s%s", text + 1, mod + 1);

    modLen = strlen(mod + 1);
    textLen = strlen(text + 1);

    std::iota(next, next + MAX_LEN, 1
    );

    get_pi();

    kmp();

    for (size_t i = next[0]; i <= textLen; i = next[i]) {
        putchar(text[i]);
    }

#ifdef _RUN_TIME
    printf("The running duration is not less than %ld ms\n", clock() - start);
#endif // _RUN_TIME
    return 0;
}

template< typename Type >
inline Type fread(Type* p) {
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
inline void fwrite(Type x) {
    int sta[MAX_NUM_SIZE];
    int top = 0;
    do {
        sta[top++] = x % 10, x /= 10;
    } while (x);
    while (top) {
        putchar(sta[--top] + '0');
    }  // 48 是 '0'
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