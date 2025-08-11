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
#include <numeric>
#include <ctype.h>
#include <cstdarg>
#include <climits>
#include <time.h>
#include <iostream>
#include <stdint.h>

#define _FREAD        true
#define MAX_INF       1e18
#define MAX_NUM_SIZE  35
#define MAXN          (size_t)(4e5+5)
#define GET_BIT(x, y) ((x >> (31-y)) & 1)

typedef long long int ll;
typedef unsigned long long int ull;

//快读函数声明
template< typename Type >
inline Type fread(Type* p = nullptr);

//快速输出函数
template<typename Type>
inline void fwrite(Type x);

template<size_t _SIZE_SUM>
struct Trie {
    struct _Trie_node {
        ll ind[2]; //子节点下标
        _Trie_node() {
            memset(ind, 0, sizeof(ind));
            return;
        }
    };

    _Trie_node _trie[_SIZE_SUM];
    size_t trie_cnt = 0;

    //贪心的，从高往第插入
    void insert(ll pos, ll val, ll deep);

    ll query(ll pos, ll val, ll cnt);

    inline void clear();
};

Trie<32 * MAXN> trie;
ll preXor[MAXN], bestL[MAXN], bestR[MAXN]; //[0,i]内左端点的区间的最大异或和 [i,n]内右端点的区间的最大异或和
ll n, ans = 0;

template<size_t _SIZE_SUM>
ll Trie<_SIZE_SUM>::query(ll pos, ll val, ll cnt) {
    //2中情况
    if (cnt == 32) {
        return 0;
    }
    ll res = 0, temp = GET_BIT(val, cnt);
    if (_trie[pos].ind[GET_BIT(val, cnt) ^ 1]) {
        res += (1 << (31 - cnt));
        res += query(_trie[pos].ind[GET_BIT(val, cnt) ^ 1], val, cnt + 1);
    }
    else {
        res += query(_trie[pos].ind[GET_BIT(val, cnt)], val, cnt + 1);
    }
    return res;
}

template<size_t _SIZE_SUM>
void Trie<_SIZE_SUM>::insert(ll pos, ll val, ll deep) {
    if (deep == 32) {
        return;
    }
    ll res = 0;
    if (!_trie[pos].ind[GET_BIT(val, deep)]) {
        _trie[pos].ind[GET_BIT(val, deep)] = ++trie_cnt;
    }
    insert(_trie[pos].ind[GET_BIT(val, deep)] = ++trie_cnt, val, deep + 1);
    return;
}

template<size_t _SIZE_SUM>
inline void Trie<_SIZE_SUM>::clear() {
    std::fill(_trie, _trie + trie_cnt + 1, _Trie_node());
    trie_cnt = 0;
    return;
}

int main() {

#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    fread(&n);

    for (size_t i = 1; i <= n; i++) {
        ll temp = fread<ll>();
        preXor[i] = preXor[i - 1] ^ temp;
    }

    trie.insert(0, 0, 0);
    for (size_t i = 1; i <= n; i++) {
        bestR[i] = std::max(bestR[i - 1], trie.query(0, preXor[i], 0));
        trie.insert(0, preXor[i], 0);
    }

    trie.clear();
    trie.insert(0, 0, 0);
    for (size_t i = 1; i <= n; i++) {
        bestL[i] = std::max(bestL[i + 1], trie.query(0, preXor[i], 0));
        trie.insert(0, preXor[n] ^ preXor[i - 1], 0);
    }

    for (size_t i = 1; i < n; i++) {
        ans = std::max(bestR[i], bestL[i + 1]);
    }

    printf("%lld\n", ans);


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