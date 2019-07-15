#include <bits/stdc++.h>
using namespace std;

#define db double
#define N 110
db a[N][N], v[N];
int n, w[N];

void gauss() {
	db eps = 1e-6;
	for (int i = 1; i <= n; ++i) {
		int p = 0;
		db mx = 0;
		for (int j = 1; j <= n; ++j) {
			if (fabs(a[i][j]) - eps > mx) {
				mx = fabs(a[i][j]); p = j;
			}
		}
		if (!p) {
			printf("No Solution");
			return;
		}
		w[i] = p;
		for (int j = 1; j <= n; ++j) {
			if (i != j) {
				db t = a[j][p] / a[i][p];
				for (int k = 1; k <= n + 1; ++k) {
					a[j][k] -= a[i][k] * t;
				}
			}
		}
	}
	for (int i = 1; i <= n; ++i) v[w[i]] = a[i][n + 1] / a[i][w[i]];
	for (int i = 1; i <= n; ++i) printf("%.2f\n", v[i]);
	//v[i]保存的是未知量
}

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n + 1; ++j) {
				scanf("%lf", a[i] + j);
			}
		}
		gauss();
	}
	return 0;
}
