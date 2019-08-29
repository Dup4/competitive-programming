#include <bits/stdc++.h>
using namespace std;

#define db double
const int N = 70;
int n, g, f[N][1200], a[N];

int main() {
	while (scanf("%d%d", &n ,&g) != EOF) {
		for (int i = 1; i <= n; ++i)
			scanf("%d", a + i), a[i] -= 10;
		memset(f, 0, sizeof f);
		f[0][0] = 1;
		for (int _ = 1; _ <= n; ++_) 
			for (int i = _; i >= 1; --i) {
				for (int j = g + 10; j >= 0; --j) {
					if (j >= a[_]) {
						f[i][j] |= f[i - 1][j - a[_]];
					}
				}
			}
		int A = 10000000, B = 1; 
		for (int i = 0; i <= n; ++i) {
			for (int j = 0; j <= g + 10; ++j) {
				if (f[i][j]) {
					int a = g - j, b = i + 1;
				    if (j + 10 * (i + 1) >= g && j + 5 * (i + 1) <= g) {
						if (a * B < b * A) {
							A = a;
							B = b;
						}
					}
				}
			}
		}
		if (A == 10000000) puts("impossible");
		else printf("%.7f\n", 10 - A * 1.0 / B);
	}
	return 0;
}
