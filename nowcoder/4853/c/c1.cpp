#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int mod = 1e9 + 7; 
constexpr int N = 1e3 + 10; 
int n, K, pre[330]; ll f[N][N]; char s[N];

int main() {
	scanf("%d%d", &n, &K);
	scanf("%s", s + 1);
	memset(f, 0, sizeof f);
	memset(pre, -1, sizeof pre);
	f[0][0] = 1;
	for (int i = 1; i <= n; ++i) {
		int ch = s[i] - 'a';
		for (int j = 0; j < i; ++j) {
			if (pre[ch] == -1) {
				(f[i][j + 1] += f[i - 1][j + 1] + f[i - 1][j]) %= mod;
			} else {
				(f[i][j + 1] += f[i - 1][j + 1] + f[i - 1][j] - f[pre[ch] - 1][j] + mod) %= mod;
			}
		}
		f[i][0] = 1;
		pre[ch] = i;
	}
	printf("%lld\n", f[n][K]);
	return 0;
}
