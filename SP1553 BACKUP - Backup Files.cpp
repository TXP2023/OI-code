#include <vector>
#include <stdio.h>
#include <algorithm>
#include <ctype.h>
#include <climits>
#include <iostream>
#include <stdint.h>
#include <queue>

typedef int64_t ll;
typedef uint64_t unill;

//函数前向声明
//快读函数
template< typename T >
inline T readf();

template< typename T >
inline void inputf(T* p);

struct road {
    ll length;
    ll l, r;
    bool vis;
};

struct heap_node {
    ll length;
    ll p;
    bool operator <(const heap_node other) const {
        return length > other.length;
    }
};

std::priority_queue< heap_node > heap;
std::vector< road > roads;
ll n, k, ans;

inline void del(ll _x) {
    if (roads[_x].l != -1) {
        roads[roads[_x].l].vis = true;
        roads[_x].l = roads[roads[_x].l].l;
        if (roads[_x].l != -1) {
            roads[roads[_x].l].r = _x;
        }
    }
    if (roads[_x].r < roads.size()) {
        roads[roads[_x].r].vis = true;
        roads[_x].r = roads[roads[_x].r].r;
        if (roads[_x].r < roads.size()) {
            roads[roads[_x].r].l = _x;
        }
    }
    return;
}

void main_() {
    

    n = readf< ll >(), k = n / 2;

    roads.resize(n + 1);
    std::vector< road >(roads).swap(roads);

    ll* old = new ll(readf< ll >());
    for (ll i = 1; i < n; i++) {
        ll now = readf< ll >();
        roads[i] = { now - *old, i - 1, i + 1, false };
        *old = now;
        heap.push({ roads[i].length, i });
    }
    delete old;
    roads[0].length = roads[n].length = INT_MAX;

    for (size_t i = 0; i < k; i++) {
        while (roads[heap.top().p].vis) {
            heap.pop();
        }
        road now = roads[heap.top().p];
        ans += now.length;
        //roads[heap.top().p].length = roads[now.l].length + roads[now.r].length - now.length;
        roads[heap.top().p].length = 0 - roads[heap.top().p].length;
        if (now.l != -1) {
            roads[heap.top().p].length += roads[now.l].length;
        }
        if (now.r < roads.size()) {
            roads[heap.top().p].length += roads[now.r].length;
        }
        heap.push({ roads[heap.top().p].length, heap.top().p });
        del(heap.top().p);
        heap.pop();
    }

    printf("%lld\n", ans);
    return;
}

int main() {
    freopen("input.txt", "r", stdin);
    int t = readf< ll >();
    while (t--) {
        main_();
        roads.clear();
        while (!heap.empty()) {
            heap.pop();
        }
        ans = 0;
        n = 0;
        k = 0;
    }
    return 0;
}

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