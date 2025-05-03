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
#include <queue>

#define READ          false
#define MAX_INF       1e18
#define MAX_NUM_SIZE  35
#define MAX_LENGTH    (uint32_t)(2e6+5)
#define MAXN          (uint32_t)(2e6+5)
#define ROOT          0

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

struct trie_node {
    uint32_t index[26];
    uint32_t cnt, str_id;

    trie_node() {
        memset(index, 0, sizeof(index));
        cnt = 0;
        return;
    }
};

char str[MAX_LENGTH];
size_t fail[MAX_LENGTH], strPos[MAXN], ans[MAXN], inDegree[MAX_LENGTH], trie_cnt = 0; //失配指针 
trie_node trie[MAX_LENGTH];
ll n, textLength;

#if true
void insert(const char* str, const size_t& pos, const size_t& str_id) {
    if (*str == '\0') {
        if (!trie[pos].str_id) {
            trie[pos].str_id = str_id;
        }
        strPos[str_id] = trie[pos].str_id;
        return;
    }
    //trie[pos].cnt++;
    if (!trie[pos].index[*str - 'a']) {
        trie[pos].index[*str - 'a'] = ++trie_cnt;
    }
    insert(str + 1, trie[pos].index[*str - 'a'], str_id);
    return;
}

void _insert(std::string S, int ip) {
    int pos = 0;
    for (int i = 0; i < S.size(); ++i) {
        if (!trie[pos].index[S[i] - 'a']) {
            trie[pos].index[S[i] - 'a'] = ++trie_cnt;
        }
        pos = trie[pos].index[S[i] - 'a'];
    }
    if (!trie[pos].str_id) {
        trie[pos].str_id = ip;
    }
    strPos[ip] = trie[pos].str_id;
    return;
}
#endif

inline void get_fail() {
    std::queue<uint32_t> que;
    for (size_t i = 0; i <= 25; i++) {
        if (trie[ROOT].index[i]) {
            fail[trie[ROOT].index[i]] = ROOT;
            que.push(trie[ROOT].index[i]);
        }
    }
    while (!que.empty()) {
        uint32_t u = que.front();
        que.pop();
        for (size_t i = 0; i <= 25; i++) {
            if (trie[u].index[i]) {
                fail[trie[u].index[i]] = trie[fail[u]].index[i];
                ++inDegree[trie[fail[u]].index[i]];
                que.push(trie[u].index[i]);
            }
            else {
                trie[u].index[i] = trie[fail[u]].index[i];
            }
        }
    }
    return;
}

void Fail() {
    std::queue<int> q;
    for (register long long i = 0; i <= 25; ++i) {
        if (trie[0].index[i])
            fail[trie[0].index[i]] = 0, q.push(trie[0].index[i]);
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (register long long i = 0; i <= 25; ++i) {
            if (trie[u].index[i])
                fail[trie[u].index[i]] = trie[fail[u]].index[i],
                inDegree[trie[fail[u]].index[i]]++, q.push(trie[u].index[i]);
            else
                trie[u].index[i] = trie[fail[u]].index[i];
        }
    }
}

inline void query() {
    size_t u = ROOT;
    for (size_t i = 1; i <= textLength; i++) {
        u = trie[u].index[str[i] - 'a'];
        ++trie[u].cnt;
    }
    return;
}

inline void getAnswer() {
    std::queue<uint32_t> que;
    for (size_t i = 0; i <= trie_cnt; i++) {
        if (!inDegree[i]) {
            que.push(i);
        }
    }
    while (!que.empty()) {
        size_t u = que.front(), v;
        que.pop();
        ans[trie[u].str_id] = trie[u].cnt;
        v = fail[u];
        trie[v].cnt += trie[u].cnt;
        if (!(--inDegree[v])) {
            que.push(v);
        }
    }
    return;
}

void tuopu() {
    std::queue<int> q;
    for (register long long i = 0; i <= trie_cnt; ++i) {
        if (!inDegree[i]) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        ans[trie[x].str_id] = trie[x].cnt;
        int y = fail[x];
        trie[y].cnt += trie[x].cnt;
        if (!(--inDegree[y])) q.push(y);
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

    //TODO
    while (true) {
        readf(&n);
        if (n == 0) {
            return 0;
        }
        
        for (size_t i = 1; i <= n; i++) {
            scanf("%s", str + 1);
            insert(str + 1, ROOT, i);
        }

        scanf("%s", str + 1);
        textLength = strlen(str + 1);
        get_fail();

        query();
        getAnswer();
        ll ans;

        for (size_t i = 1; i <= n; i++) {
            printf("%lld\n", ans[strPos[i]]);
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