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
constexpr int N = 1e3 + 10; 
int n, d[N];  
vector <vector<int>> G;

int ask(int u, int v) {
	pt("?", u, v);
	cout.flush(); 
	int x; rd(x);
	return x;
}

void done(int u) {
	pt("!", u);
	cout.flush();
	return;
}

void del(int u) {
	for (auto &v : G[u]) {
		--d[v];
	}
	d[u] = -1;
}

void run() {
	G.clear(); G.resize(n + 1);
	memset(d, 0, sizeof d);
	for (int i = 1, u, v; i < n; ++i) {
		rd(u, v);
		G[u].push_back(v);
		G[v].push_back(u);
		++d[u]; ++d[v];
	}
	while (1) {
		int u = -1, v = -1;
		for (int i = 1; i <= n && v == -1; ++i) {
			if (d[i] == 1) {
				if (u == -1) u = i;
				else if (v == -1) v = i;
			}
		}
		if (v == -1) { 
			for (int i = 1; i <= n; ++i) if (d[i] == 0)
				return done(i);
		} else {
			int lca = ask(u, v);
			if (lca == u || lca == v) return done(lca);	
			del(u); del(v);
		}
	}
	assert(0);
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
