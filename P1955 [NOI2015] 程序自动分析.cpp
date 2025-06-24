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
#include <map>

#define MAX_INF       1e18
#define MAX_NUM_SIZE  35
#define MAXN          (size_t)(1e5)

typedef long long int ll;
typedef unsigned long long int ull;

//快读函数声明
template< typename Type >
inline Type readf(Type* p = nullptr);

//快速输出函数
template<typename Type>
inline void writef(Type x);

struct Task {
    ll u, v, opt;
};

Task tasks[MAXN];
ll diff[MAXN], set[MAXN];
std::map<ll, int> mapping;
ll t, n, cnt;

inline void init() {
    ll num_cnt[MAXN * 2 + 1];
    for (size_t i = 1; i <= n; i++) {
        num_cnt[i * 2 - 1] = tasks[i].u;
        num_cnt[i * 2] = tasks[i].v;
    }
    std::sort(num_cnt + 1, num_cnt + 1 + n * 2);
    cnt = (std::unique(num_cnt + 1, num_cnt + 1 + n * 2) - (num_cnt + 1));
    for (size_t i = 1; i <= cnt; i++) {
        mapping[num_cnt[i]] = i;
    }
    std::iota(set + 1, set + 1 + cnt, 1);
    std::sort(tasks + 1, tasks + 1 + n, [](const Task& a, const Task& b) {
        return a.opt > b.opt;
        }
    );
    return;
}

ll find(ll x) {
    if (set[x] == x) {
        return x;
    }
    else {
        return set[x] = find(set[x]);
    }
}

inline void merge(ll x, ll y) {
    set[find(x)] = set[find(y)];
    return;
}
inline bool same_set(ll x, ll y) {
    return find(x) == find(y);
}

inline bool slove() {
    //多种情况
    // 让 u！=v
    // 判断此时u？=v， 如果为true，那么就无法成立
    //否则可以成立
    //让 u==v
    bool flag = true;//
    readf(&n);
    
    for (size_t i = 1; i <= n; i++) {
        ll opt, u, v;
        readf(&u), readf(&v), readf(&opt);
        tasks[i].opt = opt;
        tasks[i].u = u;
        tasks[i].v = v;
    }
    init();

    for (size_t i = 1; i <= n; i++) {
        ll opt = tasks[i].opt, u = mapping[tasks[i].u], v = mapping[tasks[i].v];
        if (opt == 1) { //相同
            merge(u, v);
        }
        else {
            //不同
            if (same_set(u, v)) {
                return false;
            }
        }
    }
    return true;
}

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    readf(&t);
    while (t--) {
        puts(slove() ? "YES" : "NO");
    }



#ifdef _RUN_TIME
    printf("The running duration is not less than %ld ms\n", clock() - start);
#endif // _RUN_TIME
    return 0;
}

template< typename Type >
inline Type readf(Type* p) {
    Type ret = 0, sgn = 0, ch = getchar();
    while (!isdigit(ch)) {
        sgn |= ch == '-', ch = getchar();
    }
    while (isdigit(ch)) ret = ret * 10 + ch - '0', ch = getchar();
    if (p != nullptr) {
        *p = Type(sgn ? -ret : ret);
    }
    return sgn ? -ret : ret;
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