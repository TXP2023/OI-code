//P1941 [NOIP2014 �����] �����С��
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <ctype.h>
#include <climits>
#include <iostream>
#include <stdint.h>

typedef long long ll;
typedef unsigned long long unill;

struct operate {
    unill up; //���һ�������ĸ߶�
    unill down; //������½��ĸ߶�
};

struct _data //�ܵ�����
{
    unill x; //������
    unill up; //�ܵ�����
    unill down; //�ܵ�����

    //��������ؿ���sort����
    bool operator <(const _data& other)const {
        return x < other.x;
    }
};


std::vector< std::vector< unill > > dp(2); //��̬�滮����
std::vector< operate > opers; //�����������
std::vector< _data > datas; //�����ϰ�����
std::vector< bool > out; //����С�����ͨ�������ϰ�
unill n, m, k, maxout = 0; //����ĳ��ȣ��߶Ⱥ�ˮ�ܵ�����
unill ans = LLONG_MAX;

int main() {
    // freopen("D:\\code\\SHU_RU.in", "r", stdin);

    scanf("%lld%lld%lld", &n, &m, &k);

    //�����������
    opers.resize(n);
    for (unill i = 0; i < n; i++) {
        scanf("%lld%lld", &opers[i].up, &opers[i].down);
    }

    //����ܵ�����
    datas.resize(k);
    for (unill i = 0; i < k; i++) {
        scanf("%lld%lld%lld", &datas[i].x, &datas[i].down, &datas[i].up);
    }
    std::sort(datas.begin(), datas.end());

    //��̬�滮

    dp[0].resize(m, 0);
    dp[1].resize(m, LLONG_MAX);
    for (unill i = 1; i <= n; i++) {
        //����
        for (unill j = opers[i - 1].up; j < m; j++) {
            dp[i % 2][j] = std::min(dp[i % 2 ^ 1][j - opers[i - 1].up] + 1, dp[i % 2][j - opers[i - 1].up] + 1);
        }

        //�����컨����������
        for (unill j = m - 1; j < m + opers[i - 1].up; j++) {
            dp[i % 2][m - 1] = std::min(dp[i % 2 ^ 1][j - opers[i - 1].up] + 1, dp[i % 2][m - 1]);
        }

        //���µ�
        for (unill j = 0; j <= m - opers[i - 1].down - 1; j++) {
            dp[i % 2][j] = std::min(dp[i % 2][j], dp[i % 2 ^ 1][j + opers[i - 1].down]);
        }

        //������Ϊ�ܵ����޷�����ĵط�
        if (!datas.empty() && datas.front().x == i) {
            //���޴���
            for (unill j = 0; j < datas.front().down; j++) {
                dp[i % 2][j] =  LLONG_MAX;
            }

            //���ߴ���
            for (unill j = datas.front().up - 1; j <= m - 1; j++) {
                dp[i % 2][j] = LLONG_MAX;
            }

            //����
            datas.erase(datas.begin());
            for (unill j = 0; j < m; j++) {
                if (dp[i % 2][j] < LLONG_MAX) {
                    maxout++;
                    break;
                }
            }
        }

        //Ԥ����
        dp[i % 2 ^ 1].clear();
        dp[i % 2 ^ 1].resize(m, LLONG_MAX);
    }

    //Ѱ�ҽ��
    for (unill i = 0; i < m; i++) {
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