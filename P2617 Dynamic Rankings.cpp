
//
//  我是罪人啊！！
//  I am a sinner!!
//  
//  我危害OI啊！！
//  I'm endangering OI!!
// 
//  我辜负洛谷啊！！！
//  I failed Luogu!!
// 
//  我对着题解复制粘贴啊！！
//  I copy and paste the question answer!!
// 
//  我愿抛开估值！！！
//  I am willing to put aside value!!!!
//  
//  消除AC记录！！！
//  Erase AC records!!
// 
//  归于真我啊！！！
//  Belong to me!!
///
// 
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
//
//      ???????????????????????????????????????????????????
// 
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
#pragma once
#include <vector>
#include <map>
#include <math.h>
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
#define MAXN 100007

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

struct tree_node{
    int data;
    int ls, rs;
};

std::vector< question > questions;
std::vector< ll > dis_vec; //离散化数组
std::vector< ll > vec;

tree_node seg_tree[MAXN * 400];
int root[MAXN], t1[MAXN], t2[MAXN];
int n, m, num, Top, n1, n2;

//离散化
inline void discretization() {
    std::sort(dis_vec.begin(), dis_vec.end());
    dis_vec.erase(std::unique(dis_vec.begin(), dis_vec.end()), dis_vec.end());
    num = dis_vec.size();
    return;
}

template<typename T>
inline T lowbit(T x) {
    return x & -x;
}

void Add(int& rt, int l, int r, int ind, int c) {
    if (!rt) rt = ++Top;
    seg_tree[rt].data += c;
    if (l == r) return;
    int m = (l + r) >> 1;
    if (ind <= m) Add(seg_tree[rt].ls, l, m, ind, c);
    else Add(seg_tree[rt].rs, m + 1, r, ind, c);
}

void Change(int ind, int val) {
    int x = std::lower_bound(dis_vec.begin(), dis_vec.end(), vec[ind - 1]) - dis_vec.begin() + 1;
    for (int i = ind; i <= n; i += lowbit(i))
        Add(root[i], 1, num, x, val);
}

int Kth(int l, int r, int k) { //求第 k 大
    // printf("%d %d %d\n", l, r, k);
    if (l == r) return l;
    int m = (l + r) >> 1, sum = 0;
    for (int i = 1; i <= n2; ++i)
        sum += seg_tree[seg_tree[t2[i]].ls].data;
    for (int i = 1; i <= n1; ++i)
        sum -= seg_tree[seg_tree[t1[i]].ls].data;
    if (sum >= k) {
        for (int i = 1; i <= n1; ++i) //所有树的节点保持对应
            t1[i] = seg_tree[t1[i]].ls;
        for (int i = 1; i <= n2; ++i)
            t2[i] = seg_tree[t2[i]].ls;
        return Kth(l, m, k);
    }
    else {
        for (int i = 1; i <= n1; ++i)
            t1[i] = seg_tree[t1[i]].rs;
        for (int i = 1; i <= n2; ++i)
            t2[i] = seg_tree[t2[i]].rs;
        return Kth(m + 1, r, k - sum);
    }
}

int Kth_pre(int l, int r, int k) {
    n1 = n2 = 0;
    for (int i = l - 1; i >= 1; i -= lowbit(i)) //处理出需要求和的 n1 棵树
        t1[++n1] = root[i];
    for (int i = r; i >= 1; i -= lowbit(i))
        t2[++n2] = root[i];
    return Kth(1, num, k);
}

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    
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
        ll x, y, k;
        scanf("%s", &ch);
        readf(&x), readf(&y);
        switch (ch[0]) {
        case 'Q':
            k = readf<ll>();
            questions[i] = { ll(i), 'Q', x, y, k };
            break;

        case 'C':
            questions[i] = { ll(i), 'C', x, y, -1 };
            dis_vec.push_back(y);
            break;
        }
    }

    discretization();
    for (int i = 1; i <= n; ++i)
        Change(i, 1);
    //处理操作&询问
    for (int i = 0; i < m; ++i) {
        if (questions[i].operate == 'Q') {
            printf("%d\n", dis_vec[Kth_pre(questions[i].l, questions[i].r, questions[i].k) - 1]);
        }
        else {
            Change(questions[i].l, -1);
            vec[questions[i].l - 1] = questions[i].r;
            Change(questions[i].l, 1);
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