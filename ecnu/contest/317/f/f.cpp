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
constexpr int N = 2e5 + 10; 
constexpr int S = 600;
int q, n, f[N], in[N], out[N], fin[N], vis[N]; 
vector <vector<pII>> G;

struct Query {
	int op, x, y;
	void scan() {
		string _op;
		rd(_op, x, y);
		if (_op == "A") op = 0;
		else op = 1;
	}
}qnode[N];

void dfs(int u) {
	in[u] = ++*in;
	fin[*in] = u;
	for (auto &it : G[u]) {
		int v = it.fi, w = it.se;
		f[v] = f[u] ^ w;
		dfs(v);
	}
	out[u] = *in;
}

int rt[N];
struct Trie {
	struct node {
		int son[2], cnt;
		node() { son[0] = son[1] = cnt = 0; }
	}t[N * 32];
	int tot;
	void init() { tot = 0; t[0] = node(); }
	int newnode() { ++tot; t[tot] = node(); return tot; }
	void insert(int x, int id) {
		int _rt = newnode();
		rt[id] = _rt;
		t[_rt] = t[rt[id - 1]];
		for (int i = 30; i >= 0; --i) {
			int ix = ((x >> i) & 1);
			int now = newnode();
			t[now] = t[t[_rt].son[ix]];
			++t[now].cnt;
			t[_rt].son[ix] = now;
			_rt = now;
		}
	}
	int query(int x, int l_rt, int r_rt) {
		int ans = 0;
		l_rt = rt[l_rt], r_rt = rt[r_rt];
		for (int i = 30; i >= 0; --i) {
			int ix = ((x >> i) & 1) ^ 1;
			int ok = 1;
			if (t[t[r_rt].son[ix]].cnt - t[t[l_rt].son[ix]].cnt <= 0) {
				ix ^= 1;
				ok = 0;
			}
			if (ok) ans |= 1 << i;
			r_rt = t[r_rt].son[ix];
			l_rt = t[l_rt].son[ix];
		}
		return ans;
	}
}trie;

void rebuild(int pre) {
	int gao = 0;
	for (int i = 1; i <= n; ++i) {
		if (!gao && fin[i] >= pre) {
			trie.tot = rt[i] + 100; 
			gao = 1;
		}
		if (gao) {
			if (vis[fin[i]] == 0) {
				rt[i] = rt[i - 1];
			} else {
				trie.insert(f[fin[i]], i);
			}
		}
	}
}

void run() {
	rd(q);
	for (int i = 1; i <= q; ++i) qnode[i].scan();
	memset(f, 0, sizeof f);
	memset(vis, 0, sizeof vis);
	rt[0] = 0;
	vis[1] = 1;
	G.clear(); G.resize(N);
	n = 1;
	for (int i = 1; i <= q; ++i) {
		Query it = qnode[i];
		if (it.op == 0) {
			G[it.x].push_back(pII(++n, it.y));
		}
	}
	f[1] = 0; *in = 0;
	dfs(1);
	vector <int> vec;
	int _n = 1;
	rebuild(1);
	for (int i = 1; i <= q; ++i) {
		Query it = qnode[i];
		if (it.op == 0) {
			vec.push_back(++_n);
		} else {
			if (SZ(vec) > S) {
				int pre = vec[0];
				for (auto &it : vec) vis[it] = 1;
				vec.clear();
				rebuild(pre);
			}
			int u = it.x, v = it.y;
			int res = trie.query(f[u], in[v] - 1, out[v]);
			for (auto &it : vec) {
				if (in[it] >= in[v] && in[it] <= out[v]) {
					chmax(res, f[u] ^ f[it]);
				}
			}
			pt(res);
		}
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
