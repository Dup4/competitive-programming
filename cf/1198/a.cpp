#include <bits/stdc++.h>
using namespace std;
#define debug(...) { printf("#  "); printf(__VA_ARGS__); puts(""); }
const int N = 1e6 + 10;
int n, a[N], b[N], I;

struct Hash {
	int a[N], cnt;
	Hash() {
		cnt = 0;
	}
	void add(int x) {
		a[++cnt] = x;
	}
	void work() {
		sort(a + 1, a + 1 + cnt);
		cnt = unique(a + 1, a + 1 + cnt) - a - 1;
	}
	int get(int x) {
		return lower_bound(a + 1, a + 1 + cnt, x) - a;
	}
}hs;

int main() {
	while (scanf("%d%d", &n, &I) != EOF) {
		hs = Hash();
		memset(b, 0, sizeof b);
		for (int i = 1; i <= n; ++i) scanf("%d", a + i), hs.add(a[i]);
		hs.work();
		for (int i = 1; i <= n; ++i) a[i] = hs.get(a[i]);
		for (int i = 1; i <= n; ++i) ++b[a[i]];
		for (int i = 1; i <= hs.cnt; ++i) b[i] += b[i - 1];
		I *= 8;
		int k = 0;
		while (1ll * (k + 1) * n <= I) {
			++k;
			if (k >= 64) break;
		}
		k = min(k, 30);
		int Max = 1ll << k;
		int res = 0; 
		for (int i = 0; i <= hs.cnt; ++i) {
			res = max(b[min(hs.cnt, i + Max)] - b[i], res);
		}
		printf("%d\n", n - res); 
	}
	return 0;
}
