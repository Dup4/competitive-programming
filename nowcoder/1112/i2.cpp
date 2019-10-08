#include <bits/stdc++.h>
#define debug(...) { printf("#  "); printf(__VA_ARGS__); puts(""); }
#define fi first
#define se second
#define endl "\n" 
using namespace std;
using db = double;
using ll = long long;
using ull = unsigned long long; 
using pII = pair <int, int>;
using pLL = pair <ll, ll>;
constexpr int mod = 1e9 + 7;
template <class T1, class T2> inline void chadd(T1 &x, T2 y) { x += y; while (x >= mod) x -= mod; while (x < 0) x += mod; } 
template <class T1, class T2> inline void chmax(T1 &x, T2 y) { if (x < y) x = y; }
template <class T1, class T2> inline void chmin(T1 &x, T2 y) { if (x > y) x = y; }
inline int rd() { int x; cin >> x; return x; }
template <class T> inline void rd(T &x) { cin >> x; }
template <class T> inline void rd(vector <T> &vec) { for (auto &it : vec) cin >> it; }
inline void pt() { cout << endl; }
template <class T, class... Ts> void pt(const T& arg, const Ts&... args) { cout << arg << " "; pt(args...); }
template <class T> inline void pt(const T &s) { cout << s << "\n"; }
template <class T> inline void pt(const vector <T> &vec) { for (auto &it : vec) cout << it << " "; cout << endl; } 
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
inline ll qpow(ll base, ll n) { ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
constexpr int N = 1e5 + 10;  
int n, c[N], cnt[N], tot[N], ans[N];  
vector <vector<pII>> G;  
unordered_map <int, int> mp[N];
void dfs(int u, int fa, int id) {
	mp[u].clear(); mp[u][c[u]]++;
	cnt[u] = (tot[c[u]] == 1 ? 0 : 1);
	for (auto &it : G[u]) {
		int v = it.fi;
		if (v == fa) continue;
		dfs(v, u, it.se);
		if (mp[u].size() < mp[v].size()) swap(mp[u], mp[v]), swap(cnt[u], cnt[v]);
		for (auto &it2 : mp[v]) {
			int C = it2.fi, num = it2.se;
			mp[u][C] += num; 
			if (mp[u][C] == num) ++cnt[u];
			if (mp[u][C] == tot[C]) --cnt[u];
		}
		mp[v].clear();
	}
	ans[id] = cnt[u];
}
void run() {
	G.clear(); G.resize(n + 1);
	memset(tot, 0, sizeof (tot[0]) * (n + 10));
	for (int i = 1; i <= n; ++i) c[i] = rd(), ++tot[c[i]];
	for (int i = 1, u, v; i < n; ++i) {
		cin >> u >> v;
		G[u].push_back(pII(v, i));
		G[v].push_back(pII(u, i));
	}
	dfs(1, 1, 0);
	for (int i = 1; i < n; ++i) pt(ans[i]);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n) run();
	return 0;
}
