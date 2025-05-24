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
#define MAXN          105
#define MAXM          2505

typedef long long int ll;
typedef unsigned long long int ull;

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
    size_t size;
    ll arr_[MAXN][MAXN];

    inline Matrix operator *(const Matrix& other) const {
        Matrix ret;
        ret.size = other.size;
        memset(ret.arr_, 1, sizeof(ret.arr_));
        for (size_t i = 1; i <= size; i++) {
            for (size_t j = 1; j <= size; j++) {
                for (size_t k = 1; k <= size; k++) {
                    if (ret.arr_[i][j] > this->arr_[i][k] + other.arr_[k][j]) {
                        ret.arr_[i][j] = this->arr_[i][k] + other.arr_[k][j];
                    }
                }
            }
        }
        return ret;
    }

    inline void operator =(const Matrix& other) {
        this->size = other.size;
        for (size_t i = 1; i <= size; i++) {
            for (size_t j = 1; j <= size; j++) {
                this->arr_[i][j] = other.arr_[i][j];
            }
        }
        return;
    }

    inline void operator *=(const Matrix& other) {
        (*this) = (*this) * other;
        return;
    }
};

struct edge {
    size_t u, v, w;
};

edge edges[MAXM];
ll graph[MAXN][MAXN];
ll n, m, magic;
Matrix ans;

inline Matrix Matrix_pow(Matrix x, size_t index) {
    Matrix e, f(x);
    e.size = x.size;
    for (size_t i = 1; i <= e.size; ++i)
        for (size_t j = 1; j <= e.size; ++j)
            e.arr_[i][j] = graph[i][j];
    while (index) {
        if (index & 1)
            e *= f;
        f *= f;
        index >>= 1;
    }
    return e;
}

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    readf(&n), readf(&m), readf(&magic);

    for (size_t i = 1; i <= n; i++) {
        for (size_t j = 1; j <= n; j++) {
            if (i != j) {
                graph[i][j] = MAX_INF;
            }
        }
    }


    for (size_t i = 1; i <= m; i++) {
        readf(&edges[i].u), readf(&edges[i].v), readf(&edges[i].w);
        graph[edges[i].u][edges[i].v] = edges[i].w;
    }

    for (size_t k = 1; k <= n; k++) {
        for (size_t i = 1; i <= n; i++) {
            for (size_t j = 1; k != i && j <= n; j++) {
                if (i != j && graph[i][j] > graph[i][k] + graph[k][j]) {
                    graph[i][j] = graph[i][k] + graph[k][j];
                }
            }
        }
    }

    if (magic) {
        ans.size = n;
        for (size_t i = 1; i <= n; i++) {
            for (size_t j = 1; j <= n; j++) {
                ans.arr_[i][j] = graph[i][j];
            }
        }

        for (size_t k = 1; k <= m; k++) {
            for (size_t i = 1; i <= n; i++) {
                for (size_t j = 1; j <= n; j++) {
                    if (ans.arr_[i][j] > ll(graph[i][edges[k].u] + graph[edges[k].v][j] - edges[k].w)) {
                        ans.arr_[i][j] = ll(graph[i][edges[k].u] + graph[edges[k].v][j] - edges[k].w);
                    }
                }
            }
        }

        ans = Matrix_pow(ans, magic);
        printf("%lld\n", ans.arr_[1][n]);
    }
    else {
        printf("%lld\n", graph[1][n]);
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