#define  _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <stdio.h>
#include <algorithm>
#include <ctype.h>
#include <climits>

typedef long long ll;
typedef unsigned long long unill;

//����ǰ������
//�������
template< typename T >
inline T readf();

std::vector< std::vector< ll > > edge;
std::vector< std::vector< ll > > father; //father[i,j]Ϊ��i��2��j�η�����ĵ�
std::vector< ll > depth; //���
std::vector< ll > vis;
ll n, m, ans = 0;

//�������ڵ����� ���������
inline void dfsDepth(ll v/*��ǰ�鿴�ĸ��ڵ�*/, ll fa/*��ǰ�鿴�ĸ��ڵ�ĸ��ڵ�*/)
{
    for (size_t i = 0; i < edge[v].size(); i++)
    {
        ll child = edge[v][i];
        if (child == fa)
        {
            continue;
        }
        depth[child] = depth[v] + 1; //�����ӽڵ�ȨֵΪ���ڵ�+1
        father[child][0] = v; //��¼���ڵ� 2��0�η�Ϊ1
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
    if (u == v)
    {
        return u;
    }
    if (depth[u] < depth[v])
    {
        std::swap(u, v);
    }

    for (ll i = 18; i >= 0; i--)
    {
        if (depth[u] - depth[v] >= (1 << i)) //���Ŀǰ�Ĳ�����2��i�η�����ôҪ����u��������2��i+1�η�
        {
            u = father[u][i]; //������
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
            u = father[u][i], v = father[v][i]; //������
        }
    }
    return father[u][0];
}

inline void findAns(ll u, ll fa)
{
    for (ll i = 0; i < edge[u].size(); i++)
    {
        if (edge[u][i] == fa)
        {
            continue;
        }
        findAns(edge[u][i], u);
        vis[u] += vis[edge[u][i]];
    }
    ans = std::max(vis[u], ans);
    return;
}

int main()
{
    freopen(".in", "r", stdin);

    //����n��m��s
    n = readf< ll >(), m = readf < ll >();

    edge.resize(n);
    for (size_t i = 1; i < n; i++)
    {
        ll from = readf< ll >(), to = readf< ll >();
        edge[--from].push_back(--to);
        edge[to].push_back(from);
    }

    depth.resize(n, 0);
    father.resize(n, std::vector< ll >(20, 0));
    depth[0] = 1;
    dfsDepth(0, 0);

    init();
    vis.resize(n, 0);
    while (m--)
    {
        ll u = readf< ll >(), v = readf< ll >();
        //printf("%lld\n", LCA(--u, --v) + 1);
        ll lca = LCA(--u, --v);
        vis[u]++, vis[v]++, vis[lca]--;
        if (lca != 0)
        {
            vis[father[lca][0]]--;
        }
    }
    
    findAns(0, 0);

    printf("%lld\n", ans);
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