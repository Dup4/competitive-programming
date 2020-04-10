#include <bits/stdc++.h>
#define fi first
#define se second
#define SZ(x) int((x).size())
#define endl "\n" 
using namespace std;
using db = double;
using ll = long long;
using ull = unsigned long long; 
using pII = pair <int, int>;
using pLL = pair <ll, ll>;
constexpr int mod = 1e9 + 7;
template <class T1, class T2> inline void chadd(T1 &x, T2 y, int Mod = mod) { x += y; while (x >= Mod) x -= Mod; while (x < 0) x += Mod; } 
template <class T1, class T2> inline void chmax(T1 &x, T2 y) { if (x < y) x = y; }
template <class T1, class T2> inline void chmin(T1 &x, T2 y) { if (x > y) x = y; }
inline int nextInt() { int x; cin >> x; return x; }
void rd() {}
template <class T, class... Ts> void rd(T& arg, Ts&... args) { cin >> arg; rd(args...); }
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
template <template<typename...> class T, typename t, typename... A> 
void err(const T <t> &arg, const A&... args) { for (auto &v : arg) cout << v << ' '; err(args...); }
void ptt() { cout << endl; }
template <class T, class... Ts> void ptt(const T& arg, const Ts&... args) { cout << ' ' << arg; ptt(args...); }
template <class T, class... Ts> void pt(const T& arg, const Ts&... args) { cout << arg; ptt(args...); }
void pt() {}
template <template<typename...> class T, typename t, typename... A>
void pt(const T <t> &arg, const A&... args) { for (int i = 0, sze = arg.size(); i < sze; ++i) cout << arg[i] << " \n"[i == sze - 1]; pt(args...); }
inline ll qpow(ll base, ll n) { assert(n >= 0); ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
//head
constexpr int N = 5e4 + 10, M = 1e3 + 10; 
int n, a[N]; 

vector <vector<int>> G;

struct BIT {
	int a[M], pos[N], POS;
	void init() { memset(a, 0, sizeof a); memset(pos, 0, sizeof pos); POS = 0; }
	void update(int x, int v) {
		for (; x < N; x += x & -x) {
			if (pos[x] < POS) {
				a[x] = v;
				pos[x] = POS;
			} else {
				chmax(a[x], v);
			}
		}
	}
	int query(int x) {
		int res = -1; 
		for (; x > 0; x -= x & -x) {
			if (pos[x] == POS) {
				chmax(res, a[x]);
			}
		}
		return res;
	}
}bit;

namespace DCTree {
	int sum, rt, vis[N];
	int sze[N], f[N];
	int dist[N], deep[N], t[M], res;
	void getrt(int u, int fa) {
		f[u] = 0, sze[u] = 1;
		for (auto &v : G[u]) {
		 	if (v == fa || vis[v]) continue;	
			getrt(v, u);
			sze[u] += sze[v];
			f[u] = max(f[u], sze[v]);
		}
		f[u] = max(f[u], sum - sze[u]);
		if (f[u] < f[rt]) rt = u;
	}
	void getdeep(int u, int fa) {
		int tmp = bit.query(a[u]);
		if (tmp != -1) chmax(res, a[u] * (tmp + deep[u]));
		for (auto &v : G[u]) {
			if (v == fa || vis[v]) continue;
			deep[v] = deep[u] + 1;
			getdeep(v, u);
		}
	}
	void add(int u, int fa) {
		bit.update(a[u], deep[u]);
		for (auto &v : G[u]) {
			if (v == fa || vis[v]) continue;
			add(v, u);
		}
	}
	void solve(int u) {
		++bit.POS;
		vis[u] = 1; 
		bit.update(a[u], 0); 
		for (auto &v : G[u]) {
			if (vis[v]) continue;
			deep[v] = 1;
			getdeep(v, u);
			add(v, u);
		}
		++bit.POS;
		bit.update(a[u], 0); 
		reverse(G[u].begin(), G[u].end());
		for (auto &v : G[u]) {
			if (vis[v]) continue;
			deep[v] = 1;
			getdeep(v, u);
			add(v, u);	
		}
		for (auto &v : G[u]) {
			if (vis[v]) continue;
			sum = f[0] = sze[v]; rt = 0;
			getrt(v, 0);
			solve(rt);
		}
	}
	int gao() {
		res = 0;
		memset(vis, 0, sizeof vis);
		memset(t, 0x3f, sizeof t);
		sum = f[0] = n; rt = 0;
		getrt(1, 0); 
		solve(rt);
		return res;
	}
};

void run() {
	for (int i = 1; i <= n; ++i) rd(a[i]);
	G.clear(); G.resize(n + 1);
	for (int i = 1, u, v; i < n; ++i) {
		rd(u, v); 
		G[u].push_back(v);
		G[v].push_back(u);
	}
	assert(n > 1);
	if (n == 2) return pt(max(a[1], a[2]));
	pt(DCTree::gao());
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n) run();
//    for (int kase = 1; kase <= _T; ++kase) {
//        cout << "Case #" << kase << ":\n";
//        run();
//    }
	return 0;
}
