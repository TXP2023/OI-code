//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
//
//      By txp2024 www.luogu.com.cn  TXP2023 www.github.com
// 
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
#ifdef ONLINE_JUDGE
    #pragma G++ optimize(3)
    #pragma G++ target("avx")
    #pragma G++ optimize("Ofast")
    #pragma G++ optimize("inline")
    #pragma G++ optimize("-fgcse")
    #pragma G++ optimize("-fgcse-lm")
    #pragma G++ optimize("-fipa-sra")
    #pragma G++ optimize("-ftree-pre")
    #pragma G++ optimize("-ftree-vrp")
    #pragma G++ optimize("-fpeephole2")
    #pragma G++ optimize("-ffast-math")
    #pragma G++ optimize("-fsched-spec")
    #pragma G++ optimize("unroll-loops")
    #pragma G++ optimize("-falign-jumps")
    #pragma G++ optimize("-falign-loops")
    #pragma G++ optimize("-falign-labels")
    #pragma G++ optimize("-fdevirtualize")
    #pragma G++ optimize("-fcaller-saves")
    #pragma G++ optimize("-fcrossjumping")
    #pragma G++ optimize("-fthread-jumps")
    #pragma G++ optimize("-funroll-loops")
    #pragma G++ optimize("-fwhole-program")
    #pragma G++ optimize("-freorder-blocks")
    #pragma G++ optimize("-fschedule-insns")
    #pragma G++ optimize("inline-functions")
    #pragma G++ optimize("-ftree-tail-merge")
    #pragma G++ optimize("-fschedule-insns2")
    #pragma G++ optimize("-fstrict-aliasing")
    #pragma G++ optimize("-fstrict-overflow")
    #pragma G++ optimize("-falign-functions")
    #pragma G++ optimize("-fcse-skip-blocks")
    #pragma G++ optimize("-fcse-follow-jumps")
    #pragma G++ optimize("-fsched-interblock")
    #pragma G++ optimize("-fpartial-inlining")
    #pragma G++ optimize("no-stack-protector")
    #pragma G++ optimize("-freorder-functions")
    #pragma G++ optimize("-findirect-inlining")
    #pragma G++ optimize("-fhoist-adjacent-loads")
    #pragma G++ optimize("-frerun-cse-after-loop")
    #pragma G++ optimize("inline-small-functions")
    #pragma G++ optimize("-finline-small-functions")
    #pragma G++ optimize("-ftree-switch-conversion")
    #pragma G++ optimize("-foptimize-sibling-calls")
    #pragma G++ optimize("-fexpensive-optimizations")
    #pragma G++ optimize("-funsafe-loop-optimizations")
    #pragma G++ optimize("inline-functions-called-once")
    #pragma G++ optimize("-fdelete-null-pointer-checks")
    #pragma G++ optimize(2)
#endif // ONLINE_JUDGE

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

typedef long long int ll;
typedef unsigned long long int ull;

//快读函数声明
template< typename Type >
inline Type readf(Type* p = nullptr);

//快速输出函数
template<typename Type>
inline void writef(Type x);


int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    



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
    if (p != nullptr){
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