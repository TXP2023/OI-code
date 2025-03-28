//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
//
//      By txp2024 www.luogu.com.cn  TXP2023 www.github.com
// 
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
#pragma once
#include <vector>
#include <stdio.h>
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
#define MAXN          (int64_t)(1e5 + 1)
#define MAXK          (int64_t)(2e5 + 1)

typedef long long ll;
typedef unsigned long long unill;

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

struct data {
    int32_t a, b, c;
    int32_t id, cnt;

    data(int32_t _a, int32_t _b, int32_t _c) {
        a = _a;
        b = _b;
        c = _c;
        cnt = 1;
        return;
    }

    data() {
        return;
    }

    inline bool operator <(const data& other)const {
        if (a == other.a) {
            if (b == other.b) {
                return c < other.c;
            }
            else {
                return b < other.b;
            }
        }
        else {
            return a < other.a;
        }
    }

    inline bool operator ==(const data& other)const {
        return a == other.a && b == other.b && c == other.c;
    }
};

data array[MAXN], cdq_arr[MAXN];
int32_t bit[MAXK]; //
int32_t n, k;
int32_t f[MAXN], ans[MAXN];

template<typename Type>
inline Type lowbit(Type _Value) {
    return _Value & -_Value;
}

inline void insert(int32_t _Index, int32_t _Value) {
    for (size_t i = _Index; i <= k; i+=lowbit(i)) {
        bit[i] += _Value;
    }
    return;
}

inline int32_t query(ll _Index) {
    ll sum = 0;
    for (ll pos = _Index; pos >= 1; pos-=lowbit(pos)) {
        sum += bit[pos];
    }
    return sum;
}

inline int32_t initialization() {
    std::sort(array + 1, array + n + 1);
    int32_t _Index = 1;
    for (size_t i = 2; i <= n; i++) {
        if (array[i] == array[_Index]) {
            array[_Index].cnt++;
        }
        else {
            array[++_Index] = array[i];
        }
    }
    return _Index;
}

void cdq(int32_t left, int32_t right) {
    if (left == right) {
        return;
    }
    int32_t mid = (left + right) >> 1;
    cdq(left, mid);
    cdq(mid + 1, right);
    uint32_t pos_1 = left;
    for (size_t pos_2 = mid + 1; pos_2 <= right; pos_2++) {
        while (pos_1 <= mid && array[pos_1].b <= array[pos_2].b) {
            insert(array[pos_1].c, array[pos_1].cnt);
            ++pos_1;
        }
        f[array[pos_2].id] += query(array[pos_2].c);
    }

    //memset(bit, 0, sizeof(bit));
    for (size_t i = left; i < pos_1; i++) {
        insert(array[i].c, -array[i].cnt);
    }

    pos_1 = left;
    int32_t pos_2 = mid + 1, pos = left;
    while (pos_1 <= mid && pos_2 <= right) {
        if (array[pos_1].b <= array[pos_2].b) {
            cdq_arr[pos] = array[pos_1];
            ++pos_1;
        }
        else {
            cdq_arr[pos] = array[pos_2];
            ++pos_2;
        }
        ++pos;
    }

    while (pos_1 <= mid) {
        cdq_arr[pos++] = array[pos_1++];
    }

    while (pos_2 <= right) {
        cdq_arr[pos++] = array[pos_2++];
    }

    for (size_t i = left; i <= right; ++i) {
        array[i] = cdq_arr[i];
    }
    return;
}

int32_t main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    //TODO
    readf(&n), readf(&k);

    for (size_t i = 1; i <= n; i++) {
        int32_t a = readf<int>(), b = readf<int>(), c = readf<int>();
        array[i] = data(a, b, c);
    }
    
    ll size = initialization();

    for (size_t i = 1; i <= size; i++) {
        array[i].id = i;
    }

    cdq(1, size);

    for (size_t i = 1; i <= size; i++) {
        ans[f[array[i].id] + array[i].cnt - 1] += array[i].cnt;
    }

    for (size_t i = 1; i <= n; i++) {
        printf("%lld\n", ans[i]);
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
    int32_t sta[MAX_NUM_SIZE];
    int32_t top = 0;
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