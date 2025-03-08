//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
//
//      By txp2024 www.luogu.com.cn  TXP2023 www.github.com
// 
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
/*
����һ����,��ʼÿһ�����ȨֵΪ0
��2�ֲ���
1. �����u~v��·����Ȩֵ����max_value�ĵ����������u~v·���Ͻڵ�����
2. ����T��Ȩֵ��1

Ȩֵ����Ϊ2*1e5

*/
#pragma once
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <ctype.h>
#include <cstdarg>
#include <climits>
#include <time.h>
#include <iostream>
#include <stdint.h>
#include <time.h>

#define READ          false
#define MAX_INF       1e18
#define MAX_NUM_SIZE  35
#define MAXN          (int64_t)(8)

typedef long long int ll;
typedef unsigned long long int unill;

//�����������
#if READ
template< typename T >
inline T readf();
#else
template< typename Type >
inline Type readf(Type* p = nullptr);
#endif

//�����������
template<typename Type>
inline void writef(Type x);

//�ɳ־û�Ȩֵ�߶���

struct node {
    ll ls, rs; 
    ll cnt; //���ֵ�Ĵ���

    node(){
        ls = 0;
        rs = 0;
        cnt = 0;
        return;
    }
};

std::vector<ll> graph[MAXN];
uint64_t root[MAXN];
ll deep[MAXN], father[MAXN], heavy_son[MAXN], chain_top[MAXN], node_num[MAXN], id[MAXN];
node tree[MAXN];
ll n, q, tree_root, tree_cnt = 0, cnt = 1;

namespace Tree {
	//��ʼ��������Ҫ�Ľڵ�id���
    ll id_cnt = 1;
    
	//��ʼ����
    inline void init();

	//��ʼ��������ȣ����ڵ㣬�ڵ��������ض���
	inline void _init(ll _u, ll _father, ll _deep);
	
	//��ʼ����������
    inline void _init_have_chain(ll _u, ll _father, ll _top, ll &_cnt);

    //����ֵΪһ��pair��firstΪ;����������� secondΪȨֵ����_max_value������
	inline std::pair< uint64_t, uint64_t> query(ll _u, ll _v, ll _max_value);
}

namespace Persistent_data_structure {
    inline ll update(ll _pre, ll _lp, ll _rp, ll _Index);
    inline ll query(ll root_left, ll root_right, ll _lp, ll _rp, ll _max_value);
}

inline void Tree::init() {
    memset(heavy_son, -1, sizeof(heavy_son));
	Tree::_init(tree_root, -1, 0);
	Tree::_init_have_chain(tree_root, tree_root, tree_root, id_cnt);
	return;
}

inline void Tree::_init(ll _u, ll _father, ll _deep) {
    deep[_u] = _deep;
	father[_u] = _father;
	node_num[_u] = 1;
	for (size_t i = 0; i < graph[_u].size(); i++) {
		if (graph[_u][i] == _father) {
			continue;
		}
		ll v = graph[_u][i];
		_init(v, _u, _deep + 1);
		node_num[_u] += node_num[v];
		if (heavy_son[_u] == -1 || node_num[heavy_son[_u]] < node_num[v]) {
			heavy_son[_u] = v;
		}
	}
	return;
}

inline void Tree::_init_have_chain(ll _u, ll _father, ll top, ll &_cnt) {
	id[_u] = _cnt++;
	chain_top[_u] = top;
	if (heavy_son[_u] == -1) {
		return;
	}
	Tree::_init_have_chain(heavy_son[_u], _u, top, _cnt);
	for (size_t i = 0; i < graph[_u].size(); i++) {
		if (graph[_u][i] != _father && graph[_u][i] != heavy_son[_u]) {
			Tree::_init_have_chain(graph[_u][i], _u, graph[_u][i], _cnt);
		}
	}
	return;
}

std::pair< uint64_t, uint64_t> Tree::query(ll _u, ll _v, ll _max_value) {
    ll ret = 0, path = 0;;
	while (chain_top[_u] != chain_top[_v]) {
		if (deep[chain_top[_u]] < deep[chain_top[_v]]) {
			std::swap(_u, _v);
		}
		ret += Persistent_data_structure::query(root[id[chain_top[_u]]], root[id[_u]], 1, MAXN, _max_value);
        path += deep[_u] - deep[chain_top[_u]] + 1;
		_u = father[chain_top[_u]];
	}
	if (deep[_u] > deep[_v]) {
		std::swap(_u, _v);
	}
	ret += Persistent_data_structure::query(root[id[_u]], root[id[_v]], 1, MAXN, _max_value);
    path += deep[_v] - deep[chain_top[_u]] + 1;
    return { path, ret };
}

inline ll Persistent_data_structure::update(ll _pre, ll _lp, ll _rp, ll _Index) {
    ll p = ++tree_cnt;
    tree[p] = tree[_pre];
    tree[p].cnt++;
    if (_lp != _rp) {
        ll mid = (_lp + _rp) >> 1;
        if (_Index <= mid) {
            tree[p].ls = update(tree[_pre].ls, _lp, mid, _Index);
        }
        else {
            tree[p].rs = update(tree[_pre].rs, mid + 1, -_rp, _Index);
        }
    }
    return p;
}

inline ll Persistent_data_structure::query(ll root_left, ll root_right, ll _lp, ll _rp, ll _max_value) {
	//��ǰ�ڵ�����ʾ����Сֵ���ڵ���_max_value
    if (_lp > _max_value) {
		return tree[root_right].cnt - tree[root_left].cnt;
    }

    ll mid = (_lp + _rp) >> 1;
    //���ڽ������������ ��ô���_max_value����λ����������ڻ������������Сֵ��С
    //����������Сֵ���Դ���_max_value
    ll ret = query(tree[root_left].ls, tree[root_right].ls, _lp, mid, _max_value); 
	
    if (mid >= _max_value) {
        //�����������ֵ����_max_value
		//����������
        ret += query(tree[root_left].rs, tree[root_right].rs, mid + 1, _rp, _max_value);
    }
    return ret;
}

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    //TODO
    readf(&n);

    for (size_t i = 0; i < n; i++) {
        ll u = readf<ll>();
        if (u) {
			graph[i].push_back(--u);
            graph[u].push_back(i);
        }
        else {
            tree_root = i;
        }
    }
    Tree::init();

    readf(&q);
    for (size_t i = 0; i < n; i++) {
        switch (readf<short>()) {
        //����
        case 1: {
            ll u, v, max_value;
            std::pair< uint64_t, uint64_t> ans;
            readf(&u), readf(&v), readf(&max_value);
            ans = Tree::query(--u, --v, max_value);
            printf("%lld %lld\n", ans.first, ans.second);
        }
            break;
        //���
        case 2:
            ll t = readf<ll>();
			root[t] = Persistent_data_structure::update(root[t], 1, MAXN, i);
            break;
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
 *      |  |  ϣ���˴�����bug|  |  |     |         |      |
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