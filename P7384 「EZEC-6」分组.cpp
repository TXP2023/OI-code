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
#define BIT_SIZE      61

typedef long long int ll;
typedef unsigned long long int ull;

//快读函数声明
template< typename Type >
inline Type readf(Type* p = nullptr);

//快速输出函数
template<typename Type>
inline void writef(Type x);

#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1 << 21], * p1 = buf, * p2 = buf;
template <typename T>
inline void read(T& r) {
    r = 0; bool w = 0; char ch = getchar();
    while (ch < '0' || ch>'9') w = ch == '-' ? 1 : 0, ch = getchar();
    while (ch >= '0' && ch <= '9') r = r * 10 + (ch ^ 48), ch = getchar();
    r = w ? -r : r;
}

ull arr[BIT_SIZE + 1]; //记录位之间相互绑定的关系
ull n, ans = 0;
ull all;

#ifdef _MSVC
inline ll __builtin_ffsll(ull x) {
    ull temp = x & -x, res = 0;
    while (temp) {
        temp >>= 1;
        ++res;
    }
    return --res;
}
#endif // _MSVC



int main() {

#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    for (int i = 1; i <= BIT_SIZE; ++i) {
        arr[i] = 1ll << (i - 1);
    } 

    read(n);

    while (n--) {
        ull value;
        read(value);
        if (!value) {
            //这个数字为0，单独分一组不会产生任何影响
            ++ans;
            continue;
        }
        //这个数字可能会对位之间加以绑定关系，计算并施加绑定关系
        all |= value;
        ull p = __builtin_ffsll(value), temp = arr[p] | value;
        if (temp == arr[p]) {
            continue;
        }
        //进行传染
        for (size_t i = 1; i <= BIT_SIZE; ++i) {
            if ((1ll << (i - 1)) & temp) {
                temp |= arr[i];
            }
        }
            
        for (size_t i = 1; i <= BIT_SIZE; ++i) {
            if ((1ll << (i - 1)) & temp) {
                arr[i] |= temp;
            }
        }
    }

    for (size_t i = 1; i <= BIT_SIZE; i++) {
        if ((1ll << (i - 1)) & all) {
            if (arr[i]) {
                ++ans;
                ull t = arr[i];
                //把所有相连的染上色
                for (size_t j = 1; j <= BIT_SIZE; ++j) {
                    if ((1ll << (j - 1)) & t) {
                        arr[j] = 0;
                    }
                }
                    
            }
        }
    }

    printf("%llu\n", ans);

#ifdef _RUN_TIME
    printf("The running duration is not less than %ld ms\n", clock() - start);
#endif // _RUN_TIME
    return 0;
}

template< typename Type >
inline Type readf(Type* p) {
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