#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 10;
int n, a[N][N], res[N]; 

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				scanf("%d", a[i] + j);
			}
		}
		if (n == 2) {
			printf("%d %d\n", 1, a[1][2] - 1);
		} else {
			res[2] = (a[1][2] - a[1][3] + a[2][3]) / 2;
			for (int i = 1; i <= n; ++i) if (i != 2)
				res[i] = a[2][i] - res[2];
			for (int i = 1; i <= n; ++i)
				printf("%d%c", res[i], " \n"[i == n]);
		}
	}
	return 0;
}
