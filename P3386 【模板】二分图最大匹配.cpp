#include <vector>
#include <stdio.h>
#include <algorithm>
#include <ctype.h>
#include <climits>
#include <stdint.h>

typedef long long int ll;
typedef unsigned long long int  ull;
typedef long double lf;

//����ǰ������
//�������
template< typename T >
inline T readf();

std::vector< std::vector< ll > > graph; //graphΪ���ڵ㼯A�ĵ�i������˵�����������ӵ㼯b����Щ��
std::vector< ll > allot; //allot[i]Ϊ�㼯B�ĵ�i���������ĵ㼯A�ĵ�ı��
std::vector< bool > ub; //ub[i]Ϊ�㼯B�ĵ�i���Ƿ��Ѿ����
ll n/*����ͼ�㼯A����*/, m/*����ͼ�㼯B����*/, e/*����*/, ans = 0/*���ƥ����*/;

inline bool dfs(ll v) //���㼯a�ĵ�x��Ե㼯2�ĵ�
{
    for (ll u : graph[v]) {
        if (!ub[u]) {
            ub[u] = true; //���һ��
            if (allot[u] == -1 || dfs(allot[u])) {
                allot[u] = v;
                return true;
            }
        }
    }
    return false;
}

int main() {
    freopen(".in", "r", stdin);

    n = readf< ll >(), m = readf< ll >(), e = readf< ll >();
    /*˵�� �㼯A�ĵ�ı��Ϊ1~n, �㼯B�ĵ�ı��Ϊ1~m*/

    //����
    graph.resize(n);
    for (size_t i = 0; i < e; i++) {
        ll v1/*�㼯a�ĵ�*/, u2/*�㼯b�ĵ�*/;
        v1 = readf< ll >(), u2 = readf< ll >();
        graph[v1 - 1].push_back(u2 - 1);
    }

    allot.resize(m, -1);
    ub.resize(m, false);
    for (size_t i = 0; i < n; i++) {
        std::fill(allot.begin(), allot.end(), -1);
        if (dfs(i)) {
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