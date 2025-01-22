//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
//
//      By txp2024 www.luogu.com.cn  TXP2023 www.github.com
// 
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
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

#define READ false
#define MAX_INF 1e18
#define MAX_NUM_SIZE 35

typedef long long int ll;
typedef unsigned long long int unill;

//�����������
#if READ
template< typename T >
inline T readf();
#else
template< typename Type >
inline Type readf(Type* p = NULL);
#endif

//�����������
template<typename Type>
inline void writef(Type x);

std::vector< ll > deep, father, heavy_son, chain_top, node_num, id, map;
std::vector < std::vector< ll > > edge;
std::vector< ll > tree;
ll n, q, num = 0;

inline void init() {
    id.resize(n);
    id.shrink_to_fit();
    map.resize(n);
    deep.resize(n);
    deep.shrink_to_fit();
    father.resize(n);
    father.shrink_to_fit();
    node_num.resize(n);
    node_num.shrink_to_fit();
    heavy_son.resize(n, -1);
    heavy_son.shrink_to_fit();
    chain_top.resize(n);
    chain_top.shrink_to_fit();
    return;
}

//�������Ҫ��ʼ������deep�� father�� heavy_son, node_num����Ϊ��Чֵ
inline void tree_init(ll _u, ll _father, ll _deep) {
    deep[_u] = _deep;
    father[_u] = _father;
    node_num[_u] = 1;
    for (size_t i = 0; i < edge[_u].size(); i++) {
        if (edge[_u][i] == _father) {
            continue;
        }
        ll v = edge[_u][i];
        tree_init(v, _u, _deep + 1);
        node_num[_u] += node_num[v];
        if (heavy_son[_u] == -1 || node_num[heavy_son[_u]] < node_num[v]) {
            heavy_son[_u] = v;
        }
    }
    return;
}

inline void tree_init_heavy_chain(ll _u, ll _top, ll _father, ll& _num) {
    id[_u] = _num++;
    map[_num - 1] = _u;
    chain_top[_u] = _top; //��¼��������ͷ
    if (heavy_son[_u] == -1) /*�����ΪҶ�ӽڵ� �������û���ض��� ��û�ж���*/ {
        return;
    }
    tree_init_heavy_chain(heavy_son[_u], _top, _u, _num); //�ȹ�������
    //����ʣ�µ���������
    for (size_t i = 0; i < edge[_u].size(); i++) {
        ll v = edge[_u][i];
        if (v != _father && v != heavy_son[_u]) /*����һ������� ����Ӳ����ض���Ҳ���Ǹ��ڵ�*/ {
            tree_init_heavy_chain(v, v, _u, _num); //�������������� ���������������� ���⽫�½�һ������ �����������ͷ������������
        }
    }
    return;
}

inline void updata(ll _Index, ll _P, ll _Lp, ll _Rp) {
    if (_Lp == _Rp) {
        tree[_P] = 1;
        return;
    }

    ll mid = (_Lp + _Rp) >> 1;
    if (_Index <= mid) {
        updata(_Index, _P * 2, _Lp, mid);
    }
    else {
        updata(_Index, _P * 2 + 1, mid + 1, _Rp);
    }
    tree[_P] = tree[_P * 2] + tree[_P * 2 + 1];
    return;
}

inline ll segment_tree_query(ll _Left, ll _Right, ll _P, ll _Lp, ll _Rp) {
    if (_Left <= _Lp && _Right >= _Rp) {
        return tree[_P];
    }

    ll mid = (_Lp + _Rp) >> 1, sum = 0;
    if (_Left <= mid) {
        sum += segment_tree_query(_Left, _Right, _P * 2, _Lp, mid);
    }
    if (_Right > mid) {
        sum += segment_tree_query(_Left, _Right, _P * 2 + 1, mid + 1, _Rp);
    }
    return sum;
}

inline ll query(ll _Index) {
    ll r = id[_Index] + 1, l = id[chain_top[_Index]] + 1;
    while (true) {
        if (segment_tree_query(l, r, 1, 1, n)) { //˵����������б��
            //��ʱ����2�����
            ll mid = (l + r) >> 1;
            //������������
            if (segment_tree_query(mid + 1, r, 1, 1, n)) {
                l = mid + 1;
            }
            else {
                r = mid;
            }
            if (l == r) {
                return l - 1;
            }
        }
        else { //�������û�б��
            r = id[father[map[l - 1]]] + 1;
            l = id[chain_top[ father[map[l - 1]]] ] + 1;
        }
    }
    
}


int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    //TODO
    readf(&n), readf(&q);

    edge.resize(n);
    for (size_t i = 0; i < n - 1; i++) {
        ll u = readf<ll>(), v = readf<ll>();
        edge[--u].push_back(--v);
        edge[v].push_back(u);
    }

    init();

    tree_init(0, -1, 1);
    tree_init_heavy_chain(0, 0, -1, num);

    

    tree.resize((n << 2) + 1, 0);
    updata(id[0] + 1, 1, 1, n);
    for (size_t i = 0; i < q; i++) {
        char oper[3];
        ll num;
        scanf("%s", &oper);
        readf(&num);
        if (oper[0] == 'C') {
            updata(id[num - 1] + 1, 1, 1, n);
        }
        else {
            printf("%lld\n", map[query(num - 1)] + 1);
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