#include <iostream>

#define TRIE_SIZE (size_t)(1e6+5)
using ll = long long int;

struct trie_node {
	ll cnt;
	size_t index[26];
};

trie_node trie[TRIE_SIZE];
ll n, m, trie_cnt = 0;

void insert(size_t pos, const char* str) {
	
	if (str[1] == '\0') {
		++trie[pos].cnt;
		return;
	}
	if (!trie[pos].index[str[1] - 'a']) {
		trie[pos].index[str[1] - 'a'] = ++trie_cnt;
	}
	insert(trie[pos].index[str[1] - 'a'], str + 1);
	return;
}

ll query(size_t pos, const char* str) {
	if (str[1] == '\0') {
		return trie[pos].cnt;
	}
	if (!trie[pos].index[str[1] - 'a']) {
		return trie[pos].cnt;
	}
	return query(trie[pos].index[str[1] - 'a'], str + 1) + trie[pos].cnt;
}

int main() {
#ifdef _FREOPEN
	freopen("input.txt", "r", stdin);
#endif // _FREOPEN
	std::cin >> n >> m;

	for (size_t i = 1; i <= n; i++) {
		char str[TRIE_SIZE];
		scanf("%s", str + 1);
		insert(0, str);
	}

	for (size_t i = 1; i <= m; i++) {
		char str[TRIE_SIZE];
		scanf("%s", str + 1);
		printf("%lld\n", query(0, str));
	}
	return 0;
}