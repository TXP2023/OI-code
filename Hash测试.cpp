#include <iostream>
#include <set>
#include <cstring>
#include <bits/stdc++.h>
#define MAXN  10001
#define MAX_LENGTH	1505
typedef  long long int ll;
template<uint64_t _Base, uint64_t _Mod>
class Hash {
public:
	inline void get_hash(const char* str) {
		ll length = strlen(str + 1);
		for (size_t i = 1; i <= length; i++) {
			hash_[i] = (hash_[i - 1] * _Base + str[i] - 'a' + 1) % _Mod;
		}
		sum = hash_[length];
	}

	uint64_t get_sum() {
		return sum;
	}

private:
	uint64_t hash_[MAX_LENGTH], sum;
};

Hash<131, UINT64_MAX> hash2;
Hash<233, UINT64_MAX> hash1;
std::set<uint64_t> set1, set2;
ll n, ans;

int main() {
	std::cin >> n;

	for (size_t i = 0; i < n; i++) {
		char str[MAX_LENGTH];
		scanf("%s", str + 1);
		hash1.get_hash(str);
		hash2.get_hash(str);
		if (!set1.count(hash1.get_sum()) && !set2.count(hash2.get_sum())) {
			++ans;
		}
		set1.insert(hash1.get_sum());
		set2.insert(hash2.get_sum());
		
	}
	printf("%lld\n", ans);
}

