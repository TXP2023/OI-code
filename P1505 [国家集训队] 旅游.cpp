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

#define READ          false
#define MAX_INF       1e18
#define MAX_NUM_SIZE  35
#define ls(x)  x << 1 
#define rs(x)  x << 1 | 1

typedef long long int ll;
typedef unsigned long long int unill;

//快读函数声明
#if READ
template< typename T >
inline T readf();
#else
template< typename Type >
inline Type readf(Type* p = NULL);
#endif

//快速输出函数
template<typename Type>
inline void writef(Type x);

struct edge {
    ll u, v, w;
};

struct tree_node {
    ll max_value, min_value;
    ll sum;
    std::pair< bool/*是否存在tag*/, short/*tag的值*/> tag = {false, 0};
};

std::vector< ll > deep, father, heavy_son, chain_top, node_num, id;
std::vector< std::vector< ll > > graph;
std::vector< tree_node > tree;
std::vector< edge > edges;
std::vector< ll > edge_id;
std::vector< ll > array;
ll n, m, cnt = 0;


//这个函数要初始化树的deep， father， heavy_son, node_num数组为有效值
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
        if (heavy_son[_u] == -1 || node_num[heavy_son[_u]] < node_num[v]) {
            heavy_son[_u] = v;
        }
    }
    return;
}

inline void tree_init_heavy_chain(ll _u, ll _top, ll _father, ll& _cnt) {
    id[_u] = _cnt++;
    chain_top[_u] = _top; //记录这个点的链头
    //newSequence[id[_u]] = sequence[_u];
    if (heavy_son[_u] == -1) /*这个点为叶子节点 即这个点没有重儿子 即没有儿子*/ {
        return;
    }
    tree_init_heavy_chain(heavy_son[_u], _top, _u, _cnt); //先构建重链
    //遍历剩下的所有轻链
    for (size_t i = 0; i < graph[_u].size(); i++) {
        ll v = graph[_u][i];
        if (v != _father && v != heavy_son[_u]) /*这是一个轻儿子 轻儿子不是重儿子也不是父节点*/ {
            tree_init_heavy_chain(v, v, _u, _cnt); //遍历到这个轻儿子 由于这个点是轻儿子 故这将新建一个重链 这个重链的链头就是这个轻儿子
        }
    }
    return;
}

inline void push_up(ll _P, ll _Lp, ll _Rp) {
    ll mid = (_Lp + _Rp) >> 1;
    //不存在区间[1~1]在右子节点的情况
    tree[_P].sum = tree[rs(_P)].sum;
    tree[_P].max_value = tree[rs(_P)].max_value;
    tree[_P].min_value = tree[rs(_P)].min_value;
    
    if (_Lp != mid || (_Lp == mid && mid != 1)) {
        tree[_P].sum += tree[ls(_P)].sum;
        tree[_P].max_value = std::max(tree[ls(_P)].max_value, tree[_P].max_value);
        tree[_P].min_value = std::max(tree[ls(_P)].min_value, tree[_P].min_value);
    }
    return; 
}

inline void push_down(ll _P) {
    if (tree[_P].tag.first && tree[_P].tag.second) {
        tree[ls(_P)].tag.second = 1;
        tree[rs(_P)].tag.second = 1;
        tree[ls(_P)].sum *= -1;
        tree[rs(_P)].sum *= -1;
        std::swap(tree[ls(_P)].max_value, tree[ls(_P)].min_value);
        tree[ls(_P)].max_value *= -1;
        tree[ls(_P)].min_value *= -1;
        std::swap(tree[rs(_P)].max_value, tree[rs(_P)].min_value);
        tree[rs(_P)].max_value *= -1;
        tree[rs(_P)].min_value *= -1;
    }
    return;
}

void build_tree(ll _P, ll _Lp, ll _Rp) {
    if (_Lp == _Rp) {
        tree[_P].max_value = array[_Lp - 1];
        tree[_P].min_value = array[_Lp - 1];
        tree[_P].sum = array[_Lp - 1];
        return;
    }

    ll mid = (_Lp + _Rp) >> 1;
    build_tree(ls(_P), _Lp, mid);
    build_tree(rs(_P), mid + 1, _Rp);
    push_up(_P, _Lp, _Rp);
    return;
}


//将第_Index个点的权值更改为_Value
void point_updata(ll _Index, ll _Value, ll _P, ll _Lp, ll _Rp) {
    if (_Lp == _Rp) {
        tree[_P].max_value = _Value;
        tree[_P].min_value = _Value;
        tree[_P].sum = _Value;
        return;
    }

    push_down(_P);
    ll mid = (_Lp + _Rp) >> 1;
    if (_Index <= mid) {
        point_updata(_Index, _Value, ls(_P), _Lp, mid);
    }
    else {
        point_updata(_Index, _Value, rs(_P), mid + 1, _Rp);
    }
    return;
}

void seg_updata_opposite(ll _Left, ll _Right, ll _P, ll _Lp, ll _Rp) {
    if (_Left <= _Lp && _Right >= _Rp) {
        tree[_P].tag.second ^= 1;
        tree[_P].tag.first = true;
        std::swap(tree[_P].max_value, tree[_P].min_value);
        tree[_P].max_value *= -1;
        tree[_P].min_value *= -1;
        tree[_P].max_value *= -1;
        return;
    }

    push_down(_P);
    ll mid = (_Lp + _Rp) >> 1;
    if (_Left <= mid) {
        seg_updata_opposite(_Left, _Right, ls(_P), _Lp, mid);
    }
    if (_Right > mid) {
        seg_updata_opposite(_Left, _Right, rs(_P), mid + 1, _Rp);
    }
    push_up(_P, _Lp, _Rp);
    return;
}

ll seg_query_sum(ll _Left, ll _Right, ll _P, ll _Lp, ll _Rp) {
    if (_Left <= _Lp && _Right >= _Rp) {
        return tree[_P].sum;
    }


    push_down(_P);
    ll mid = (_Lp + _Rp) >> 1, sum = 0;
    if (_Left <= mid) {
        if (!(_Left == mid && mid == 1)) {
            sum += seg_query_sum(_Left, _Right, ls(_P), _Lp, mid);
        }
    }
    if (_Right > mid) {
        sum += seg_query_sum(_Left, _Right, rs(_P), mid + 1, _Rp);
    }
    return sum;
}

ll seg_query_max(ll _Left, ll _Right, ll _P, ll _Lp, ll _Rp) {
    if (_Left <= _Lp && _Right >= _Rp) {
        return tree[_P].sum;
    }


    push_down(_P);
    ll mid = (_Lp + _Rp) >> 1, max = 0;
    if (_Left <= mid) {
        if (!(_Left == mid && mid == 1)) {
            max = std::max(seg_query_sum(_Left, _Right, ls(_P), _Lp, mid), max);
        }
    }
    if (_Right > mid) {
        max = std::max(seg_query_sum(_Left, _Right, rs(_P), mid + 1, _Rp), max);
    }
    return max;
}

ll seg_query_min(ll _Left, ll _Right, ll _P, ll _Lp, ll _Rp) {
    if (_Left <= _Lp && _Right >= _Rp) {
        return tree[_P].sum;
    }


    push_down(_P);
    ll mid = (_Lp + _Rp) >> 1, min = 0;
    if (_Left <= mid) {
        if (!(_Left == mid && mid == 1)) {
            min = std::min(seg_query_min(_Left, _Right, ls(_P), _Lp, mid), min);
        }
    }
    if (_Right > mid) {
        min = std::min(seg_query_min(_Left, _Right, rs(_P), mid + 1, _Rp), min);
    }
    return min;
}

inline void updata(ll _u, ll _v) {
    while (chain_top[_u] != chain_top[_v]) {
        //在跳的过程中 存在点u和点v不再一个树链上 故要将点u移动至点u所在树链的链头的父节点，即向上提一个重链
        if (deep[chain_top[_u]] < deep[chain_top[_v]]) {
            std::swap(_u, _v);
        }
        seg_updata_opposite(id[chain_top[_u]] + 1, id[_u] + 1, 1, 1, n);
        //注意更新原来点u所在的重链
        _u = father[chain_top[_u]];
    }
    if (deep[_u] > deep[_v]) {
        std::swap(_u, _v);
    }
    seg_updata_opposite(id[_u] + 1, id[_v] + 1, 1, 1, n); //此时u和v在同一条重链上 那就直接区间加
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
    readf(&n);

    for (size_t i = 0; i < n - 1; i++) {
        edges[i] = edge{ readf<ll>() - 1, readf<ll>() - 1 , readf<ll>() };
        graph[edges[i].u].push_back(edges[i].v);
        graph[edges[i].v].push_back(edges[i].u);
    }

    tree_init(0, -1, 1);
    tree_init_heavy_chain(0, 0, -1, cnt);

    array[0] = 0;
    for (size_t i = 0; i < n - 1; i++) {
        ll u = edges[i].u, v = edges[i].v, w = edges[i].w;
        
        if (father[u] == v) {;
            array[id[u]] = w;
            edge_id[i] = id[u];
        }
        else {
            array[id[v]] = w;
            edge_id[i] = id[v];
        }
    }

    tree.resize((n << 2) + 1);
    build_tree(1, 1, n);

    readf(&m);
    for (size_t i = 0; i < m; i++) {
        char ch[5];
        scanf("%s", &ch);
        switch (ch[0]) {
        case 'C':

            break;
        case 'N':
            break;
        case 'S':
            break;
        case 'M':
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
 *      |  |  希望此代码无bug|  |  |     |         |      |
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