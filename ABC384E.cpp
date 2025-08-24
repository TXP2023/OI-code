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
#include <queue>

#define _FREAD        true
#define MAX_INF       1e18
#define MAX_NUM_SIZE  35
#define MAXH		  1005
#define MAXW          1005

typedef unsigned long long int ll;
typedef unsigned long long int ull;

//快读函数声明
template< typename Type >
inline Type fread(Type* p = nullptr);

//快速输出函数
template<typename Type>
inline void fwrite(Type x);

ll map[MAXH][MAXW];
bool flag[MAXH][MAXW];
ll h, w, x, p, q, sum;

struct queNode {
    ll x, y, weight;

    inline bool operator < (const queNode& b) const {
        return weight > b.weight;
	}
};

inline bool inMap(ll x, ll y) {
    return 1 <= x && x <= h && 1 <= y && y <= w;
}

int main() {

#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

	fread(&h), fread(&w), fread(&x), fread(&p), fread(&q);

    for (size_t i = 1; i <= h; i++) {
        for (size_t j = 1; j <= w; j++) {
			fread(&map[i][j]);
        }
    }

	std::priority_queue<queNode> que;

	//que.push({ map[p][q], p, q});
    sum += map[p][q];
	flag[p][q] = true;
    if (inMap(p + 1, q)) {
		que.push({ p + 1, q, map[p + 1][q], });
    }
    if (inMap(p - 1, q)) {
		que.push({ p - 1, q, map[p - 1][q] });
    }
    if (inMap(p, q + 1)) {
		que.push({ p, q + 1, map[p][q + 1] });
    }
    if (inMap(p, q-1)) {
		que.push({ p, q - 1, map[p][q - 1] });
    }
    while (!que.empty()) {
        while (flag[que.top().x][que.top().y] && !que.empty()) {
            que.pop();
        }
        if (!que.empty() &&  (x >= sum ||que.top().weight * x >= sum)) {
            break;
        }
        if (que.empty()) {
            break;
        }
		queNode now = que.top();
        que.pop();
        sum += now.weight;
		flag[now.x][now.y] = true;
        if (inMap(now.x + 1, now.y) && !flag[now.x + 1][now.y]) {
            que.push({ now.x + 1, now.y, map[now.x + 1][now.y] });
        }
        if (inMap(now.x - 1, now.y) && !flag[now.x - 1][now.y]) {
			que.push({ now.x - 1, now.y, map[now.x - 1][now.y] });
        }
        if (inMap(now.x, now.y + 1) && !flag[now.x][now.y + 1]) {
			que.push({ now.x, now.y + 1, map[now.x][now.y + 1] });
        }
        if (inMap(now.x, now.y - 1) && !flag[now.x][now.y - 1]) {
            que.push({now.x, now.y - 1,  map[now.x][now.y - 1] });
        }
    }

	printf("%lld\n", sum);


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