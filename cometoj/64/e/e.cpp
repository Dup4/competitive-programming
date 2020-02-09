#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
#define fi first
#define se second
const int N = 2e5 + 10, mod = 786433, g = 10; 
int n, a[N], fa[N];
vector <vector<int>> G;
vector <map<int, int>> mp;
unordered_map <int, int> f;

inline void chadd(int &x, int y) {
	x += y;
	while (x >= mod) x -= mod;
	while (x < 0) x += mod;
}

int pg[N << 2], ind[N << 2];
int get(int x, int y) {
	x %= mod;
	if (!x) return 0;
	return pg[1ll * ind[x] * y % (mod - 1)];
}

ll qpow(ll base, ll n) {
	if (base == 0 && n == 0) return 0;
	ll res = 1;
	base %= mod;
	while (n) {
		if (n & 1) res = res * base % mod;
		base = base * base % mod;
		n >>= 1;
	}
	return res;
}

void dfs(int u) {
	mp[u][a[u]] = 1;
	chadd(f[a[u]], 1);
	for (auto &v : G[u]) if (v != fa[u]) {
		fa[v] = u;
		dfs(v);
		for (auto &i : mp[u]) {
			for (auto &j : mp[v]) {
				chadd(f[i.fi & j.fi], 1ll * i.se * j.se % mod);
			}
		}
		for (auto &j : mp[v]) chadd(mp[u][j.fi & a[u]], j.se);
		mp[v].clear();
	}
}


int main() {
	pg[0] = 1;
	for (int i = 1; i < mod; ++i) {
		pg[i] = 1ll * pg[i - 1] * g % mod;
		ind[pg[i]] = i;
	}	
	while (scanf("%d", &n) != EOF) {
		G.clear(); G.resize(n + 1);
		mp.clear(); mp.resize(n + 1);
		f.clear();
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		for (int i = 1, u, v; i < n; ++i) {
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);	
		}
		fa[1] = 0;
		dfs(1);
		int res = 0;
		for (auto &it : f) {
			chadd(res, 1ll * get(it.fi, it.fi) * it.se % mod);
		}
		printf("%d\n", res);
	}
	return 0;
}
