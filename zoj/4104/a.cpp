#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, a[N], b[N];

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			b[i] = a[i];
		}
		sort(b + 1, b + 1 + n);
		int pos = n;
		for (int i = n; i >= 1; --i) {
			if (a[i] == b[pos]) {
				--pos;
			}
		}
		printf("%d\n", pos);
	}
	return 0;
}
