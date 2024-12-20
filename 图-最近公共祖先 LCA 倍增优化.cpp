#define  _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <stdio.h>
#include <algorithm>
#include <ctype.h>
#include <climits>

typedef long long ll;
typedef unsigned long long unill;

//函数前向声明
//快读函数
template< typename T >
inline T readf();

std::vector< std::vector< ll > > edge;
std::vector< std::vector< ll > > father; //father[i,j]为点i跳2的j次方到达的点
std::vector< ll > depth; //深度
ll n, m, s;

//处理父节点数组 和深度数组
inline void dfsDepth(ll v/*当前查看的父节点*/, ll fa/*当前查看的父节点的父节点*/)
{
    for (size_t i = 0; i < edge[v].size(); i++)
    {
        ll child = edge[v][i];
        if (child == fa)
        {
            continue;
        }
        depth[child] = depth[v] + 1; //更新子节点权值为父节点+1
        father[child][0] = v; //记录父节点 2的0次方为1
        dfsDepth(child, v);
    }
    return;
}

inline void init()
{
    for (size_t j = 1; j <= 18; j++)
    {
        for (size_t i = 0; i < n; i++)
        {
            father[i][j] = father[father[i][j - 1]][j - 1];
        }
    }
    return;
}

inline ll LCA(ll u, ll v)
{
    //如果两个是同一个点的话，那就是这个点本身
    if (u == v)
    {
        return u;
    }
    //让u成为深度更大的那个点
    if (depth[u] < depth[v])
    {
        std::swap(u, v);
    }

    for (ll i = 18; i >= 0; i--)
    {
        if (depth[u] - depth[v] >= (1 << i)) //如果目前的差距大于2的i次方，那么要更新u，并计算2的i+1次方
        {
            u = father[u][i]; //往上提
        }
    }

    if (u == v)
    {
        return u;
    }

    for (ll i = 18; i >= 0; i--)
    {
        if (father[u][i] != father[v][i])
        {
            u = father[u][i], v = father[v][i]; //往上提
        }
    }
    return father[u][0];
}

int main()
{
    freopen(".in", "r", stdin);

    //输入n，m，s
    n = readf< ll >(), m = readf < ll >(), s = readf< ll >();

    edge.resize(n);
    for (size_t i = 1; i < n; i++)
    {
        ll from = readf< ll >(), to = readf< ll >();
        edge[--from].push_back(--to);
        edge[to].push_back(from);
    }

    depth.resize(n, 0);
    father.resize(n, std::vector< ll >(20, 0));
    depth[--s] = 1;
    dfsDepth(s, s);

    init();
    //father[s].clear();
    //father[s].resize(20, s);
    while (m--)
    {
        ll u = readf< ll >(), v = readf< ll >();
        printf("%lld\n", LCA(--u, --v) + 1);
    }
    return 0;
}


template< typename T >
inline T readf()
{
#if false
    T sum = 0;
    char ch = getchar();
    while (ch > '9' || ch < '0') ch = getchar();
    while (ch >= '0' && ch <= '9') sum = sum * 10 + ch - 48, ch = getchar();
    return sum;
#else
    T ret = 0, sgn = 0, ch = getchar();
    while (!isdigit(ch))
    {
        sgn |= ch == '-', ch = getchar();
    }
    while (isdigit(ch)) ret = ret * 10 + ch - '0', ch = getchar();
    return sgn ? -ret : ret;
#endif
}