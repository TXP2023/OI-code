//P1941 [NOIP2014 �����] �����С��
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <ctype.h>
#include <climits>
#include <iostream>
#include <stdint.h>

typedef long long ll;
typedef unsigned long long ull;

//����ǰ������
//�������
template< typename T >
inline T readf();

struct operate {
    ull up; //���һ�������ĸ߶�
    ull down; //������½��ĸ߶�
};

struct pipeline //�ܵ�����
{
    ll x; //������
    ull up; //�ܵ�����
    ull down; //�ܵ�����

    //��������ؿ���sort����
    bool operator <(const pipeline other)const {
        return x < other.x;
    }
};

std::vector< std::vector< ull > > dp(2); //��̬�滮����
std::vector< operate > opers; //�����������
std::vector< pipeline > pipelines; //�����ϰ�����
std::vector< pipeline >::iterator it;
std::vector< bool > out; //����С�����ͨ�������ϰ�
ull n, m, k, maxout = 0; //����ĳ��ȣ��߶Ⱥ�ˮ�ܵ�����
ull ans = LLONG_MAX;

int main() {
    freopen("input.txt", "r", stdin);

    scanf("%lld%lld%lld", &n, &m, &k);

    //�����������
    opers.resize(n);
    for (ull i = 0; i < n; i++) {
        //scanf("%lld%lld", &opers[i].up, &opers[i].down);
        opers[i].up = readf< ll >(),
        opers[i].down = readf< ll >();
    }

    //����ܵ�����
    pipelines.resize(k);
    for (ull i = 0; i < k; i++) {
        //scanf("%lld%lld%lld", &pipelines[i].x, &pipelines[i].down, &pipelines[i].up);
        pipelines[i].x = readf< ll >(), 
        pipelines[i].down = readf< ll >(),
        pipelines[i].up = readf< ll >();
    }
    std::sort(pipelines.begin(), pipelines.end());
    pipelines.push_back({ -1, 0, 0 });
    //��̬�滮

    dp[0].resize(m, 0);
    dp[1].resize(m, LLONG_MAX);
    it = pipelines.begin();
    for (ull i = 1; i <= n; i++) {
        //����
        for (ull j = opers[i - 1].up; j < m; j++) {
            dp[i % 2][j] = std::min(dp[i % 2 ^ 1][j - opers[i - 1].up] + 1/*��һ��*/, dp[i % 2][j - opers[i - 1].up] + 1/*��������*/);
        }

        //�����컨����������
        for (ull j = m - 1; j < m + opers[i - 1].up; j++) {
            //dp[i % 2][m - 1] = std::min(dp[i % 2 ^ 1][j - opers[i - 1].up] + 1, dp[i % 2][m - 1]);
            dp[i % 2][m - 1] = std::min(dp[i % 2 ^ 1][j - opers[i - 1].up] + 1, std::min(dp[i % 2][m - 1], dp[i % 2][j - opers[i - 1].up] + 1));
        }

        //���µ�
        for (ull j = 0; j <= m - opers[i - 1].down - 1; j++) {
            dp[i % 2][j] = std::min(dp[i % 2][j], dp[i % 2 ^ 1][j + opers[i - 1].down]);
        }

#if true

        //������Ϊ�ܵ����޷�����ĵط�
        if ((*it).x == i) {
            //���޴���
            for (ull j = 0; j < (*it).down; j++) {
                dp[i % 2][j] =  LLONG_MAX;
            }

            //���ߴ���
            for (ull j = (*it).up - 1; j <= m - 1; j++) {
                dp[i % 2][j] = LLONG_MAX;
            }

            //����
            it++;
            for (ull j = 0; j < m; j++) {
                if (dp[i % 2][j] < LLONG_MAX) {
                    maxout++;
                    break;
                }
            }
        }
#else
        //������Ϊ�ܵ����޷�����ĵط�
        if (!pipelines.empty() && pipelines.front().x == i) {
            //���޴���
            for (ull j = 0; j < pipelines.front().down; j++) {
                dp[i % 2][j] = LLONG_MAX;
            }

            //���ߴ���
            for (ull j = pipelines.front().up - 1; j <= m - 1; j++) {
                dp[i % 2][j] = LLONG_MAX;
            }

            //����
            pipelines.erase(pipelines.begin());
            for (ull j = 0; j < m; j++) {
                if (dp[i % 2][j] < LLONG_MAX) {
                    maxout++;
                    break;
                }
            }
        }
#endif
        //Ԥ����
        std::fill(dp[i % 2 ^ 1].begin(), dp[i % 2 ^ 1].end(), LLONG_MAX);
        //dp[i % 2 ^ 1].clear();
        //dp[i % 2 ^ 1].resize(m, LLONG_MAX);
    }

    //Ѱ�ҽ��
    for (ull i = 0; i < m; i++) {
        if (dp[n % 2][i] < ans) {
            ans = dp[n % 2][i];
        }
    }

    //������
    switch (ans) {
    case LLONG_MAX:
        printf("0\n%llu\n", maxout);
        break;

    default:
        printf("1\n%llu\n", ans);
        break;
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