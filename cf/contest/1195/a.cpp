#include <bits/stdc++.h>
using namespace std;

#define N 1010
int n, k, a[N];

int main() {
	while (scanf("%d%d", &n, &k) != EOF) {
		memset(a, 0, sizeof a);
		for (int i = 1, x; i <= n; ++i) {
			scanf("%d", &x);
			++a[x];
		}
		int res = 0;
		int num = n / 2 + (n & 1);
		for (int i = 1; i <= k; ++i) {
			while (a[i] >= 2 && num > 0) {
				--num;
				a[i] -= 2;
				res += 2;
			}
		}
		printf("%d\n", res + num); 
	}
	return 0;
}
