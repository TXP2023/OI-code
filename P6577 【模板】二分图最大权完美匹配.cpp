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
ull n, m, ans = 0;

inline void init(); //��ʼ��
inline void find_Path(ll u); //��������·��
inline void Kuhn_Munkres(); //KM�㷨
inline void add_Path(ll u); //ת��

inline void init() /*��ʼ��*/ {
    Ltop.resize(n, LLONG_MIN);
    std::vector< ll >(Ltop).swap(Ltop);
    Rtop.resize(n, 0);
    std::vector< ll >(Rtop).swap(Rtop);
    pre.resize(n, 0);
    std::vector< ll >(pre).swap(pre);
    Lmatch.resize(n, -1);
    std::vector< ll >(Lmatch).swap(Lmatch);
    Rmatch.resize(n, -1);
    std::vector< ll >(Rmatch).swap(Rmatch);
    ltag.resize(n, false);
    std::vector< bool >(ltag).swap(ltag);
    rtag.resize(n, false);
    std::vector< bool >(rtag).swap(rtag);
    slack.resize(n, 0);
    std::vector< ll >(slack).swap(slack);
    graph.resize(n, std::vector< ll >(n, LLONG_MIN));
}

inline void Kuhn_Munkres() {
    for (size_t i = 0/*�����i��ö����ͼ��*/; i < n; i++) {
        std::fill(slack.begin(), slack.end(), LLONG_MAX);
        //std::fill(pre.begin(), pre.end(), -1);
        std::fill(ltag.begin(), ltag.end(), false);
        std::fill(rtag.begin(), rtag.end(), false);
        find_Path(i);
    }
    return;
}

inline void find_Path(ll u) {
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
                        if (Rmatch[i] == -1) /*�������Ҳ�ͼ�ڵ�û�б�ƥ��*/ {
                            add_Path(i);
                            return;
                        }
                        else {
                            que.push(Rmatch[i]);
                        }
                    }
                }
            }
        }
        ll MinDifference = LLONG_MAX/*����С��ֵ*/;
        for (size_t i = 0; i < n; i++) {
            if (!rtag[i]) /*�������Ҳ�ͼ�㲻�������ͼ��*/ {
                MinDifference = std::min(MinDifference, slack[i]);
            }
        }
        for (size_t i = 0; i < n; i++) {
            if (ltag[i]) {
                Ltop[i] -= MinDifference;
            }
            if (rtag[i]) {
                Rtop[i] += MinDifference;
            }
            else {
                slack[i] -= MinDifference;
            }
        }
        for (size_t i = 0; i < n; i++) {
            if (!rtag[i] && slack[i] == 0) /*��ӵ������ͼ*/ {
                rtag[i] = 1;
                if (Rmatch[i] == -1) {
                    add_Path(i);
                    return;
                }
                else {
                    que.push(Rmatch[i]);
                }
            }
        }
    }
}


inline void add_Path(ll u) {
    ll t;
    while (u != -1) {
        t = Rmatch[pre[u]];
        Rmatch[pre[u]] = u;
        Lmatch[u] = pre[u];
        u = t;
    }
    return;
}


int main() {
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    n = readf< ull >(), m = readf< ull >();

    graph.resize(n, std::vector< ll >(m, 0));

    init();

    for (size_t i = 0; i < m; i++) {
        ll u = readf< ll >(), //��ͼ
            v = readf< ll >(), //�Ҳ�ͼ
            w = readf< ll >(); //Ȩֵ
        graph[u - 1][v - 1] = w;
        Ltop[u - 1] = std::max(Ltop[u - 1], w);
    }

    Kuhn_Munkres();

    for (size_t i = 0; i < n; i++) {
        ans += Lmatch[i] + Rmatch[i];
    }
    printf("%lld\n", ans);
    for (size_t i = 0; i < n; i++) {
        printf("%lld ", Rmatch[i]);
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