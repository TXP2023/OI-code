//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
//
//      By txp2024 www.luogu.com.cn  TXP2023 www.github.com
// 
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
#pragma once
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <ctype.h>
#include <set>
#include <cstdarg>
#include <climits>
#include <time.h>
#include <iostream>
#include <stdint.h>

#define READ             false
#define MAX_INF          1e18
#define MAX_NUM_SIZE     35
#define MAX_BASE_LENGTH  (size_t)(1e5+5)
#define HASH_BASE        233
#define HASH_MOD         UINT64_MAX
#define MAXN             7
#define MOD              (uint64_t)(1e9+7)

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

char bases[MAX_BASE_LENGTH]; //碱基序列 
Hash<MAX_BASE_LENGTH, HASH_BASE, HASH_MOD> hash;
std::multiset<uint64_t> SubsequenceHashing[MAXN];
std::set<uint64_t> Hashing;
std::vector<uint64_t> vec;
int n, m, k;
uint64_t ans;


inline short mapping(const char& ch) {
    switch (ch) {
    case 'A':
        return 1;
        break;
    case 'G':
        return 2;
        break;
    case 'C':
        return 3;
        break;
    case 'T':
        return 4;
        break;
    default:
        return 0;
    }
}

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
    memset(hash, 0, sizeof(hash));
    for (size_t i = 1; i <= strlen(_Str); i++) {
        hash[i] = (hash[i - 1] * base + mapping(_Str[i - 1])) % _mod;
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

    
void dfs(size_t pos, size_t cnt, size_t mul) {
    if (cnt == m) {
        ans += mul;
        ans %= MOD;
        return;
    }
    if (pos == vec.size()) {
        return;
    }
    dfs(pos + 1, cnt + 1, mul * vec[pos]);
    dfs(pos + 1, cnt, mul);
    return;
}

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    //TODO
    readf(&n), readf(&m), readf(&k);

    for (size_t i = 1; i <= n; i++) {
        scanf("\n%s", bases + 1);
        hash = Hash<MAX_BASE_LENGTH, HASH_BASE, HASH_MOD>(bases + 1);
        for (size_t j = 1; j + k - 1 <= strlen(bases + 1); ++j) {
            uint64_t val = hash.get_range_hash(j, j + k - 1);
            SubsequenceHashing[i].insert(val);
            Hashing.insert(val);
        }
    }

    for (auto& hash_value : Hashing) {
        vec.clear();
        for (size_t i = 1; i <= n; i++) {
            ll val = SubsequenceHashing[i].count(hash_value);
            if (val) {
                vec.push_back(val);
            }
        }
        if (vec.size() >= m) {
            dfs(0, 0, 1);
        }
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