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
#include <ctype.h>
#include <cstdarg>
#include <climits>
#include <time.h>
#include <iostream>
#include <stdint.h>
#include <math.h>
#include <cmath>

#define READ          false
#define MAX_INF       1e18
#define MAX_NUM_SIZE  35
#define MAXN          (size_t)(1e6 + 5)
#define BLOCKS_SIZE   (size_t)(1e3+5)

typedef long long int ll;
typedef unsigned long long int ull;

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

struct Block {
    std::vector<ll> vec;
    ll tag;
};

Block blocks[BLOCKS_SIZE];
size_t arr[MAXN], belong[MAXN];
size_t blockSize, blockNum;
ll n, q;

inline void update(size_t index) {
    for (size_t i = (index-1)* blockSize +1, j = 0; j < blocks[index].vec.size(); j++, i++) {
        blocks[index].vec[j] = arr[i];
    }
    std::sort(blocks[index].vec.begin(), blocks[index].vec.end());
}

inline void Add(size_t _First, size_t _Last, ll _Val) {
    if (belong[_First] == belong[_Last]) {
        for (size_t i = _First; i <= _Last; i++) {
            arr[i] += _Val;
        }
        update(belong[_First]);
    }
    else {
        for (size_t i = _First; i <= belong[_First]* blockSize; i++) {
            arr[i] += _Val;
        }
        update(belong[_First]);
        for (size_t i = belong[_First] + 1; i < belong[_Last]; i++) {
            blocks[i].tag += _Val;
        }
        for (size_t i = (belong[_Last]-1)*blockSize+1; i <= _Last; i++) {
            arr[i] += _Val;
        }
        update(belong[_Last]);
    }
    return;
}

inline ll query(size_t _First, size_t _Last, ll _Val) {
    ll res = 0;
    if (belong[_First] == belong[_Last]) {
        for (size_t i = _First; i <= _Last; i++) {
            res += (arr[i] + blocks[belong[_First]].tag >= _Val);
        }
    }
    else {
        for (size_t i = _First; i <= belong[_First] * blockSize; i++) {
            res += (arr[i] + blocks[belong[_First]].tag >= _Val);
        }
        for (size_t i = belong[_First] + 1; i < belong[_Last]; i++) {
            ll ans = blockSize;
            for (ll left = 0, right = blockSize - 1; left <= right; ) {
                ll mid = (left + right) >> 1;
                if (blocks[i].vec[mid] + blocks[i].tag >= _Val) {
                    ans = mid;
                    right = mid - 1;
                }
                else {
                    left = mid + 1;
                }
            }
            res += blockSize - ans;
        }
        for (size_t i = (belong[_Last] - 1) * blockSize + 1; i <= _Last; i++) {
            res += (arr[i] + blocks[belong[_Last]].tag >= _Val);
        }
    }
    return res;
}

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    readf(&n), readf(&q);
    blockSize = (int)(std::sqrt(n)) + 1;
    blockNum = n / blockSize + (n % blockSize != 0);

    for (size_t i = 1; i <= n; i++) {
        readf(&arr[i]);
        blocks[i / blockSize + (i % blockSize != 0)].vec.push_back(arr[i]);
        belong[i] = i / blockSize + (i%blockSize != 0);
    }

    for (size_t i = 1; i <= blockNum; i++) {
        std::sort(blocks[i].vec.begin(), blocks[i].vec.end());
        blocks[i].tag = 0;
    }

    while (q--) {
        char opt[2];
        scanf("%s", opt);
        if (opt[0] == 'M') {
            size_t first = readf<size_t>(), last = readf<size_t>();
            ll val = readf<ll>();
            Add(first, last, val);
        }
        else {
            size_t first = readf<size_t>(), last = readf<size_t>();
            ll val = readf<ll>();
            printf("%lld\n", query(first, last, val));

        }
        //puts("Debug");
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