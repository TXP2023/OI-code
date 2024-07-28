#include <vector>
#include <stdio.h>
#include <climits>
#include <algorithm>
#include <ctype.h>
#include <numeric>
#include <queue>

typedef long long ll;
typedef size_t unill;

//����ǰ������
//�������
template< typename T >
inline T readf();

//���
class Edge
{
public:
    ll from;//���˽ڵ�
    ll to;
    ll val;//Ȩֵ

//private:
    bool operator <(const Edge& other)const {
        return val < other.val;
    }
};

struct data
{
    ll to;//�ڵ�
    ll val;//Ȩֵ
};

std::vector< std::vector< data > > mst; //��С������
std::vector< bool > vecb;
std::vector< Edge > v_edge; //Kruskal ������
ll n, m, min_length, ans; 

//���鼯����
template< typename T, typename T2 > 
inline T findSet(T x, std::vector< T2 >& _set)
{
    if (_set[x] == x)
    {
        return x;
    }
    else
    {
        return _set[x] = findSet(_set[x], _set);
    }
}

//��³˹������С����������
inline ll Kruskal(ll _n/*�ڵ���*/, std::vector< Edge > _e/*�߼�*/)
{
    mst.resize(_n);

    //�����Ȩ
    //std::sort(_e.begin(), _e.end()); 
    
    //���� ��ʼ�����鼯
    std::vector< ll > set(_e.size());
    std::iota(set.begin(), set.end(), 0);

    ll cnt = 0, lenght = 0;
    for (ll i = 0; i < _n-1;)
    {
        if (findSet(_e.front().from, set) != findSet(_e.front().to, set))
        {
            i++;
            lenght += _e.front().val;
            set[findSet(_e.front().from, set)] = findSet(_e.front().to, set);
            mst[_e.front().from].push_back({ _e.front().to, _e.front().val });
            mst[_e.front().to].push_back({ _e.front().from, _e.front().val });
            _e.erase(_e.begin());
            vecb[cnt] = true;
        }
        else
        {
            _e.erase(_e.begin());
        }
        cnt++;
    }
    return lenght;
}

template< typename T1 >
inline ll minPath(T1 _n, T1 from/*��ʼ��*/, T1 to/*�յ�*/, std::vector< std::vector< data > > _dat/*��ͼ*/)
{
    std::vector< std::pair< ll, ll > > dits(_n, { LLONG_MAX, 0}); //��·�� ����󵥴�·
    std::queue< std::pair< ll, ll >/*��Ȩֵ����ڵ��*/ > que;
    que.push({ 0, from });
    dits[from] = { 0, 0 };
    while (!que.empty())
    {
        std::pair< ll, ll > now = que.front();
        que.pop();
        for (size_t i = 0; i < _dat[now.second].size(); i++)
        {
            if (dits[_dat[now.second][i].to].first > dits[now.second].first + _dat[now.second][i].val)
            {
                dits[_dat[now.second][i].to].first = dits[now.second].first + _dat[now.second][i].val;
                dits[_dat[now.second][i].to].second = std::max(dits[_dat[now.second][i].to].second, _dat[now.second][i].val);
                que.push({ dits[_dat[now.second][i].to].first, _dat[now.second][i].to });
            }
        }
    }
    return dits[to].second;
}

int main(void)
{
    freopen(".in", "r", stdin);
    n = readf< ll >(), m = readf< ll >();
    
    for (ll i = 0; i < m; i++)
    {
        ll from = readf< ll >() - 1, to = readf< ll >() - 1, val = readf< ll >();
        v_edge.push_back({ from,to,val });
    }

    bool f = false;
    vecb.resize(m, false);
    std::sort(v_edge.begin(), v_edge.end());
    min_length = Kruskal(n, v_edge); //��ȷ
    for (ll i = 0; i < vecb.size(); i++)
    {
        if (!vecb[i])
        {
            ll mPath = minPath(n, v_edge[i].from , v_edge[i].to, mst);
            if (mPath < v_edge[i].val)
            {
                if (!f)
                {
                    f = true;
                    ans = min_length - mPath + v_edge[i].val;
                }
                else
                {
                    ans = std::min(ans, min_length - mPath + v_edge[i].val);
                }
            }
        }
    }

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
        sgn |= ch == '-', ch = getchar();
    while (isdigit(ch)) 
        ret = ret * 10 + ch - '0', ch = getchar();
    return sgn ? -ret : ret;
#endif
}