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
#define TRIE_SIZE     6400005
#define ROOT          0
#define GET_BINARY_INDEX(n, i)  ((n >> uint32_t(32 - i - 1)) & 1)

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

struct tree_node {
    size_t Index[2];
    size_t cnt;

    tree_node() {
        Index[0] = 0;
        Index[1] = 0;
        cnt = 0;
        return;
    }
};

tree_node trie[TRIE_SIZE];
ll n;
uint32_t trie_cnt = 0, ans;

void insert(uint32_t val, uint32_t cnt = 0, uint32_t pos = ROOT) {
    ++trie[pos].cnt;
    if (cnt == 32) {
        return;
    }
    if (!trie[pos].Index[GET_BINARY_INDEX(val, cnt)]) {
        trie[pos].Index[GET_BINARY_INDEX(val, cnt)] = ++trie_cnt;
    }
    ll p = trie[pos].Index[GET_BINARY_INDEX(val, cnt)];
    insert(val, ++cnt, p);
    return;
}

uint32_t get_xor(uint32_t val, uint32_t cnt = 0, const uint32_t & this_pos = ROOT, const uint32_t & other_pos = ROOT, uint32_t sum = 0) {
    if (cnt == 32) {
        return sum;
    }
    if (trie[other_pos].Index[GET_BINARY_INDEX(val, cnt) ^ 1]) {
        return get_xor(
            val, ++cnt, 
            trie[this_pos].Index[GET_BINARY_INDEX(val, cnt)], 
            trie[other_pos].Index[GET_BINARY_INDEX(val, cnt) ^ 1], 
            sum << 1 | 1
        );
    }
    else {
        return get_xor(
            val, ++cnt,
            trie[this_pos].Index[GET_BINARY_INDEX(val, cnt)],
            trie[other_pos].Index[GET_BINARY_INDEX(val, cnt)],
            sum << 1
        );
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
    readf(&n);

    for (size_t i = 0; i < n; i++) {
        uint32_t val;
        readf(&val);
        insert(val);
        ans = std::max(ans, get_xor(val));
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