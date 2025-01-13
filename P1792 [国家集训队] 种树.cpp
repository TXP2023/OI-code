//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
//
//      By txp2024 www.luogu.com.cn  TXP2023 www.github.com
// 
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
#pragma once
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <queue>
#include <ctype.h>
#include <cstdarg>
#include <climits>
#include <iostream>
#include <stdint.h>
#include <initializer_list>

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

struct node {
    ll l, r;
    ll value;
    bool tag = true;
};

struct queue_data {
    ll volue;
    ll p;

    bool operator <(const queue_data other)const {
        return volue < other.volue;
    }
};

std::priority_queue<queue_data> que;
std::vector<node> v;
ll n, k, ans = LLONG_MIN, sum = 0;

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

    readf(&n), readf(&k);
    if ((n / 2) < k) {
        puts("Error!");
        return 0;
    }

    v.resize(n);
    v.shrink_to_fit();

    for (ll i = 0; i < n; i++) {
        scanf("%lld", &v[i].value);
        v[i].l = i - 1, v[i].r = i + 1;
        que.push({ v[i].value, i });
    }
    v[0].l = n - 1;
    v[n - 1].r = 0;

    while (k--) {
        //std::vector<node>::iterator max_it = std::max_element(v.begin(), v.end());
        while (!v[que.top().p].tag) {
            que.pop();
        }
        ll max_it = que.top().p;
        que.pop();
        sum += v[max_it].value;
        ans = std::max(ans, sum);
        v[max_it].value = -v[max_it].value;

        if (v[max_it].l != -1) {
            v[max_it].value += v[v[max_it].l].value;
            v[v[max_it].l].tag = false;
            v[max_it].l = v[v[max_it].l].l;
            if (v[max_it].l != -1) {
                v[v[max_it].l].r = max_it;
            }
        }
        if (v[max_it].r != n) {
            v[max_it].value += v[v[max_it].r].value;
            v[v[max_it].r].tag = false;
            v[max_it].r = v[v[max_it].r].r;
            if (v[max_it].r != n) {
                v[v[max_it].r].l = max_it;
            }
        }
        que.push({ v[max_it].value, max_it });
    }

    printf("%lld\n", sum);
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
    while (top) putchar(sta[--top] + 48);  // 48 是 '0'
    return;
}