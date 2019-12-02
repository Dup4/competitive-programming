#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	int n; scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		ll x; scanf("%lld", &x);
		if (i > 1) {
			if (x & 1) puts("0");
			else puts("1");
		}
	}	
	return 0;
}
