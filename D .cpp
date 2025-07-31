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
#include <set>

#define _FREAD        true
#define MAX_INF       1e18
#define MAX_NUM_SIZE  35
#define MAXN          (size_t)(3e5+5)

typedef long long int ll;
typedef unsigned long long int ull;

//快读函数声明
template< typename Type >
inline Type readf(Type* p = nullptr);

//快速输出函数
template<typename Type>
inline void writef(Type x);

ll arrA[MAXN], arrB[MAXN];
ll t, n, m;

inline void slove() {
    readf(&n), readf(&m);
    ll cntA = 0, cntB = 0, ans = 0;
    std::multiset<ll> a, b, c;
    for (size_t i = 1; i <= n; i++) {
        ll val = readf<ll>();
        a.insert(val);
        c.insert(m - val);
    }

    //现在的s
    for (size_t i = 1; i <= n; i++) {
        ll val;
        readf(&val);
        if (c.count(val)) {
            a.erase(a.find(m - val));
            c.erase(val);
        }
        else {
            b.insert(val);
        }
    }
    

    ll apos = cntA, bpos = cntB;
    while (!a.empty()) {
        std::multiset<ll>::iterator aend = a.end(), bend = b.end();
        --aend, --bend;
        if ((*aend) > (*bend)) {
            //现在a最大的大于b最大
            ll val = m - *(aend), temp = 0;
            std::multiset<ll>::iterator p = b.lower_bound(val);
            if (p == b.end()) {
                temp += *b.begin();
                b.erase(b.begin());
            }
            else {
                if ((*p + *aend) % m < (*b.begin() + *(aend)) % m) {
                    temp += *p;
                    b.erase(p);
                }
                else {
                    temp += *b.begin();
                    b.erase(b.begin());
                }
            }
            temp += *(aend);
            temp %= m;
            ans += temp;
            a.erase(aend);
        }
        else {
            //现在a最大的大于b最大
            ll val = m - *(bend), temp = 0;
            std::multiset<ll>::iterator p = a.lower_bound(val);
            if (p == a.end()) {
                temp += *a.begin();
                a.erase(a.begin());
            }
            else {
                if ((*p + *(bend)) % m < (*a.begin() + *(bend)) % m) {
                    temp += *p;
                    a.erase(p);
                }
                else {
                    temp += *a.begin();
                    a.erase(a.begin());
                }
            }
            temp += *(bend);
            temp %= m;
            ans += temp;
            b.erase(bend);
        }
    }

    
    printf("%lld\n", ans);
    return;
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
		slove();
    }



#ifdef _RUN_TIME
    printf("The running duration is not less than %ld ms\n", clock() - start);
#endif // _RUN_TIME
    return 0;
}

template< typename Type >
inline Type readf(Type* p) {
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