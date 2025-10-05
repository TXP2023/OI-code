#include <bits/stdc++.h>

typedef long long int ll;

#define MAXN (ll)(1e6+5)
#define LS(x)  ((x) << 1)
#define RS(x)  ((x) << 1 | 1)

struct node {
    ll sum;
    ll flag = -1;
};

node tree[MAXN << 2];
ll n, q;

void push_down(ll p, ll lp, ll rp) {
    if (tree[p].flag == -1) {
        return;
    }
    ll ls = LS(p), rs = RS(p), mid = (lp + rp) >> 1;
    tree[ls].flag = tree[p].flag;
    tree[ls].sum = tree[p].flag * (mid - lp + 1);
    tree[rs].flag = tree[p].flag;
    tree[rs].sum = tree[p].flag * (rp - mid);
    tree[p].flag = -1;
    return;
}

void upd(ll p, ll lp, ll rp, ll l, ll r, ll weight) {
    if (l <= lp && rp <= r) {
        tree[p].sum = weight * (rp - lp + 1);
        tree[p].flag = weight;
        return;
    }
    push_down(p, lp, rp);
    ll mid = (lp + rp) >> 1;
    if (l <= mid) {
        upd(LS(p), lp, mid, l, r, weight);
    }
    if (r > mid) {
        upd(RS(p), mid + 1, rp, l, r, weight);
    }
    tree[p].sum = tree[LS(p)].sum + tree[RS(p)].sum;
    return;
}

//count all node < val
ll ask(ll p, ll l, ll r, ll val) {
    if (r <= val) {
        return tree[p].sum;
    }
    push_down(p, l, r);
    ll mid = (l + r) >> 1, res = ask(LS(p), l, mid, val);
    if (mid < val) {
        res += ask(RS(p), mid + 1, r, val);
    }
    return res;
}

int main() {
    //freopen("input.txt", "r", stdin);
    scanf("%lld%lld", &n, &q);

    for (ll i = 1; i <= n; ++i) {
        upd(1, 1, n, i, i, 1);
    }

    while (q--) {
        ll x, y;
        scanf("%lld%lld", &x, &y);
        ll res = ask(1, 1, n, x);
        printf("%lld\n", res);
        res += ask(1, 1, n, y) - ask(1, 1, n, y - 1);
        upd(1, 1, n, 1, x, 0);
        upd(1, 1, n, y, y, res);
    }

    return 0;
}

































