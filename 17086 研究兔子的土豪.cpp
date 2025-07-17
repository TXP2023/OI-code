#include <iostream>
#include <cstring>

using namespace std;
typedef long long ll;

ll m[3][3] = { {1,1,0} ,
				{1,0,0} ,
				{1,0,1} };

ll f[3] = { 1,0,0 };
ll n, mod;

void multi(ll a[3][3], ll b[3]) {
	ll c[3];
	memset(c, 0, sizeof(c));
	for (ll j = 0; j < 3; j++) {
		for (ll k = 0; k < 3; k++) {
			c[j] += a[j][k] * b[k];
			c[j] %= mod;
		}
	}
	for (ll i = 0; i < 3; i++) {
		b[i] = c[i];
	}
	return;
}

void multi(ll a[3][3]) {
	ll b[3][3];
	memset(b, 0, sizeof(b));
	for (ll i = 0; i < 3; i++) {
		for (ll j = 0; j < 3; j++) {
			for (ll k = 0; k < 3; k++) {
				b[i][j] += a[i][k] * a[k][j];
				//b[j][i] %= mod;
				//b[i][j] += a[i][k] * a[k][j];
				b[i][j] %= mod;
			}
		}
	}
	for (ll i = 0; i < 3; i++) {
		for (ll j = 0; j < 3; j++) {
			a[i][j] = b[i][j];
		}
	}
	return;
}

int main() {
	cin >> n;
	mod = 1007;

	while (n) {
		if (n & 1) {
			multi(m, f);
		}
		n /= 2;
		multi(m);
	}
	cout << f[1];
}

/**
* @runId: 47508
* @language: C++ With O2
* @author: txp2024
* @submitTime: 2025-07-06 14:13:37
*/