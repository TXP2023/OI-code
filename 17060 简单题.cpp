#include <iostream>
using namespace std;
signed main() {
	int n;
	cin >> n;
	if (n == 0) {
		cout << 1;
		return 0;
	}
	cout << 5;
	for (int i = 1; i <= n - 1; i++) {
		cout << 0;
	}
	cout << 5;
	for (int i = 1; i <= n - 1; i++) {
		cout << 0;
	}
}