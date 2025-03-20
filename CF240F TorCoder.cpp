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
#include <time.h>
#include <iostream>
#include <stdint.h>

#define READ          false
#define MAX_INF       1e18
#define MAX_NUM_SIZE  35
#define MAXN          (int64_t)(1e5 + 5)

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

typedef std::pair<bool, short> Tag;

struct tree_node {
    ll sum;
    Tag tag;
};

tree_node tree[26][MAXN << 2];
ll array[MAXN];
ll n, m;

template<typename Type>
inline Type ls(Type _X) {
    return _X << 1;
}

template<typename Type>
inline Type rs(Type _X) {
    return _X << 1 | 1;
}

inline void add_tag(tree_node &node, ll _Lp, ll _Rp, ll _value) {
    node.tag = std::pair<bool, short>(1, _value);
    if (_value == 1) {
        node.sum = _Rp - _Lp + 1;
    }
    else {
        node.sum = 0;
    }
    return;
}

inline void push_down(ll root, ll _P, ll _Lp, ll _Rp) {
    if (tree[root][_P].tag.first) {
        ll mid = (_Lp + _Rp) >> 1;
        add_tag(tree[root][ls(_P)], _Lp, mid, tree[root][_P].tag.second);
        add_tag(tree[root][rs(_P)], mid + 1, _Rp, tree[root][_P].tag.second);
        tree[root][_P].tag = Tag(false, 0);
    }
    return;
}

void update(ll root, ll _Left, ll _Right, ll value, ll _P, ll _Lp, ll _Rp) {
    if (_Left <= _Lp && _Rp <= _Right) {
        add_tag(tree[root][_P], _Lp, _Rp, value);
        return;
    }

    ll mid = (_Lp + _Rp) >> 1;
    push_down(root, _P, _Lp, _Rp);
    if (_Left <= mid) {
        update(root, _Left, _Right, value, ls(_P), _Lp, mid);
    }
    if (mid < _Right) {
        update(root, _Left, _Right, value, rs(_P), mid + 1, _Rp);
    }
    tree[root][_P].sum = tree[root][ls(_P)].sum + tree[root][rs(_P)].sum;
    return;
}

inline ll query(ll root, ll _Left, ll _Right, ll _P, ll _Lp, ll _Rp) {
    if (_Left <= _Lp && _Rp <= _Right) {
        return tree[root][_P].sum;
    }

    ll mid = (_Lp + _Rp) >> 1, ret = 0;
    push_down(root, _P, _Lp, _Rp);
    if (_Left <= mid) {
        ret += query(root, _Left, _Right, ls(_P), _Lp, mid);
    }
    if (mid < _Right) {
        ret += query(root, _Left, _Right, rs(_P), mid + 1, _Rp);
    }
    return ret;
}

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#else
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    //TODO
    readf(&n), readf(&m);

    scanf("\n");
    for (size_t i = 1; i <= n; ++i) {
        array[i] = getchar() - 'a';
    }

    for (size_t i = 1; i <= n; i++) {
        update(array[i], i, i, 1, 1, 1, n);
        //printf("debug %lld", query(25, 1, 1, 1, 1, n));
    }

    //printf("debug %lld", query(25, 1, 1, 1, 1, n));
    for (size_t j = 0; j < m; j++) {
        ll beg = 0;
        ll left = readf<ll>(), right = readf<ll>();
        int cnt[26], t = 0;
        for (size_t i = 0; i <= 25; i++) {
            cnt[i] = query(i, left, right, 1, 1, n);
            if (cnt[i] % 2) {
                if (t == 0) {
                    t = 1;
                }
                else {
                    goto LOOP;
                }
            }
        }
        
        for (size_t i = 0; i <= 25; i++) {
            if (!cnt[i]) {
                continue;
            }
            update(i, left, right, 0, 1, 1, n);
            
            if (cnt[i] % 2) {
                ll mid = (left + right) >> 1;
                update(i, mid, mid, 1, 1, 1, n);
                --cnt[i];
            }
            update(i, left + beg, left + beg + cnt[i] / 2 - 1, 1, 1, 1, n);
            update(i, right - beg - cnt[i] / 2 + 1, right - beg, 1, 1, 1, n);
            beg += cnt[i] / 2;
        }
    LOOP:;
    }

    for (size_t i = 1; i <= n; i++) {
        for (size_t j = 0; j <= 25; ++j) {
            if (query(j, i, i, 1, 1, n)) {
                putchar(j + 'a');
                break;
            }
        }
    }

#ifdef _RUN_TIME
    printf("\nThe running duration is not less than %ld ms\n", clock() - start);
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