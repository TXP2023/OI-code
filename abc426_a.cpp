#include <bits/stdc++.h>

using namespace std;

int main() {
    char str1[10], str2[10], ch1, ch2;
    cin >> str1 >> str2;
    ch1 = str1[0];
    ch2 = str2[0];
    if (ch1 == ch2) {
        cout << "Yes" << '\n';
        return 0;
    }
    switch (ch1) {
    case 'O':
        if (ch2 == 'O') {
            cout << "Yes" << '\n';
        }
        else {
            cout << "No" << '\n';
        }
        break;
    case 'S':
        if (ch2 == 'L') {
            cout << "No" << '\n';
        }
        else {

            cout << "Yes" << '\n';
        }
        break;
    case 'L':
        cout << "Yes" << '\n';
        break;
    }
}
