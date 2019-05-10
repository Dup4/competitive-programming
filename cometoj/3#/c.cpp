#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 5010
const int p = int(1e9) + 7;
int n, m, a[N];
int f[2][N], g[2][N][30];
int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}
int bit[30]; 
int vis[N * N];
void up(int &x, int y) {
	x += y;
	if (x >= p) {
		x -= p;
	}
}
int add(int x, int y, int p) {
	x += y;
	if (x >= p) {
		x -= p;
	}
	return x;
}

int main() {
	bit[0] = 1;
	vis[1] = 1; 
	for (int i = 1; i < 30; ++i) {
		bit[i] = bit[i - 1] << 1;
		if (bit[i] >= N * N) {
			break;
		}
		vis[bit[i]] = i + 1; 
	}
	while (scanf("%d%d", &n, &m) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		f[0][0] = 1;
		for (int i = 1; i <= n; ++i) {
			int now = i & 1;
			int pre = now ^ 1;
			for (int j = 0; j < m; ++j) {
				f[now][j] = f[pre][j];
			}
			for (int j = 0; j < m; ++j) {
				up(f[now][add(j, a[i], m)], f[pre][j]);
			}
		}
		g[0][0][0] = 1;
		g[1][0][0] = 1;
		for (int i = 1; i <= n; ++i) {
			int now = i & 1;
			int pre = now ^ 1;
			for (int j = 0; j < m; ++j) {
				for (int k = 1; k < 13; ++k) {
					g[now][j][k] = g[pre][j][k];
				}
			}
			for (int j = 0; j < m; ++j) {
				for (int k = 1; k < 13; ++k) {
				    up(g[now][j][k], g[pre][add(j, m - a[i], m)][k - 1]);	
				}
			}
		}
		int res = f[n & 1][0];
		int now = n & 1;
		for (int i = 1; i < m; ++i) {
			int lcm = i * m / gcd(i, m);
			int need = vis[lcm / i] - 1; 
			if (need != -1) {
				up(res, f[now][i]);
				for (int j = 0; j <= need; ++j) {
					up(res, p - g[now][i][j]);
				}
			}
		}
		up(res, p -1);
		printf("%d\n", res);
	}
	return 0;
}
