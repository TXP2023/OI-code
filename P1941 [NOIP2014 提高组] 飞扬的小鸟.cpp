//P1941 [NOIP2014 提高组] 飞扬的小鸟
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <ctype.h>
#include <climits>
#include <iostream>
#include <stdint.h>

typedef long long ll;
typedef unsigned long long ull;

//函数前向声明
//快读函数
template< typename T >
inline T readf();

struct operate {
    ull up; //点击一下上升的高度
    ull down; //不点击下降的高度
};

struct pipeline //管道数据
{
    ll x; //横坐标
    ull up; //管道上限
    ull down; //管道下限

    //运算符重载控制sort函数
    bool operator <(const pipeline other)const {
        return x < other.x;
    }
};

std::vector< std::vector< ull > > dp(2); //动态规划数组
std::vector< operate > opers; //储存操作数据
std::vector< pipeline > pipelines; //储存障碍数据
std::vector< pipeline >::iterator it;
std::vector< bool > out; //储存小年可以通过几个障碍
ull n, m, k, maxout = 0; //界面的长度，高度和水管的数量
ull ans = LLONG_MAX;

int main() {
    freopen("input.txt", "r", stdin);

    scanf("%lld%lld%lld", &n, &m, &k);

    //输入操作数据
    opers.resize(n);
    for (ull i = 0; i < n; i++) {
        opers[i].up = readf< ll >(),
        opers[i].down = readf< ll >();
    }

    //输入管道数据
    pipelines.resize(k);
    for (ull i = 0; i < k; i++) {
        //scanf("%lld%lld%lld", &pipelines[i].x, &pipelines[i].down, &pipelines[i].up);
        pipelines[i].x = readf< ll >(), 
        pipelines[i].down = readf< ll >(),
        pipelines[i].up = readf< ll >();
    }
    std::sort(pipelines.begin(), pipelines.end());
    pipelines.push_back({ -1, 0, 0 });
    //动态规划

    dp[0].resize(m, 0);
    dp[1].resize(m, LLONG_MAX);
    it = pipelines.begin();
    for (ull i = 1; i <= n; i++) {
        //上升
        for (ull j = opers[i - 1].up; j < m; j++) {
            dp[i % 2][j] = std::min(dp[i % 2 ^ 1][j - opers[i - 1].up] + 1/*跳一下*/, dp[i % 2][j - opers[i - 1].up] + 1/*跳更多下*/);
        }

        //碰到天花板的特殊情况
        for (ull j = m - 1; j < m + opers[i - 1].up; j++) {
            //dp[i % 2][m - 1] = std::min(dp[i % 2 ^ 1][j - opers[i - 1].up] + 1, dp[i % 2][m - 1]);
            dp[i % 2][m - 1] = std::min(dp[i % 2 ^ 1][j - opers[i - 1].up] + 1, std::min(dp[i % 2][m - 1], dp[i % 2][j - opers[i - 1].up] + 1));
        }

        //往下掉
        for (ull j = 0; j <= m - opers[i - 1].down - 1; j++) {
            dp[i % 2][j] = std::min(dp[i % 2][j], dp[i % 2 ^ 1][j + opers[i - 1].down]);
        }

#if true

        //处理因为管道而无法到达的地方
        if ((*it).x == i) {
            //下限处理
            for (ull j = 0; j < (*it).down; j++) {
                dp[i % 2][j] =  LLONG_MAX;
            }

            //上线处理
            for (ull j = (*it).up - 1; j <= m - 1; j++) {
                dp[i % 2][j] = LLONG_MAX;
            }

            //弹出
            it++;
            for (ull j = 0; j < m; j++) {
                if (dp[i % 2][j] < LLONG_MAX) {
                    maxout++;
                    break;
                }
            }
        }
#else
        //处理因为管道而无法到达的地方
        if (!pipelines.empty() && pipelines.front().x == i) {
            //下限处理
            for (ull j = 0; j < pipelines.front().down; j++) {
                dp[i % 2][j] = LLONG_MAX;
            }

            //上线处理
            for (ull j = pipelines.front().up - 1; j <= m - 1; j++) {
                dp[i % 2][j] = LLONG_MAX;
            }

            //弹出
            pipelines.erase(pipelines.begin());
            for (ull j = 0; j < m; j++) {
                if (dp[i % 2][j] < LLONG_MAX) {
                    maxout++;
                    break;
                }
            }
        }
#endif
        //预处理
        std::fill(dp[i % 2 ^ 1].begin(), dp[i % 2 ^ 1].end(), LLONG_MAX);
        //dp[i % 2 ^ 1].clear();
        //dp[i % 2 ^ 1].resize(m, LLONG_MAX);
    }

    //寻找结果
    for (ull i = 0; i < m; i++) {
        if (dp[n % 2][i] < ans) {
            ans = dp[n % 2][i];
        }
    }

    //输出结果
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