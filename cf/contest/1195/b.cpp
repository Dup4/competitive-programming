#include <bits/stdc++.h>
using namespace std;

#define ll long long
ll n, k;

ll f(int x) {
	return 1ll * x * (x + 1) / 2;
}

int main() {
	while (scanf("%lld%lld", &n, &k) != EOF) {
		for (int i = 1; i <= n; ++i) {
			if (f(i) - (n - i) == k) {
				printf("%lld\n", n - i);
				break;
			}
		}
	}
	return 0;
}
