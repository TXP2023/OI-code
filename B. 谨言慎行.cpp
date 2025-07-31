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
#include <map>
#include <queue>
#include <set>

//typedef long long size_t;

#define _FREAD        true
#define MAX_INF       1e18
#define MAX_NUM_SIZE  35
#define MAXM          (size_t)(1e5+5)
#define MAXN          (size_t)(1e5+5)
#define TRIE_SIZE     (size_t)(2e5+5)
#define ROOT          0

typedef long long int ll;
typedef unsigned long long int ull;

//快读函数声明
template< typename Type >
inline Type readf(Type* p = nullptr);

//快速输出函数
template<typename Type>
inline void writef(Type x);

struct KeyWord {
    std::string s;
    ll level;

    bool operator ==(const KeyWord& other) {
        return other.s == s;
    }
}; 

struct Record {
    std::string s;
    ll user;
};

struct Trie_node {
    ll ind[26];
    ll cnt, str_id; //经过这个节点的模式串数量 以这个节点为终点的模式串数量

    Trie_node() {
        memset(ind, 0, sizeof(ind));
        cnt = 0, str_id = 0;
        return;
    }
};

Trie_node trie[TRIE_SIZE];
ll inDegree[TRIE_SIZE], fail[TRIE_SIZE];
KeyWord words[MAXN];
ll res[MAXM];
Record records[MAXN];
std::map<std::string, ll> userId;
std::map<ll, std::string> userName;
bool flag[MAXN];
ll n, m, userCnt = 0, myId, trie_cnt, a, b, ans = 0;

//对于一个审查级别，存在4中情况
//群聊没封， 自己给封了  在这个情况下，没有正解
//群聊没封， 自己没封    证明这个审查级别低了 返回-1
//群聊封了， 自己给封了  证明这个审查级别高了 返回 1
//群聊封了， 自己没封    证明这个审查级合适别 返回 0

inline void _clear_trie() {
    for (size_t i = 0; i <= trie_cnt; i++) {
        trie[i] = Trie_node();
    }
    trie_cnt = 0;
    memset(inDegree, 0, sizeof(inDegree));
    memset(fail, 0, sizeof(fail));
    return;
}

//将模式串str插入到trie的pos节点，这个模式串的id为str_id
void _insert(std::string s, ll cnt, const size_t& pos, const size_t& str_id) {
    if (cnt == s.length()) { 
        if (!trie[pos].str_id) { //以前没有从根节点当前trie节点的模式串
            trie[pos].str_id = str_id;  //记录从根节点当前trie节点的模式串的id
        }
        //strPos[str_id] = trie[pos].str_id;  //记录当前模式串首次出现的id
        //如果这次是首次出现，那么 strPos[str_id] = trie[pos].str_id = str_id
        //如果已经出现过相同的模式串 strPos[str_id] = trie[pos].str_id = 首次出现的id
        return;
    }
    if (!trie[pos].ind[s[cnt] - 'a']) {
        trie[pos].ind[s[cnt] - 'a'] = ++trie_cnt;
    }
    _insert(s, cnt + 1, trie[pos].ind[s[cnt] - 'a'], str_id);
    return;
}

//将文本串插入到trie中
inline void _insert_text(std::string s) {
    //由于已经在程序的第101行中按照失配指针计算方法处理了没有子节点的情况，因此直接插入，不会新建节点。
    size_t u = ROOT;
    for (size_t i = 0; i < s.length(); i++) {
        u = trie[u].ind[s[i] - 'a'];
        ++trie[u].cnt;
    }
    return;
}

//将文本串插入到trie中
inline void _remove_text(std::string s) {
    //由于已经在程序的第101行中按照失配指针计算方法处理了没有子节点的情况，因此直接插入，不会新建节点。
    size_t u = ROOT;
    for (size_t i = 0; i < s.length(); i++) {
        u = trie[u].ind[s[i] - 'a'];
        --trie[u].cnt;
    }
    return;
}

//计算失配指针
inline void _get_fail() {
    std::queue<uint32_t> que;
    //一个节点u所代表的字母w，这个节点的失配指针为这个节点的父节点的失配指针所指向字母w的对应节点
    //所有根节点的子节点的失配指针为根节点
    for (size_t i = 0; i <= 25; i++) {
        if (trie[ROOT].ind[i]) {
            fail[trie[ROOT].ind[i]] = ROOT;
            que.push(trie[ROOT].ind[i]);
        }
    }
    while (!que.empty()) {
        uint32_t u = que.front();
        que.pop();
        for (size_t i = 0; i <= 25; i++) {
            //通过一个节点作为父节点，计算子节点的失配指针
            if (trie[u].ind[i]) {
                fail[trie[u].ind[i]] = trie[fail[u]].ind[i];
                //这个节点的失配指针为这个节点的父节点的失配指针所指向对应字母的对应节点
                ++inDegree[trie[fail[u]].ind[i]]; //inDegree[i]记录节点i被多少个失配指针所指向
                //这个节点的失配指针已经被计算，那么其的子节点的失配指针可以由这个节点计算
                que.push(trie[u].ind[i]);
            }
            else {
                trie[u].ind[i] = trie[fail[u]].ind[i]; //没有这个节点的话，则子节点索引指向失配指针
            }
        }
    }
    return;
}

inline void _getAnswer() {
    std::queue<uint32_t> que;
    ll ret = 0;
    for (size_t i = 0; i <= trie_cnt; i++) {
        if (!inDegree[i]) {
            que.push(i);
        }
    }
    while (!que.empty()) {
        size_t u = que.front(), v;
        que.pop();
        res[trie[u].str_id] = trie[u].cnt;
        v = fail[u];
        trie[v].cnt += trie[u].cnt;
        if (!(--inDegree[v])) {
            que.push(v);
        }
    }
    return;
}

inline void _init() {
    _clear_trie();
    memset(res, 0, sizeof(res));
    memset(fail, 0, sizeof(fail));
    memset(inDegree, 0, sizeof(inDegree));
    return;
}

inline int check(ll _lev) {
    //首先，初始化trie
    // |-清空trie
    // |-构建trie

    _init();
    //构建
    for (size_t i = 1; i <= m && words[i].level <= _lev; i++) {
        _insert(words[i].s, 0, 0, i);
    }

    //构建fail指针
    _get_fail();
    
    ll cnt = 0;
    bool flag = false;// 自己有没有被封
    
    for (size_t i = 1; i <= n; i++) {
        ll temp = 0;
        _insert_text(records[i].s);
        _getAnswer();
        //扫一遍，记录多少个模式串在这个聊天记录中存在 
        for (size_t i = 1; i <= m; i++) {
            temp += res[i];
        }
        _remove_text(records[i].s);
        if (temp >= a) {
            ++cnt;
        }
        if (temp >= a && records[i].user == myId) {
            flag = true;
        }
    }
    if (cnt >= b) {
        if (flag) {
            ////群聊封了， 自己给封了  证明这个审查级别高了 返回 1
            return 1;
        }
        else {
            //群聊封了， 自己没封    证明这个审查级合适别 返回 0
            return 0;
        }
    }
    else {
        return -1;
    }
}

inline void get_user(ll _lev) {
    //首先，初始化trie
    // |-清空trie
    // |-构建trie

    //清空
    _init();
    //构建
    for (size_t i = 1; i <= m && words[i].level <= _lev; i++) {
        _insert(words[i].s, 0, 0, i);
    }

    //构建fail指针
    _get_fail();

    ll cnt = 0;

    memset(flag, 0, sizeof(flag));
    for (size_t i = 1; i <= n; i++) {
        ll temp = 0;
        _insert_text(records[i].s);
        _getAnswer();
        //扫一遍，记录多少个模式串在这个聊天记录中存在
        _remove_text(records[i].s);
        for (size_t i = 1; i <= m; i++) {
            temp += res[i];
        }
        if (temp >= a) {
            flag[records[i].user] = true;
        }
    }
    
    std::vector<std::string> v;
    for (size_t i = 1; i <= n; i++) {
        if (flag[i]) {
            v.push_back(userName[i]);
        }
    }

    std::sort(v.begin(), v.end(), [](const std::string& a, const std::string& b) {
        if (a.size() != b.size()) {
            //return a.size() < b.size();
            return a < b;
        }
        return a < b;
    });

    for (auto& i : v) {
        std::cout << i << '\n';
    }
    return;
}


int main() {

#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN
    std::cin >> n >> m;

    for (size_t i = 1; i <= m; i++) {
        std::cin >> words[i].level;
        std::cin >> words[i].s;
    }

    std::sort(words + 1, words + 1 + m, [](const KeyWord& a, const KeyWord& b) {
        if (a.s == b.s) {
            return a.level < b.level;
        }
        return a.s < b.s;
    });

    m = std::unique(words + 1, words + 1 + m) - (words + 1);

    std::sort(words + 1, words + 1 + m, [](const KeyWord& a, const KeyWord& b) {
        return a.level < b.level;
    });

    for (size_t i = 1; i <= n; i++) {
        std::string s, user;
        std::cin >> user >> records[i].s;
        if (!userId[user]) {
            userId[user] = ++userCnt;
            userName[userId[user]] = user;
        }
        if (user == "littlez") {
            myId = userId[user];
            //myRecord.push_back(s);
        }
        records[i].user = userId[user];
    }

    std::cin >> a >> b;

    for (size_t l = 1, r = 1e9; l <= r ;) {
        ll mid = (l + r) >> 1;
        ll ret = check(mid);
        switch (ret) {
        case -1:
            l = mid + 1;
            break;
        case 0:
            r = mid - 1;
            ans = mid;
            break;
        case 1:
            r = mid - 1;
            break;
        }
    }

    if (!ans) {
        puts("hehe");
        return 0;
    }

    printf("%lld\n", ans);

    get_user(ans);
    return 0;
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