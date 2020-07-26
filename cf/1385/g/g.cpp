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
constexpr int N = 2e5 + 10, INF = 0x3f3f3f3f; 
int n, a[N], b[N], cnt[N], vis[N]; 

vector <set<int>> G(n + 5);
vector <int> vec;
void dfs(int u) {
	vec.push_back(u);
	vis[u] = 1;
	for (auto &v : G[u]) if (!vis[v]) dfs(v);
	
}

void run() {
	rd(n);
	vector <int> res;
	memset(cnt, 0, sizeof (cnt[0]) * (n + 5));
	memset(vis, 0, sizeof (vis[0]) * (n + 5));
	map <pII, int> mp;
	vector <vector<pII>> c(n + 5);
	for (int i = 1; i <= n; ++i) rd(a[i]), ++cnt[a[i]];
	for (int i = 1; i <= n; ++i) rd(b[i]), ++cnt[b[i]];
	for (int i = 1; i <= n; ++i) if (cnt[i] != 2) return pt("-1");
	for (int i = 1; i <= n; ++i) {
		c[a[i]].push_back(pII(1, i));
		c[b[i]].push_back(pII(2, i));
	}
	G.clear(); G.resize(n + 1);
	for (int i = 1; i <= n; ++i) {
		pII x = c[i][0], y = c[i][1]; 
		if (x.se == y.se) continue;
		G[x.se].insert(y.se);
		G[y.se].insert(x.se);
		mp[pII(x.se, y.se)] = mp[pII(y.se, x.se)] = (x.fi == y.fi);
	}
	for (int i = 1; i <= n; ++i) {
		if (!vis[i]) {
			vec.clear();
			int rt = i;
			dfs(rt);
			vector <int> tmp[2];
			for (auto st : {0, 1}) {
				int ori = st;
				if (st) tmp[ori].push_back(vec[0]);
				for (int j = 1; j < SZ(vec); ++j) {
					if (mp[pII(vec[j - 1], vec[j])]) st ^= 1;
					if (st) tmp[ori].push_back(vec[j]);
				}
			}
			if (SZ(tmp[0]) <= SZ(tmp[1])) res.insert(res.end(), all(tmp[0]));
			else res.insert(res.end(), all(tmp[1]));
		}
	}	
	sort(all(res));
	pt(SZ(res));
	pt(res);
	if (!SZ(res)) pt("");
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	int _T = nextInt();
	while (_T--) run(); 
//    for (int kase = 1; kase <= _T; ++kase) {
//        cout << "Case #" << kase << ": ";
//        run();
//    }
//	while (cin >> n) run();
//	run();
	return 0;
}
