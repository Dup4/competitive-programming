#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 110
const ll p = 1e9 + 7;  
int n, T;
int t[N], g[N];
ll f[20][20][20];
	
void add(ll &x, ll y) {
	x += y;
	if (x >= p) {
		x -= p;
	}
}

int main() {
	memset(f, 0, sizeof f);
	f[1][0][0] = 1;
	f[0][1][0] = 1;
	f[0][0][1] = 1;
	for (int i = 0; i <= 15; ++i) {
		for (int j = 0; j <= 15; ++j) {
			for (int k = 0; k <= 15; ++k) {
				if (i + j + k >= 2) {
					int tot = i + j + k;
					if (i > 0 && j > 0 && k > 0) {
					
					} else if (i > 0 && j > 0) {
					
					} else if (i > 0 && k > 0) {
						
					} else if (j > 0 && k > 0) {
					
					} else if (i > 0) {
						add(f[i][j][k], f[i - 1])
					} else if (j > 0) {
						
					} else if (k > 0) {
						
					}
				}
			}
		}
	}
	while (scanf("%d%d", &n, &T) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d%d", t + i, g + i);
		}
		ll res = 0;
		for (int i = 0; i < (1 << n); ++i) {
			int tot = 0;
			int x[4] = {0, 0, 0};
			for (int j = 1; j <= n; ++j) {
				if ((i >> (j - 1)) & 1) {
					tot += t[j];
					++x[g[j]]; 
				}
			}
			if (tot == T) {
				add(res, f[x[1]][x[2]][x[3]]);
			}
		}
		printf("%lld\n", res); 
	}
	return 0;
}
