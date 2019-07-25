#include <bits/stdc++.h>
using namespace std;

#define N 100010
#define ll long long
#define pii pair <int, int>
#define fi first
#define se second
ll p, n, m;
int fac[N], tot;

struct node {
	ll a[2][2];
	node() {
		memset(a, 0, sizeof a);
	}
	void set() {
		a[0][0] = a[0][1] = 1;
	}
	node operator * (const node &other) const {
		node res = node();
		for (int i = 0; i < 2; ++i) {
			for (int j = 0; j < 2; ++j) {
				for (int k = 0; k < 2; ++k) {
					res.a[i][j] = (res.a[i][j] + a[i][k] * other.a[k][j] % p) % p;
				}
			}
		}
		return res;
	}
}base, res;

node qmod(node base, ll n) {
	node res = node(); res.set();
	while (n) {
		if (n & 1) {
			res = res * base;
		}
		base = base * base; 
		n >>= 1;
	}
	return res;
}

int main() {
	base = node();
	base.a[0][0] = 10;
	base.a[1][0] = 1;
	base.a[1][1] = 1;
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%lld%lld%lld", &p, &n, &m);
		if (p == 2 || p == 5) {
			puts("0");
		} else if (p == 3) {
			ll t = 3;
			printf("%lld\n", (n / t) * m);	
		} else {
			tot = 0;
			int limit = sqrt(p - 1) + 10;
			ll tmp = p - 1;
			for (int i = 2; i <= limit && i <= tmp; ++i) {
				while (tmp % i == 0) {
					fac[++tot] = i;
					tmp /= i;
				}
			}
			if (tmp != 1) fac[++tot] = tmp;
			ll t = p - 1;
			for (int i = 1; i <= tot; ++i) {
				res = qmod(base, t / fac[i] - 1);
				if (res.a[0][0] == 0) {
					t = t / fac[i];
				}
			}
			printf("%lld\n", (n / t) * m);
		}
	}
	return 0;
}
