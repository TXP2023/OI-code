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
#include <iostream>
#include <stdint.h>
#include <initializer_list>

#define READ false
#define MAX_INF 1e18

typedef long long int ll;
typedef unsigned long long int unill;

//快读函数声明
#if READ
template< typename T >
inline T readf();
#else
template< typename Type >
inline Type readf(Type* p = NULL);
#endif

class segment_tree {
public:
    segment_tree(ll size);

    inline ll query(ll x, ll p = 1);

    void up_data(ll left, ll right, ll operate/*1为住房 0为退房*/, ll p = 1);

private:
    struct tree_node {
        ll max_length;
        ll left_length, right_length;
        int lp, rp;
        bool tag_bool = false;
        int tag;
    };

    std::vector< tree_node > tree;

    void build_tree(ll p, ll lp, ll rp);

    inline void push_down(ll p);

    inline void push_up(ll p);

    inline void add_tag(ll p, ll operate);
};

segment_tree::segment_tree(ll size) {
    tree.resize((size << 2) + 1);
    build_tree(1, 1, size);
    return;
}

void segment_tree::build_tree(ll p, ll lp, ll rp) {
    tree[p].lp = lp, tree[p].rp = rp;

    if (lp == rp) {
        tree[p].max_length = 1;
        tree[p].left_length = 1;
        tree[p].right_length = 1;
        return;
    }

    ll mid = (lp + rp) >> 1;
    build_tree(p * 2, lp, mid);
    build_tree(p * 2 + 1, mid + 1, rp);
    tree[p].max_length = rp - lp + 1;
    tree[p].right_length = rp - lp + 1;
    tree[p].left_length = rp - lp + 1;
    return;
}

inline void segment_tree::push_down(ll p) {
    if (tree[p].tag_bool) {
        tree[p].tag_bool = false;
        tree[p * 2].tag_bool = true;
        tree[p * 2 + 1].tag_bool = true;
        if (tree[p].tag == 1)/*全部住上人*/ {
            tree[p * 2].tag = 1;
            tree[p * 2].max_length = 0;
            tree[p * 2].left_length = 0;
            tree[p * 2].right_length = 0;
            tree[p * 2 + 1].tag = 1;
            tree[p * 2 + 1].max_length = 0;
            tree[p * 2 + 1].left_length = 0;
            tree[p * 2 + 1].right_length = 0;
        }
        else /*全部退房*/ {
            ll left_length = tree[p * 2].rp - tree[p * 2].lp + 1;
            ll right_lenght = tree[p * 2 + 1].rp - tree[p * 2 + 1].lp + 1;
            tree[p * 2].max_length = left_length;
            tree[p * 2].left_length = left_length;
            tree[p * 2].right_length = left_length;
            tree[p * 2 + 1].max_length = right_lenght;
            tree[p * 2 + 1].left_length = right_lenght;
            tree[p * 2 + 1].right_length = right_lenght;
            tree[p * 2].tag = 0;
            tree[p * 2 + 1].tag = 0;
        }
        tree[p].tag = 0;
    }
    return;
}

inline void segment_tree::push_up(ll p) {
    tree[p].left_length = tree[p * 2].left_length;
    if (tree[p * 2].left_length == tree[p * 2].rp - tree[p * 2].lp + 1) {
        tree[p].left_length += tree[p * 2 + 1].left_length;
    }
    tree[p].right_length = tree[p * 2 + 1].right_length;
    if (tree[p * 2 + 1].right_length == tree[p * 2 + 1].rp - tree[p * 2 + 1].lp + 1) {
        tree[p].right_length += tree[p * 2].right_length;
    }
    tree[p].max_length = std::max(
        std::max(tree[p * 2].right_length + tree[p * 2 + 1].left_length/*最大值位于两个子节点中间*/,
            std::max(tree[p * 2].max_length, tree[p * 2 + 1].max_length))/*最大值为两个子节点之间*/,
        std::max(tree[p].right_length, tree[p].left_length)/*最大值为左边或右边*/);
    return;
}

inline void segment_tree::add_tag(ll p, ll operate) {
    tree[p].tag = operate;
    tree[p].tag_bool = true;
    if (operate) {
        tree[p].max_length = 0;
        tree[p].left_length = 0;
        tree[p].right_length = 0;
    }
    else {
        tree[p].max_length = tree[p].rp - tree[p].lp + 1;
        tree[p].left_length = tree[p].rp - tree[p].lp + 1;
        tree[p].right_length = tree[p].rp - tree[p].lp + 1;
    }
    return;
}

inline ll segment_tree::query(ll x, ll p) {
    if (tree[p].max_length < x) {
        return -1;
    }

    //五种可能
    if (tree[p].left_length >= x) /*这个点的左端点连续x个*/ {
        return tree[p].lp;
    }
    //在左子节点的内部
    if (tree[p * 2].max_length >= x) {
        return query(x, p * 2);
    }
    /*在左右节点中间*/
    if (tree[p * 2].right_length + tree[p * 2 + 1].left_length >= x) {
        return tree[p * 2].rp - tree[p * 2].right_length + 1;
    }
    //在右子节点内部有
    if (tree[p * 2 + 1].max_length >= x) {
        return query(x, p * 2 + 1);
    }
    //在当前节点的最左边
    if (tree[p].right_length >= x) {
        return tree[p].rp - tree[p].right_length + 1;
    }
}

ll n, m;

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

    readf(&n), readf(&m);

    segment_tree hotel(n);
    while (m--) {
        int operate = readf< int >();
        if (operate == 1) {
            ll x = readf< ll >();
            ll p = hotel.query(x);
            if (p == -1) {
                puts("0");
            }
            else {
                printf("%lld\n", p);
                hotel.up_data(p, p + x - 1, 1);
            }

        }
        else {
            ll x = readf< ll >(), y = readf< ll >();
            hotel.up_data(x, x + y - 1, 0);
        }
    }

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

