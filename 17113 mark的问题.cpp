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
#define MAX_LENGTH    2005          

typedef long long int ll;
typedef unsigned long long int ull;

//快读函数声明
template< typename Type >
inline Type fread(Type* p = nullptr);

//快速输出函数
template<typename Type>
inline void fwrite(Type x);

template<typename Type>
inline Type fpow(Type a, Type n, Type _Mod);


unsigned long long hash[MAX_LENGTH];
ll cnt[MAX_LENGTH];
char str[MAX_LENGTH];
ll t, length;

inline void get_hash() {
    hash[0] = 0;
    for (size_t i = 1; i <= length; i++) {
        hash[i] = hash[i - 1] * 131 + str[i] - 'a' + 1;
    }
	return;
}

inline ll get_sub_hash(ll l, ll r) {
    return hash[r] - hash[l - 1] * fpow((unsigned long long)131, (unsigned long long)(r - l + 1), (unsigned long long)ULLONG_MAX);
}

inline void slove() {
	scanf("%s", str + 1);
	length = strlen(str + 1);

	get_hash();
    
    for (size_t i = 2; i <= length; ++i) {
        for (size_t j = i-1; j >= 1; j-=2) {
			ll mid = (i + j) >> 1;
            if (get_sub_hash(j, mid) == get_sub_hash(mid + 1, i)) {
                ++cnt[i];
            }
        }
    }

    for (size_t i = 2; i <= length; ++i) {
        for (size_t j = i - 1; j >= 1; j -= 2) {
            ll mid = (i + j) >> 1;
            if (get_sub_hash(j, mid) == get_sub_hash(mid + 1, i)) {
                ++cnt[i];
            }
        }
    }

    for (size_t i = 2; i <= length; ++i) {
        for (size_t j = i - 1; j >= 1; j -= 2) {
            ll mid = (i + j) >> 1;
            
        }
    }

    return;
}

int main() {

#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    fread(&t);

    while (t--) {

    }



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

template<typename Type>
inline Type fpow(Type a, Type n, Type _Mod) {
    Type base = a, ret = 1;
    while (n) {
        if (n & 1) {
            ret = ret * base;
            ret %= _Mod;
        }
        base = base * base;
        base %= _Mod;
        n >>= 1;
    }
    return ret % _Mod;
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