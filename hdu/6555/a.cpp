#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
	int T; scanf("%d", &T);
	for (int kase = 1; kase <= T; ++kase) {
		printf("Case %d: ", kase);
		int n; scanf("%d", &n);
		ll res = 0;
		for (int i = 1, j; i <= n; i = j + 1) {
			j = n / (n / i);
			res += (j - i + 1) % 2 * (n / i) % 2;
			res %= 2;
		}
		puts(res ? "odd" : "even");
	}
	return 0;
}
