#include <vector>
#include <stdio.h>
#include <algorithm>
#include <ctype.h>
#include <climits>
#include <stdint.h>

typedef long long int ll;
typedef unsigned long long int  ull;
typedef long double lf;

//函数前向声明
//快读函数
template< typename T >
inline T readf();

std::vector< std::vector< ll > > graph; //graph为对于点集A的第i个点来说，它可以链接点集b的那些点
std::vector< ll > allot; //allot[i]为点集B的第i个点分配给的点集A的点的编号
std::vector< ll > ub; //ub[i]为点集B的第i点是否已经配对
ll n/*二分图点集A点数*/, m/*二分图点集B点数*/, e/*边数*/, ans = 0/*最大匹配数*/;

inline bool dfs(ll v, ll tag) //给点集a的点x配对点集2的点
{
    if (ub[v] == tag) {
        return false;
    }
    ub[v] = tag;
    for (ll u : graph[v]) {
        if (allot[u] == -1 || dfs(allot[u], tag)) {
            allot[u] = v;
            return true;
        }
    }
    return false;
}

int main() {
    //freopen(".in", "r", stdin);

    n = readf< ll >(), m = readf< ll >(), e = readf< ll >();
    /*说明 点集A的点的编号为1~n, 点集B的点的编号为1~m*/

    //输入
    graph.resize(n);
    for (size_t i = 0; i < e; i++) {
        ll v1/*点集a的点*/, u2/*点集b的点*/;
        v1 = readf< ll >(), u2 = readf< ll >();
        graph[v1 - 1].push_back(u2 - 1);
    }

    allot.resize(m, -1);
    ub.resize(n, -1);
    for (size_t i = 0; i < n; i++) {
        if (dfs(i, i)) {
            ans++;
        }
    }


    printf("%lld\n", ans);
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