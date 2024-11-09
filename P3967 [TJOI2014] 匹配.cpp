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

//������Ϊ��ͼ��Ů��Ϊ�Ҳ�ͼ

std::vector< bool > ltag(0), rtag(0); //ƥ��
std::vector< ll > Lmatch(0), Rmatch(0); //ƥ��
std::vector< ll > Ltop(0), Rtop(0); //����
std::vector< ll > initLtop(0); //����
std::vector< ll > pre(0);
std::vector< ll > slack(0);
std::vector< ll > MaxLmatch;
std::vector< std::vector< ll > > graph(0);
ll n, m, Max_match = 0;

inline void init(); //��ʼ��
inline void find_Path(ll u); //��������·��
inline void Kuhn_Munkres(); //KM�㷨
inline void add_Path(ll u); //ת��

inline void init() /*��ʼ��*/ {
    initLtop.resize(n, -inf);
    std::vector< ll >(initLtop).swap(initLtop);
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
}

inline void Kuhn_Munkres() {
    //Ltop = initLtop;
    //Rtop.clear();
    //Rtop.resize(n, 0);
    //std::vector< ll >(Rtop).swap(Rtop);
    //pre.clear();
    //pre.resize(n, -1);
    //std::vector< ll >(pre).swap(pre);
    //Lmatch.resize(n, -1);
    //std::vector< ll >(Lmatch).swap(Lmatch);
    //Rmatch.resize(n, -1);
    //std::vector< ll >(Rmatch).swap(Rmatch);
    //ltag.resize(n, false);
    //std::vector< bool >(ltag).swap(ltag);
    //rtag.resize(n, false);
    //std::vector< bool >(rtag).swap(rtag);
    //slack.resize(n, 0);
    //std::vector< ll >(slack).swap(slack);
    Ltop = initLtop;
    std::fill(Rtop.begin(), Rtop.end(), 0);
    std::fill(pre.begin(), pre.end(), -1);
    std::fill(Lmatch.begin(), Lmatch.end(), -1);
    std::fill(Rmatch.begin(), Rmatch.end(), -1);
    std::fill(ltag.begin(), ltag.end(), false);
    std::fill(rtag.begin(), rtag.end(), false);
    std::fill(slack.begin(), slack.end(), 0);

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
                if (!rtag[i]/*����Ҳ�ͼ��û�б�ƥ��*/ && Ltop[v] + Rtop[i] - graph[v][i]/*graph[v][i].first*/ < slack[i] /* && graph[v][i].second*/) {
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

    n = readf< ull >();

    init();

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            graph[i][j] = readf< ll >();
            initLtop[i] = std::max(initLtop[i], graph[i][j]);
        }
    }

    Kuhn_Munkres();

    for (ll i = 0; i < n; i++) {
        Max_match += graph[Rmatch[i]][i];
    }
    printf("%lld\n", Max_match);

    MaxLmatch = Lmatch;

    /*����Ӧ������ȷ��*/
    for (size_t i = 0; i < n; i++) {
        ll w = graph[i][MaxLmatch[i]];
        graph[i][MaxLmatch[i]] = 0;
        Kuhn_Munkres();
        graph[i][MaxLmatch[i]] = w;
        ll match = 0;
        for (size_t i = 0; i < n; i++) {
            match += graph[Rmatch[i]][i];
        }
        if (match < Max_match) {
            printf("%lld %lld\n", i + 1, MaxLmatch[i] + 1);
        }
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