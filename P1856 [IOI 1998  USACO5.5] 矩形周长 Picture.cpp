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
#include <time.h>
#include <iostream>
#include <stdint.h>
#include <vector>

#define _FREAD        true
#define MAX_INF       0x7f7f7f7f7f7f7f7f
#define MAX_NUM_SIZE  35
#define MAXN          5005
#define LS(p)         ((p) << 1)
#define RS(p)         ((p) << 1 | 1)
#define MAX_LEN       (size_t)(2e4 + 5)

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
    ll num; //这个区间被几个不相交的字段覆盖
    ll cnt; // 这个区间被整体覆盖了几次
    ll len; //这个区间被覆盖的总长度
    bool Ltag, Rtag;

    node() = default;

    node(ll _num, ll _cnt, ll _len, bool _Ltag, bool _Rtag) :
        num(_num), cnt(_cnt), len(_len), Ltag(_Ltag), Rtag(_Rtag) {
    }

};

struct Line {
    ll l, r, h; //线段的左右范围和高度坐标
    int flag;

    Line() = default;

    Line(ll _l, ll _r, ll _h, int _flag) : l(_l), r(_r), h(_h), flag(_flag) {}
};

Line lines[MAXN << 1];
node tree[MAX_LEN << 2];
ll n, lineCnt = 0, ans = 0;

void push_up(ll p, ll l, ll r) {
    if (tree[p].cnt) {
        tree[p].len = r - l + 1;
        tree[p].num = 1;
        tree[p].Ltag = true;
        tree[p].Rtag = true;
        return;
    }
    if (l == r) {
        tree[p].len = 0;
        tree[p].num = 0;
        tree[p].Ltag = false;
        tree[p].Rtag = false;
        return;
    }
    ll ls = LS(p), rs = RS(p);
    tree[p].num = tree[ls].num + tree[rs].num;
    if (tree[ls].Rtag && tree[rs].Ltag) {
        tree[p].num--;
    }
    tree[p].len = tree[ls].len + tree[rs].len;
    tree[p].Ltag = tree[ls].Ltag;
    tree[p].Rtag = tree[rs].Rtag;
    return;
}

void add(ll p, ll pl, ll pr, ll l, ll r, int tag) {
#if _DEBUG
    printf("[log] %lld %lld %lld %lld %lld\n", p, pl, pr, l, r);
#endif
    if (l <= pl && pr <= r) {
        tree[p].cnt += tag;
        push_up(p, pl, pr);
        return;
    }
    ll mid = (pl + pr) >> 1;
    if (l <= mid) {
        add(LS(p), pl, mid, l, r, tag);
    }
    if (r > mid) {
        add(RS(p), mid + 1, pr, l, r, tag);
    }
    push_up(p, pl, pr);
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

    for (size_t i = 1, j = 0; i <= n; i++) {
        ll x1, y1, x2, y2;
        fread(&x1), fread(&y1), fread(&x2), fread(&y2);
#ifndef _DEBUG

#endif // !1

        x1 += 1e4;
        x2 += 1e4;
        y1 += 1e4;
        y2 += 1e4;
        if (x1 > x2) {
            std::swap(x1, x2);
        }
        if (y1 > y2) {
            std::swap(y1, y2);
        }
        lines[++lineCnt] = Line(x1, x2, y1, 1);
        lines[++lineCnt] = Line(x1, x2, y2, -1);
    }

    std::sort(lines + 1, lines + 1 + lineCnt, [](const Line& a, const Line& b) {
        if (a.h == b.h) {
            return a.flag > b.flag;
        }
        return a.h < b.h;
    });

    for (size_t i = 1, last = 0; i <= lineCnt; i++) {
        add(1, 1, 2e4, lines[i].l, lines[i].r - 1, lines[i].flag);
        while (lines[i].h == lines[i + 1].h && lines[i].flag == lines[i + 1].flag) {
            ++i;
            add(1, 1, 2e4, lines[i].l, lines[i].r - 1, lines[i].flag);
        }
        ans += std::abs(ll(tree[1].len - last));
        last = tree[1].len;
        ans += tree[1].num * 2 * (lines[i + 1].h - lines[i].h);
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