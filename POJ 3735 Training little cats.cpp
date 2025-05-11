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
#include <ctype.h>
#include <cstdarg>
#include <climits>
#include <time.h>
#include <iostream>
#include <stdint.h>

#define READ          false
#define MAX_INF       1e18
#define MAX_NUM_SIZE  35

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

struct Matrix {
    ll arr[110][110];
};

ll n, m, k;
Matrix tmp, ans;

inline Matrix mul(Matrix a, Matrix b) {
    Matrix ans;
    memset(ans.arr, 0, sizeof(ans.arr));
    for (int k = 0; k <= n; k++)
        for (int i = 0; i <= n; i++)
            if (a.arr[i][k])
                for (int j = 0; j <= n; j++)
                    ans.arr[i][j] += a.arr[i][k] * b.arr[k][j];

    return ans;
}

Matrix fast_mul(int g, Matrix x) {
    Matrix ans;
    memset(ans.arr, 0, sizeof(ans.arr));
    for (int i = 0; i <= n; i++)
        ans.arr[i][i] = 1;
    while (g) {
        if (g & 1) ans = mul(ans, x);
        x = mul(x, x);
        g >>= 1;
    }
    return ans;
}

Matrix init(int k) {
    Matrix tmp;
    memset(tmp.arr, 0, sizeof(tmp.arr));
    for (int i = 0; i <= n; ++i)
        tmp.arr[i][i] = 1;

    char ch[5];
    int a, b;
    while (k--) {
        scanf("%s", ch);
        switch (ch[0]) {
        case 'g':
            scanf("%d", &a);
            tmp.arr[0][a]++;
            break;
        case 's':
            scanf("%d%d", &a, &b);
            for (int i = 0; i <= n; i++) {
                std::swap(tmp.arr[i][a], tmp.arr[i][b]);
            }
            break;
        default:
            scanf("%d", &a);
            for (int i = 0; i <= n; i++) {
                tmp.arr[i][a] = 0;
            }
            break;
        }
    }
    return tmp;
}

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    while (1) {
        readf(&n), readf(&m), readf(&k);
        if ((!n) && (!m) && (!k)) {
            break;
        }
        tmp = init(k);
        ans = fast_mul(m, tmp);
        memset(tmp.arr, 0, sizeof(tmp.arr));
        tmp.arr[0][0] = 1;
        ans = mul(tmp, ans);
        for (int i = 1; i <= n; i++) {
            if (i != 1) {
                printf(" ");
            } 
            printf("%lld", ans.arr[0][i]);
        }
        puts("");
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