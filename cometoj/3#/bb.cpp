#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, a[2][N];

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 0; i < 2; ++i) {
			for (int j = 1; j <= n; ++j) {
				scanf("%d", a[i] + j);
			}
		}
		int res = 0;
		int last[2] = {0, 0};
		int cost[2];
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j < 2; ++j) {
				if (a[j][i] == 1) {
					if (last[0] == 0 && last[1] == 0) {
						last[j] = i;
					} else {
						cost[0] = i - 1 - last[j];
						cost[1] = i - last[j ^ 1];
						if (cost[0] < cost[1]) {
							last[j] = i;
							res += cost[0];
						} else {
							last[0] = last[1] = i;
							res += cost[1];
						}
					}
				}
			}
		}
		printf("%d\n", res);	
	}
	return 0;
}
