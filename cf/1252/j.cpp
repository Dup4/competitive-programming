#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 10;
int n, limit, pre[N], g[3], f[N][60];
char s[N];

ll get(ll x, ll y) {
	if (x >= limit || g[0] * 2 <= g[1]) {
		x = min(x, 1ll * limit);
		return x * g[0] + y * g[1];
	}
	if (limit - x >= y * 2) {
		x += y * 2;
		return x * g[0];
	}
	if ((limit - x) % 2 == 0) {
		int need = limit - x;
		y -= need / 2;
		x += need;	
		return x * g[0] + y * g[1];
	} else {
		int need = limit - x - 1;
		y -= need / 2;
		x += need;
		--y;
		return x * g[0] + y * g[1] + max(g[0], g[1]); 
	}
}

int main() {
	while (scanf("%d%d", &n, &limit) != EOF) {
		memset(f, 0, sizeof f);
		for (int i = 0; i < 3; ++i) scanf("%d", g + i);
		scanf("%s", s + 1);
		memset(f, -0x3f, sizeof f);
		f[0][0] = 0;
		pre[0] = 0;
		for (int i = 1; i <= n; ++i) {
			pre[i] = pre[i - 1] + (s[i] == '.');
			for (int j = 0; j <= 50; ++j) {
				f[i][j] = f[i - 1][j];
			}
			if (i > 1 && s[i] == '.' && s[i - 1] == '.') {
				for (int j = 0; j <= 50; ++j) {
					f[i][j] = max(f[i][j], f[i - 2][j] + 1);
				}
			}
			if (i > 2 && s[i] == '.' && s[i - 1] == '#' && s[i - 2] == '.') {
				for (int j = 0; j <= 50; ++j) {
					f[i][j + 1] = max(f[i][j + 1], f[i - 3][j]);
				}
			}
		}
		ll res = 0;
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j <= 50 && f[i][j] >= 0; ++j) {
				ll now = 1ll * j * g[2];
				ll x = pre[i] - (j + f[i][j]) * 2;
				ll y = f[i][j];
				now += get(x, y);
				res = max(res, now);
			}
		}
		printf("%lld\n", res);
	}
	return 0;
}
