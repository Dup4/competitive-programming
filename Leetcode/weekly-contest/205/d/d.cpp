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
int n; 
vector <vector<int>> edges;

struct UFS {
	int fa[N], rk[N];
	void init(int n) {
		memset(fa, 0, sizeof (fa[0]) * (n + 5));
		memset(rk, 0, sizeof (rk[0]) * (n + 5));
	}
	int find(int x) { return fa[x] == 0 ? x : fa[x] = find(fa[x]); }
	bool merge(int x, int y) {
		int fx = find(x), fy = find(y);
		if (fx != fy) {
			if (rk[fx] > rk[fy]) swap(fx, fy);
			fa[fx] = fy;
			if (rk[fx] == rk[fy]) ++rk[fy];
			return true;
		}
		return false;
	}
	bool same(int x, int y) { return find(x) == find(y); }
}ufs[3];

int gao() {
	ufs[0].init(n);
	ufs[1].init(n);
	ufs[2].init(n);
	int res = 0;
	for (auto &it : edges) {
		int tp = it[0], u = it[1], v = it[2];
		if (tp == 3) {
			res += ufs[0].merge(u, v) ^ 1;
		}
	}
	ufs[1] = ufs[2] = ufs[0];
	for (int i = 1; i <= 2; ++i) {
		for (auto &it : edges) {
			int tp = it[0], u = it[1], v = it[2];
			if (tp == i) {
				res += ufs[i].merge(u, v) ^ 1;
			}
		}
		int cnt = 0;
		for (int j = 1; j <= n; ++j) {
			cnt += ufs[i].fa[j] == 0;
		}
		if (cnt > 1) return -1;
	}
	return res;
}

class Solution {
public:
    int maxNumEdgesToRemove(int _n, vector<vector<int>>& _edges) {
		n = _n;
		edges = _edges;
		return gao();	
    }
};

void run() {

}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	int _T = nextInt();
//	while (_T--) run(); 
    for (int kase = 1; kase <= _T; ++kase) {
        cout << "Case #" << kase << ": ";
        run();
    }
//	while (cin >> n) run();
//	run();
	return 0;
}
