#include <bits/stdc++.h>
#define fi first
#define se second
#define endl "\n" 
using namespace std;
using ll = long long;
constexpr int mod = 1e9 + 7;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
template <template<typename...> class T, typename t, typename... A> 
void err(const T <t> &arg, const A&... args) { for (auto &v : arg) cout << v << ' '; err(args...); }
//head
constexpr int N = 1e5 + 10;
int n, m, l[N], r[N], inv[N];
vector <vector<int>> G;
ll P, res;

struct BIT_2D {
    struct BIT {
        int a[N];
		void init() { memset(a, 0, sizeof a); }
        void add(int x, int v) { for (; x <= m; a[x] = (a[x] + v) % mod, x += x & -x); }
        int ask(int x) { int res = 0; for (; x > 0; res = (res + a[x]) % mod, x -= x & -x); return res; }
    }bit1, bit2;
	inline void init() { bit1.init(); bit2.init(); }
    inline ll ask(int x) { return (1ll * (x + 1) * bit1.ask(x) % mod - bit2.ask(x) + mod) % mod; }
    inline void add(int x, int v) { bit1.add(x, v); bit2.add(x, 1ll * x * v % mod); }
    inline ll ask(int l, int r) { return (ask(r) - ask(l - 1) + mod) % mod; }
    inline void add(int l, int r, int v) { add(l, v); add(r + 1, (-v + mod) % mod); }
}bit[2];

int rt, all, deep[N], sze[N], f[N], vis[N];
void getrt(int u, int fa) {
	sze[u] = 1; f[u] = 0;
	for (auto &v : G[u]) if (v != fa && !vis[v]) {
		getrt(v, u);
		sze[u] += sze[v];
		f[u] = max(f[u], sze[v]);
	}
	f[u] = max(f[u], all - sze[u]);
	if (f[u] <= f[rt]) rt = u;
}

void getdeep(int u, int fa) {
	res = (res + bit[0].ask(l[u], r[u]) * inv[r[u] - l[u] + 1] % mod) % mod;
	res = (res + bit[1].ask(l[u], r[u]) * inv[r[u] - l[u] + 1] % mod * deep[u] % mod) % mod;
	for (auto &v : G[u]) if (v != fa && !vis[v]) {
		deep[v] = deep[u] + 1;
		getdeep(v, u);
	}
}

void add(int u, int fa, int f) {
	bit[0].add(l[u], r[u], (P * inv[r[u] - l[u] + 1] % mod * deep[u] % mod * f + mod) % mod);
	bit[1].add(l[u], r[u], (P * inv[r[u] - l[u] + 1] % mod * f + mod) % mod);
	for (auto &v : G[u]) if (v != fa && !vis[v]) {
		add(v, u, f);
	}
}

void gao(int u) {
	vis[u] = 1;
	bit[1].add(l[u], r[u], P * inv[r[u] - l[u] + 1] % mod);
	for (auto &v : G[u]) if (!vis[v]) {
		deep[v] = 1; 
		getdeep(v, u);
		add(v, u, 1); 
	}
	bit[1].add(l[u], r[u], (mod - P * inv[r[u] - l[u] + 1] % mod) % mod);
	for (auto &v : G[u]) if (!vis[v]) add(v, u, -1);
	for (auto &v : G[u]) if (!vis[v]) {
		all = f[0] = sze[v]; rt = 0;
		getrt(v, 0);
		gao(rt);
	}
}

void run() {
	m = 1;
	res = 0; P = 1;
	G.clear(); G.resize(n + 1);
	memset(vis, 0, sizeof vis);
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d", l + i, r + i);
		m = max(m, r[i]);
		P = P * (r[i] - l[i] + 1) % mod;
	}
	for (int i = 1, u, v; i < n; ++i) {
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	bit[0].init(); bit[1].init();
	all = f[0] = n; rt = 0;
	getrt(1, 0);
	gao(rt);
	printf("%lld\n", res);
}

int main() {
	inv[1] = 1;
	for (int i = 2; i < N; ++i) {
		inv[i] = 1ll * inv[mod % i] * (mod - mod / i) % mod;
	}
	while (scanf("%d", &n) != EOF) run();
	return 0;
}
