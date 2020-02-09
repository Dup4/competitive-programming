#include <bits/stdc++.h>
using namespace std;
using db = double;
const int N = 1e6 + 10;
char s[N]; int n, vis[220]; db f[N];

int main() {
	for (auto &it : "aeiouy") {
		vis[it] = 1;
	}
	while (scanf("%s", s + 1) != EOF) {
		n = strlen(s + 1);
		f[0] = 0;
		for (int i = 1; i <= n; ++i) {
			f[i] = f[i - 1];
			f[i] += 1.0 / i;
		}
		db res = 0;
		db cur = 0;
		for (int i = 1; i <= n; ++i) {
			cur += f[n - i + 1];
			cur -= f[i - 1];
			if (vis[s[i]]) res += cur;
		}
		res /= 1ll * n * (n + 1) / 2;
		printf("%.10f\n", res);
	}
	return 0;
}
