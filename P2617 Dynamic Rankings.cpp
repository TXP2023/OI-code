//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
//
//      By txp2024 www.luogu.com.cn  TXP2023 www.github.com
// 
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
#pragma once
#include <vector>
#include <map>
#include <stdio.h>
#include <algorithm>
#include <ctype.h>
#include <cstdarg>
#include <climits>
#include <time.h>
#include <iostream>
#include <stdint.h>
#include <time.h>

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
inline Type readf(Type* p = NULL);
#endif

//快速输出函数
template<typename Type>
inline void writef(Type x);

struct question {
    ll id;
    char operate;
    ll l, r, k;
};

class Segment_tree {
public:
    Segment_tree(ll _size);
    ~Segment_tree();

private:
    const ll ROOT_SIZE = 1e10;
    
    ll build_tree(ll _pre, ll _lp, ll _rp);

    struct tree_node {
        ll l, r;
        ll data;
    };

    tree_node tree[100000000];
    std::vector< ll > root;

    ll tree_cnt;
};

Segment_tree::Segment_tree(ll _size) {
    
    
    
}

Segment_tree::~Segment_tree() {
}

class Binary_indexed_tree {
public:
    Binary_indexed_tree(ll _size);
    
    inline void add(ll _x);

private:
    std::vector<Segment_tree> tree_;

    ll size_;

    template<typename lowbit_Type>
    inline lowbit_Type lowbit(lowbit_Type x);


};



std::vector< question > questions;
std::vector< ll > dis_vec; //离散化数组
std::map< ll, ll > dis_map;
std::vector< ll > vec;
ll n, m, num;

Binary_indexed_tree::Binary_indexed_tree(ll _size) {
    tree_.resize(_size + 1);
    size_ = _size;

}

template<typename lowbit_Type>
inline lowbit_Type Binary_indexed_tree::lowbit(lowbit_Type x) {
    return lowbit_Type(x & -x);
}

inline void Binary_indexed_tree::add(ll _x) {
    while (_x <= size_) {
        
    }
}


inline void discretization() {
    std::sort(dis_vec.begin(), dis_vec.end());
    dis_vec.erase(std::unique(dis_vec.begin(), dis_vec.end()), dis_vec.end());
    for (size_t i = 0; i < dis_vec.size(); i++) {
        dis_map[dis_vec[i]] = i;
    }
    num = dis_vec.size();
    return;
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

    vec.resize(n);
    questions.resize(m);
    dis_vec.resize(n, -1);
    for (size_t i = 0; i < n; i++) {
        readf(&vec[i]);
        dis_vec[i] = vec[i];
    }

    for (size_t i = 0; i < m; i++) {
        char ch[3];
        ll x, y;
        scanf("%s", &ch);
        readf(&x), readf(&y);
        switch (ch[0]) {
        case 'Q':
            ll k = readf<ll>();
            questions[i] = { ll(i), 'Q', x, y, k };
            dis_vec.push_back(k);
            break;

        case 'C':
            questions[i] = { ll(i), 'Q', x, y, -1 };
            break;
        }
    }

    discretization();




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