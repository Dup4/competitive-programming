#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 110, mod = 1e9 + 7;
int n, m, g[N][N];
ll fac[N], inv[N], res;
vector <int> vec;

inline void chadd(ll &x, ll y) {
	x += y;
	while (x >= mod) x -= mod;
	while (x < 0) x += mod;
}

ll qpow(ll base, ll n) {
	ll res = 1;
	while(n) {
		if (n & 1) res = res * base % mod;
		base = base * base % mod;
		n >>= 1;
	}
	return res;
}

ll C(int n, int m) {
	if (n < m) return 0;
	return fac[n] * inv[m] % mod * inv[n - m] % mod;
}

int cnt(int x) {
	int res = 0;
	for (; x > 0; x -= x & -x)
		++res;
	return res;
}

void check() {
	int sze = vec.size();
	for (int i = 0; i < (1 << sze); ++i) {
		if (cnt(i) == 3) {
			vector <int> tmp;
			for (int j = 0; j < sze; ++j) {
				if ((i >> j) & 1) {
					tmp.push_back(vec[j]);
				}
			}
			if (g[tmp[0]][tmp[1]] == g[tmp[0]][tmp[2]] && g[tmp[0]][tmp[1]] == g[tmp[1]][tmp[2]]) {
				++res;
				return;
			}
		}
	}
}

void dfs(int cur) {
	if (cur > n) { 
		return;
	}
	dfs(cur + 1);
	if (vec.size() < 5) { 
		vec.push_back(cur);
		check();
		dfs(cur + 1);
		vec.pop_back(); 
	}	
}

int main() {
	fac[0] = 1;
	for (int i = 1; i < N; ++i) fac[i] = fac[i - 1] * i % mod;
	inv[N - 1] = qpow(fac[N - 1], mod - 2);
	for (int i = N - 1; i >= 1; --i) inv[i - 1] = inv[i] * i % mod;
	int _T; scanf("%d", &_T);
	for (int kase = 1; kase <= _T; ++kase) {
		printf("Case #%d: ", kase);
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				g[i][j] = 0;
		for (int i = 1, u, v; i <= m; ++i) {
			scanf("%d%d", &u, &v);
			g[u][v] = g[v][u] = 1;
		}
		res = 0;
		for (int i = 6; i <= n; ++i)
			chadd(res, C(n, i));
		vec.clear();
		dfs(1); 
		printf("%lld\n", res);
	}
	return 0;
}
