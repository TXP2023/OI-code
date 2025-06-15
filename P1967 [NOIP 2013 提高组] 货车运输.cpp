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
#define MAXN          (size_t)(1e4+5)
#define MAXM          (size_t)(5e4+5)
#define MAX_LOG       15

typedef long long int ll;
typedef unsigned long long int ull;

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

struct Edge {
    size_t u, v, next;
    ll w;

    Edge() {
        u = 0;
		v = 0;
        next = 0;
		w = 0;
        return;
    }

    Edge(size_t u, size_t v, ll w) {
		this->u = u;
        this->v = v;
        this->w = w;
        this->next = 0;
        return;
	}
};

template<size_t __MAX_VALUE>
class Log2 {
public:
    Log2();

    int operator ()(const size_t& val) {
        return log_[val];
    }

private:
    int log_[__MAX_VALUE + 1];
};

template<size_t __MAX_VALUE>
Log2<__MAX_VALUE>::Log2() {
    log_[1] = 0;
    log_[1] = 0;
    log_[2] = 1;
    for (size_t i = 3; i <= __MAX_VALUE; i++) {
        log_[i] = log_[i / 2] + 1;
    }
    return;
}

Edge graph[MAXM], edges[MAXM], tree[MAXM];
ll head[MAXN], tree_head[MAXN], set[MAXN], weight[MAXN];
ll deep[MAXN], father[MAXN], heavy_son[MAXN], top[MAXN], node_num[MAXN], id[MAXN];
ll stTable[MAXN][MAX_LOG];
size_t graph_cnt = 0, tree_cnt = 0, cnt = 0;
Log2<MAXN> get_log2;
ll n, m, q;

//初始化ST表
inline void init_stTable() {
    for (size_t i = 1; i <= MAX_LOG; i++) {
        for (size_t j = 1; j + (1 << i) - 1 <= n; j++) {
            stTable[j][i] = std::min(
                stTable[j][i - 1],
                stTable[j + (1 << (i - 1))][i - 1]
            );
        }
    }
    return;
}

inline ll stTableQuery(size_t range_begin, size_t range_end) {
    size_t Log = get_log2(range_end - range_begin + 1);
    return std::min(stTable[range_begin][Log], stTable[range_end - (1 << Log) + 1][Log]);
}


void add_edge(size_t u, size_t v, ll w, size_t &cnt, Edge* _Edges, ll* _Head) {
	cnt++;
    _Edges[cnt].u = u;
    _Edges[cnt].v = v;
    _Edges[cnt].w = w;
    _Edges[cnt].next = _Head[u];
	_Head[u] = cnt;
    return;
}

inline void set_init() {
    for (size_t i = 1; i <= n; i++) {
        set[i] = i;
    }
	return;
}

inline size_t find_set(size_t x) {
    if (set[x] == x) {
        return set[x];
    }
    return set[x] = find_set(set[x]);
}

inline void build_max_tree() {
    //kruskal
    ll edge_num = 1;
    std::sort(edges + 1, edges + 1 + m, [](const Edge& a, const Edge& b) {
        return a.w > b.w;
        }
    );
	//一个树有 n - 1 条边
    for (size_t i = 1; i <= n - 1; i++) {
        while (find_set(edges[edge_num].u) == find_set(edges[edge_num].v) && edge_num <= m) {
            ++edge_num;
        }
        if (edge_num > m) {
            break;
        }
        set[find_set(edges[edge_num].u)] = set[find_set(edges[edge_num].v)];
        add_edge(edges[edge_num].u, edges[edge_num].v, edges[edge_num].w, tree_cnt, tree, tree_head);
        add_edge(edges[edge_num].v, edges[edge_num].u, edges[edge_num].w, tree_cnt, tree, tree_head);
        ++edge_num;
    }
    return;
}

// 这个函数要初始化树的deep， father， heavy_son, node_num数组为有效值
inline void tree_init(ll _u, ll _father, ll _deep) {
    deep[_u] = _deep;
    father[_u] = _father;
    node_num[_u] = 1;
    for (size_t i = tree_head[_u]; i; i = tree[i].next) {
        if (tree[i].v == _father) {
            continue;
        }
        ll v = tree[i].v;
        tree_init(v, _u, _deep + 1);
        node_num[_u] += node_num[v];
        if (!heavy_son[_u] || node_num[heavy_son[_u]] < node_num[v]) {
            heavy_son[_u] = v;
        }
    }
    return;
}

inline void tree_init_heavy_chain(ll _u, ll _top, ll _father, size_t &cnt) {
    id[_u] = ++cnt;
    top[_u] = _top; //记录这个点的链头
    //newSequence[id[_u]] = sequence[_u];
    if (!heavy_son[_u]) /*这个点为叶子节点 即这个点没有重儿子 即没有儿子*/ {
        return;
    }
    tree_init_heavy_chain(heavy_son[_u], _top, _u, cnt); //先构建重链
    //遍历剩下的所有轻链
    for (size_t i = tree_head[_u]; i; i = tree[i].next) {
        ll v = tree[i].v;
        if (v != _father && v != heavy_son[_u]) {
            /*这是一个轻儿子 轻儿子不是重儿子也不是父节点*/
            tree_init_heavy_chain(v, v, _u, cnt);
            //遍历到这个轻儿子 由于这个点是轻儿子 故这将新建一个重链 这个重链的链头就是这个轻儿子
        }
    }
    return;
}

inline ll st_query(ll _First, ll _Last) {
    size_t Log = get_log2(_Last - _First + 1);
    return std::min(stTable[_First][Log], stTable[_Last - (1 << Log) + 1][Log]);
}

//初始化ST表
inline void init() {
    for (size_t i = 1; i <= MAX_LOG; i++) {
        for (size_t j = 1; j + (1 << i) - 1 <= cnt; j++) {
            stTable[j][i] = std::min(
                stTable[j][i - 1],
                stTable[j + (1 << (i - 1))][i - 1]
            );
        }
    }
    return;
}


//如何借助树剖求lca，对于点u，v的lca分类讨论
//1）点u，v在一条重链上 节点深度低的就是
//2）点u，v不在一条重链上 让深度低的往上跳，直到 1）

inline ll query(ll _u, ll _v) {
    ll res = INT_MAX;
    while (top[_u] != top[_v]) {
        //在跳的过程中 存在点u和点v不再一个树链上 故要将点u移动至点u所在树链的链头的父节点，即向上提一个重链
        if (deep[top[_u]] < deep[top[_v]]) {
            std::swap(_u, _v);
        }
        res = std::min(res , st_query(id[top[_u]], id[_u]));
        //注意更新原来点u所在的重链
        _u = father[top[_u]];
    }
    if (deep[_u] < deep[_v]) {
        std::swap(_u, _v);
    }
    if (_u == _v) {
        return res;
    }
    res = std::min(res, st_query(id[_v] + 1, id[_u]));
    return res;
}

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    readf(&n), readf(&m);

    for (size_t i = 1; i <= m; i++) {
        ll u, v, w;
		readf(&u), readf(&v), readf(&w);    
        add_edge(u, v, w, graph_cnt, edges, head);
		add_edge(v, u, w, graph_cnt, edges, head); // 无向图
		edges[i] = Edge(u, v, w);
    }

    set_init();
    build_max_tree();

    for (size_t i = 1; i <= n; i++) {
        if (!id[i]) {
            tree_init(i, 0, 1);
            tree_init_heavy_chain(i, i, 0, cnt);
        }
    }

    //tree_init(1, 0, 1);
    //tree_init_heavy_chain(1, 1, 0, cnt);

    for (size_t i = 1; i <= tree_cnt; i+=2) {
        ll u = tree[i].u, v = tree[i].v;
        if (deep[u] < deep[v]) {
            std::swap(u, v);
        }
        stTable[id[u]][0] = tree[i].w;
    }
    for (size_t i = 1; i <= cnt; i++) {
        if (stTable[i][0] == 0) {
            stTable[i][0] = INT16_MAX;
        }
    }
    init();
    
    readf(&q);

    while (q--) {
        ll u, v;
        readf(&u), readf(&v);
        if (set[find_set(u)] != set[find_set(v)]) {
            puts("-1");
            continue;
        }
        printf("%lld\n", query(u, v));
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