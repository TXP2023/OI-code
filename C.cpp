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
#define MAXN          (size_t)(2e5 + 5)
#define MAXM          (size_t)(2e5 + 5)
#define MAXQ          (size_t)(2e5 + 5)

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

struct Question {
    uint32_t user, type, page, id;
    inline bool operator ==(const Question& other)const {
        return user == other.user && type == other.type && page == other.page;
    }

    inline bool operator <(const Question& other)const {
        if (*this == other) {
            return false;
        }
        if (user < other.user) {
            return true;
        }
        else {
            if (id < other.id) {
            return true;
            }
            return false;
        }
        return false;
    }

    Question() {
        return;
    }
    Question(uint32_t _User, uint32_t _Type, uint32_t _Page, uint32_t _Id) {
        user = _User;
        id = _Id;
        type = _Type;
        page = _Page;
        return;
    }
};

Question questions[MAXN];
bool pages_tag[MAXM], tag;//pages_tag[i]是这个user是否可以访问第i个页面， tag就是这个user是否可以访问所有页面*/
uint32_t n, m, q, old_user = -1;

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    //TODO
    readf(&n), readf(&m), readf(&q);

    for (size_t i = 1; i <= q; i++) {
        uint32_t type = readf<uint32_t>(), user = readf<uint32_t>(), page = 0;
        if (type != 2) {
            page = readf<uint32_t>();
        }
        questions[i] = Question(user, type, page, i);
    }

    std::sort(questions + 1, questions + 1 + q);

    for (auto& quest : questions) {
        if (old_user != quest.user) { /*此时要开始处理一个新的user的信息*/
            tag = false;
            memset(pages_tag, 0, sizeof(pages_tag));
            old_user = quest.user;
        }

        switch (quest.type) {
        case 1:
            pages_tag[quest.page] = true;
            break;
        case 2:
            tag = true;
            break;
        case 3:
            if (tag == true || pages_tag[quest.page]) { //这个用户可以访问所有的页面
                puts("Yes");
            }
            else {
                puts("No");
            }
        }
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