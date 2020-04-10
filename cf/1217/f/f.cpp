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
constexpr int N = 4e5 + 10; 
int n, m, lstans, ans[N]; 
map <int, map<int, int>> exist;

struct E { int op, u, v; }e[N];

struct UFS {
	struct node { int fa, sze; }t[N];
	struct BackNode { int u; node e; } Back[N << 1];
	int T;
	void init() { T = 0; }
	int find(int x) { return t[x].fa == 0 ? x : find(t[x].fa); }
	void merge(int x, int y) {
		int fx = find(x), fy = find(y);
		if (fx != fy) {
			if (t[fx].sze > t[fy].sze) swap(fx, fy);
			Back[++T] = { fx, t[fx] };
			Back[++T] = { fy, t[fy] };
			t[fx].fa = fy;
			if (t[fx].sze == t[fy].sze) ++t[fy].sze;
		}
	}
	bool same(int x, int y) { return find(x) == find(y); }
	void rollBack(int _T) {
		while (T > _T) {
			t[Back[T].u] = Back[T].e;
			--T;
		}
	}
}ufs;

struct SEG {
	vector <pII> t[N << 2];
	void update(int id, int l, int r, int ql, int qr, pII e) {
		if (l >= ql && r <= qr) {
			t[id].push_back(e);
			return;
		}
		int mid = (l + r) >> 1;
		if (ql <= mid) update(id << 1, l, mid, ql, qr, e);
		if (qr > mid) update(id << 1 | 1, mid + 1, r, ql, qr, e);
	}
	void gao(int id, int l, int r) {
		int _T = ufs.T;
		for (auto &it : t[id]) {
			if (exist[it.fi][it.se])
				ufs.merge(it.fi, it.se);
		}
		if (l == r) {
			if (e[l].op == 2) {
				lstans = ans[l] = ufs.same(e[l].u, e[l].v);
			}
			if (l < m) {
				e[l + 1].u = (e[l + 1].u + lstans - 1) % n + 1;
				e[l + 1].v = (e[l + 1].v + lstans - 1) % n + 1;
				if (e[l + 1].u > e[l + 1].v) swap(e[l + 1].u, e[l + 1].v);
				if (e[l + 1].op == 1) exist[e[l + 1].u][e[l + 1].v] ^= 1;
			}
			ufs.rollBack(_T);
			return;
		}
		int mid = (l + r) >> 1;
		gao(id << 1, l, mid);
		gao(id << 1 | 1, mid + 1, r);
		ufs.rollBack(_T);
	}
}seg;

void run() {
	exist.clear();
	lstans = 0;
	for (int i = 1; i <= m; ++i) {
		rd(e[i].op, e[i].u, e[i].v);
		if (e[i].u > e[i].v) swap(e[i].u, e[i].v);
		if (e[i].op == 1) {
			int u = e[i].u, v = e[i].v;
			if (u > v) swap(u, v);
			if (exist[u].count(v)) seg.update(1, 1, m, exist[u][v], i, pII(u, v));
			exist[u][v] = i;

			u = (u % n) + 1;
			v = (v % n) + 1;
			if (u > v) swap(u, v);
			if (exist[u].count(v)) seg.update(1, 1, m, exist[u][v], i, pII(u, v));
			exist[u][v] = i;
		} 
	}
	for (int i = 1; i <= n; ++i) 
		for (auto &it : exist[i]) {
			if (it.se < m) 
				seg.update(1, 1, m, it.se, m, pII(i, it.fi));
		}
    exist.clear();
	if (e[1].op == 1) exist[e[1].u][e[1].v] = 1;
	seg.gao(1, 1, m);
	for (int i = 1; i <= m; ++i) {
		if (e[i].op == 2)
			cout << "01"[ans[i]];
	}
	cout << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n >> m) run();
//    for (int kase = 1; kase <= _T; ++kase) {
//        cout << "Case #" << kase << ":\n";
//        run();
//    }
	return 0;
}
