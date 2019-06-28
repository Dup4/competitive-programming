#include <bits/stdc++.h>
using namespace std;

#define N 510
int n, a[N];
int f[N], g[N], h[N];

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		memset(f, 0, sizeof f);
		memset(h, 0, sizeof h);
		for (int i = 1; i <= n; ++i) {
			g[i] = 0;
			f[i] = a[i];
			for (int j = i - 1; j >= 1; --j) {
				if (a[i] >= a[j] && f[j] + a[i] > f[i]) {
					f[i] = f[j] + a[i];
					g[i] = j;
				}
			}
		}
		int Max = *max_element(f + 1, f + 1 + n);  
		int res = Max;
		for (int i = n; i >= 1; --i) {
			if (f[i] == Max) {
				h[i] = 1;
				int it = i;
				while (g[it] >= 1) {
					it = g[it];
					h[it] = 1;
				}
				break;
			}
		}
		memset(f, 0, sizeof f);
		for (int i = 1; i <= n; ++i) if (!h[i]) {
			for (int j = i - 1; j >= 1; --j) if (!h[j]) {
				if (a[i] >= a[j] && f[j] > f[i]) {
					f[i] = f[j];
				}
			}
			f[i] += a[i];
		}
		printf("%d\n", res + *max_element(f + 1, f + 1 + n));
	}
	return 0;
}
