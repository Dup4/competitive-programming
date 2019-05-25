#include <bits/stdc++.h>
using namespace std;

#define ll long long
int main() {
	int r, D; ll x;
	while (scanf("%d%d%lld", &r, &D, &x) != EOF) {
		for (int i = 1; i <= 10; ++i) {
			x = 1ll * r * x - D;
			printf("%lld\n", x);
		}
	}
	return 0;
}
