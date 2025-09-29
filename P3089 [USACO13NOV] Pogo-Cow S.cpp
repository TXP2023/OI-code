#include <vector>
#include <bits/stdc++.h>

typedef long long int ll;

#define MAXN    (ll)(1e3+5)

struct Pos {
    ll x, p;
};

ll n;
ll dp[MAXN][MAXN], ans = 0;
Pos p[MAXN];

ll get_dist(Pos a, Pos b) {
    return std::abs(a.x - b.x);
}

int main() {
    //freopen("jump.in", "r", stdin);
    scanf("%lld", &n);

    for (ll i = 1; i <= n; ++i) {
        scanf("%lld%lld", &p[i].x, &p[i].p);
    }

    std::sort(p + 1, p + 1 + n, [](const Pos& a, const Pos& b) {
        return a.x < b.x;
    });

    for (ll i = 1; i <= n; i++) {
        //dp[i][0] = p[i].p;
        dp[i][i] = p[i].p;
        ans = std::max(ans, p[i].p);
    }

    //
    for (ll i = 1; i <= n; ++i) {
        for (ll j = i - 1; j >= 1; --j) {
            if (i == j) {
                continue;
            }
            //dp[i][j] = dp[j][0] + p[i].p;
            for (ll k = j; k >= 1; --k) {
                if (get_dist(p[i], p[j]) < get_dist(p[j], p[k])) {
                    break;
                }
                dp[i][j] = std::max(dp[j][k] + p[i].p, dp[i][j]);
            }
            ans = std::max(dp[i][j], ans);
        }
    }

    for (ll i = n - 1; i >= 1; --i) {
        for (ll j = i + 1; j <= n; ++j) {
            //dp[i][j] = dp[j][0] + p[i].p;
            for (ll k = j; k <= n; ++k) {
                if (get_dist(p[i], p[j]) < get_dist(p[j], p[k])) {
                    break;
                }
                dp[i][j] = std::max(dp[j][k] + p[i].p, dp[i][j]);
            }
            ans = std::max(dp[i][j], ans);
        }
    }

    printf("%lld\n", ans);


    return 0;
}