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
#define MAXN          (int)(1e5+1)

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

class segment_tree {
public:
    void build_tree(ll _Val_Pos, ll _Index, ll _Left, ll _Right);

    void update(ll _Index, ll _RangeL, ll _RangeR, ll _Left, ll _Right);

    ll query(ll _Index, ll _RangeL, ll _RangeR, ll _Left, ll _Right);
private:
    template<typename Type>
    inline Type ls(Type _X);

    template<typename Type>
    inline Type rs(Type _X);

    inline void add_tag(ll _Index, ll _Left, ll _Right);

    inline void push_down(ll _Index, ll _Left, ll _Right);

    inline void push_up(ll _Index);

    //维护二进制的第_Val_Pos位，最左边为第0位*
    

    struct node {
        ll sum;
        ll tag;
        node() {
            tag = 0;
            return;
        }
    };
    node tree[MAXN << 2];
};


ll array[MAXN];
ll n, m;

template<typename Type>
inline Type segment_tree::ls(Type _X) {
    return _X << 1;
}

template<typename Type>
inline Type segment_tree::rs(Type _X) {
    return _X << 1 | 1;
}

inline void segment_tree::add_tag(ll _Index, ll _Left, ll _Right) {
    tree[_Index].tag ^= 1;
    tree[_Index].sum = (_Right - _Left + 1) - tree[_Index].sum;
    return;
}

inline void segment_tree::push_down(ll _Index, ll _Left, ll _Right) {
    if (tree[_Index].tag) {
        ll mid = (_Left + _Right) >> 1;
        add_tag(ls(_Index), _Left, mid);
        add_tag(rs(_Index), mid + 1, _Right);
        tree[_Index].tag = 0;
    }
    return;
}

inline void segment_tree::push_up(ll _Index) {
    tree[_Index].sum = tree[ls(_Index)].sum + tree[rs(_Index)].sum;
    return;
}

//维护二进制的第_Val_Pos位，最左边为第0位*
void segment_tree::build_tree(ll _Val_Pos, ll _Index, ll _Left, ll _Right) {
    if (_Left == _Right) {
        tree[_Index].sum = (array[_Left] >> _Val_Pos) % 2;
        return;
    }

    ll mid = (_Left + _Right) >> 1;
    build_tree(_Val_Pos, ls(_Index), _Left, mid);
    build_tree(_Val_Pos, rs(_Index), mid + 1, _Right);
    push_up(_Index);
    return;
}

void segment_tree::update(ll _Index, ll _RangeL, ll _RangeR, ll _Left, ll _Right) {
    if (_Left <= _RangeL && _RangeR <= _Right) {
        add_tag(_Index, _RangeL, _RangeR);
        return;
    }

    ll mid = (_RangeL + _RangeR) >> 1;
    push_down(_Index, _RangeL, _RangeR);
    if (_Left <= mid) {
        update(ls(_Index), _RangeL, mid, _Left, _Right);
    }
    if (mid < _Right) {
        update(rs(_Index), mid + 1, _RangeR, _Left, _Right);
    }
    push_up(_Index);
    return;
}

ll segment_tree::query(ll _Index, ll _RangeL, ll _RangeR, ll _Left, ll _Right) {
    if (_Left <= _RangeL && _RangeR <= _Right) {
        return tree[_Index].sum;
    }

    ll mid = (_RangeL + _RangeR) >> 1, sum = 0;
    push_down(_Index, _RangeL, _RangeR);
    if (_Left <= mid) {
        sum += query(ls(_Index), _RangeL, mid, _Left, _Right);
    }
    if (mid < _Right) {
        sum += query(rs(_Index), mid + 1, _RangeR, _Left, _Right);
    }
    return sum;
}

segment_tree seg_tree[20];

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    //TODO
    readf(&n);

    for (size_t i = 1; i <= n; ++i) {
        readf(&array[i]);
    }

    for (size_t i = 0; i < 20; i++) {
        seg_tree[i].build_tree(i, 1, 1, n);
    }

#if false
    ll sum = 0;
    for (size_t i = 0; i < 20; i++) {
        sum += seg_tree[i].query(1, 1, n, 1, n) << i;
    }
    printf("debug sum: %lld\n", sum);
#endif // true


    readf(&m);

    while (m--) {
        short opt = readf<short>();
        ll left = readf<ll>(), right = readf<ll>(), sum, value;
        switch (opt) {
        case 1:
            sum = 0;
            for (size_t i = 0; i < 20; i++) {
                //ll v = seg_tree[i].query(1, 1, n, left, right);
                //sum += v << i;
                sum += seg_tree[i].query(1, 1, n, left, right) << i;
            }
            printf("%lld\n", sum);
            break;
        case 2:
            value = readf<ll>();
            for (size_t i = 0; i < 20 && value; ++i) {
                if (value % 2) {
                    seg_tree[i].update(1, 1, n, left, right);
                }
                value >>= 1;
            }
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