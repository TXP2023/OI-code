
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
#define GET_BINARY_INDEX(n, i)  ((n >> uint32_t(32 - i - 1)) & 1)
#define TRIE_SIZE     12800005
#define ROOT          0

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

struct trie_node {
    size_t child[2];
    uint32_t cnt;

    trie_node() {
        child[0] = 0;
        child[1] = 0;
        cnt = 0;
        return;
    }
};


trie_node trie[TRIE_SIZE];
uint32_t q, trie_cnt = 0;

void insert(const uint32_t &pos, uint32_t val, uint32_t val_cnt) {
    ++trie[pos].cnt;
    if (val_cnt == 32) {
        return;
    }
    if (!trie[pos].child[GET_BINARY_INDEX(val, val_cnt)]) {
        trie[pos].child[GET_BINARY_INDEX(val, val_cnt)] = ++trie_cnt;
    }
    insert(trie[pos].child[GET_BINARY_INDEX(val, val_cnt)], val, val_cnt + 1);
    return;
}

void remove(const uint32_t &pos, uint32_t val, uint32_t val_cnt) {
    --trie[pos].cnt;
    if (val_cnt == 32) {
        return;
    }
    remove(trie[pos].child[GET_BINARY_INDEX(val, val_cnt)], val, ++val_cnt);
    return;
}

uint32_t query(const uint32_t &pos, uint32_t val, uint32_t val_cnt) {
    if (val_cnt == 32) {
        return 0;
    }
    if (trie[trie[pos].child[GET_BINARY_INDEX(val, val_cnt) ^ 1]].cnt && trie[pos].child[GET_BINARY_INDEX(val, val_cnt) ^ 1] != 0) {
        return (1 << (32 - val_cnt)) + query(trie[pos].child[GET_BINARY_INDEX(val, val_cnt) ^ 1], val, ++val_cnt);
    }
    else {
        return query(trie[pos].child[GET_BINARY_INDEX(val, val_cnt)], val, ++val_cnt);
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
    readf(&q);

    for (size_t i = 0; i < q; i++) {
        scanf("\n");
        char opt = getchar();
        uint32_t val = readf<uint32_t>();
        switch (opt) {
        case '+':
            insert(ROOT, val, 0);
            break;
        case '-':
            remove(ROOT, val, 0);
            break;
        case '?':
            printf("%lld\n", query(ROOT, val, 0));
            break;
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