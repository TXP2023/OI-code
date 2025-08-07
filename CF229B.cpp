#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <set>

using namespace std;
const int maxn = int(1e5 + 5);

using ll = long long int;

struct node {
	int v, w;
	bool operator<(const node& ano) const {
		return w > ano.w;
	}
};
std::set<int> wait[maxn];
vector <node> G[maxn];
int dis[maxn];
priority_queue <node> q;

int extra(int x, int t) {
	ll temp = 0;
	while (wait[x].count(t)) {
		++temp;
		++t;
	}
	return temp;
}
int read() {
	int igt = 0, sgn = 1;
	char c = getchar();
	while (c > '9' or c < '0') {
		if (c == '-') {
			sgn = -1;
		}
		c = getchar();
	}
	while (c <= '9' and c >= '0') {
		igt = (igt << 3) + (igt << 1) + c - '0';
		c = getchar();
	}
	return igt * sgn;
}

bool vis[maxn];
int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
#endif // _DEBUG

	int n = read(), m = read();
	for (int i = 1; i <= m; i++) {
		int u = read(), v = read(), w = read();
		G[u].push_back({ v,w });
		G[v].push_back({ u,w });
	}
	for (int i = 1; i <= n; i++) {
		int num = read();
		for (int j = 1; j <= num; j++) {
			ll temp = read();
			wait[i].insert(temp);
		}
	}
	//memset(dis, 0x3f, sizeof(dis));
	std::fill(dis, dis + n + 1, INT_MAX);
	dis[1] = 0;
	q.push({ 1,0 });
	while (!q.empty()) {
		int u = q.top().v;
		ll temp = 0 + extra(u, dis[u]);
		q.pop();
		if (vis[u]) {
			continue;
		}
		vis[u] = 1;
		for (int i = 0; i < G[u].size(); i++) {
			int tmp = dis[u] + G[u][i].w + temp;
			if (dis[G[u][i].v] > tmp) {
				dis[G[u][i].v] = tmp;
				q.push({ G[u][i].v,dis[G[u][i].v] });
			}
		}
	}
	if (dis[n] == INT_MAX) {
		cout << "-1";
		return 0;
	}
	cout << dis[n];
	return 0;
}