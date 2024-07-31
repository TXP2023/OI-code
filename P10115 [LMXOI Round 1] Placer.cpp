#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

typedef long long ll;

std::vector<ll> v, head, c;
std::vector<ll> dp;
std::string str;
ll n;

int main() {
    freopen(".in", "r", stdin);
    std::cin >> n;      // ��ȡ�ַ�������
    std::cin >> str;    // ��ȡ�����ַ���

    v.resize(n + 1);
    head.resize(n + 1, 0);

    // ��ȡÿ������
    for (ll i = 1; i <= n; i++) {
        std::cin >> v[i];  // ʹ�� cin ��ȡÿ������
    }

    // �����������
    for (ll i = 1; i <= n; i++) {
        if (i > 1 && str[i - 1] == ')' && str[i - 2] == '(') {
            head[i - 1] = i - 2;  // ������Ե�����λ��
        }
    }

    // ���� head ����
    for (ll i = 1; i < n; i++) {
        if (str[i - 1] == '(' || head[i - 1]) {
            continue;
        }
        ll j = i - 2;
        while (j >= 0 && head[j] != 0) {
            j = head[j] - 1;
            if (j >= 0 && str[j] == '(') {
                head[i - 1] = j;  // ���� head ����
                break;
            }
        }
    }

    ll _max = 0;
    dp.resize(n + 1, 0);
    c.resize(n + 1, -0x3f3f3f3f);  // ʹ�ø�������ʼ��

    // ��̬�滮����
    for (ll i = 1; i <= n; i++) {
        dp[i] = _max;  // ��ʼ�� dp[i]
        if (head[i - 1] != 0) // �����ǰ���������
        {  
            c[i] = std::max(dp[head[i - 1]] - v[head[i - 1] + 1], c[head[i - 1]]);  // ���� c
            dp[i] = std::max(_max, c[i] + v[i]);  // ���� dp[i]
            _max = std::max(_max, dp[i]);  // �������ֵ
        }
    }

    std::cout << dp[n] << std::endl;  // ������ս��
    return 0;
}
