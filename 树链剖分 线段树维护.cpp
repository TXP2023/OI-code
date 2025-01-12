//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
//
//      By txp2024 www.luogu.com.cn  TXP2023 www.github.com
// 
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

//原题 洛谷 P3384
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

//分别是记录第i个节点的深度，父节点，重儿子，所在重链的链头， 以这个点为根的子树的节点数量， 以及这个点的重链dfs序
std::vector< ll > deep, father, heavy_son, chain_top, node_num, id;
std::vector< std::vector< ll > > edge;//树
std::vector< ll > sequence, newSequence;
ll n, m, r, p, num = 0; //树的节点个数，操作个数，根节点的序号， 取模数

inline void init() {
    edge.resize(n);
    id.resize(n);
    id.shrink_to_fit();
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
    sequence.resize(n);
    sequence.shrink_to_fit();
    newSequence.resize(n);
    newSequence.shrink_to_fit();
    return;
}

//这个函数要初始化树的deep， father， heavy_son, node_num数组为有效值
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
    chain_top[_u] = _top; //记录这个点的链头
    newSequence[id[_u]] = sequence[_u];
    if (heavy_son[_u] == -1) /*这个点为叶子节点 即这个点没有重儿子 即没有儿子*/ {
        return;
    }
    tree_init_heavy_chain(heavy_son[_u], _top, _u, _num); //先构建重链
    //遍历剩下的所有轻链
    for (size_t i = 0; i < edge[_u].size(); i++) {
        ll v = edge[_u][i];
        if (v != _father && v != heavy_son[_u]) /*这是一个轻儿子 轻儿子不是重儿子也不是父节点*/ {
            tree_init_heavy_chain(v, v, _u, _num); //遍历到这个轻儿子 由于这个点是轻儿子 故这将新建一个重链 这个重链的链头就是这个轻儿子
        }
    }
    return;
}

//使用线段树维护多个树链组成的区间 使用id来对应区间中的点 对于每个树链id的dfs序的连续的
class segment_tree {
public:
    segment_tree(ll _size);

    //将区间_left ~ _right 的点的值增加_x 
    void updata(ll _left, ll _right, ll _p, ll _lp, ll _rp, ll _x);

    inline void updata_lca_path(ll u, ll v, ll x);

    //将以点_p为根节点的字树的每一个节点增加_x
    inline void updata_tree(ll _p, ll _x);

    ll query(ll _left, ll _right, ll _p, ll _lp, ll _rp);

    inline ll query_lca_path(ll _u, ll _v);

    inline ll query_tree(ll _p);

private:
    void add_tag(ll _p, ll _lp, ll _rp, ll _x);

    void build_tree(ll _p, ll _lp, ll _rp);

    void push_up(ll _p);

    void push_down(ll _p, ll lp, ll rp);

    std::vector< ll > tag_;
    std::vector< ll > tree_;
};

segment_tree::segment_tree(ll _size) {
    tree_.resize((_size << 2) + 1);
    tag_.resize((_size << 2) + 1);

    build_tree(1, 1, n);

    return;
}

void segment_tree::push_up(ll _p) {
    tree_[_p] = tree_[_p * 2] + tree_[_p * 2 + 1];
    tree_[_p] %= p;
    return;
}

void segment_tree::push_down(ll _p, ll _lp, ll _rp) {
    if (tag_[_p]) {
        ll mid = (_lp + _rp) >> 1;
        add_tag(_p * 2, _lp, mid, tag_[_p]);
        add_tag(_p * 2 + 1, mid + 1, _rp, tag_[_p]);
        tag_[_p] = 0;
    }
    return;
}

void segment_tree::add_tag(ll _p, ll _lp, ll _rp, ll _x) {
    tree_[_p] += (_rp - _lp + 1) * _x;
    tree_[_p] %= p;
    tag_[_p] += _x;
    return;
}

void segment_tree::build_tree(ll _p, ll _lp, ll _rp) {
    if (_lp == _rp) {
        tree_[_p] = newSequence[_lp - 1];
        tree_[_p] %= p;
        return;
    }

    ll mid = (_lp + _rp) >> 1;
    build_tree(_p * 2, _lp, mid);
    build_tree(_p * 2 + 1, mid + 1, _rp);
    push_up(_p);

    return;
}

void segment_tree::updata(ll _left, ll _right, ll _p, ll _lp, ll _rp, ll _x) {
    if (_left <= _lp && _right >= _rp) {
        add_tag(_p, _lp, _rp, _x);
        return;
    }

    push_down(_p, _lp, _rp);

    ll mid = (_lp + _rp) >> 1;
    if (_left <= mid) {
        updata(_left, _right, _p * 2, _lp, mid, _x);
    }
    if (_right > mid) {
        updata(_left, _right, _p * 2 + 1, mid + 1, _rp, _x);
    }

    push_up(_p);
    return;
}

//将以点_p为根节点的字树的每一个节点增加_x
inline void segment_tree::updata_tree(ll _p, ll _x) {
    //要将子树转化为连续区间 由于_p为子树的根节点 故区间起始位置为点_p的id  那么结束位置即为故区间起始位置为点_p的id加上以点p为根的子树的节点数量
    updata(id[_p] + 1, id[_p] + node_num[_p], 1, 1, n, _x);
    // 对于此处 updata的第二个实参 由于id是从0开始记录的 而区间是从1开始的 故要+1 但是由于id[_p] + node_num[_p] 多记录了一个节点故要-1 而+1 -1 抵消
    return;
}

inline void segment_tree::updata_lca_path(ll _u, ll _v, ll _x) {
    //进行lca使_u _v位于同一个树链上
    while (chain_top[_u] != chain_top[_v]) {
        //在跳的过程中 存在点u和点v不再一个树链上 故要将点u移动至点u所在树链的链头的父节点，即向上提一个重链
        if (deep[chain_top[_u]] < deep[chain_top[_v]]) {
            std::swap(_u, _v);
        }
        updata(id[chain_top[_u]] + 1, id[_u] + 1, 1, 1, n, _x);
        //注意更新原来点u所在的重链
        _u = father[chain_top[_u]];
    }
    if (deep[_u] > deep[_v]) {
        std::swap(_u, _v);
    }
    updata(id[_u] + 1, id[_v] + 1, 1, 1, n, _x); //此时u和v在同一条重链上 那就直接区间加
    return;
}

ll segment_tree::query(ll _left, ll _right, ll _p, ll _lp, ll _rp) {
    if (_left <= _lp && _right >= _rp) {
        return tree_[_p];
    }

    push_down(_p, _lp, _rp);

    ll mid = (_lp + _rp) >> 1;

    ll sum = 0;
    if (_left <= mid) {
        sum += query(_left, _right, _p * 2, _lp, mid);
    }
    if (_right > mid) {
        sum += query(_left, _right, _p * 2 + 1, mid + 1, _rp);
    }

    return sum % p;
}

inline ll segment_tree::query_lca_path(ll _u, ll _v) {
    ll sum = 0;

    //进行lca使_u _v位于同一个树链上
    while (chain_top[_u] != chain_top[_v]) {
        //在跳的过程中 存在点u和点v不再一个树链上 故要将点u移动至点u所在树链的链头的父节点，即向上提一个重链
        if (deep[chain_top[_u]] < deep[chain_top[_v]]) {
            std::swap(_u, _v);
        }
        sum += query(id[chain_top[_u]] + 1, id[_u] + 1, 1, 1, n);
        //注意更新原来点u所在的重链
        _u = father[chain_top[_u]];
    }
    if (deep[_u] > deep[_v]) {
        std::swap(_u, _v);
    }
    sum += query(id[_u] + 1, id[_v] + 1, 1, 1, n); //此时u和v在同一条重链上 那就直接区间加
    return sum % p;
}

inline ll segment_tree::query_tree(ll _p) {
    return query(id[_p] + 1, id[_p] + node_num[_p], 1, 1, n) % p;
}

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

    readf(&n), readf(&m), readf(&r), readf(&p);
    --r;

    init();

    for (size_t i = 0; i < n; i++) {
        sequence[i] = readf< ll >();
    }

    for (size_t i = 0; i < n - 1; i++) {
        ll u = readf< ll >() - 1, v = readf< ll >() - 1;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }

    tree_init(r, -1, 1);
    tree_init_heavy_chain(r, r, -1, num);

    segment_tree tree(n);

    for (size_t i = 0; i < m; i++) {
        short int operate = readf< int >();
        ll u, v, x;
        switch (operate) {
        case 1:
            u = readf< ll >(), v = readf< ll >(), x = readf< ll >();
            tree.updata_lca_path(u - 1, v - 1, x);
            break;
        case 2:
            u = readf< ll >(), v = readf< ll >();
            printf("%lld\n", tree.query_lca_path(u - 1, v - 1));
            break;
        case 3:
            u = readf< ll >(), x = readf< ll >();
            tree.updata_tree(u - 1, x);
            break;
        case 4:
            u = readf< ll >();
            printf("%lld\n", tree.query_tree(u - 1));
            break;
        }
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
    while (top) putchar(sta[--top] + '0');  // 48 是 '0'
    return;
}

