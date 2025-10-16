#include <bits/stdc++.h>

typedef int ll;

using std::cin;
using std::cout;

#define MAXN (ll)(12)
#define MAXD (ll)(1005)

ll dp[(1 << MAXN)][MAXD];
ll arr[MAXN], cnt[10];
ll t, p, n;

ll f(ll x) {
    ll res = 1;
    while (x) {
        res *= 10;
        x /= 10;
    }
    return res;
}

void solve() {
    memset(dp, 0, sizeof dp);
    memset(arr, 0, sizeof arr);
    memset(cnt, 0, sizeof cnt);
    std::string s;
    cin >> s >> p;
    for (ll i = 0; i < s.size(); ++i) {
        arr[i + 1] = s[i] - '0';
        ++cnt[arr[i + 1]];
        dp[1 << i][arr[i + 1] % p] = 1;
    }

    n = s.size();
    std::fill(dp[0], dp[0] + p, 1);
    for (ll i = 1; i < (1 << n); ++i) {
        for (ll j = 1; j <= n; ++j) {
            if (i >> (j - 1) & 1) {
                continue;
            }
            ll temp = i | (1 << (j - 1)), val = arr[j], log;
            for (ll k = 0; k < p; ++k) {
                dp[temp][(k * 10 % p + val) % p] += dp[i][k];
                //ll debug = (dp[i][k] + val*f(dp[i][k])) % p;
                //dp[temp][(dp[i][k] + val*f(dp[i][k])) % p] += dp[i][k];
            }
        }
    }

    ll mul = 1;
    for (ll i = 0; i <= 9; ++i) {
        //预处理出去重的阶乘
        if (!cnt[i]) {
            continue;
        }
        ll temp = 1;
        for (ll j = 2; j <= cnt[i]; ++j) {
            temp *= j;
        }
        mul *= temp;
    }

    printf("%lld\n", dp[(1 << n) - 1][0] / mul);
}

int main() {
    //freopen("input", "r", stdin);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
