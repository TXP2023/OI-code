//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
//
//      By txp2024 www.luogu.com.cn  TXP2023 www.github.com
// 
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
#pragma once
#include <vector>
#include <set>
#include <map>
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
#define ERROR_INF -1

#define INSTERT       1    //向 M 中插入一个数
#define REMOVE        2    //从 M 中删除一个数x（若有多个相同的数，应只删除一个）
#define Q_POSITION    3    //查询 M中有多少个数比 X小，并且将得到的答案加一。
#define Q_RANK        4    // 查询如果将 M 从小到大排列后，排名位于第 X 位的数
#define Q_PRODROMAL   5    //查询M中X的前驱
#define Q_SUBSEQUENT  6    // 查询M中X 的后继

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

struct operate {
    ll x;
    short opt;
};

class Segment_tree {
public:
    Segment_tree(ll _size);

    void insert(ll _x, ll _p = 1, ll _lp = 1, ll _rp = -1);

    void remove(ll _x, ll _p = 1, ll _lp = 1, ll _rp = -1);

    ll query_position(ll _x, ll _cnt = 0, ll _p = 1, ll _lp = 1, ll _rp = -1);

    ll query_rank(ll _x, ll _p = 1, ll _lp = 1, ll _rp = -1);

    ll query_prodromal(ll _x, ll _p = 1, ll _lp = 1, ll _rp = -1);

    //
    ll query_subsequent(ll _x, ll _p = 1, ll _lp = 1, ll _rp = -1);

private:
    static inline ll ls(ll x);

    static inline ll rs(ll x);

    inline void push_up(ll _p);

    std::vector< ll > tree;

    ll value_cnt = 1, size;
};

std::vector< operate > operates;
std::vector< ll > dis_value;
ll n, cnt = 0, num;

inline void Discretization() /*离散化*/ {
    std::sort(dis_value.begin(), dis_value.end());
    dis_value.erase(std::unique(dis_value.begin(), dis_value.end()), dis_value.end());
    for (size_t i = 0; i < n; i++) {
        if (operates[i].opt != 4) {
            operates[i].x = std::lower_bound(dis_value.begin(), dis_value.end(), operates[i].x) - dis_value.begin() + 1;
        }
    }
    num = dis_value.size();
    return;
}

Segment_tree::Segment_tree(ll _size) {
    tree.resize((_size << 2) + 1, 0);
    size = _size;
}

inline void Segment_tree::push_up(ll _p) {
    tree[_p] = tree[ls(_p)] + tree[rs(_p)];
    return;
}

inline ll Segment_tree::ls(ll x) {
    return x << 1;
}

inline ll Segment_tree::rs(ll x) {
    return (x << 1) + 1;
}

inline void Segment_tree::insert(ll _x, ll _p, ll _lp, ll _rp) {
    _rp = (_rp == -1) ? size : _rp;

    if (_lp == _x && _lp == _rp) {
        ++tree[_p];
        return;
    }

    ll mid = (_lp + _rp) >> 1;
    if (_x <= mid) {
        insert(_x, ls(_p), _lp, mid);
    }
    else {
        insert(_x, rs(_p), mid + 1, _rp);
    }

    push_up(_p);
    return;
}

inline void Segment_tree::remove(ll _x, ll _p, ll _lp, ll _rp) {
    _rp = (_rp == -1) ? size : _rp;

    if (_lp == _x && _lp == _rp) {
        --tree[_p];
        return;
    }

    ll mid = (_lp + _rp) >> 1;
    if (_x <= mid) {
        remove(_x, ls(_p), _lp, mid);
    }
    else {
        remove(_x, rs(_p), mid + 1, _rp);
    }

    push_up(_p);
    return;
}

ll Segment_tree::query_position(ll _x, ll _cnt, ll _p, ll _lp, ll _rp) {
    _rp = (_rp == -1) ? num : _rp;
    if (_lp == _rp && _lp == _x) {
        return _cnt + 1;
    }

    ll mid = (_lp + _rp) >> 1;
    if (_x <= mid) {
        return query_position(_x, _cnt, ls(_p), _lp, mid);
    }
    else {
        return query_position(_x, _cnt + tree[ls(_p)], rs(_p), mid + 1, _rp);
    }
}

ll Segment_tree::query_rank(ll _x, ll _p, ll _lp, ll _rp) {
    _rp = (_rp == -1) ? num : _rp;
    if (_lp == _rp) {
        return dis_value[_lp - 1];
    }

    ll mid = (_lp + _rp) >> 1;
    if (tree[ls(_p)] >= _x) {
        return query_rank(_x, ls(_p), _lp, mid);
    }
    else {
        return query_rank(_x - tree[ls(_p)], rs(_p), mid + 1, _rp);
    }
}

ll Segment_tree::query_prodromal(ll _x, ll _p, ll _lp, ll _rp) {
    _rp = (_rp == -1) ? num : _rp;

    if (_lp >= _x) {
        return ERROR_INF;
    }

    if (_lp == _rp) {
        return dis_value[_lp - 1];
    }

    ll pre = ERROR_INF, mid = (_lp + _rp) >> 1;
    if (tree[rs(_p)]) {
        pre = query_prodromal(_x, rs(_p), mid + 1, _rp);
    }
    if (tree[ls(_p)] && pre == ERROR_INF) {
        pre = query_prodromal(_x, ls(_p), _lp, mid);
    }

    return pre;
}

ll Segment_tree::query_subsequent(ll _x, ll _p, ll _lp, ll _rp) /*后继*/ {
    
    _rp = (_rp == -1) ? num : _rp;

    if (_rp <= _x) {
        return ERROR_INF;
    }

    if (_lp == _rp) {
        return dis_value[_lp - 1];
    }

    ll pre = ERROR_INF, mid = (_lp + _rp) >> 1;
    if (tree[ls(_p)] ) {
        pre = query_subsequent(_x, ls(_p), _lp, mid);
    }
    if (tree[rs(_p)] && pre == ERROR_INF) {
        pre = query_subsequent(_x, rs(_p), mid + 1, _rp);
    }
    
    return pre;
}

int main() {
#ifdef _FREOPEN
    freopen("input.txt", "r", stdin);
#endif // _FREOPEN

    readf(&n);

    operates.resize(n);
    dis_value.resize(n);
    for (operate &i : operates) {
        readf(&i.opt), readf(&i.x);
        if (i.opt != 4) {
            //dis_value.push_back(i.x);
            dis_value[cnt++] = i.x;
        }
    }

    dis_value.erase(dis_value.begin() + cnt, dis_value.end());
    Discretization();

    Segment_tree tree(num);
    for (const operate ope : operates) {
        switch (ope.opt) {
        case INSTERT:
            tree.insert(ope.x);
            break;

        case REMOVE:
            tree.remove(ope.x);
            break;

        case Q_POSITION:
            printf("%lld\n", tree.query_position(ope.x));
            break;

        case Q_RANK:
            printf("%lld\n", tree.query_rank(ope.x));
            break;

        case Q_PRODROMAL:
            printf("%lld\n", tree.query_prodromal(ope.x));
            break;

        case Q_SUBSEQUENT:
            printf("%lld\n", tree.query_subsequent(ope.x));
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