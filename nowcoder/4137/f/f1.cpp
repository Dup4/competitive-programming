#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 5e3 + 5;
int n, a[N][N], P, D, b[N], c[N]; 
ll A, B, C;

inline int sqr(int x) { return 1ll * x * x % P; }

int main() {
	while (scanf("%d%lld%lld%lld%d%d", &n, &A, &B, &C, &P, &D) != EOF) {
		for (int i = 1; i <= n; ++i) {
			for (int j = i + 1; j <= n; ++j) { 
				a[i][j] = (A * sqr(i + j) + B * sqr(i - j) + C) % P > D; 
			}
		}
		memset(b, 0, sizeof b);
		memset(c, 0, sizeof c); 
		ll res = 0;
		for (int i = n - 1; i >= 1; --i) {
			for (int j = i + 2; j <= n; ++j) {
				if (a[i][j] != a[i + 1][j]) {
					if (a[i][j]) {
						for (int k = j + 1; k <= n; ++k) {
							b[k] += a[j][k];
							c[k] -= a[j][k] ^ 1; 
						}
					} else {
						for (int k = j + 1; k <= n; ++k) {
							c[k] += a[j][k] ^ 1;
							b[k] -= a[j][k];
						}
					}
				}
			}
			for (int j = i + 2; j <= n; ++j) {
				if (a[i][i + 1]) b[j] += a[i + 1][j];
				else c[j] += a[i + 1][j] ^ 1;
			}
			for (int j = i + 2; j <= n; ++j) {
				if (a[i][j]) res += b[j];
				else res += c[j];
			}	
		}
		printf("%lld\n", res);
	}
	return 0;
}
