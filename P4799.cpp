//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
//
//      By txp2024 www.luogu.com.cn  TXP2023 www.github.com
// 
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

#pragma once
#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <numeric>
#include <ctype.h>
#include <cstdarg>
#include <climits>
#include <time.h>
#include <iostream>
#include <stdint.h>

#define _FREAD        true
#define MAX_INF       1e18
#define MAX_NUM_SIZE  35
#define MAXN          45
#define MAX_SIZE      2010000

typedef long long int ll;
typedef unsigned long long int ull;

//快读函数声明
template< typename Type >
inline Type fread(Type* p = nullptr);

//快速输出函数
template<typename Type>
inline void writef(Type x);

template<typename Type, size_t _MAX_SIZE>
class StaticVector {
public:

    StaticVector() {
        size_ = 0;
        return;
    }

    template<typename T>
    inline Type& operator [] (T _Pos) {
        return arr_[_Pos];
    }

    inline void push_back(Type _Value) {
        arr_[size_++] = _Value;
        return;
    }

    inline size_t size() {
        return size_;
    }

    inline Type* begin() {
        return arr_;
    }

    inline Type* end() {
        return &arr_[size_];
    }

private:
    Type arr_[_MAX_SIZE];
    size_t size_;
};

using vec = StaticVector<size_t, MAX_SIZE>;

vec va, vb;
ll ticket[MAXN];
ll n, m, ans = 0;

inline void dfs(const ll &l, const ll &r, const uint64_t &sum, vec &_v) {
    if (sum > m) {
        return;
    }

    if (l > r) {
        _v.push_back(sum);
        return;
    }
    dfs(l + 1, r, sum + ticket[l], _v);
    dfs(l + 1, r, sum, _v);
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
        fread(&ticket[i]);
    }

    ll mid = (n >> 1);

    dfs(1, mid, 0, va);
    dfs(mid + 1, n, 0, vb);

    std::sort(vb.begin(), vb.end());
    for (auto& i : va) {        
        ans += std::upper_bound(vb.begin(), vb.end(), m - i) - vb.begin();
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