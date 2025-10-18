#include <bits/stdc++.h>

typedef long long int ll;

#define MAXN    (ll)(5e5+5)

using std::cin;
using std::cout;

struct Edge {
    ll v, next;
};

ll res[MAXN];
ll sec_id[MAXN]; //非严格次长的编号
ll sec[MAXN]; //非严格次长的长度
ll sec2[MAXN]; //以i为根的次短路的长度
ll sec2_id[MAXN]; ////以i为根的次短路的长度的端点
ll dp[MAXN]; //dp[i] 为以i为根的子树的深度
ll id[MAXN]; //id[i] 为以i为根的子树的最远距离点的编号
ll deep[MAXN];
ll head[MAXN];
ll res_len[MAXN];
Edge e[MAXN << 1];
ll n, tot;

void add_edge(ll u, ll v) {
    ++tot;
    e[tot] = { v, head[u] };
    head[u] = tot;
    return;
}

void solve(ll u, ll fa, ll d) {
    deep[u] = d;
    dp[u] = 0;
    id[u] = u;
    for (ll i = head[u]; i; i = e[i].next) {
        ll v = e[i].v;
        if (v == fa) {
            continue;
        }
        solve(v, u, d + 1);
        if (dp[v] + 1 > dp[u]) {
            sec[u] = dp[u];
            sec_id[u] = id[u];
            dp[u] = dp[v] + 1;
            id[u] = id[v];
            //flag = true;
        }
        else {
            if (dp[v] + 1 == dp[u] && id[v] > id[u]) {
                sec[u] = dp[u];
                sec_id[u] = id[u];
                id[u] = id[v];
                //flag = true;
            }
            else {
                //尝试更新次长路
                if (dp[v] + 1 == dp[u] && ((dp[v] + 1 > sec[u]) || (dp[v] + 1 == sec[u] && id[v] > sec_id[u]))) {
                    sec[u] = dp[v] + 1;
                    sec_id[u] = id[v];
                }
                else {
                    if (dp[v] + 1 < dp[u] && ((dp[v] + 1 > sec[u]) || (dp[v] + 1 == sec[u] && id[v] > sec_id[u]))) {
                        sec[u] = dp[v] + 1;
                        sec_id[u] = id[v];
                    }
                }
                //else {
                //    if (dp[v] + 1 < dp[u] && dp[v] + 1 > sec[u]) {
                //        sec[u] = dp[v] + 1;
                //        sec_id[u] = id[v];
                //    }
                //    else {
                //        if (dp[v] + 1 == sec[u] && sec_id[u] < id[v]) {
                //            sec[u] = dp[v] + 1;
                //            sec_id[u] = id[v];
                //        }
                //    }
                //}
                
            }
        }
    }
    return;
}

void get_ans(ll u, ll fa) {
    for (ll i = head[u]; i; i = e[i].next) {
        ll v = e[i].v;
        if (v == fa) {
            continue;
        }
        //更新最段路
        if (res_len[u] == dp[v] + 1 && res[u] == id[v]) {
            //v就处于u的最长路经上
            if (dp[v] > sec2[u] + 1) {
                res[v] = id[v];
                res_len[v] = dp[v];
            }
            else {
                if (dp[v] < sec2[u] + 1) {
                    res[v] = sec2_id[u];
                    res_len[v] = sec2[u] + 1;
                }
                else {
                    res[v] = std::max(sec2_id[u], id[v]);
                    res_len[v] = sec2[u] + 1;
                }
            }
        }
        else {
            if (dp[v] > res_len[u] + 1) {
                res[v] = id[v];
                res_len[v] = dp[v];
            }
            else {
                if (dp[v] < res_len[u] + 1) {
                    res[v] = res[u];
                    res_len[v] = res_len[u] + 1;
                }
                else {
                    res_len[v] = res_len[u] + 1;
                    res[v] = std::max(res[u], id[v]);
                }
            }
        }
        //更新次长路
        if (res_len[u] == res_len[v] + 1 && res[u] == res[v]) {
            //夫节点的最长路和这个节点的最长路重叠
            //使用次长路计算
            if (sec2[u] + 1 > sec[v]) {
                sec2[v] = sec2[u] + 1;
                sec2_id[v] = sec2_id[u];
            }
            else {
                if (sec2[u] + 1 < sec[v]) {
                    sec2[v] = sec[v];
                    sec2_id[v] = sec_id[v];
                }
                else {
                    sec2[v] = sec[v];
                    sec2_id[v] = std::max(sec_id[v], sec2_id[u]);
                }
            }
        }
        else {
            //使用最长路计算
            if (dp[u] + 1 > sec[v]) {
                sec2[v] = dp[u] + 1;
                sec2_id[v] = id[u];
            }
            else {
                if (dp[u] + 1 < sec[v]) {
                    sec2[v] = sec[v];
                    sec2_id[v] = sec_id[v];
                }
                else {
                    sec2[v] = sec[v];
                    sec2_id[v] = std::max(sec_id[v], id[u]);
                }
            }
        }
        get_ans(v, u);
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    cin >> n;

    for (ll i = 0; i < n - 1; ++i) {
        ll u, v;
        cin >> u >> v;
        add_edge(u, v);
        add_edge(v, u);
    }

    solve(1, 0, 1);

    res[1] = id[1];
    res_len[1] = dp[1];
    sec2[1] = sec[1];
    sec2_id[1] = sec_id[1];

    get_ans(1, 0);

    for (ll i = 1; i <= n; ++i) {
        printf("%lld\n", res[i]);
    }

    return 0;
}
