//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
//
//      By txp2024 www.luogu.com.cn  TXP2023 www.github.com
// 
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

#pragma once
#include <vector>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <numeric>
#include <ctype.h>
#include <cstdarg>
#include <climits>
#include <string>
#include <queue>
#include <time.h>
#include <iostream>
#include <stdint.h>

#define _FREAD        true
#define MAX_INF       1e18
#define MAX_NUM_SIZE  35
#define MAX_LENGTH    2000005
#define ROOT          0

typedef long long int ll;
typedef unsigned long long int ull;

//快读函数声明
template< typename Type >
inline Type fread(Type* p = nullptr);

//快速输出函数
template<typename Type>
inline void fwrite(Type x);

// AC 自动机数组
ll trie_index[MAX_LENGTH][26]; // 子节点编号
ll fail[MAX_LENGTH];           // 失配指针
ll trie_cnt_arr[MAX_LENGTH];   // 节点匹配次数
ll end_id[MAX_LENGTH];         // 终止节点对应的模式串ID（首次出现）
ll strPos[MAX_LENGTH];         // 每个模式串首次出现的ID
ll ans[MAX_LENGTH];            // 每个模式串的匹配次数
ll inDegree[MAX_LENGTH];       // 入度

ll trie_cnt = 0; // 节点计数（0是根节点）
ll n;            // 模式串数量
std::string text;      // 文本串

// 插入模式串（迭代版本）
void insertMod(const std::string& s, ll str_id) {
    ll u = ROOT;
    for (char ch : s) {
        ll c = ch - 'a';
        if (!trie_index[u][c]) trie_index[u][c] = ++trie_cnt;
        u = trie_index[u][c];
    }
    if (!end_id[u]) end_id[u] = str_id; // 记录首次出现的模式串ID
    strPos[str_id] = end_id[u];         // 所有相同的模式串指向首次出现的ID
}

// 构建失配指针（BFS）
void get_fail() {
    std::queue<ll> que;

    // 根节点的子节点失配指针指向根节点
    for (ll i = 0; i < 26; i++) {
        if (trie_index[ROOT][i]) {
            fail[trie_index[ROOT][i]] = ROOT;
            que.push(trie_index[ROOT][i]);
        }
    }

    // BFS 构建失配指针
    while (!que.empty()) {
        ll u = que.front();
        que.pop();

        for (ll i = 0; i < 26; i++) {
            if (trie_index[u][i]) {

                // 子节点的失配指针指向父节点失配指针的对应字符子节点
                fail[trie_index[u][i]] = trie_index[fail[u]][i];
                // // 增加入度（被多少失配指针指向）
                inDegree[trie_index[fail[u]][i]]++;
                //// 子节点入队，继续 BFS
                que.push(trie_index[u][i]);
            }
            else {
                // 如果没有该字符子节点，则直接跳到失配节点对应的子节点
                trie_index[u][i] = trie_index[fail[u]][i];
            }
        }
    }
}

// 将文本串匹配进 AC 自动机
void insert_text() {
    ll u = ROOT;
    for (char c : text) {
        u = trie_index[u][c - 'a'];
        trie_cnt_arr[u]++;
    }
}

// 统计所有模式串的匹配次数（拓扑排序 + 失配指针回溯）
void getAnswer() {
    std::queue<ll> que;
    for (ll i = 0; i <= trie_cnt; i++) {
        //// 入度为 0 的节点入队
        if (!inDegree[i]) {
            que.push(i);
        }
    }

    while (!que.empty()) {
        ll u = que.front();
        que.pop();
        // // 如果该节点是某个模式串的结尾，则记录匹配次数
        ans[end_id[u]] = trie_cnt_arr[u]; // 如果是模式串结尾节点，记录匹配次数
        ll v = fail[u];
        trie_cnt_arr[v] += trie_cnt_arr[u];
        // 失配节点入度减 1，若入度为 0，则入队
        if (!(--inDegree[v])) {
            que.push(v);
        }
    }
}

ll main() {

    fread(&n);
    for (ll i = 1; i <= n; i++) {
        std::string mod;
        std::cin >> mod;
        insertMod(mod, i);
    }

    std::cin >> text;

    get_fail();
    insert_text();
    getAnswer();

    for (ll i = 1; i <= n; i++) {
        printf("%lld\n", ans[strPos[i]]);
    }
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
    ll sta[MAX_NUM_SIZE];
    ll top = 0;
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