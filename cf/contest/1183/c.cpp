#include <bits/stdc++.h>
using namespace std;

int k, n, a, b;

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d%d", &k, &n, &a, &b);
		--k;
		int tot = k / b;
		if (tot < n) {
			puts("-1");
			continue;
		}
		int gap = a - b;
		k -= n * b;
		printf("%d\n", min(k / gap, n));
	}
	return 0;
}
