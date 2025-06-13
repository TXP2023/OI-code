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
#include <iostream>
#include <stdint.h>
#include <initializer_list>

#define READ false
#define MAX_INF 1e18
#define MAX_NUM_SIZE 35
#define MAXN         (size_t)(5e5+5)

typedef long long int ll;
typedef long long int* llp;
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

std::vector<ll> graph[MAXN];
ll deep[MAXN], father[MAXN], heavy_son[MAXN], node_num[MAXN], chain_top[MAXN];
ll n, m, s;//n���ڵ�

//dppe[u]Ϊ�ڵ�u����ȣ� father[u]Ϊ�ڵ�u�ĸ��ڵ�, node_num[u]Ϊ�Խڵ�uΪ���ڵ�������Ľڵ������� 
// chain_top[u]Ϊ�ڵ�u��������ͷ�ڵ�

//heavy_son[u]Ϊ�ڵ�u�����ӽڵ㣬����һ���ڵ�����ӽڵ�Ϊ����ڵ�������ӽڵ�
//�У��Ը��ӽڵ�Ϊ�����������ĵĵ�

// �������Ҫ��ʼ������deep�� father�� heavy_son, node_num����Ϊ��Чֵ
inline void tree_init(ll _u, ll _father, ll _deep) {
    deep[_u] = _deep;
    father[_u] = _father;
    node_num[_u] = 1;
    for (size_t i = 0; i < graph[_u].size(); i++) {
        if (graph[_u][i] == _father) {
            continue;
        }
        ll v = graph[_u][i];
        tree_init(v, _u, _deep + 1);
        node_num[_u] += node_num[v];
        if (!heavy_son[_u] || node_num[heavy_son[_u]] < node_num[v]) {
            heavy_son[_u] = v;
        }
    }
    return;
}

inline void tree_init_heavy_chain(ll _u, ll _top, ll _father) {
    chain_top[_u] = _top; //��¼��������ͷ
    //newSequence[id[_u]] = sequence[_u];
    if (!heavy_son[_u]) /*�����ΪҶ�ӽڵ� �������û���ض��� ��û�ж���*/ {
        return;
    }
    tree_init_heavy_chain(heavy_son[_u], _top, _u); //�ȹ�������
    //����ʣ�µ���������
    for (size_t i = 0; i < graph[_u].size(); i++) {
        ll v = graph[_u][i];
        if (v != _father && v != heavy_son[_u]) {
            /*����һ������� ����Ӳ����ض���Ҳ���Ǹ��ڵ�*/
            tree_init_heavy_chain(v, v, _u); 
            //�������������� ���������������� ���⽫�½�һ������ �����������ͷ������������
        }
    }
    return;
}

//��ν���������lca�����ڵ�u��v��lca��������
//1����u��v��һ�������� �ڵ���ȵ͵ľ���
//2����u��v����һ�������� ����ȵ͵���������ֱ�� 1��

inline ll lca(ll _u, ll _v) {
    while (chain_top[_u] != chain_top[_v]) {
        //�����Ĺ����� ���ڵ�u�͵�v����һ�������� ��Ҫ����u�ƶ�����u������������ͷ�ĸ��ڵ㣬��������һ������
        if (deep[chain_top[_u]] < deep[chain_top[_v]]) {
            std::swap(_u, _v);
        }
        //ע�����ԭ����u���ڵ�����
        _u = father[chain_top[_u]];
    }
    
    return (deep[_u] < deep[_v]) ? _u : _v;
}

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

    readf(&n), readf(&m), readf(&s);

    for (size_t i = 0; i < n - 1; i++) {
        ll u, v;
        readf(&u), readf(&v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    std::fill(heavy_son + 1, heavy_son + n + 1, 0);

    tree_init(s, 0, 1);
    tree_init_heavy_chain(s, s, 1);

    for (size_t i = 0; i < m; i++) {
        ll u, v;
        readf(&u), readf(&v);
        printf("%lld\n", lca(u, v));
    }
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
    while (top) putchar(sta[--top] + 48);  // 48 �� '0'
    return;
}