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
#define MAXN          (size_t)(2e5+5)
#define SERVER        0

typedef long long int ll;
typedef unsigned long long int ull;

//快读函数声明
template< typename Type >
inline Type readf(Type* p = nullptr);

//快速输出函数
template<typename Type>
inline void writef(Type x);

struct Computer {
    ll prePos;
    std::string suffix;
    Computer() {
        prePos = -1;
    }

    inline void add_suffix() {
        std::string s;
        std::cin >> s;
        suffix += s;
    }
};
Computer computers[MAXN];
ll n, q;

void show(ll pos) {
    if (computers[pos].prePos != -1) {
        show(computers[pos].prePos);
    }
    std::cout << computers[pos].suffix;
    return;
}

ll find(ll pos) {
    if (computers[pos].prePos != -1) {
        return find(computers[pos].prePos);
    }
    return pos;
}

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    readf(&n), readf(&q);

    while (q--) {
        ll opt, p, s;
        readf(&opt), readf(&p);
        switch (opt) {
        case 1: //将pc P 的字符串替换为服务器的字符串
            if (computers[SERVER].prePos != -1) {
                computers[SERVER].prePos = find(computers[SERVER].prePos);
            }
            if (computers[find(SERVER)].suffix.size() == 0) {
                continue;
            }
            computers[p].prePos = find(SERVER);
            computers[p].suffix = computers[find(SERVER)].suffix;
            break;
        case 2: //将字符串s添加到PC p的末尾
            computers[p].add_suffix();
            break;
        case 3://将服务器 的字符串替换为PC[p]的字符串
            if (computers[p].prePos != -1) {
                if (computers[find(computers[p].prePos)].suffix.length() == 0) {
                    computers[p].prePos = -1;
                }
                if (computers[p].prePos != -1) {
                    computers[p].prePos = find(computers[p].prePos);
                }
                
            }
            computers[SERVER].suffix = computers[find(p)].suffix;
            break;
        }
    }

    std::cout << computers[0].suffix;
    puts("");


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