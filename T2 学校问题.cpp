#include <vector>
#include <iostream>
#include <cmath>
#include <math.h>
#include <queue>
#include <algorithm>
#include <string>
#include <stack>

typedef long long int ll;

#define MAXN    (ll)(2e5+5)

using std::cin;
using std::cout;
using std::max;

struct Student {
    ll h, w;
};

struct node {
    ll ls, rs;
    ll cnt;
};

Student stu[MAXN];
node tree[MAXN << 4];
ll root[MAXN], tot;
ll n, k, ans = 0;;

void ins(ll pre, ll& pos, ll lp, ll rp, ll val) {
    pos = ++tot;
    tree[pos] = tree[pre];
    ++tree[pos].cnt;
    if (lp == rp) {
        return;
    }
    ll mid = (lp + rp) >> 1;
    if (val <= mid) {
        ins(tree[pre].ls, tree[pos].ls, lp, mid, val);
    }
    else {
        ins(tree[pre].rs, tree[pos].rs, mid + 1, rp, val);
    }
    return;
}

//查询在区间lpos~rpos中，找一个子区间使得子区间的跨度为k的和最大
ll ask(ll lpos, ll rpos, ll l, ll r, ll val) {
    if (r <= val) {
        return tree[rpos].cnt - tree[lpos].cnt;
    }
    ll res = 0, mid = (l + r) >> 1;
    res += ask(tree[lpos].ls, tree[rpos].ls, l, mid, val);
    if (val > mid) {
        res += ask(tree[lpos].rs, tree[rpos].rs, mid + 1, r, val);
    }
    return res;
}

int main() {
    freopen("input", "r", stdin);

    cin >> n >> k;

    for (ll i = 1; i <= n; ++i) {
        cin >> stu[i].h >> stu[i].w;
    }

    std::sort(stu + 1, stu + 1 + n, [](const Student& a, const Student& b) {
        if (a.h == b.h) {
            return a.w < b.w;
        }
        return a.h < b.h;
    });

    for (size_t i = 1; i <= n; i++) {
        //插入
        ins(root[i - 1], root[i], 1, 5000, stu[i].w);
    }


    for (size_t h = 1; h <= 5000 - k; h++) {
        for (size_t w = 1; w <= 5000 - k; w++) {
            ll posl, posr;
            for (size_t l = 1, r = n; l <= r; ) {
                ll mid = (l + r) >> 1;
                if (stu[mid].h >= h) {
                    posl = mid;
                    l = mid + 1;
                }
                else {
                    r = mid - 1;
                }
            }
            for (size_t l = 1, r = n; l <= r; ) {
                ll mid = (l + r) >> 1;
                if (stu[mid].h <= h + k) {
                    posr = mid;
                    l = mid + 1;
                }
                else {
                    r = mid - 1;
                }
            }
            ans = std::max(ask(root[posl - 1], root[posr], 1, 5000, w + k) - ask(root[posl - 1], root[posr], 1, 5000, w - 1), ans);
        }
    }

    printf("%lld\n", ans);

    return 0;
}
