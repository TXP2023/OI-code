#include <bits/stdc++.h>

typedef long long int ll;

#define MAXN (ll)(1e6+5)
#define LS(x)  ((x) <<1)
#define RS(x)  ((x) <<1|1)

struct coin {
    ll p, t;
};

ll tree[MAXN], dp[MAXN];
ll dif[MAXN], size;
coin c[MAXN];
std::map<ll, ll> map, reMap;
ll n, ans = 0;

void dis() {
    ll temp[MAXN];
    memcpy(temp, dif, sizeof dif);
    std::sort(temp + 1, temp + 1 + n);
    size = std::unique(temp + 1, temp + 1 + n) - (temp + 1);
    for (ll i = 1; i <= size; ++i) {
        map[temp[i]] = i;
        reMap[i] = temp[i];
    }
    return;
}

void upd(ll p, ll lp, ll rp, ll val, ll w) {
    if (lp == rp) {
        tree[p] = std::max(w, tree[p]);
        return;
    }
    ll mid = (lp + rp) >> 1;
    if (val <= mid) {
        upd(LS(p), lp, mid, val, w);
    }
    else {
        upd(RS(p), mid + 1, rp, val, w);
    }
    tree[p] = std::max(tree[LS(p)], tree[RS(p)]);
    return;
}

//查询区间内所有小于等于val的dp数组值
ll ask(ll p, ll lp, ll rp, ll val) {
    if (rp <= val) {
        return tree[p];
    }
    ll mid = (lp + rp) >> 1, res = 0;
    res = ask(LS(p), lp, mid, val);
    if (mid < val) {
        res = std::max(ask(RS(p), mid + 1, rp, val), res);
    }
    return res;
}

int main() {
    //freopen("input", "r", stdin);
    scanf("%lld", &n);

    for (ll i = 1; i <= n; ++i) {
        scanf("%lld%lld", &c[i].p, &c[i].t);
        if (c[i].p > c[i].t) {
            --n;
            --i;
        }
    }

    if (n == 0) {
        puts("0");
        return 0;
    }


    std::sort(c + 1, c + 1 + n, [](const coin& a, const coin& b) {
        if (a.p == b.p) {
            return a.t < b.t;
        }
        return a.p < b.p;
    });

    for (ll i = 1; i <= n; ++i) {
        dif[i] = c[i].t - c[i].p;
    }

    //目前p是严格递增的
    dis();

    for (ll i = 1; i <= n; ++i) {
        //按照位置扫描
        dp[i] = ask(1, 0, size, map[dif[i]]) + 1;
        ans = std::max(ans, dp[i]);
        upd(1, 0, size, map[dif[i]], dp[i]);
    }
    printf("%lld\n", ans);
    return 0;
}