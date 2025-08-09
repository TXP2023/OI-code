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

typedef long long int ll;
typedef unsigned long long int ull;

//快读函数声明
template< typename Type >
inline Type fread(Type* p = nullptr);

//快速输出函数
template<typename Type>
inline void fwrite(Type x);

#pragma once
#include <stdint.h>
template<typename Type, size_t _MAX_SIZE>
class Vector {
public:

    Vector() {
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



Vector<ll, 105> arr[20];
ll f[105];
std::pair<ll, ll> ave[105];
bool flag[105];
ll rank[105];
ll vec[105];
ll n, m, b, ans = INT_MAX;

inline void dfs(ll cnt, ll tot, ll sum) {
    if (sum >= ans) {
        return;
    }
    if (cnt == n + 1) {
        ans = sum;
        return;
    }
    for (size_t i = 0; i < arr[cnt].size(); i++) {
        if (flag[arr[cnt][i]]) {
            dfs(cnt + 1, tot, sum);
        }
        else {
            flag[arr[cnt][i]] = true;
            if (tot < vec[arr[cnt][i]]) {
                dfs(cnt + 1, vec[arr[cnt][i]], sum + f[arr[cnt][i]] + b * (vec[arr[cnt][i]] - tot));
            }
            else {
                dfs(cnt + 1, tot, sum + f[arr[cnt][i]]);
            }
            flag[arr[cnt][i]] = false;
        }
    }
}

int main() {

#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    fread(&m), fread(&n), fread(&b);

    for (size_t i = 1; i <= m; i++) {
        ll x, k, c;
        fread(&x), fread(&k), fread(&c);
        f[i] = x;
        ave[i].second = i;
        ave[i].first = x / c;
        vec[i] = k;
        for (size_t j = 0; j < c; j++) {
            ll temp;
            fread(&temp);
            arr[temp].push_back(i);
        }
    }

    for (size_t i = 1; i <= n; i++) {
        if (!arr[i].size()) {
            puts("-1");
            return 0;
        }
    }

    //启发式搜索
    std::sort(ave + 1, ave + 1 + m); //对每一个人的性价比排序

    for (size_t i = 1; i <= m; i++) {
        rank[ave[i].second] = i;
    }

    for (size_t i = 1; i <= n; i++) {
        std::sort(arr[i].begin(), arr[i].end(), [](ll a, ll b) {
            return rank[a] < rank[b];
        });
    }

    dfs(1, 0, 0);

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