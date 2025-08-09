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
#include <stack>
#include <iostream>
#include <stdint.h>

#define _FREAD        true
#define MAX_INF       1e18
#define MAX_NUM_SIZE  35
#define MAXN          2005
#define MAXM          2005

typedef long long int ll;
typedef unsigned long long int ull;

//快读函数声明
template< typename Type >
inline Type fread(Type* p = nullptr);

//快速输出函数
template<typename Type>
inline void fwrite(Type x);

ll f[MAXN][MAXM], map[MAXN][MAXM];
ll n, m, ans = 0;

struct StackData {
    ll hight;
    ll beg;

    StackData() : hight(0), beg(0) {}

    StackData(ll _h, ll _b) : hight(_h), beg(_b) {}
};

inline void init() {
    ll temp[MAXN][MAXM];
    memset(temp, 0, sizeof(temp));
    // 初始化 a[i][j] = 高度 i、宽度 j 的矩形数量
    for (size_t i = 1; i <= n; i++) {
        for (size_t j = 1; j <= m; j++) {
            temp[i][j] = (ll)i * j;
        }
    }

    // 横向前缀和: t[i][j] 表示 高度固定为 i，宽度 ≤ j 的矩形总数
    for (size_t i = 1; i <= n; i++) {
        for (size_t j = 1; j <= m; j++) {
            f[i][j] = (ll)f[i][j - 1] + temp[i][j];
        }
    }

    //// 再横向累加到 a：a[i][j] 表示 高度 ≤ i 且宽度 ≤ j 的矩形总数（纵向前缀还没做）
    for (size_t i = 1; i <= n; i++) {
        for (size_t j = 1; j <= m; j++) {
            temp[i][j] = (ll)temp[i][j - 1] + f[i][j];
        }
    }

    // 纵向前缀和：t[i][j] 表示 高度 ≤ i 且宽度 ≤ j 的矩形总数（最终贡献表）
    for (size_t i = 1; i <= n; i++) {
        for (size_t j = 1; j <= m; j++) {
            f[i][j] = (ll)f[i - 1][j] + temp[i][j];
        }
    }
    return;
}


int main() {

#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    fread(&n), fread(&m);

    for (size_t i = 1; i <= n; i++) {
        for (size_t j = 1; j <= m; j++) {
            char ch;
            std::cin >> ch;
            if (ch == '.') {
                map[i][j] = map[i - 1][j] + 1;
            }
            else {
                map[i][j] = 0;
            }
        }
    }

    init();

    for (size_t i = 1; i <= n; i++) {
        std::stack<StackData> stack;
        for (size_t j = 1; j <= m; j++) {
            //ll hight = f[i][j], begin = j; //当前柱子高度  当前柱子起始列
            StackData now = StackData(map[i][j], j);
            // 栈内保持非递减高度，一旦遇到更低的柱子就结算
            while (!stack.empty() && stack.top().hight >= now.hight) {
                StackData temp = stack.top();
                stack.pop();
                now.beg = temp.beg;

                //弹出一个柱子时，我们先算“从它到当前列”的所有矩形数，再减去“由更矮柱子负责的矩形数”。
                ans += f[temp.hight][j - temp.beg];
                ans -= f[std::max(stack.empty() ? 0ll : stack.top().hight, now.hight)][j - temp.beg];
            }
            stack.push(now);
        }

        // 处理本行剩余栈中的柱子
        while (!stack.empty()) {
            StackData temp = stack.top();
            stack.pop();
            ans += f[temp.hight][m + 1 - temp.beg];
            ans -= f[stack.empty() ? 0ll : stack.top().hight][m + 1 - temp.beg];
        }
    }

    printf("%lld\n", ans);



#ifdef _RUN_TIME
    printf("The running duration is not less than %ld ms\n", clock() - start);
#endif // _RUN_TIME
    return 0;
}

template< typename Type >
inline Type fread(Type* p) {
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
inline void fwrite(Type x) {
    int sta[MAX_NUM_SIZE];
    int top = 0;
    do {
        sta[top++] = x % 10, x /= 10;
    } while (x);
    while (top) {
        putchar(sta[--top] + '0');
    }  // 48 是 '0'
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