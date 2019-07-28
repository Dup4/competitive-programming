#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, k, a[N], b[N];

int main() {
	while (scanf("%d%d", &n, &k) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		for (int i = 1; i <= n; ++i) b[i] = 0;
		int res = 0;
		for (int i = 2; i <= n; ++i) {
			if (b[i - 1]) continue; 
			if (abs(a[i] - a[i - 1]) < k) {
				++res;
				b[i] = 1; 
			}
		}
		printf("%d\n", res);
	}
	return 0;
}
