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

#define READ           false
#define MAX_INF        1e18
#define MAX_NUM_SIZE   35
#define MAXN           (int64_t)(3e4+1)
#define BINARY_CNT_MAX 11
#define BINARY_SIZE    3

typedef long long int ll;
typedef unsigned long long int unill;

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
    ll u, v, w;
    Edge(ll _u, ll _v, ll _w) {
        u = _u;
        v = _v;
        w = _w;
        return;
    }
    Edge() {
        u = 0;
        v = 0;
        return;
    }
};

class segment_tree {
public:
    struct tree_node {
        ll cnt[2];

        tree_node() {
            cnt[0] = 0;
            cnt[1] = 0;
            return;
        }

        inline void operator +=(const tree_node& other) {
            this->cnt[0] += other.cnt[0];
            this->cnt[1] += other.cnt[1];
            return;
        }
    };

    void update(ll _Pos, ll _Index, ll _RangeL, ll _RangeR);

    tree_node query(ll _Index, ll _RangeL, ll _RangeR, ll _Left, ll _Right);

    void build_tree(ll _Val_Pos, ll _Index, ll _RangeL, ll _RangeR);



private:

    template<typename Type>
    inline Type ls(Type _X);

    template<typename Type>
    inline Type rs(Type _X);

    inline void push_up(ll _Index);

    tree_node tree[MAXN << 2];
};

Edge edges[MAXN];
std::vector<ll> graph[MAXN];
ll deep[MAXN], dfn[MAXN], top[MAXN], father[MAXN], node_num[MAXN], heavy_son[MAXN];
segment_tree seg_tree[BINARY_SIZE];
ll weight[MAXN];
ll n, q, dnf_cnt = 0;

void _tree_init(ll _u = 1, ll _father = 0, ll _deep = 1) {
    deep[_u] = _deep;
    father[_u] = _father;
    node_num[_u] = 1;
    for (auto& v : graph[_u]) {
        if (v != _father) {
            _tree_init(v, _u, _deep + 1);
            node_num[_u] += node_num[v];
            if (!heavy_son[_u] || node_num[v] > node_num[heavy_son[_u]]) {
                heavy_son[_u] = v;
            }
        }
    }
    return;
}

void _init_chain(ll _u = 1, ll _father = 0, ll _top = 1) {
    top[_u] = _top;
    dfn[_u] = ++dnf_cnt;
    if (heavy_son[_u]) {
        _init_chain(heavy_son[_u], _u, _top);
    }
    for (auto& v : graph[_u]) {
        if (v != heavy_son[_u] && v != _father) {
            _init_chain(v, _u, v);
        }
    }
    return;
}

inline void tree_init() {
    _tree_init();
    _init_chain();
    return;
}

template<typename Type>
inline Type segment_tree::ls(Type _X) {
    return _X << 1;
}

template<typename Type>
inline Type segment_tree::rs(Type _X) {
    return _X << 1 | 1;
}

inline void segment_tree::push_up(ll _Index) {
    tree[_Index].cnt[0] = tree[ls(_Index)].cnt[0] + tree[rs(_Index)].cnt[0];
    tree[_Index].cnt[1] = tree[ls(_Index)].cnt[1] + tree[rs(_Index)].cnt[1];
    return;
}

void segment_tree::build_tree(ll _Val_Pos, ll _Index, ll _RangeL, ll _RangeR) {
    if (_RangeL == _RangeR) {
        tree[_Index].cnt[0] = ((weight[_RangeL] >> _Val_Pos) & 1) ^ 1;
        tree[_Index].cnt[1] = (weight[_RangeL] >> _Val_Pos) & 1;
        return;
    }

    ll mid = (_RangeL + _RangeR) >> 1;
    build_tree(_Val_Pos, ls(_Index), _RangeL, mid);
    build_tree(_Val_Pos, rs(_Index), mid + 1, _RangeR);
    push_up(_Index);
    return;
}

void segment_tree::update(ll _Pos, ll _Index, ll _RangeL, ll _RangeR) {
    if (_RangeL == _RangeR) {
        tree[_Index].cnt[0] ^= 1;
        tree[_Index].cnt[1] ^= 1;
        return;
    }

    ll mid = (_RangeL + _RangeR) >> 1;
    if (_Pos <= mid) {
        update(_Pos, ls(_Index), _RangeL, mid);
    }
    else {
        update(_Pos, rs(_Index), mid + 1, _RangeR);
    }
    push_up(_Index);
    return;
}

segment_tree::tree_node segment_tree::query(ll _Index, ll _RangeL, ll _RangeR, ll _Left, ll _Right) {
    if (_Left <= _RangeL && _RangeR <= _Right) {
        return tree[_Index];
    }

    ll mid = (_RangeL + _RangeR) >> 1;
    tree_node ret;
    if (_Left <= mid) {
        ret += query(ls(_Index), _RangeL, mid, _Left, _Right);
    }
    if (mid < _Right) {
        ret += query(rs(_Index), mid + 1, _RangeR, _Left, _Right);
    }
    return ret;
}

inline void query(ll _u, ll _v) {
    ll cnt[BINARY_SIZE][2];
    memset(cnt, 0, sizeof(cnt));
	while (top[_u] != top[_v]) {
		if (deep[top[_u]] < deep[top[_v]]) {
			std::swap(_u, _v);
		}
        for (size_t i = 0; i < BINARY_SIZE; i++) {
			segment_tree::tree_node ans = seg_tree[i].query(1, 1, n, dfn[top[_u]], dfn[_u]);
			cnt[i][0] += ans.cnt[0];
			cnt[i][1] += ans.cnt[1];
        }
		_u = father[top[_u]];
	}
    if (deep[_u] < deep[_v]) {
        std::swap(_u, _v);
    }
    for (size_t i = 0; i < BINARY_SIZE; i++) {
        segment_tree::tree_node ans = seg_tree[i].query(1, 1, n, dfn[_v] + 1, dfn[_u]);
        cnt[i][0] += ans.cnt[0];
        cnt[i][1] += ans.cnt[1];
    }
    ll ans = 0;
    for (size_t i = 0; i < BINARY_SIZE; i++) {
		ans += cnt[i][0] * cnt[i][1] * (1 << i);
    }
	writef(ans);
    puts("\n");
	return;
}

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

#ifdef _RUN_TIME
    clock_t start = clock();
#endif // _RUN_TIME

    
    readf(&n), readf(&q);

    for (size_t i = 1; i <= n - 1; i++) {
        ll u = readf<ll>(), v = readf<ll>(), w = readf<ll>();
        graph[u].push_back(v);
        graph[v].push_back(u);
        edges[i] = Edge(u, v, w);
    }

    tree_init();

    for (size_t i = 1; i <= n - 1; i++) {
        ll u = edges[i].u, v = edges[i].v;
        weight[dfn[deep[u] > deep[v] ? u : v]] = edges[i].w;
    }

    for (size_t i = 0; i < 10; i++) {
		seg_tree[i].build_tree(i, 1, 1, n);
    }

    while (q--) {
        ll opt = readf<ll>(), u = readf<ll>(), v = readf<ll>(), w;
        if (opt == 1) {
            query(u, v);
        }
        else {
            w = readf<ll>();
            for (size_t i = 0; i < 10; i++) {
                if ((w >> i) & 1) {
                    seg_tree[i].update(dfn[deep[u] > deep[v] ? dfn[u] : dfn[v]], 1, 1, n);
                }
            }
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