#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define SZ(x) int((x).size())
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
constexpr int N = 1e2 + 10; 
int n[4], m, cnt[4], _n, res; 

vector <int> vec;

struct UFS {
	int fa[N], sze[N];
	void init(int n) {
		memset(fa, 0, sizeof (fa[0]) * (n + 5));
		for (int i = 0; i <= n; ++i) sze[i] = 1;
	}
	int find(int x) { return fa[x] == 0 ? x : fa[x] = find(fa[x]); }
	bool merge(int x, int y) {
		int fx = find(x), fy = find(y);
		if (fx != fy) {
			if (sze[fx] > sze[fy]) swap(fx, fy);
			fa[fx] = fy;
			sze[fy] += sze[fx];
			return true;
		}
		return false;
	}
	bool same(int x, int y) { return find(x) == find(y); }
}ufs;

void dfs(int cur) {
	if (cur >= _n) {
		int ok = 1;
		for (int i = 0; i < 4; ++i) {
			if (n[i] != cnt[i]) {
				ok = 0;
				break;
			}
		}
		res += ok;
		return;
	}
	for (int i = 0; i < 4; ++i) {
		cnt[i] += vec[cur];
		dfs(cur + 1);
		cnt[i] -= vec[cur];
	}
}

void run() {
	rd(n[0], n[1], n[2], n[3], m);
	ufs.init(100);
	for (int i = 1, x, y; i <= m; ++i) {
		rd(x, y);
		ufs.merge(x, y);
	}
	vec.clear();
	for (int i = 1; i <= 12; ++i) {
		if (ufs.fa[i] == 0) vec.push_back(ufs.sze[i]);
	}
	_n = SZ(vec);
	res = 0;
	dfs(0);
	pt(res);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	run();
//	while (cin >> n) run();
//    for (int kase = 1; kase <= _T; ++kase) {
//        cout << "Case #" << kase << ":\n";
//        run();
//    }
	return 0;
}
