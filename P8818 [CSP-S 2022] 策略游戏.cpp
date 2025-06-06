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

#define READ          false
#define MAX_INF       1e18
#define MAX_NUM_SIZE  35
#define MAXN          (size_t)(1e5+5)
#define MAXN_LOG2     (size_t)(17)

typedef long long int ll;
typedef unsigned long long int ull;

//�����������
#if READ
template< typename T >
inline T readf();
#else
template< typename Type >
inline Type readf(Type* p = nullptr);
#endif

//�����������
template<typename Type>
inline void writef(Type x);

template<size_t __MAX_VALUE>
class Log2 {
public:
    Log2() {
        log_[1] = 0;
        log_[1] = 0;
        log_[2] = 1;
        for (size_t i = 3; i <= __MAX_VALUE; i++) {
            log_[i] = log_[i / 2] + 1;
        }
        return;
    }

    int operator ()(const size_t& val) {
        return log_[val];
    }

private:
    int log_[__MAX_VALUE + 1];
};

template<size_t _size, size_t _size_log>
struct StTable {
    ll arrMax[_size + 1][_size_log + 1], arrMin[_size + 1][_size_log + 1];
    ll maxNeg[_size + 1][_size_log + 1]/*�������ֵ*/, minUNeg[_size + 1][_size_log + 1];
    Log2<_size> get_log2;

    inline void insert(size_t pos, ll val) {
        arrMax[pos][0] = val;
        arrMin[pos][0] = val;
        if (val >= 0) {
            minUNeg[pos][0] = val;
            maxNeg[pos][0] = LLONG_MIN;
        }
        else {
            minUNeg[pos][0] = LLONG_MAX;
            maxNeg[pos][0] = val;
        }
        return;
    }

    inline void init() {
        for (size_t i = 1; i <= _size_log; i++) {
            for (size_t j = 1; j + (1 << i) - 1 <= _size; j++) {
                arrMax[j][i] = std::max(
                    arrMax[j][i - 1],
                    arrMax[j + (1 << (i - 1))][i - 1]
                );
                maxNeg[j][i] = std::max(
                    maxNeg[j][i - 1],
                    maxNeg[j + (1 << (i - 1))][i - 1]
                );
                arrMin[j][i] = std::min(
                    arrMin[j][i - 1],
                    arrMin[j + (1 << (i - 1))][i - 1]
                );
                minUNeg[j][i] = std::min(
                    minUNeg[j][i - 1],
                    minUNeg[j + (1 << (i - 1))][i - 1]
                );
            }
        }
    }

    inline ll get_max(size_t left, size_t right) {
        size_t Log = get_log2(right - left + 1);
        return std::max(arrMax[left][Log], arrMax[right - (1 << Log) + 1][Log]);
    }

    inline ll get_maxNeg(size_t left, size_t right) {
        size_t Log = get_log2(right - left + 1);
        return std::max(maxNeg[left][Log], maxNeg[right - (1 << Log) + 1][Log]);
    }

    inline ll get_min(size_t left, size_t right) {
        size_t Log = get_log2(right - left + 1);
        return std::min(arrMin[left][Log], arrMin[right - (1 << Log) + 1][Log]);
    }

    inline ll get_minUNeg(size_t left, size_t right) {
        size_t Log = get_log2(right - left + 1);
        return std::min(minUNeg[left][Log], minUNeg[right - (1 << Log) + 1][Log]);
    }

};

StTable<MAXN, MAXN_LOG2> arrA, arrB;
ll n, m, q;

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    readf(&n), readf(&m), readf(&q);

    for (size_t i = 1; i <= n; i++) {
        arrA.insert(i, readf<ll>());
    }
    arrA.init();

    for (size_t i = 1; i <= m; i++) {
        arrB.insert(i, readf<ll>());
    }
    arrB.init();
    
    while (q--) {
        size_t aLeft, aRight, bLeft, bRight;
        readf(&aLeft), readf(&aRight), readf(&bLeft), readf(&bRight);
        ll aMax = arrA.get_max(aLeft, aRight), aMin = arrA.get_min(aLeft, aRight);
        ll aNegMax = arrA.get_maxNeg(aLeft, aRight), aUNegMin = arrA.get_minUNeg(aLeft, aRight);
        ll bMax = arrB.get_max(bLeft, bRight), bMin = arrB.get_min(bLeft, bRight);
        ll ans = LLONG_MIN;

        ans = std::max(ans, aMax * (aMax >= 0 ? bMin : bMax));
        ans = std::max(ans, aMin * (aMin >= 0 ? bMin : bMax));
        if (aNegMax != LLONG_MIN) {
            ans = std::max(ans, aNegMax* (aNegMax >= 0 ? bMin : bMax));
        }
            
        if (aUNegMin != LLONG_MAX) {
            ans = std::max(ans, aUNegMin * (aUNegMin >= 0 ? bMin : bMax));
        }
        printf("%lld\n", ans);
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
    while (top) putchar(sta[--top] + '0');  // 48 �� '0'
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