#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define pII pair <int, int>
#define fi first
#define se second
const int mod = 998244353;
const int N = 1e6 + 10; 
int q; ll n, ans, A; pII table[N];
inline void add(int &x, int y) {
	x += y;
	if (x >= mod) x -= mod; 
}
struct node {
	int a[2][2];
	node() { memset(a, 0, sizeof a); }
	node operator * (const node &other) const {
		node res = node();
		for (int i = 0; i < 2; ++i)
			for (int j = 0; j < 2; ++j)
				for (int k = 0; k < 2; ++k)
					add(res.a[i][j], 1ll * a[i][k] * other.a[k][j] % mod);
		return res;
	}
}base, res;
void qpow(node &res, node base, ll n) {
	while (n) {
		if (n & 1) res = res * base;
		base = base * base;
		n >>= 1; 
	}	
}

int main() {
	base = node();
	base.a[0][0] = 3; base.a[0][1] = 1;
	base.a[1][0] = 2;
	table[0].fi = 0, table[0].se = 1;
	for (int i = 1; i <= 1000000; ++i) {
		res = node();
		res.a[0][0] = table[i - 1].se, res.a[0][1] = table[i - 1].fi;
		qpow(res, base, 1000);
		table[i].fi = res.a[0][1], table[i].se = res.a[0][0];
	//	if (i % 1000 == 0) cout << i << endl;
	}
	while (scanf("%d%lld", &q, &n) != EOF) {
		ans = 0;
		for (int i = 1; i <= q; ++i) {
			cout << n << endl;
			int p = n / 1000;
			res = node();
			res.a[0][0] = table[p].se, res.a[0][1] = table[p].fi;
			qpow(res, base, n - 1ll * p * 1000);
			A = res.a[0][1]; 
			ans ^= A;
			n = n ^ (A * A);
		}
		printf("%lld\n", ans);
	}
	return 0;
}
