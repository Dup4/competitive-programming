#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int n, a[N], b[N];

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			b[i] = a[i];
		}
		sort(b + 1, b + 1 + n);
		for (int i = 1; i <= n; ++i) {
			printf("%d%c", (int)(upper_bound(b + 1, b + 1 + n, a[i]) - b - 1), " \n"[i == n]);
		}
	}
	return 0;
}
