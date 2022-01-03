#include <bits/stdc++.h>
using ll = long long;
using namespace std;

const int mod = 1e9 + 7;
int n;

inline void chadd(ll &x, ll y) {
	x += y;
	while (x >= mod) x -= mod;
	while (x < 0) x += mod;
}

struct node {
	ll a[4][4];
	node() {}
	ll* operator[] (int x) { return a[x]; }
	void init() { memset(a, 0, sizeof a); }
	node operator * (const node &other) const {
		node res = node();
		res.init();
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				for (int k = 0; k < 4; ++k) {
					chadd(res.a[i][j], a[i][k] * other.a[k][j] % mod);
				}
			}
		}
		return res;
	}
};

node qpow(node base, node res, ll n) {
	while (n) {
		if (n & 1) res = res * base;
		base = base * base;
		n >>= 1;	
	}
	return res;
}

ll gao() {
	if (n == 1) return 2;
	if (n == 2) return 24;
	node base = node();
	base.init();
	base[0][0] = 6, base[0][1] = 1, base[0][2] = 0, base[0][3] = 4;
	node res = node();
	res.init();
	res[0][0] = 2, res[0][1] = 1;
	res[1][0] = 4, res[1][2] = 2;
	res[2][2] = 2;
	res[3][0] = 1, res[3][3] = 2;
	swap(res, base);
	res = qpow(base, res, n - 2);	
	return 4ll * (res[0][0] + 2ll * res[0][2] % mod) % mod;
}

int main() {
	scanf("%d", &n);
	ll res = gao();
	res = (res % mod + mod) % mod;
	printf("%lld\n", res);
	return 0;
}
