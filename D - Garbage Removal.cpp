#include <iostream>
#include <vector>
using namespace std;

using Vector = std::vector<std::vector<int>>;

int main() {
	int h, w, n;
	cin >> h >> w >> n;
	Vector a(h + 1, vector<int>());
	Vector b(w + 1, vector<int>());
	vector<bool> ux(h + 1), uy(w + 1); // Whether the query for each row or column is already given
	vector<bool> used(n); // Whether each trash is already removed
	for (int i = 0; i < n; i++) {
		int x, y;
		cin >> x >> y;
		a[x].push_back(i);
		b[y].push_back(i);
	}
	int q;
	cin >> q;
	while (q--) {
		int t;
		cin >> t;
		if (t == 1) {
			int x;
			cin >> x;
			if (ux[x]) cout << 0 << '\n';
			else {
				int ans = 0;
				for (int e : a[x]) {
					if (!used[e]) {
						used[e] = true;
						ans++;
					}
				}
				ux[x] = true;
				cout << ans << '\n';
			}
		}
		else {
			int y;
			cin >> y;
			if (uy[y]) cout << 0 << '\n';
			else {
				int ans = 0;
				for (int e : b[y]) {
					if (!used[e]) {
						used[e] = true;
						ans++;
					}
				}
				uy[y] = true;
				cout << ans << '\n';
			}
		}
	}
}
