#include <vector>
#include <iostream>
#include <cmath>
#include <math.h>
#include <queue>
#include <string>
#include <stack>

typedef long long int ll;

#define MAXN    (ll)(205)

using std::cin;
using std::cout;
using std::max;

struct Time {
    ll h, m;
};

struct Edge {
    ll s, t;
};

ll dits[4];
Edge zg[MAXN], gw[MAXN];
ll cnt1, cnt2;
ll n = 0, ans = 1e18;

int main() {
    freopen("input.txt", "r", stdin);

    //cin >> n;
    scanf("%lld", &n);

    for (ll i = 0; i < n; ++i) {
        std::string s1, s2;
        cin >> s1;
        ll a, b, c, d;
        scanf("%lld:%lld--%lld:%lld", &a, &b, &c, &d);
        std::pair<ll, ll>  t;
        t.first = a * 60 + b;
        t.second = c * 60 + d;
        if (s1 == "Zagreb-Graz") {
            zg[++cnt1] = { t.first, t.second };
        }
        else {
            gw[++cnt2] = { t.first, t.second };
        }
    }

    if (!cnt1 || !cnt2) {
        puts("NEMOGUCE");
        return 0;
    }

    for (ll i = 1; i <= cnt1; ++i) {
        for (ll j = 1; j <= cnt2; ++j) {
            ll res = 0;
            if (zg[i].t <= zg[i].s) {
                res += 1440 - zg[i].s + zg[i].t;
            }
            else {
                res += zg[i].t - zg[i].s;
            }

            //分类讨论
            if (zg[i].t < gw[j].s) {
                //当天就可以座上下一班车
                res += gw[j].s - zg[i].t;
                if (gw[j].s < gw[j].t) {
                    res += gw[j].t - gw[j].s;
                }
                else {
                    res += gw[j].t + 1440 - gw[j].s;
                }
            }
            else {
                //当天无法座上下一班车
                res += 1440 - zg[i].t + gw[j].s;
                if (gw[j].s < gw[j].t) {
                    res += gw[j].t - gw[j].s;
                }
                else {
                    res += 1440 - gw[j].s + gw[j].t;
                }
            }
            ans = std::min(res + 1, ans);
        }
    }

    if (ans == 1e18) {
        puts("NEMOGUCE");
    }
    else {
        printf("%lld:", ans / 60);
        if (ans % 60 < 10) {
            printf("0");
        }
        printf("%lld\n", ans % 60);
    }


    return 0;
}