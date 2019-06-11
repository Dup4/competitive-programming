#include <bits/stdc++.h>
using namespace std;

#define ll long long
ll p = 1e9 + 7;
ll n;
int f[5], g[5], c;   

void add(ll &x, ll y) {
	x += y;
	if (x >= p) {
		x -= p;
	}
}
struct node {
	ll a[5][5];
	node() {
		memset(a, 0, sizeof a);
	}
	node operator * (const node &other) const {
		node res = node();
		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j < 5; ++j) {
				for (int k = 0; k < 5; ++k) {
					add(res.a[i][j], a[i][k] * other.a[k][j] % p); 
				}
			}
		}
		return res;
	}	
}base, res, base2, res2;
ll marx[][5] = {
	{1, 1, 0, 0, 0},
	{1, 0, 1, 0, 0},
	{1, 0, 0, 0, 0},
	{2, 0, 0, 1, 0},
	{-6, 0, 0, 1, 1}
};
void qmod(node base, node &res, ll n) {
	while (n) {
		if (n & 1) {
			res = res * base;
		}
		base = base * base;
		n >>= 1;
	}
}
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
	while (scanf("%lld", &n) != EOF) {
		for (int i = 1; i <= 3; ++i) {
			scanf("%d", f + i);
		}
		scanf("%d", &c);
		base = node(); res = node();
		res.a[0][3] = 4;
		res.a[0][4] = 1;
		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j < 5; ++j) {
				base.a[i][j] = marx[i][j];
			}
		}
		base2 = node(); res2 = node();
		for (int i = 0; i < 3; ++i) {
			base2.a[i][0] = 1;
		}
		base2.a[0][1] = 1;
		base2.a[1][2] = 1;
		--p;
	
		res2.a[0][2] = 1;
		qmod(base2, res2, n - 3);
		g[1] = res2.a[0][0];
	
		res2 = node();
		res2.a[0][1] = 1;
		qmod(base2, res2, n - 3);
		g[2] = res2.a[0][0];
	
		res2 = node();
		res2.a[0][0] = 1;
		qmod(base2, res2, n - 3); 
		g[3] = res2.a[0][0]; 
		
		qmod(base, res, n - 3); 
		add(res.a[0][0], p);
		++p;
		printf("%lld\n", qmod(f[1], g[1]) * qmod(f[2], g[2]) % p * qmod(f[3], g[3]) % p * qmod(c, res.a[0][0]) % p);
	}
	return 0;
}
