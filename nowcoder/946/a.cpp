#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 200010
const ll p = 1e9 + 7;
int n;
struct node {
	ll a, b;
	node() {}
	void scan() {
		scanf("%lld%lld", &b, &a);
	}
	bool operator < (const node &other) const {
		return a * other.b > b * other.a;
	}
}a[N];
ll qmod(ll base, ll n) {
	ll res = 1;
	while (n) {
		if (n & 1) {
			res = res * base % p;
		}
		base = base * base % p;
		n >>= 1;
	}
	return res;
}

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			a[i].scan();
		}
		sort(a + 1, a + 1 + n);
		for (int i = 1; i <= n; ++i) {
			printf("%lld\n", a[i].a * qmod(a[i].b, p - 2) % p);
		}
	}
	return 0;
}
