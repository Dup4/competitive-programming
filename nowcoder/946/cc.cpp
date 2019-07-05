#include <bits/stdc++.h>
using namespace std;

#define INF 0x3f3f3f3f
#define N 2000010
#define pii pair <int, int>
#define fi first
#define se second
int n, m, a[N], f[N], g[N];
int b[2100], c[2100]; 

int main() {
	while (scanf("%d", &n) != EOF) {
		m = n * (n + 1);
		for (int i = 1; i <= m; ++i) scanf("%d", a + i);
		for (int i = 1; i <= 2 * n; ++i) b[i] = INF;
		b[0] = -1;
		for (int i = 1; i <= m; ++i) {  
			int pos = upper_bound(b + 1, b + 1 + 2 * n, a[i]) - b - 1;
			f[i] = pos + 1;
			g[i] = c[pos];
			if (a[i] < b[f[i]]) {
				b[f[i]] = a[i];
				c[f[i]] = i;
			} 			
		}
		if (b[2 * n] == INF) puts("IMPOSSIBLE");
		else {
			vector <int> res;
			int it = c[2 * n];
			while (it) {
				res.push_back(it);
				it = g[it];
			}
			for (int i = 2 * n - 1; i >= 0; --i) printf("%d%c", res[i], " \n"[!i]);
		}
	}
	return 0;
}
