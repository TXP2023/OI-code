#include <bits/stdc++.h>

using ll = long long int;
using std::cin;

#define MAXN (ll)(21)
#define INF  (ll)(1e18)
#define MAXC      1005

struct film {
    ll beg, end;
};

film f[MAXN][MAXC];
ll dp[(1 << MAXN)];
ll num[MAXN];
ll n, l, ans = INF;

ll cnt_bit(ll val) {
    ll res = 0;
    while (val) {
        if (val & 1) {
            ++res;
        }
        val >>= 1;
    }
    return res;
}

int main() {
    //freopen("input", "r", stdin);
    cin >> n >> l;

    for (ll i = 1; i <= n; ++i) {
        ll len;
        cin >> len >> num[i];
        for (ll j = 1; j <= num[i]; ++j) {
            cin >> f[i][j].beg;
            f[i][j].end = f[i][j].beg + len;
        }
    }

    memset(dp, -1, sizeof dp);
    dp[0] = 0;
    //dp[i] 为看状态为i的电影的情况下的最大结束时间
    for (ll i = 0; i < (1 << n); ++i) {
        if (dp[i] == INF) {
            continue;
        }
        ll cnt = cnt_bit(i);
        for (ll j = 0; j < n; j++) {
            //枚举每个合法的下一场电影
            if (i >> j & 1) {
                continue;
            }

            //我们要观看这场电影
            //二分确定一个场次使得开始时间小于等于当前的结束时间
            ll temp = 0;
            for (ll l = 1, r = num[j + 1]; l <= r;) {
                ll mid = (l + r) >> 1;
                if (f[j + 1][mid].beg <= dp[i]) {
                    temp = mid;
                    l = mid + 1;
                }
                else {
                    r = mid - 1;
                }
            }

            //我们无法观看以后的任意一场这个电影
            if (!temp) {
                continue;
            }

            dp[i | (1 << j)] = std::max(f[j + 1][temp].end, dp[i | (1 << j)]);
            if (dp[i | (1 << j)] >= l) {
                ans = std::min(cnt + 1, ans);
            }
        }
    }

    printf("%lld\n", ans != INF ? ans : -1);

    return 0;
}