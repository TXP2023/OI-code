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
#define MAXM          (size_t)(2e5)
#define MAXN          (size_t)(1e5)

typedef long long int ll;
typedef unsigned long long int ull;

//�����������
template< typename Type >
inline Type readf(Type* p = nullptr);

//�����������
template<typename Type>
inline void writef(Type x);

struct tree_node {
    size_t ls, rs;
    ll fa, deep;
};

tree_node tree[MAXN << 4];
size_t root[MAXM];
ll version_root;
ll n, m, root_cnt = 0;

inline size_t build(ll left = 1, ll right = n) {
    ++root_cnt;
    if (left == right) {
        tree[root_cnt].fa = left;
        return root_cnt;
    }
    ll mid = (left + right) >> 1;
    tree[root_cnt].ls = build(left, mid);
    tree[root_cnt].rs = build(mid + 1, right);
    return root_cnt;
}



int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    readf(&n), readf(&m);

    root[0] = build();
    version_root = root[0];
    for (size_t i = 1; i <= m; i++) { 
        char opt[3], x, y;
        scanf("%s", opt);
        switch (opt[0]) {
        case '1':
            readf(&x), readf(&y);

            break;
        case '2':
            readf(&x);
            root[i] = root[x];
            break;
        case '3':
            break;
        }
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
    while (top) putchar(sta[--top] + '0');  // 48 �� '0'
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