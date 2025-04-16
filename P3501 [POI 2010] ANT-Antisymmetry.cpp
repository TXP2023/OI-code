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
#define MAXN          (uint64_t)(5e5+5)

typedef long long int ll;
typedef unsigned long long int unill;

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

template<size_t _MaxStrLenght, uint64_t _base, uint64_t _mod>
class Hash {
public:
    Hash();
    Hash(const char* _Str);

    inline uint64_t get_range_hash(size_t _First_Pos, size_t _Last_Pos);

    inline uint64_t fast_pow(size_t bas, size_t pow);

    uint64_t base = _base;
private:
    uint64_t hash[_MaxStrLenght];

};

Hash<MAXN, 131, UINT64_MAX> hash_1;
Hash<MAXN, 131, UINT64_MAX> hash_2;
char arr[MAXN];
uint32_t n, ans = 0;

template<size_t _MaxStrLenght, uint64_t _base, uint64_t _mod>
inline uint64_t Hash<_MaxStrLenght, _base, _mod>::fast_pow(size_t bas, size_t pow) {
    uint64_t ret = 1;
    while (pow > 0) {
        if (pow & 1) {
            ret *= bas;
        }
        bas *= bas;
        bas %= _mod;
        pow >>= 1;
    }
    return ret % _mod;
}

template<size_t _MaxStrLenght, uint64_t _base, uint64_t _mod>
Hash<_MaxStrLenght, _base, _mod>::Hash() {
    memset(hash, 0, sizeof(hash));
    return;
}

template<size_t _MaxStrLenght, uint64_t _base, uint64_t _mod>
Hash<_MaxStrLenght, _base, _mod>::Hash(const char* _Str) {
    for (size_t i = 1; i <= n; i++) {
        hash[i] = (hash[i - 1] * base + _Str[i] - '0' + 1) % _mod;
    }
    return;
}

template<size_t _MaxStrLenght, uint64_t _base, uint64_t _mod>
inline uint64_t Hash<_MaxStrLenght, _base, _mod>::get_range_hash(size_t _First_Pos, size_t _Last_Pos) {
    if (_First_Pos > _Last_Pos) {
        return 0;
    }
    return (hash[_Last_Pos] - hash[_First_Pos - 1] * fast_pow(_base, _Last_Pos - _First_Pos + 1)) % _mod;
}

inline bool chick(ll _First, ll _Last) {
    return hash_1.get_range_hash(_First, _Last) == hash_2.get_range_hash(n - _Last + 1, n - _First + 1);
}

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    //TODO
    readf(&n);

    for (size_t i = 1; i <= n; i++) {
        arr[i] = getchar();
    }

    hash_1 = Hash<MAXN, 131, UINT64_MAX>(arr);

    for (size_t i = 1; i <= n / 2; i++) {
        std::swap(arr[i], arr[n - i + 1]);
        arr[i] ^= 1;
        arr[n - i + 1] ^= 1;
    }
    if (n % 2 == 1) {
        arr[n / 2 + 1] ^= 1;
    }

    hash_2 = Hash<MAXN, 131, UINT64_MAX>(arr);

    for (size_t mid = 0; mid < n; mid++) /*区间中位线*/ {
        size_t length_max = std::min(mid, n - mid - 1), length_min = 1, right_length = 0; //向侧边扩展的长度
        while (length_max >= length_min) {
            size_t length_mid = (length_max + length_min) >> 1;
            if (chick(mid + 1 - length_mid, mid + length_mid)) {
                right_length = length_mid;
                length_min = length_mid + 1;
            }
            else {
                length_max = length_mid - 1;
            }
        }
        ans += right_length;
    }

    printf("%lld\n", ans);

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