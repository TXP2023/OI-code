//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
//
//      By txp2024 www.luogu.com.cn  TXP2023 www.github.com
// 
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
#pragma once
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <ctype.h>
#include <cstdarg>
#include <climits>
#include <cstring>
#include <time.h>
#include <iostream>
#include <stdint.h>
#include <time.h>

#define READ        false
#define MAX_INF     1e18
#define MAX_NUM_SIZE 35
#define MAXN        5

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

struct tree_data {
    ll l = 0, r = 0;
    ll sum = 0;
};

ll appraise[MAXN];
ll root[MAXN];
tree_data tree[MAXN << 2];
ll n, m, tree_cnt;

ll insert(ll root, ll _Left, ll _Right, ll _Value) {
    ll P = ++tree_cnt;
    tree[P] = tree[root];
    tree[P].sum++;
    if (_Left == _Right) {
        return P;
    }
    ll mid = (_Left + _Right) >> 1;
    if (_Value <= mid) {
        tree[P].l = insert(tree[root].l, _Left, mid, _Value);
    }
    else {
        tree[P].r = insert(tree[root].r, mid + 1, _Right, _Value);
    }
    return P;
}

bool query(ll _Left_Root, ll _Right_Root, ll _Left, ll _Right, ll _Value_min, ll _Value_max) {
    if (tree[_Right_Root].sum - tree[_Left_Root].sum == 0) {
        return false;
    }

    if (_Left <= _Value_min && _Value_max <= _Right) {
        return true;
    }

    ll mid = (_Left + _Right) >> 1, ret = 0;
    if (_Value_min <= mid) {
        ret += query(tree[_Left_Root].l, tree[_Right_Root].l, _Left, mid, _Value_min, mid);
    }
    if (_Value_max > mid) {
        ret += query(tree[_Left_Root].r, tree[_Right_Root].r, mid + 1, _Right, mid + 1, _Value_max);
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

    //TODO
    readf(&n), readf(&m);

    for (size_t i = 1; i <= n; i++) {
        //readf(&appraise[i]);
        ll value = readf<ll>();
        root[i] = insert(root[i - 1], 0, MAXN, value);
    }

    for (size_t i = 0; i < m; i++) {
        ll b = readf<ll>(), x = readf<ll>(), Left = readf<ll>(), Right = readf<ll>(), ans = 0;
        for (ll j = 17; j >= 0; --j) {
            ll value_min, value_max, sum;
            if (b & (1 << j)) {
                /*如果b的二进制位此时为1 那么就要让a[i]这一位的二进制值尽可能为0 那么异或结果为1（贪心的）*/
                value_min = ans, value_max = ans + ((1 << j) - 1), sum = 0;
            }
            else {
                value_min = ans + (1 << j), value_max = ans + (1 << (j + 1) - 1), sum = 1;
            }
            if (!query(root[Left - 1], root[Right], 0, MAXN, value_min, value_max)) {
                sum ^= 1;
            }
            ans += (sum << j);
        }
        printf("%lld\n", ans);
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
 *      |  |  希望此代码无bug|  |  |     |         |      |
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