#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e3 + 10;
int n, A, B, K, a[N][N];

bool ok(int x) {
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (min({a[i][j], a[i][A] + a[B][j] + x, a[i][B] + a[A][j] + x}) + x >= K)
				return false;
		}
	}
	return true;
//	for (int i = 1; i <= n; ++i) {
//		for (int j = 1; j <= n; ++j) {
//			f[i][j] = a[i][j];
//		}
//	}
//	f[A][B] = f[B][A] = min(f[A][B], x);
//	int Max = 0;
//	for (int i = 1; i <= n; ++i) {
//		for (int j = 1; j <= n; ++j) {
//			Max = max(Max, f[i][j]);
//
//		}
//	}
//	cout << x << " " << Max << endl;
//	return Max + x < K;
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) 
		for (int j = 1; j <= n; ++j)
			scanf("%d", a[i] + j);
	scanf("%d%d%d", &A, &B, &K);
	++A, ++B;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			for (int k = 1; k <= n; ++k) {
				a[j][k] = min(a[j][k], a[j][i] + a[i][k]);
			}
		}
	}
	int l = 0, r = K - 1, res = -1;
	while (r - l >= 0) {
		int mid = (l + r) >> 1;
		if (ok(mid)) {
			l = mid + 1;
			res = mid;
		} else {
			r = mid - 1;
		}
	}
//	printf("%d %d %d\n", ok(15), ok(16), ok(17));
	printf("%d\n", res);
	return 0;
}
