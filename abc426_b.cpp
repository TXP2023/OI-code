#include <iostream>
#include <string>

std::string s;

int cnt[26];

int main() {
    std::cin >> s;
    for (int i = 0; i < s.size(); ++i) {
        cnt[s[i] - 'a']++;
    }
    for (int i = 0; i < 26; ++i) {
        if (cnt[i] == 1) {
            std::cout << char(i + 'a') << '\n';
            return 0;
        }
    }
    return 0;
}
