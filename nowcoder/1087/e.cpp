#include <bits/stdc++.h>
using namespace std;
#define debug(...) { printf("#  "); printf(__VA_ARGS__); puts(""); }
#define fi first
#define se second
#define endl "\n" 
using ll = long long;
using pII = pair <int, int>;
using pLL = pair <ll, ll>;
using VI = vector <int>;
using VL = vector <ll>;
constexpr int mod = 1e9 + 7;
template <class T1, class T2> inline void chadd(T1 &x, T2 y) { x += y; while (x >= mod) x -= mod; while (x < 0) x += mod; } 
template <class T1, class T2> inline void chmax(T1 &x, T2 y) { if (x < y) x = y; }
template <class T1, class T2> inline void chmin(T1 &x, T2 y) { if (x > y) x = y; }
inline int rd() { int x; cin >> x; return x; }
template <class T> inline void rd(T &x) { cin >> x; }
template <class T> inline void rd(vector <T> &vec) { for (auto &it : vec) cin >> it; }
template <class T> inline void out(T s) { cout << s << "\n"; }
template <class T> inline void out(vector <T> &vec) { for (auto &it : vec) cout << it << " "; cout << endl; } 
inline ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
inline ll qpow(ll base, ll n) { ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
constexpr int N = 1e5 + 10;
int n, q, a[N], b[N], f[N][2]; 
vector <vector<int>> G;
bitset <N> w;
void Hash() {
	sort(b + 1, b + 1 + n);
	b[0] = n;
	b[0] = unique(b + 1, b + 1 + n) - b - 1;
	for (int i = 1; i <= n; ++i)
		a[i] = lower_bound(b + 1, b + 1 + b[0], a[i]) - b;
}
struct BIT {
	int a[N];
	void init() { memset(a, 0, sizeof a); }
	void update(int x, int v) {
		for (; x < N; x += x & -x)
			a[x] += v;
	} 
	int query(int x) {
		int res = 0;
		for (; x > 0; x -= x & -x)
			res += a[x];
		return res;
	}
	int query(int l, int r) {
		if (l > r) return 0;
		return query(r) - query(l - 1);
	}
}bit[2];
void DFS(int u, int fa) {
	f[u][0] = bit[0].query(1, a[u] - 1);
	bit[1].update(a[u], 1);
	bit[0].update(a[u], 1);
	f[u][1] -= bit[1].query(1, a[u] - 1); 
	for (auto &v : G[u]) if (v != fa) DFS(v, u);
	f[u][1] += bit[1].query(1, a[u] - 1);
    bit[0].update(a[u], -1);	
}
void run() {
	G.clear(); G.resize(n + 1);
	for (int i = 1; i <= n; ++i) cin >> a[i], b[i] = a[i];
	Hash();
	for (int i = 1, u, v; i < n; ++i) {
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	bit[0].init(); bit[1].init();
	memset(f, 0, sizeof f); 
	DFS(1, 1);
	ll sum = 0;
	for (int i = 1; i <= n; ++i) {
		if (f[i][0] > f[i][1]) swap(f[i][0], f[i][1]);
		sum += f[i][0];
		f[i][1] -= f[i][0];
	}
	w.reset();
	w[0] = 1;
	for (int i = 1; i <= n; ++i) { 
		w |= (w << f[i][1]);
	}
	cin >> q;
	while (q--) {
		int x; cin >> x; x -= sum;
		if (x >= 0 && w[x] == 1) out("Orz");
		else out("QAQ");
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n) run();
	return 0;
}
