#include <vector>
#include <stdio.h>
#include <queue>
#include <algorithm>
#include <ctype.h>
#include <cstdarg>
#include <climits>
#include <iostream>
#include <stdint.h>

#define READ true
#define inf 1e18

typedef long long int ll;
typedef unsigned long long int ull;

#if READ
//����ǰ������
//�������
template< typename T >
inline T readf();
#else
template< typename T >
inline T readf(...);
#endif


std::vector< std::vector< ll > > graph;
std::vector< ll > lmatch, rmatch;
std::vector< ll > ltop, rtop;
std::vector< ll >  pre;
ll n, max;

inline ll km();

inline void match(ll u/*����ͼ��u��ƥ��*/);

inline void add_match(ll u);

inline ll km() {
    rtop.resize(n, 0);
    std::vector< ll >(rtop).swap(rtop);
    lmatch.resize(n, -1);
    std::vector< ll >(lmatch).swap(lmatch);
    rmatch.resize(n, -1);
    std::vector< ll >(rmatch).swap(rmatch);
    pre.resize(n, -1);
    std::vector< ll >(pre).swap(pre);
    for (size_t i = 0; i < n; i++) {
        match(i);
    }
    ll sum = 0;
    for (ll i = 0; i < n; i++) {
        sum += graph[i][lmatch[i]];
    }

    rtop.clear();
    lmatch.clear();
    rmatch.clear();
    pre.clear();
    return sum;
}

inline void match(ll u/*����ͼ��u��ƥ��*/) {
    std::vector< bool > ltag(n, false), rtag(n, false);
    std::vector< ll > slack(n, inf);
    std::queue< ll > que;
    
    que.push(u);
    while (true) {
        while (!que.empty()) {
            ll v = que.front(); que.pop();
            ltag[v] = true;
            for (size_t i = 0; i < n; i++) /*�����Ҳ�����ƥ��*/ {
                if (!rtag[i] && ltop[v] + rtop[i] - graph[v][i] < slack[i]) {
                    slack[i] = ltop[v] + rtop[i] - graph[v][i];
                    pre[i] = v;/**/
                    if (slack[i] == 0) {
                        rtag[i] = true;/**/
                        if (rmatch[i] == -1) {
                            add_match(i);
                            return;
                        }
                        else {
                            que.push(rmatch[i]); /**/
                        }
                    }
                }
            }
        }
        ll min_difference = LLONG_MAX;
        for (size_t i = 0; i < n; i++) {
            if (!rtag[i]) {
                min_difference = std::min(min_difference, slack[i]);
            }
        }
        for (size_t i = 0; i < n; i++) {
            if (ltag[i]) {
                ltop[i] -= min_difference;
            }
            if (rtag[i]) {
                rtop[i] += min_difference;
            }
            else {
                slack[i] -= min_difference;
            }
        }
        for (size_t i = 0; i < n; i++) {
            if (!rtag[i] && slack[i] == 0) /*��ӵ������ͼ*/ {
                rtag[i] = 1;
                if (rmatch[i] == -1) {
                    add_match(i);
                    return;
                }
                else {
                    que.push(rmatch[i]);
                }
            }
        }
    }
    return;
}

inline void add_match(ll u) {
    ll t;
    while (u != -1) /*�����������Ҳ�ͼ��*/ {
        t = lmatch[pre[u]]; //tΪ����ǰ������Ҳ����ƥ������ƥ��
        rmatch[u] = pre[u]; //���Լ���ƥ�����Ϊ��Ӧ����ͼ��
        lmatch[pre[u]] = u; //��ô����ƥ��������Ϊ����Ҳ�ͼ��
        u = t; //�µ��Ҳ���ֵ
    }
}


int main() {
    freopen("input.txt", "r", stdin);

    n = readf< ll >();

    //���˵���ͼ��  �������Ҳ�ͼ��
    graph.resize(n, std::vector< ll >(n));
    ltop.resize(n, LLONG_MIN);
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            graph[i][j] = readf< ll >();
            ltop[i] = std::max(ltop[i], graph[i][j]);
        }
    }
    max = km(); //���ֵ

    std::fill(ltop.begin(), ltop.end(), LLONG_MIN);
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            graph[i][j] = -graph[i][j];
            ltop[i] = std::max(ltop[i], graph[i][j]);
        }
    }

    printf("%lld\n%lld\n", 0 - km(), max);
    return 0;
}

#if READ
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
#else
template< typename T >
inline T readf(...) {
    T ret = 0, sgn = 0, ch = getchar();
    while (!isdigit(ch)) {
        sgn |= ch == '-', ch = getchar();
    }
    while (isdigit(ch)) ret = ret * 10 + ch - '0', ch = getchar();
    va_list args;
    va_start(args, num_arge);
    for (size_t i = 0; i < num_arge; i++) {
        *(va_arg(args, T*)) = sgn ? -ret : ret;
    }
    va_end(args);
    return sgn ? -ret : ret;
}
#endif