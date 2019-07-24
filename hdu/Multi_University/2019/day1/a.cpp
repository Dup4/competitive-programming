#include <bits/stdc++.h>
using namespace std;

#define N 110
#define pii pair <int, int>
#define fi first
#define se second
int n, m;
vector <vector<pii>> vec;
int f[2][N][N][N];

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		vec.clear(); vec.resize(n + 1);
		for (int i = 1, l, r, x; i <= m; ++i) {
			scanf("%d%d", &l, &r, &x);
			vec[r].push_back(pii(l, x));
		}
		f[0][0][0][0] = 1;
		for (int i = 1, p = 1; i <= n; ++i, p ^= 1) {
			for (int j = 0; j <= n; ++j) {
				for (int k = 0; k <= n; ++k) {
					for (int t = 0; t <= n; ++t) {
						f[p][j][k][t] = 0;
					}
				}
			}
			for (int j = 0; j < i; ++j) {
				for (int k = 0; k <= j; ++k) {
					
				}
			}
		}
		
	}
	return 0;
}
