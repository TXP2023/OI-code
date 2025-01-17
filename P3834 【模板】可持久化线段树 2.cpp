//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
//
//      By txp2024 www.luogu.com.cn  TXP2023 www.github.com
// 
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
#pragma once
#include <cstdarg>
#include <ctype.h>
#include <climits>
#include <vector>
#include <queue>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <algorithm>
#include <stdint.h>

#define READ false
#define MAX_INF 1e18
#define MAX_NUM_SIZE 35

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

class Persistent_data_structure {
public:
    Persistent_data_structure(ll _size);
    

    ll updata(ll _pre/*从pre上继承*/, ll _lp/*当前树的左子节点*/, ll _rp/*当前树的右子节点*/, ll _value/*添加的值*/);

    ll query(ll _u, ll _v, ll _lp, ll _rp, ll _rank);

    std::deque< ll > root;

private:
    struct tree_node {
        size_t ls,  rs;
        ll data;
        
    };

    std::deque< tree_node > tree;
    
    ll node_cnt = 0;
};

std::vector< ll > vec, dis_value;
ll n, m;

inline void discretization() {
    dis_value = vec;
    std::sort(dis_value.begin(), dis_value.end());
    dis_value.erase(std::unique(dis_value.begin(), dis_value.end()), dis_value.end());
    return;
}

Persistent_data_structure::Persistent_data_structure(ll _size) {
    tree.push_back({ 0, 0, 0 });
    root.resize(_size, 0);
    return;
}

ll Persistent_data_structure::updata(ll _pre, ll _lp, ll _rp, ll _value) {
    ll p = ++node_cnt;
    tree.push_back(tree_node{ tree[_pre].ls, tree[_pre].rs, tree[_pre].data + 1 });

    if (_lp != _rp) { //非叶子节点
        ll  mid = (_lp + _rp) >> 1;
        if (_value <= mid) { //新建的点位于左子树内
            tree[p].ls = updata(tree[_pre].ls, _lp, mid, _value);
        }
        else {
            tree[p].rs = updata(tree[_pre].rs, mid + 1, _rp, _value);
        }
    }
    return p;
}

ll Persistent_data_structure::query(ll _u, ll _v, ll _lp, ll _rp, ll _rank) {
    if (_lp == _rp) {
        return _lp;
    }

    ll left_sum = tree[tree[_v].ls].data - tree[tree[_u].ls].data;
    ll mid = (_lp + _rp) >> 1;
    if (left_sum >= _rank) {
        return query(tree[_u].ls, tree[_v].ls, _lp, mid, _rank); 
    }
    else {
        return query(tree[_u].rs, tree[_v].rs, mid + 1, _rp, _rank - left_sum);
    }
}

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

    clock_t start = clock();

    readf(&n), readf(&m);

    vec.resize(n);
    for (size_t i = 0; i < n; i++) {
        readf(&vec[i]);
    }

    discretization();
    Persistent_data_structure tree(n + 1);// 加1是因为有初始树
    for (size_t i = 1; i <= n; i++) {
        tree.root[i] = tree.updata(tree.root[i - 1], 1, n, std::lower_bound(dis_value.begin(), dis_value.end(), vec[i - 1]) - dis_value.begin() + 1);
    }

    while (m--) {
        ll l = readf< ll >(), r = readf< ll >(), k = readf< ll >();
        printf("%lld\n", dis_value[tree.query(tree.root[l - 1], tree.root[r], 1, n, k) - 1]);

    }


    printf("%ld\n",clock() - start);
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