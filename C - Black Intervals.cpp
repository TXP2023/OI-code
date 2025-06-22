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

#define MAX_INF       1e18
#define MAX_NUM_SIZE  35
#define MAXN          (size_t)(5e5+5)
#define LS(x)         ((x) << 1)
#define RS(x)         ((x) << 1 | 1)

typedef long long int ll;
typedef unsigned long long int ull;

//快读函数声明
template< typename Type >
inline Type readf(Type* p = nullptr);

//快速输出函数
template<typename Type>
inline void writef(Type x);

struct tree_node {
    bool left_color, right_color;
    ll cnt;

    tree_node() {
        left_color = 0;
        right_color = 0;
        cnt = 0;
    }
};


tree_node seg_tree[MAXN << 2];
ll n, q;

inline void push_up(size_t pos) {
    seg_tree[pos].cnt = seg_tree[LS(pos)].cnt + seg_tree[RS(pos)].cnt;
    seg_tree[pos].left_color = seg_tree[LS(pos)].left_color;
    seg_tree[pos].right_color = seg_tree[RS(pos)].right_color;
    if (seg_tree[LS(pos)].right_color && seg_tree[RS(pos)].left_color) {
        --seg_tree[pos].cnt;
    }
    return;
}

void update(const size_t& pos, const size_t& left,const size_t &right, size_t index) {
    if (left == right) {
        seg_tree[pos].cnt ^= 1;
        seg_tree[pos].left_color = seg_tree[pos].cnt;
        seg_tree[pos].right_color = seg_tree[pos].cnt;
        return;
    }

    ll mid = (left + right) >> 1;
    if (index <= mid) {
        update(LS(pos), left, mid, index);
    }
    else {
        update(RS(pos), mid + 1, right, index);
    }
    push_up(pos);
    return;
}

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    readf(&n), readf(&q);

    for (size_t i = 0; i < q; i++) {
        ll index = readf<ll>();
        update(1, 1, n, index);
        printf("%lld\n", seg_tree[1].cnt);
    }



#ifdef _RUN_TIME
    printf("The running duration is not less than %ld ms\n", clock() - start);
#endif // _RUN_TIME
    return 0;
}

template< typename Type >
inline Type readf(Type* p) {
    Type ret = 0, sgn = 0, ch = getchar();
    while (!isdigit(ch)) {
        sgn |= ch == '-', ch = getchar();
    }
    while (isdigit(ch)) ret = ret * 10 + ch - '0', ch = getchar();
    if (p != nullptr) {
        *p = Type(sgn ? -ret : ret);
    }
    return sgn ? -ret : ret;
}


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