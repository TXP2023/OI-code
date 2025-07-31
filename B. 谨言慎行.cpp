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

//�����������
template< typename Type >
inline Type readf(Type* p = nullptr);

//�����������
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
    ll cnt, str_id; //��������ڵ��ģʽ������ ������ڵ�Ϊ�յ��ģʽ������

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

//����һ����鼶�𣬴���4�����
//Ⱥ��û�⣬ �Լ�������  ���������£�û������
//Ⱥ��û�⣬ �Լ�û��    ֤�������鼶����� ����-1
//Ⱥ�ķ��ˣ� �Լ�������  ֤�������鼶����� ���� 1
//Ⱥ�ķ��ˣ� �Լ�û��    ֤�������鼶���ʱ� ���� 0

inline void _clear_trie() {
    for (size_t i = 0; i <= trie_cnt; i++) {
        trie[i] = Trie_node();
    }
    trie_cnt = 0;
    memset(inDegree, 0, sizeof(inDegree));
    memset(fail, 0, sizeof(fail));
    return;
}

//��ģʽ��str���뵽trie��pos�ڵ㣬���ģʽ����idΪstr_id
void _insert(std::string s, ll cnt, const size_t& pos, const size_t& str_id) {
    if (cnt == s.length()) { 
        if (!trie[pos].str_id) { //��ǰû�дӸ��ڵ㵱ǰtrie�ڵ��ģʽ��
            trie[pos].str_id = str_id;  //��¼�Ӹ��ڵ㵱ǰtrie�ڵ��ģʽ����id
        }
        //strPos[str_id] = trie[pos].str_id;  //��¼��ǰģʽ���״γ��ֵ�id
        //���������״γ��֣���ô strPos[str_id] = trie[pos].str_id = str_id
        //����Ѿ����ֹ���ͬ��ģʽ�� strPos[str_id] = trie[pos].str_id = �״γ��ֵ�id
        return;
    }
    if (!trie[pos].ind[s[cnt] - 'a']) {
        trie[pos].ind[s[cnt] - 'a'] = ++trie_cnt;
    }
    _insert(s, cnt + 1, trie[pos].ind[s[cnt] - 'a'], str_id);
    return;
}

//���ı������뵽trie��
inline void _insert_text(std::string s) {
    //�����Ѿ��ڳ���ĵ�101���а���ʧ��ָ����㷽��������û���ӽڵ����������ֱ�Ӳ��룬�����½��ڵ㡣
    size_t u = ROOT;
    for (size_t i = 0; i < s.length(); i++) {
        u = trie[u].ind[s[i] - 'a'];
        ++trie[u].cnt;
    }
    return;
}

//���ı������뵽trie��
inline void _remove_text(std::string s) {
    //�����Ѿ��ڳ���ĵ�101���а���ʧ��ָ����㷽��������û���ӽڵ����������ֱ�Ӳ��룬�����½��ڵ㡣
    size_t u = ROOT;
    for (size_t i = 0; i < s.length(); i++) {
        u = trie[u].ind[s[i] - 'a'];
        --trie[u].cnt;
    }
    return;
}

//����ʧ��ָ��
inline void _get_fail() {
    std::queue<uint32_t> que;
    //һ���ڵ�u���������ĸw������ڵ��ʧ��ָ��Ϊ����ڵ�ĸ��ڵ��ʧ��ָ����ָ����ĸw�Ķ�Ӧ�ڵ�
    //���и��ڵ���ӽڵ��ʧ��ָ��Ϊ���ڵ�
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
            //ͨ��һ���ڵ���Ϊ���ڵ㣬�����ӽڵ��ʧ��ָ��
            if (trie[u].ind[i]) {
                fail[trie[u].ind[i]] = trie[fail[u]].ind[i];
                //����ڵ��ʧ��ָ��Ϊ����ڵ�ĸ��ڵ��ʧ��ָ����ָ���Ӧ��ĸ�Ķ�Ӧ�ڵ�
                ++inDegree[trie[fail[u]].ind[i]]; //inDegree[i]��¼�ڵ�i�����ٸ�ʧ��ָ����ָ��
                //����ڵ��ʧ��ָ���Ѿ������㣬��ô����ӽڵ��ʧ��ָ�����������ڵ����
                que.push(trie[u].ind[i]);
            }
            else {
                trie[u].ind[i] = trie[fail[u]].ind[i]; //û������ڵ�Ļ������ӽڵ�����ָ��ʧ��ָ��
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
    //���ȣ���ʼ��trie
    // |-���trie
    // |-����trie

    _init();
    //����
    for (size_t i = 1; i <= m && words[i].level <= _lev; i++) {
        _insert(words[i].s, 0, 0, i);
    }

    //����failָ��
    _get_fail();
    
    ll cnt = 0;
    bool flag = false;// �Լ���û�б���
    
    for (size_t i = 1; i <= n; i++) {
        ll temp = 0;
        _insert_text(records[i].s);
        _getAnswer();
        //ɨһ�飬��¼���ٸ�ģʽ������������¼�д��� 
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
            ////Ⱥ�ķ��ˣ� �Լ�������  ֤�������鼶����� ���� 1
            return 1;
        }
        else {
            //Ⱥ�ķ��ˣ� �Լ�û��    ֤�������鼶���ʱ� ���� 0
            return 0;
        }
    }
    else {
        return -1;
    }
}

inline void get_user(ll _lev) {
    //���ȣ���ʼ��trie
    // |-���trie
    // |-����trie

    //���
    _init();
    //����
    for (size_t i = 1; i <= m && words[i].level <= _lev; i++) {
        _insert(words[i].s, 0, 0, i);
    }

    //����failָ��
    _get_fail();

    ll cnt = 0;

    memset(flag, 0, sizeof(flag));
    for (size_t i = 1; i <= n; i++) {
        ll temp = 0;
        _insert_text(records[i].s);
        _getAnswer();
        //ɨһ�飬��¼���ٸ�ģʽ������������¼�д���
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
    while (top) putchar(sta[--top] + '0');  // 48 �� '0'
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