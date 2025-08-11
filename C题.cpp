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
#include <math.h>
#include <time.h>
#include <iostream>
#include <stdint.h>

#define _FREAD        true
#define MAX_INF       1e18
#define MAX_NUM_SIZE  35
#define MAXN          (size_t)(5e4+5)

typedef long long int ll;
typedef unsigned long long int ull;

//快读函数声明
template< typename Type >
inline Type fread(Type* p = nullptr);

//快速输出函数
template<typename Type>
inline void fwrite(Type x);

struct Range {
    ll l, r, id;
};

Range range[MAXN];
ll arr[MAXN * 2];
bool flag[MAXN];
ll n, block_size, bucket[MAXN], ans;

int main() {

#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    fread(&n);

    for (size_t i = 1; i <= 2 * n; i++) {
        fread(&arr[i]);
        range[arr[i]].id = arr[i];
        if (!range[arr[i]].l) {
            range[arr[i]].l = i;
        }
        else {
            range[arr[i]].r = i;
        }
    }

    block_size = std::sqrt(2 * n) + 1;

    std::sort(range + 1, range + 1 + n, [](const Range& a, const Range& b) {
        if (a.l / block_size + 1 == b.l / block_size + 1) {
            if ((a.l / block_size + 1) & 1) {
                return a.r < b.r;
            }
            else {
                return a.r > b.r;
            }
        }
        return a.l / block_size + 1 < b.l / block_size + 1;
    });

    ll cnt = 0;
    ll l = 1, r = 0;
    //对n/2+1个排序
    for (size_t i = 1; i <= n; i++) {
        ll rL = range[i].l, rR = range[i].r;

        while (l < rL) {
            if (bucket[arr[l]] == 2) {
                --bucket[arr[l]];
                if (!flag[arr[l]]) {
                    ++cnt;
                }
            }
            else {
                --bucket[arr[l]];
                if (!flag[arr[l]]) {
                    --cnt;
                }
            }
            ++l;
        }
        while (l > rL) {
            --l;
            if (bucket[arr[l]] == 1) {
                ++bucket[arr[l]];
                //--cnt;
                if (!flag[arr[l]]) {
                    --cnt;
                }
            }
            else {
                ++bucket[arr[l]];
                //++cnt;
                if (!flag[arr[l]]) {
                    ++cnt;
                }
            }
        }
        while (r > rR) {
            if (bucket[arr[r]] == 1) {
                --bucket[arr[r]];
                //--cnt;
                if (!flag[arr[r]]) {
                    --cnt;
                }
            }
            else {
                --bucket[arr[r]];
                //++cnt;
                if (!flag[arr[r]]) {
                    ++cnt;
                }
            }
            --r;
        }
        while (r < rR) {
            ++r;
            if (bucket[arr[r]] == 1) {
                ++bucket[arr[r]];
                //--cnt;
                if (!flag[arr[r]]) {
                    --cnt;
                }
            }
            else {
                ++bucket[arr[r]];
                //++cnt;
                if (!flag[arr[r]]) {
                    ++cnt;
                }
            }
        }
        ans += cnt;
        flag[range[i].id] = true;
        bucket[range[i].id] = 0;
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