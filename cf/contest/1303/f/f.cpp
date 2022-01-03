#include <bits/stdc++.h>
#define fi first
#define se second
#define SZ(x) ((int)x.size())
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
inline int rd() { int x; cin >> x; return x; }
template <class T> inline void rd(T &x) { cin >> x; }
template <class T> inline void rd(vector <T> &vec) { for (auto &it : vec) cin >> it; }  
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
constexpr int N = 3e2 + 10;
int n, m, q, res, a[N][N]; 
int Move[][2] = {
	-1, 0,
	1, 0,
	0,-1,
	0,1,
};
inline int id(int x, int y) { return (x - 1) * m + y; }
inline bool ok(int x, int y) { return x >= 1 && x <= n && y >= 1 && y <= m; }

struct UFS {
	struct node { int fa, sze; void init() { fa = 0; sze = 1; } }t[N * N];  
	int id[N * N]; 
	void init(int n) { *id = 0; for (int i = 1; i <= n; ++i) t[i].init(), id[i] = ++*id; }
	int find(int x) { return t[x].fa == 0 ? x : find(t[x].fa); }
	void dead(int x) {
		int fx = find(id[x]); 
		--t[fx].sze; 
		if (t[fx].sze == 0) --res;
		id[x] = 0;
	}
	void rebirth(int x) {
		dead(x);
		id[x] = ++*id;
		t[id[x]].init();
		++res;
	}
	void merge(int x, int y) {
		int fx = find(id[x]), fy = find(id[y]);
		if (fx != fy) {
			if (t[fx].sze > t[fy].sze) swap(fx, fy);
			t[fx].fa = fy;
			if (t[fx].sze && t[fy].sze) --res;
			t[fy].sze += t[fx].sze;
		}
	} 
}ufs;

void add(int x, int y) {
	for (int k = 0; k < 4; ++k) {
		int nx = x + Move[k][0];
		int ny = y + Move[k][1];
		if (ok(nx, ny) && a[x][y] == a[nx][ny]) {
			ufs.merge(id(x, y), id(nx, ny));
		}
	}
}

void run() {
	memset(a, 0, sizeof a);
	ufs.init(n * m);
	res = n * m;
	for (int x = 1; x <= n; ++x) {
		for (int y = 1; y <= m; ++y) {
			add(x, y);
		}
	}
	for (int i = 1, x, y, c; i <= q; ++i) {
		cin >> x >> y >> c;
		ufs.rebirth(id(x, y));
		a[x][y] = c;
		add(x, y);
		pt(res);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n >> m >> q) run();
	return 0;
}
