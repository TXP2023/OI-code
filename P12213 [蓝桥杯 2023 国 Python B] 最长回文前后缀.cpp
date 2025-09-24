//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
//
//      By txp2024 www.luogu.com.cn  TXP2023 www.github.com
// 
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

#pragma once
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <numeric>
#include <ctype.h>
#include <cstdarg>
#include <queue>
#include <climits>
#include <time.h>
#include <iostream>
#include <stdint.h>
#include <vector>

#define _FREAD        true
#define MAX_INF       0x7f7f7f7f7f7f7f7f
#define MAX_NUM_SIZE  35
#define MAX_LEN       (size_t)(1e5+5)
#define BASE           (131)
#define MOD            (1 << 31)

typedef long long int ll;
typedef unsigned long long int ull;

template<typename _T>
inline _T fpow(_T a, _T n, _T mod) {
    _T base = a, ret = 1;
    while (n) {
        if (n & 1) {
            ret = ret * base;
            ret %= mod;
        }
        base = base * base;
        base %= mod;
        n >>= 1;
    }
    return ret % mod;
}

template<typename _T>
inline _T fpow(_T a, _T n) {
    _T base = a, ret = 1;
    while (n) {
        if (n & 1) {
            ret = ret * base;
            //ret %= mod;
        }
        base = base * base;
        //base %= mod;
        n >>= 1;
    }
    return ret;
}
//快读函数声明
template< typename Type >
inline Type fread(Type* p = nullptr);

//快速输出函数
template<typename Type>
inline void fwrite(Type x);

ull hash[MAX_LEN], sufHash[MAX_LEN], len;
char s[MAX_LEN];

inline ll get_hash(ll l, ll r) {
    if (l > r) {
        return 0;
    }
    return  (hash[r] - hash[l - 1] * fpow(ll BASE, r - l + 1) % MOD + MOD) % MOD;
}

inline ll get_suf_hash(ll l, ll r) {
    if (l > r) {
        return 0;
    }
    return  (sufHash[l] - sufHash[r + 1] * fpow(ll BASE, r - l + 1) % MOD + MOD) % MOD;
}

int main() {

#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    scanf("%s", s + 1);
    len = strlen(s + 1);

    for (size_t i = 1; i <= len; i++) {
        hash[i] = (hash[i - 1] * BASE + s[i]) % MOD;
    }

    for (size_t i = len; i >= 1; --i) {
        sufHash[i] = (sufHash[i + 1] * BASE + s[i]) % MOD;
    }

    ll maxLen = 0;
    for (size_t i = 1; i <= len; i++) {
        if (get_hash(1, i) == get_suf_hash(len - i + 1, len)) {
            maxLen = i;
        }
    }

    ll lsize = 0;
    for (size_t i = maxLen + 1; i <= len; i++) {
        ll mid = ((i - maxLen) >> 1) + maxLen;
        if ((i - maxLen) & 1) {
            if (get_hash(maxLen + 1, mid) == get_suf_hash(mid + 2, i)) {
                lsize = i - maxLen;
            }
        }
        else {
            if (get_hash(maxLen + 1, mid) == get_suf_hash(mid + 1, i)) {
                lsize = i - maxLen;
            }
        }
    }

    ll rsize = 0;
    for (size_t i = len - maxLen; i >= 1; --i) {
        ll mid = len - maxLen - ((len - maxLen - i + 1) >> 1);
        if ((len - maxLen - i + 1) & 1) {
            if (get_hash(i, mid - 1) == get_suf_hash(mid + 1, len - maxLen)) {
                rsize = len - maxLen - i + 1;
            }
        }
        else {
            if (get_hash(i, mid) == get_suf_hash(mid + 1, len - maxLen)) {
                rsize = i - maxLen;
            }
        }
    }

    printf("%lld\n", maxLen * 2 + std::max(lsize, rsize));



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