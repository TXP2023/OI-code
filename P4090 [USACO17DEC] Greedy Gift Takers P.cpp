#include <bits/stdc++.h>

typedef long long int ll;

using std::cin;
using std::cout;

#define MAXN    (ll)(1e5+5)

ll a[MAXN];
ll n;

bool check(ll len) {
    ll temp[MAXN];
    memset(temp, 0, sizeof temp);
    if (len == 1) {
        return 1;
    }
    for (ll i = 1; i < len; ++i) {
        temp[i] = a[i];
    }

    std::sort(temp + 1, temp + len);
    ll cnt = n - len; //记录末端无法拿到礼物的牛的数量
    for (ll i = 1; i < len; ++i) {
        if (temp[i] > cnt) {
            return 0;
        }
        ++cnt;
    }
    return 1;
}

int main() {
    //freopen("input", "r", stdin);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    cin >> n;

    for (ll i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    //枚举循环节长度
    ll res = 0;
    for (ll l = 0, r = n; l <= r;) {
        ll mid = (l + r) >> 1;
        if (check(mid)) {
            res = mid;
            l = mid + 1;
        }
        else {
            r = mid - 1;
        }
    }

    printf("%lld\n", n - res);

    return 0;
}