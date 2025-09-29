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
#include <cstdarg>
#include <queue>
#include <climits>
#include <map>
#include <time.h>
#include <iostream>
#include <stdint.h>
#include <vector>

#define _FREAD        true
#define MAX_INF       0x7f7f7f7f7f7f7f7f
#define MAX_NUM_SIZE  35
#define MAXN          (size_t)(2e6+5)

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

struct node {
    ll ls, rs;
    ll cnt;

    node() = default;
};

struct Task {
    ll l, r, val;

    Task() = default;

    Task(ll _l, ll _r, ll _val) : l(_l), r(_r), val(_val) {}
};

node tree[MAXN << 5];
ll root[MAXN], arr[MAXN], dis_arr[MAXN << 1], n, m, cnt = 0, val_size, dis_cnt;
Task tasks[MAXN];
std::map<ll, ll> mapping;

ll ins(ll pre, ll l, ll r, ll val) {
    ll now = ++cnt;
    tree[now] = tree[pre];
    ++tree[now].cnt;
    if (l == r) {
        return now;
    }
    ll mid = (l + r) >> 1;
    //tree[now] = tree[pre];
    if (val <= mid) {
        tree[now].ls = ins(tree[pre].ls, l, mid, val);
    }
    else {
        tree[now].rs = ins(tree[pre].rs, mid + 1, r, val);
    }
    return now;
}

ll ask(ll pre, ll now, ll l, ll r, ll val) {
    if (l == r) {
        return tree[now].cnt - tree[pre].cnt;
    }
    ll mid = (l + r) >> 1, res = 0;
    res += ask(tree[pre].ls, tree[now].ls, l, mid, val);
    if (mid < val) {
        res += ask(tree[pre].rs, tree[now].rs, mid + 1, r, val);
    }
    return res;
}

void dis() {
    //memcpy(temp, arr, sizeof arr);
    std::sort(dis_arr + 1, dis_arr + 1 + dis_cnt);
    val_size = std::unique(dis_arr + 1, dis_arr + 1 + dis_cnt) - (dis_arr + 1);
    for (size_t i = 1; i <= val_size; i++) {
        mapping[dis_arr[i]] = i;
    }
    for (size_t i = 1; i <= n; i++) {
        arr[i] = mapping[arr[i]];
    }
    //val_size = size;
    return;
}

int main() {

#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    fread(&n), fread(&m);

    for (size_t i = 1; i <= n; i++) {
        fread(&arr[i]);
        dis_arr[++dis_cnt] = arr[i];
    }





    for (size_t i = 1; i <= m; i++) {
        ll l, r, val;

        fread(&l), fread(&r), fread(&val);
        tasks[i] = Task(l, r, val);
        dis_arr[++dis_cnt] = val;
    }

    dis();

    for (size_t i = 1; i <= n; i++) {
        root[i] = ins(root[i - 1], 1, val_size, arr[i]);
    }

    for (size_t i = 1; i <= m; i++) {
        ll l, r, val;
        l = tasks[i].l;
        r = tasks[i].r;
        val = mapping[tasks[i].val];
        printf("%lld\n", ask(root[l - 1], root[r], 1, val_size, val));
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