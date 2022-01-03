#include <bits/stdc++.h>
using namespace std;

#define N 200010
int n, k, a[N];

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &k);
		int sum = 0;
		for (int i = 1; i <= n; ++i) scanf("%d", a + i), a[i] %= 2, sum += a[i]; 
		vector <int> vec;
		if (k == 1) {
			if (sum & 1) { 
				puts("YES");
				printf("%d\n", n);
			} else {
				puts("NO");
			}
			continue;
		} 
		if (sum < k || (sum - k) % 2) {
			puts("NO");
		} else {
			puts("YES");
			int out = 0;
			for (int i = 1; i < n; ++i) {
				if (a[i]) {
					printf("%d ", i);
					++out;
				}
				if (out == k - 1) break;
			}
			printf("%d\n", n);
		}
	}
	return 0;
}
