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
#include <string.h>
#include <iostream>
#include <stdint.h>

#define READ          false
#define MAX_INF       1e18
#define MAX_NUM_SIZE  35
#define MAX_LENGTH    (uint64_t)(2e6+5)
#define _DEBUG        true
#define HASH_1_BASE   998244353
#define HASH_1_MOD    UINT64_MAX
#define HASH_2_BASE   998244353
#define HASH_2_MOD    UINT64_MAX

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
    Hash(const char *_Str);

    inline uint64_t get_range_hash(size_t _First_Pos, size_t _Last_Pos);

    inline uint64_t fast_pow(size_t bas, size_t pow);

    uint64_t base = _base;
private:
    uint64_t hash[_MaxStrLenght];
    
};


Hash<MAX_LENGTH, HASH_1_BASE, HASH_1_MOD> hash_1;
Hash<MAX_LENGTH, HASH_2_BASE, HASH_2_MOD> hash_2;
char str[MAX_LENGTH], ans_l[MAX_LENGTH/2], ans_r[MAX_LENGTH / 2];
bool left_tag = false, right_tag = false;
size_t n, ans_cnt = 0;

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
Hash<_MaxStrLenght, _base, _mod>::Hash(const char *_Str) {
    for (size_t i = 1; i <= n; i++) {
        hash[i] = (hash[i - 1] * base + _Str[i] - 'A' + 1) % _mod;
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

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    //TODO
    readf(&n);
    if (n % 2 == 0) {
        puts("NOT POSSIBLE");
        return 0;
    }
    scanf("\n%s", str + 1);
    str[0] = 'A' - 1;

    hash_1 = Hash<MAX_LENGTH, HASH_1_BASE, HASH_1_MOD>(str);

    ll size = n / 2;
    uint64_t right_hash_1 = hash_1.get_range_hash(size + 2, n);
    for (size_t i = 1; i <= size + 1; i++) {
        uint64_t uhash_1, uhash_2;
        uhash_1 = hash_1.get_range_hash(1, i - 1) * hash_1.fast_pow(hash_1.base, n / 2 - i + 1) + hash_1.get_range_hash(i + 1, size + 1);
        if (uhash_1 == right_hash_1) {
            ++ans_cnt;
            left_tag = true;
            strcpy(ans_l + 1, str + n / 2 + 2);
            break;
        }
    }

    uint64_t left_hash_1 = hash_1.get_range_hash(1, size);
    for (size_t i = n/2 + 1; i <= n; i++) {
        uint64_t uhash_1, uhash_2;
        uhash_1 = hash_1.get_range_hash(n / 2 + 1, i - 1) * hash_1.fast_pow(hash_1.base, n - i) + hash_1.get_range_hash(i + 1, n);
        if (uhash_1 == left_hash_1) {
            ++ans_cnt;
            right_tag = 1;
            strncpy(ans_r + 1, str + 1, size);
            break;
        }
    }
    
    if (ans_cnt == 0) {
        puts("NOT POSSIBLE");
        return 0;
    }
    if (ans_cnt == 1 || !strcmp(ans_l + 1, ans_r + 1)) {
        if (left_tag) {
            puts(ans_l + 1);
            return 0;
        }
        if (right_tag) {
            puts(ans_r + 1);
            return 0;
        }
        
    }
    else {
        puts("NOT UNIQUE");
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