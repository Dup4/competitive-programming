#include <bits/stdc++.h>
using namespace std;

#define M 1000010
#define ll long long
ll p = 1e9 + 7;
ll n;
int f[M], g[M], c;   

#define N 76543
int hs[N], head[N], nx[N], id[N], top; 
void insert(int x, int y) {
	int k = x % N;
	hs[top] = x, id[top] = y, nx[top] = head[k], head[k] = top++;
}
int find(int x) {
	int k = x % N;
	for (int i = head[k]; i != -1; i = nx[i]) {
		if (hs[i] == x) {
			return id[i];
		}
	}
	return -1;
}
int BSGS(int a, int b, int n) {
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
					add(res.a[i][j], a[i][k] * other.a[j][k] % p); 
				}
			}
		}
		return res;
	}	
}base, res;
ll marx[][5] = {
	{1, 1, 0, 0, 0},
	{1, 0, 1, 0, 0},
	{1, 0, 0, 0, 0},
	{2, 0, 0, 1, 0},
	{-6, 0, 0, 1, 1}
};
void qmod(ll n) {
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
		for (int i = 1; i <= 3; ++i) g[i] = BSGS(c, f[i], p);
		int F = (g[1] != -1 && g[2] != -1 && g[3] != -1);
		for (int i = 4; F == 0 && i <= n; ++i) {
			f[i] = qmod(c, (2ll * i - 6 + p - 1) % (p - 1)) * f[i - 1] % p * f[i - 2] % p * f[i - 3] % p; 
		  	g[i] = BSGS(c, f[i], p);
			if (g[i] != -1 && g[i - 1] != -1 && g[i - 2] != -1) {
				F = i;
				break;
			}	
		}
		if (n <= F || F == 0) {  
			printf("%d\n", f[n]);
			continue;
		}
		base = node(); res = node();
		res.a[0][0] = g[F];
		res.a[0][1] = g[F - 1];
		res.a[0][2] = g[F - 2];
		res.a[0][3] = F + 1;
		res.a[0][4] = 1;
		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j < 5; ++j) {
				base.a[i][j] = marx[i][j];
			}
		}
		--p;
		qmod(n - F);
		add(res.a[0][0], p);
		++p;
		printf("%lld\n", qmod(c, res.a[0][0]));
	}
	return 0;
}
