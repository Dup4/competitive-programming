#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
#define MAXL 62
int n, res;
ll a[N];

struct LinearBasis {
	ll a[MAXL + 1];
	LinearBasis() {
		fill(a, a + MAXL + 1, 0);
	}
	void insert(ll t) {
		for (int j = MAXL; j >= 0; --j) {
			if (!(t & (1ll << j))) continue;
			if (a[j]) t ^= a[j];
			else {
				for (int k = 0; k < j; ++k) {
					if (t & (1ll << k)) {
						t ^= a[k];
					}
				}
				for (int k = j + 1; k <= MAXL; ++k) {
					if (a[k] & (1ll << j)) {
						a[k] ^= t;
					}
				}
				a[j] = t;
				++res;
				return;
			}
		}
	}
}li;

int main() {
	while (scanf("%d", &n) != EOF) {
		res = 0;
		li = LinearBasis();
		for (int i = 1; i <= n; ++i) {
			scanf("%lld", a + i);
			li.insert(a[i]);
		}
		puts(res & 1 ? "First" : "Second");
	}
	return 0;
}
