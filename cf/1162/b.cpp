#include <bits/stdc++.h>
using namespace std;

#define N 110
int n, m, a[N][N], b[N][N];

void read(int a[][N]) {
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			scanf("%d", &a[i][j]);
		}
	}
}

bool check(int a[][N]) {
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			int x = a[i][j];
			if (i > 1) {
				if (x <= a[i - 1][j]) {
					return false;
				}
			}
			if (j > 1) {
				if (x <= a[i][j - 1]) {
					return false;
				}
			}
		}
	}
	return true;
}

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		read(a), read(b);
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				if (a[i][j] > b[i][j]) {
					swap(a[i][j], b[i][j]);
				}
			}
		}
		if (check(a) && check(b)) {
			puts("Possible");
		} else {
			puts("Impossible");
		}
	}
	return 0;
}
