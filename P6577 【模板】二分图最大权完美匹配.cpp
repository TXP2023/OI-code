#include <vector>
#include <queue>
#include <algorithm>
#include <ctype.h>
#include <climits>
#include <stdint.h>
#include <cstdio>

typedef long long int ll;
typedef unsigned long long int  ull;
typedef long double lf;

//����ǰ������
//�������
template< typename T >
inline T readf();

std::vector< bool > ltag, rtag; //ƥ��
std::vector< ll > Lmatch, Rmatch; //ƥ��
std::vector< ll > Ltop, Rtop; //����
std::vector< ll > pre;
std::vector< ll > slack;
std::vector< std::vector< ll > > graph;
ull n, m;

inline void add_Augment(ll u); //��������·��
inline void Kuhn_Munkres(); //KM�㷨
inline void replace(ll u); //ת�ƣ�

inline void Kuhn_Munkres() {
    std::fill(slack.begin(), slack.end(), LLONG_MAX);
    std::fill(pre.begin(), pre.end(), -1);
    std::fill(ltag.begin(), ltag.end(), false);
    std::fill(rtag.begin(), rtag.end(), false);
    for (size_t i = 0/*�����i��ö����ͼ��*/; i < n; i++) {
        add_Augment(i);
    }
    return;
}

inline void add_Augment(ll u) {
    std::queue< ll > que;//��ͼ�����
    que.push(u);

    while (true) {
        while (!que.empty()) {
            ll v = que.front(); que.pop();
            ltag[v] = true;
            for (size_t i = 0/*�����i���Ҳ�ͼ��*/; i < n; i++) {
                if (!rtag[i]/*����Ҳ�ͼ��û�б�ƥ��*/ && Ltop[u] + Rtop[i] - graph[u][i] < slack[i]) {
                    slack[i] = Ltop[u] + Rtop[i] - graph[u][i];
                    pre[i] = v;
                    if (slack[i] == 0)/*�����ǰ�����ڲ�ֵ, �������·*/ {
                        rtag[i] = true;
                        if (Rmatch[i] == -1) {
                            replace(i);
                            return;
                        }
                        else {
                            que.push(Rmatch[i]);
                        }
                    }
                }
            }
        }
        ll Difference = LLONG_MAX/*����С��ֵ*/;
        for (size_t i = 0; i < n; i++) {
            if (!rtag[i]) {
                Difference = std::min(Difference, slack[i]);
            }
        }
    }
}


inline void replace(ll u) {
    ll t;
    while (u) {
        t = Rmatch[pre[u]];
        Rmatch[pre[u]] = u;
        Rmatch[u] = pre[u];
        u = t;
    }
    return;
}


int main() {
    n = readf< ull >(), m = readf< ull >();

    graph.resize(n, std::vector< ll >(m, 0));

    Ltop.resize(n, LLONG_MIN);
    Rtop.resize(n, 0);
    pre.resize(n, 0);
    Lmatch.resize(n, -1);
    Rmatch.resize(n, -1);
    ltag.resize(n, false);
    rtag.resize(n, false);

    for (size_t i = 0; i < m; i++) {
        ll u = readf< ll >(), //��ͼ
            v = readf< ll >(), //�Ҳ�ͼ
            w = readf< ll >(); //Ȩֵ
        graph[u - 1][v - 1] = w;
        Ltop[u - 1] = std::max(Ltop[u - 1], w);
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