#include <bits/stdc++.h>
using namespace std;

#define N 200010
int n, a[N];

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		sort(a + 1, a + 1 + n);
		n = unique(a + 1, a + 1 + n) - n - 1;
		int res = a[n];
		for (int i = 1; i <= n; ++i) {
			res = 
		}
	}
	return 0;
}
