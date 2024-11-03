#include <vector>
#include <queue>
#include <algorithm>
#include <ctype.h>
#include <climits>
#include <stdint.h>
#include <cstdio>

#define inf 1e18

typedef long long int ll;
typedef unsigned long long int  ull;
typedef long double lf;

//����ǰ������
//�������
template< typename T >
inline T readf();

std::vector< bool > ltag(0), rtag(0); //ƥ��
std::vector< ll > Lmatch(0), Rmatch(0); //ƥ��
std::vector< ll > Ltop(0), Rtop(0); //����
std::vector< ll > pre(0);
std::vector< ll > slack(0);
std::vector< std::vector< ll > > graph(0);
ll n, m, ans = 0;

inline void init(); //��ʼ��
inline void find_Path(ll u); //��������·��
inline void Kuhn_Munkres(); //KM�㷨
inline void add_Path(ll u); //ת��

inline void init() /*��ʼ��*/ {
    Ltop.resize(n, -inf);
    std::vector< ll >(Ltop).swap(Ltop);
    Rtop.resize(n, 0);
    std::vector< ll >(Rtop).swap(Rtop);
    pre.resize(n, -1);
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
    graph.resize(n, std::vector< ll >(n, -inf));
#ifdef  Release false
    ll ramSum = Ltop.capacity() + Rtop.capacity() + pre.capacity() + Lmatch.capacity() + Rmatch.capacity() + slack.capacity();
    printf("%lld\n", ramSum);
#endif //  Release

}

inline void Kuhn_Munkres() {
    for (ll i = 0/*�����i��ö����ͼ��*/; i < n; i++) {
        find_Path(i); //��ÿ����ͼ��ƥ��
    }
    return;
}

inline void find_Path(ll u) {
    std::fill(ltag.begin(), ltag.end(), false);
    std::fill(rtag.begin(), rtag.end(), false);
    std::fill(slack.begin(), slack.end(), inf);
    std::queue< ll > que;//��ͼ�����
    que.push(u);

    while (true) {
        while (!que.empty()) {
            ll v = que.front(); que.pop();
            ltag[v] = true; //�����ͼ���Ѿ���ƥ�����
            for (size_t i = 0/*�����i���Ҳ�ͼ��*/; i < n; i++) {
                /*�����������ҪС�ڵ�ǰ��ͼ����������*/
                if (!rtag[i]/*����Ҳ�ͼ��û�б�ƥ��*/ && Ltop[v] + Rtop[i] - graph[v][i] < slack[i]) {
                    slack[i] = Ltop[v] + Rtop[i] - graph[v][i]; 
                    pre[i] = v;
                    if (slack[i] == 0)/*�����ǰ�����ڲ�ֵ, ��Ϊ��ȱ� �������·*/ {
                        rtag[i] = true; //�������Ϊ��ƥ��
                        if (Rmatch[i] == -1) /*�������Ҳ�ͼ�ڵ�֮ǰû�б�ƥ��*/ {
                            add_Path(i); //�������ӵ������ͼ
                            return;
                        }
                        else { //���֮ǰ�Ѿ���ƥ����� ������� �Ǿ͹�һ����˵
                            que.push(Rmatch[i]);
                        }
                    }
                }
            }
        }
        ll MinDifference = inf/*����С��ֵ*/;
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
    while (u != -1) /*�����������Ҳ�ͼ��*/ {
        t = Lmatch[pre[u]]; //tΪ����ǰ������Ҳ����ƥ������ƥ��
        Rmatch[u] = pre[u]; //���Լ���ƥ�����Ϊ��Ӧ����ͼ��
        Lmatch[pre[u]] = u; //��ô����ƥ��������Ϊ����Ҳ�ͼ��
        u = t; //�µ��Ҳ���ֵ
    }
    return;
}


int main() {
    freopen("input.txt", "r", stdin);

    n = readf< ull >(), m = readf< ull >();

    init();

    for (ll i = 0; i < m; i++) {
        ll u = readf< ll >(), //��ͼ
            v = readf< ll >(), //�Ҳ�ͼ
            w = readf< ll >(); //Ȩֵ
        graph[u - 1][v - 1] = w;
        Ltop[u - 1] = std::max(Ltop[u - 1], w);
    }

    Kuhn_Munkres();
    //_sleep(2000);
    for (ll i = 0; i < n; i++) {
        ans += graph[Rmatch[i]][i];
    }
    printf("%lld\n", ans);
    for (ll i = 0; i < n; i++) {
        printf("%lld ", Rmatch[i] + 1);
    }
    //_sleep(2000);
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