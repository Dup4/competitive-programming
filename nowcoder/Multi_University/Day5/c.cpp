#include <bits/stdc++.h>
using namespace std;

#define ll long long
ll n, x0, a, b, p, v;
int q;

ll qmod(ll base, ll n, ll p) {
	ll res = 1;
	while (n) {
		if (n & 1) res = res * base % p;
		base = base * base % p;
		n >>= 1;
	}
	return res;
}

void out(ll x) {
	if (x <= n) printf("%lld\n", x);
	else puts("-1");
}

struct BSGS {
	static const int MOD = 76543;
	int hs[MOD], head[MOD], Next[MOD], id[MOD], top;
	void insert(int x, int y) {
		int k = x % MOD;
		hs[top] = x; id[top] = y; Next[top] = head[k], head[k] = top++;
	}
	int find(int x) {
		int k = x % MOD;
		for (int i = head[k]; i != -1; i = Next[i]) {
			if (hs[i] == x) {
				return id[i];
			}
		}
		return -1;
	}
	ll work(int a, int b, int n) {
		memset(head, -1, sizeof head);
		top = 1;
		if (b == 1) return 0;
		int m = sqrt(n * 1.0), j;
		ll x = 1, p = 1;
		for (int i = 0; i < m; ++i, p = p * a % n) insert(p * b % n, i);
		for (ll i = m; ; i += m) {
			if ((j = find(x = x * p % n)) != -1) return i - j;
			if (i > n) break;
		}
		return -1;
	}
}bsgs;

void solve() {
	scanf("%lld%lld%lld%lld%lld", &n, &x0, &a, &b, &p);
	scanf("%d", &q);
	if (a == <= 1) {
		while (q--) {
			scanf("%lld", &v);
			if (a == 0) {
				if (v == x0) {
					out(0);
				} else if (v == b) {
					out(1);
				} else {
					puts("-1");
				}
			} else if (a == 1) {
				v = (v - x0 + p) % p;
				ll res = v * qmod(b, p - 2, p) % p; 
				if (res <= n) {
					out(res);
				} else {
					puts("-1");  
				}
			} 
		}
		return;
	} 
}

int main() {
	int T; scanf("%d", &T);
	while (T--) solve();
	return 0;
}
