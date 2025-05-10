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

#define READ         false
#define MAX_INF      1e18
#define MAX_NUM_SIZE 35
#define MAXN         500005

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

struct Segment_tree_node {
    ll l, r;
    ll sum;
};

ll father[MAXN], deep[MAXN], heavy_son[MAXN], node_num[MAXN], chain_top[MAXN];
std::vector< std::vector< ll > > edge;
std::vector< ll > old_array;
std::vector< ll > dis_array;
ll root[MAXN];
Segment_tree_node segment_tree[MAXN];
ll n, m, last = 0, num, tree_cnt = 0;

template<typename Type>
inline Type lowbit(Type _x) {
    return _x & -_x;
}

inline void init() {
    //deep.resize(n);
    //father.resize(n);
    //heavy_son.resize(n, -1);
    std::fill(heavy_son, heavy_son + n, -1);
    //node_num.resize(n);
    //chain_top.resize(n);
    edge.resize(n);
    //root.resize(n + 1, 0); //root[0]为初始树
    std::fill(root, root + n + 1, 0);
    //array.resize(n);
    old_array.resize(n);
    segment_tree[tree_cnt].l = 0;
    segment_tree[tree_cnt].r = 0;
    segment_tree[tree_cnt].sum = 0;
    tree_cnt++;
    return;
}

inline ll/*返回值是节点p为根节点的子树的节点数量*/ tree_init(ll _p, ll _deep, ll _father) {
    deep[_p] = _deep;
    father[_p] = _father;
    if (edge[_p].size() == 1 && _p != 0) {
        node_num[_p] = 1;
        return 1;
    }
    ll sum = 0;
    ll num = -1;
    for (size_t i = 0; i < edge[_p].size(); i++) {
        if (edge[_p][i] != _father) {
            sum += tree_init(edge[_p][i], _deep + 1, _p);
        }
    }
    heavy_son[_p] = edge[_p].front();
    for (size_t i = 1; i < edge[_p].size(); i++) {
        if (edge[_p][i] != _father && node_num[heavy_son[_p]] < node_num[edge[_p][i]]) {
            heavy_son[_p] = edge[_p][i];
        }
    }

    return node_num[_p] = sum + 1;
}

inline void tree_init_2(ll _p, ll _father) {
    chain_top[_p] = _father;
    if (heavy_son[_p] == -1) {
        return;
    }
    tree_init_2(heavy_son[_p], _father);
    for (size_t i = 0; i < edge[_p].size(); i++) {
        if (edge[_p][i] != father[_p] && heavy_son[_p] != edge[_p][i]) {
            tree_init_2(edge[_p][i], edge[_p][i]);
        }
    }
    return;
}

inline ll lca(ll _u, ll _v) {
    while (chain_top[_u] != chain_top[_v]) {
        if (deep[chain_top[_u]] < deep[chain_top[_v]]) {
            std::swap(_u, _v);
        }
        _u = father[chain_top[_u]];
    }
    return (deep[_u] < deep[_v]) ? _u : _v;
}

inline void discretization() {
    dis_array = old_array;
    std::sort(dis_array.begin(), dis_array.end());
    dis_array.erase(std::unique(dis_array.begin(), dis_array.end()), dis_array.end());
    num = dis_array.size();
    return;
}

inline ll segment_tree_updata(ll _Index, ll _Pre, ll _Lp, ll _Rp) {
    ll _P = tree_cnt++;
    segment_tree[_P] = segment_tree[_Pre];
    ++segment_tree[_P].sum;
    ll mid = (_Lp + _Rp) >> 1;
    if (_Lp != _Rp) {
        if (_Index <= mid) {
            segment_tree[_P].l = segment_tree_updata(_Index, segment_tree[_Pre].l, _Lp, mid);
        }
        else {
            segment_tree[_P].r = segment_tree_updata(_Index, segment_tree[_Pre].r, mid + 1, _Rp);
        }
    }

    return _P;
}

ll query(ll _U, ll _V, ll _Lca, ll _Lca_father, ll _Left, ll _Right, ll _K) {
    if (_Left == _Right) {
        return _Left;
    }
    ll mid = (_Left + _Right) >> 1;
    ll sum = segment_tree[segment_tree[_U].l].sum + segment_tree[segment_tree[_V].l].sum - segment_tree[segment_tree[_Lca].l].sum - segment_tree[segment_tree[_Lca_father].l].sum;
    if (_K <= sum) {
        return query(segment_tree[_U].l, segment_tree[_V].l, segment_tree[_Lca].l, segment_tree[_Lca_father].l, _Left, mid, _K);
    }
    else {
        return query(segment_tree[_U].r, segment_tree[_V].r, segment_tree[_Lca].r, segment_tree[_Lca_father].r, mid + 1, _Right, _K - sum);
    }
}

void dfs_build(ll _u, ll _father) {
    root[_u + 1] = segment_tree_updata(std::lower_bound(dis_array.begin(), dis_array.end(), old_array[_u]) - dis_array.begin() + 1, root[father[_u] + 1], 1, num);
    for (int i = 0; i < edge[_u].size(); i++) {
        if (edge[_u][i] != _father) {
            dfs_build(edge[_u][i], _u);
        }
    }
    return;
}

int main() {

    
    readf(&n), readf(&m);

    init();

    for (size_t i = 0; i < n; i++) {
        readf(&old_array[i]);
    }

    for (size_t i = 0; i < n - 1; i++) {
        ll u = readf<ll>() - 1, v = readf<ll>() - 1;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }

    discretization();
    tree_init(0, 1, -1);
    tree_init_2(0, 0);

    dfs_build(0, -1);

    for (size_t i = 0; i < m; i++) {
        ll u = readf<ll>(), v = readf<ll>(), k = readf<ll>();
        ll Lca = lca(u - 1, v - 1) + 1;
        printf("%lld\n", dis_array[query(root[u], root[v], root[Lca], root[father[Lca - 1] + 1] == -1 ? 0 : root[father[Lca - 1] + 1], 1, num, k) - 1]);
    }
    return 0;
}

#if READ
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