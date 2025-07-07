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

#define MAX_INF       1e18
#define MAX_NUM_SIZE  35
#define MAX_LENGTH    (size_t)(1e5+7)
#define MOD           (size_t)(1e9+7)

typedef unsigned long long int ll;
typedef unsigned long long int ull;

//快读函数声明
template< typename Type >
inline Type readf(Type* p = nullptr);

//快速输出函数
template<typename Type>
inline void writef(Type x);


struct matrix {
    ll arr[27][27];
    
    matrix() {
        memset(arr, 0, sizeof(arr));
        return;
    }

    template<typename Type>
    inline ll* operator [](const Type index){
        return arr[index];
    }

    inline void operator =(matrix other) {
        for (size_t i = 1; i <= 26; i++) {
            for (size_t j = 1; j <= 26; j++) {
                this->arr[i][j] = other[i][j];
            }
        }
        return;
    }

    inline matrix operator *(matrix other) {
        matrix res;
        for (size_t i = 1; i <= 26; i++) {
            for (size_t j = 1; j <= 26; j++) {
                res[i][j] = 0;
                for (size_t k = 1; k <= 26; k++) {
                    res[i][j] += this->arr[i][k] * other.arr[k][j] % MOD;
                    res[i][j] %= MOD;
                }
            }
        }
        return res;
    }

    inline void operator *=(matrix other) {
        matrix _temp = (*this) * other;
        (*this) = _temp;
        return;
    }


    //快速幂
    template<typename Type>
    inline matrix operator ^(Type _index) {
        matrix res, a;
        a = (*this);
        for (size_t i = 1; i <= 26; i++) {
            res[i][i] = 1;
        }

        while (_index) {
            if (_index & 1) {
                res = res * a;
            }
            a = a * a;
            _index >>= 1;
        }
        return res;
    }
}; 

matrix base, ans, temp;
char str[MAX_LENGTH];
ll n, length;

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    for (size_t i = 1; i <= 26; i++) {
        ans[1][i] = 1;
        temp[i][1] = 1;
        for (size_t j = 1; j <= 26; j++) {
            base[i][j] = 1;
        }
    }

    readf(&n);
    scanf("%s", str + 1);

    length = strlen(str + 1);

    for (int i = 2; i <= length; ++i) {
        base[str[i - 1] - 'a' + 1][str[i] - 'a' + 1] = 0;
    }

    printf(
        "%llu\n",
        ((ans * (base ^ (n - 1))) * temp)[1][1] % MOD
    );


#ifdef _RUN_TIME
    printf("The running duration is not less than %ld ms\n", clock() - start);
#endif // _RUN_TIME
    return 0;
}

template< typename Type >
inline Type readf(Type* p) {
    Type ret = 0, sgn = 0, ch = getchar();
    while (!isdigit(ch)) {
        sgn |= ch == '-', ch = getchar();
    }
    while (isdigit(ch)) ret = ret * 10 + ch - '0', ch = getchar();
    if (p != nullptr) {
        *p = Type(sgn ? -ret : ret);
    }
    return sgn ? -ret : ret;
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