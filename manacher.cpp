#include <iostream>
#include <cstring>

#define MAX_LENGTH	(size_t)(1.1e7 + 5)

using ll = long long int;

char str[MAX_LENGTH * 2 + 5];
ll length;

inline ll manacher() {
	ll radius[MAX_LENGTH * 2 + 5], res = 0;
	memset(radius, 0, sizeof(radius));
	radius[1] = 1;
	for (size_t i = 2, r = 1, l; i <= length; i++) {
		if (i <= r) {
			radius[i] = std::min(
				(size_t)radius[r - i + l],
				r - i + 1
			);
		}
		while (str[i + radius[i]] == str[i - radius[i]]) {
			++radius[i];
		}
		if (i + radius[i] - 1 >= r) {
			r = i + radius[i] - 1, l = i - radius[i] + 1;
		}
		res = std::max(res, radius[i]);
	}
	return res;
}

int main() {
#ifdef _FREOPEN
	freopen("input.txt", "r", stdin);
#endif // _FREOPEN
	str[length] = '$';
	str[++length] = '#';
	while (~(str[++length] = getchar())) {
		str[++length] = '#';
	}
	str[length] = '@';
	
	printf("%lld\n", manacher() - 1);
}