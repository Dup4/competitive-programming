#include <bits/stdc++.h>
using namespace std;
#define endl "\n" 
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
#define mkp make_pair
#define all(x) (x).begin(), (x).end()
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
constexpr int N = 1e5 + 10; 
int n, m, in[N], out[N]; 
vector <vector<int>> G;

struct BIT {
	ll a[N];
	void init() { memset(a, 0, sizeof a); }
	void update(int x, ll v) {
		for (; x < N; x += x & -x) 
			a[x] += v;
	}
	ll query(int x) {
		ll res = 0;
		for (; x; x -= x & -x)
			res += a[x];
		return res;
	}
	void update(int l, int r, ll v) {
	//	dbg(l, r, v);
		if (l > r) return;
		update(l, v);
		update(r + 1, -v);
	}
}bit;

void dfs(int u) {
	in[u] = ++*in;
	for (auto &v : G[u]) {
		dfs(v);
	}
	out[u] = *in;
}

void run() {
	rd(n, m);
	G.clear(); G.resize(n + 1);
	bit.init();
	int rt = -1;
	for (int i = 1, fa; i <= n; ++i) {
		rd(fa);
		if (fa) G[fa].push_back(i);
		else rt = i;
	}
	*in = 0;
//	dbg(rt);
	dfs(rt);
//	for (int i = 1; i <= n; ++i) dbg(i, in[i], out[i]);
	for (int i = 1, u, x, v; i <= m; ++i) {
		rd(u, x, v);
		pt(bit.query(in[v]));
		bit.update(in[u], out[u], x);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	int _T = 1;
	//nextInt();
	while (_T--) run(); 
//    for (int kase = 1; kase <= _T; ++kase) {
//        cout << "Case #" << kase << ": ";
//        run();
//    }
//	while (cin >> n) run();
//	run();
	return 0;
}
