#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
#define mkp make_pair
#define all(x) (x).begin(), (x).end()
#define endl "\n" 
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
constexpr int N = 2e5 + 10; 
int n, b[N], d[N];
ll a[N]; 
vector <vector<int>> G, F;

void dfs(int u) {
//	dbg(u);
	for (auto &v : G[u]) {
		dfs(v);
		if (a[v] > 0) {
			a[u] += a[v];
			F[v].push_back(u);
			++d[u];
		} else {
			F[u].push_back(v);
			++d[v];
		}
	}
}

void run() {
	rd(n);
	for (int i = 1; i <= n; ++i) rd(a[i]);
	memset(d, 0, sizeof d);
	G.clear(); G.resize(n + 1);
	F.clear(); F.resize(n + 1);
	for (int i = 1; i <= n; ++i) {
		rd(b[i]);
		if (b[i] != -1) G[b[i]].push_back(i);
	}
	for (int i = 1; i <= n; ++i) if (b[i] == -1) dfs(i); 
	pt(accumulate(a + 1, a + 1 + n, 0ll));
	queue <int> que;
	for (int i = 1; i <= n; ++i) if (d[i] == 0) que.push(i);
	vector <int> res;
	while (!que.empty()) {
		int u = que.front(); que.pop();
		res.push_back(u);
		for (auto &v : F[u]) if (--d[v] == 0) que.push(v);
	}
	pt(res);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	int _T = 1;
	while (_T--) run(); 
//    for (int kase = 1; kase <= _T; ++kase) {
//        cout << "Case #" << kase << ": ";
//        run();
//    }
//	while (cin >> n) run();
//	run();
	return 0;
}
