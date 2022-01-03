#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, s, t;
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d", &n, &s, &t);
		int res = max(n - s + 1, n - t + 1);
		printf("%d\n", res);
	}
	return 0;
}
