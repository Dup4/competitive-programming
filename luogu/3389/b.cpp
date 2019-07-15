#include <bits/stdc++.h>
using namespace std;

#define N 110
#define db double
const db eps = 1e-6;

int n;
db a[N][N], ans[N];
void guess() {
	for (int i = 1; i <= n; ++i) {
		int r = i;
		for (int j = i + 1; j <= n; ++j) {
			if (fabs(a[r][i]) < fabs(a[j][i])) r = j;
		}
		if (fabs(a[r][i]) < eps) {
			puts("No Solution");  
			return;
		}
		swap(a[i], a[r]);
		db div = a[i][i];
		for (int j = 1; j <= n + 1; ++j) {
			a[i][j] /= div;
		}
		for (int j = i + 1; j <= n; ++j) {
			div = a[j][i];
			for (int k = i; k <= n + 1; ++k) {
				a[j][k] -= a[i][k] * div;
			}
		}
		for (int i = n; i >= 1; --i) {
			ans[i] = a[i][n + 1];
			for (int j = i + 1; j <= n; ++j) {
				ans[i] -= a[i][j] * ans[j];
			}
		}
	}
	for (int i = 1; i <= n; ++i) printf("%.2f\n", ans[i]);
}

int main(){
    scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n + 1; ++j) {
			scanf("%lf", a[i] + j);
		}
	}
	guess();
    return 0;
}
