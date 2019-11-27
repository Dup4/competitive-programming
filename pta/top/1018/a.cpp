#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 10, mod = 1e9 + 7;
char s[N];
void chadd(ll &x, ll y) {
	x += y;
	while (x >= mod) x -= mod;
	while (x < 0) x += mod;
}

int main() {
	while (scanf("%s", s + 1) != EOF) {
		ll res = 0, pre = 0, cnt = 0;
		for (int i = 1; s[i]; ++i) {
			int num = s[i] - '0';
			pre = pre * 10 % mod;
			if (num) ++cnt;
			chadd(pre, cnt * num);
			chadd(res, pre);
		}
		printf("%lld\n", res);
	}
	return 0;
}
