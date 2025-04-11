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
#define MAX_LENGTH    (uint64_t)(2e6+1)
#define _DEBUG        true

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

template<size_t _MaxStrLenght>
class Hash {
public:
    Hash();
    Hash(std::string _Str);

    inline uint64_t get_range_hash(size_t _First_Pos, size_t _Last_Pos);
private:
    uint64_t hash[_MaxStrLenght];
    
};

#if _DEBUG
uint64_t base = 2, Mod = UINT64_MAX;
#else
uint64_t base = 12357166273, Mod = 1e9 + 7;
#endif // _DEBUG


std::string str;
Hash<MAX_LENGTH> hash;
size_t n, ans_l, ans_r;

inline uint64_t fast_pow(size_t bas, size_t pow) {
    uint64_t ret = 1;
    while (pow > 0) {
        if (pow & 1) {
            ret *= bas;
        }
        bas *= bas;
        bas %= Mod;
        pow >>= 1;
    }
    return ret % Mod;
}

template<size_t _MaxStrLenght>
Hash<_MaxStrLenght>::Hash() {
    memset(hash, 0, sizeof(hash));
    return;
}

template<size_t _MaxStrLenght>
Hash<_MaxStrLenght>::Hash(std::string _Str) {
    for (size_t i = 1; i <= _Str.length(); i++) {
        hash[i] = (hash[i - 1] * base + _Str[i - 1] - 'A' + 1) % Mod;
    }
    return;
}

template<size_t _MaxStrLenght>
inline uint64_t Hash<_MaxStrLenght>::get_range_hash(size_t _First_Pos, size_t _Last_Pos) {
    if (_First_Pos > _Last_Pos) {
        return 0;
    }
    return hash[_Last_Pos] - hash[_First_Pos - 1] * fast_pow(base, _Last_Pos - _First_Pos + 1) % Mod;
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
    std::cin >> str;

    hash = Hash<MAX_LENGTH>(str);

    ll size = n / 2;
    for (size_t i = 1; i <= n; i++) {
        uint64_t hash_1, hash_2;
        if (i <= n/2) {
            hash_1 = hash.get_range_hash(1, i - 1) * fast_pow(base, n/2 - i + 1) + hash.get_range_hash(i + 1, size + 1);
            hash_2 = hash.get_range_hash(size + 2, n);  
            if (hash_1 == hash_2) {
                if (ans_l == 0) {
                    ans_l = size + 2;
                }
                else {
                    if (hash.get_range_hash(ans_l, ans_l + size - 1) != hash.get_range_hash(size + 2, size + 2 + size - 1)) {
                        puts("NOT UNIQUE");
                        exit(0);
                    }
                }
            }
        }
        else {
            hash_1 = hash.get_range_hash(1, n/2);
            hash_2 = hash.get_range_hash(n/2 + 1, i - 1) * fast_pow(base, n - i) + hash.get_range_hash(i + 1, n);
            if (hash_1 == hash_2) {
                if (ans_l == 0) {
                    ans_l = 1;
                }
                else {
                    if (hash.get_range_hash(ans_l, ans_l + size - 1) != hash.get_range_hash(1, size)) {
                        puts("NOT UNIQUE");
                        exit(0);
                    }
                }
            }
        }
        
    }

    if (ans_l != 0) {
        std::cout << str.substr(ans_l - 1, n/2) << '\n';
    }
    else {
        puts("NOT POSSIBLE");
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