#include <bits/stdc++.h>
using namespace std;
#define debug(...) { printf("#  "); printf(__VA_ARGS__); puts(""); }
#define ll long long
#define pii pair <int, int>
#define fi first
#define se second
const int N = 1e6 + 10;
const int ALP = 26;
const int mod = 1e9 + 7;
template <class T1, class T2> inline void chadd(T1 &x, T2 y) { x += y; if (x >= mod) x -= mod; } 
template <class T1, class T2> inline void chmax(T1 &x, T2 y) { if (x < y) x = y; }
template <class T1, class T2> inline void chmin(T1 &x, T2 y) { if (x > y) x = y; }
inline int rd() { int x; cin >> x; return x; }
template <class T > inline void out(T s) { cout << s << "\n"; }
inline ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
inline ll qpow(ll base, ll n) { ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
int n, q, nd[N], res[N]; 
vector < vector <pii> > qvec;

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
}bit;

struct ACAM {
	struct node {
		int nx[ALP], nx2[ALP], fail, fa;
		node() {
			memset(nx, -1, sizeof nx);
			memset(nx2, -1, sizeof nx2);
			fail = fa = 0;
		}
	}t[N];
	int root, tot, in[N], out[N], cnt;
	vector <vector<int>> G;
	int newnode() {
		++tot;
		t[tot] = node();
		return tot;
	}
	void init() {
		tot = 0;
		root = newnode();
	}
	int insert(int rt, int ch) {
		if (t[rt].nx[ch] == -1) {
			int tmp = newnode();
			t[rt].nx[ch] = tmp;
			t[tmp].fa = rt;
		}
		return t[rt].nx[ch];  
	}
	int insert(const string &s) {
		int rt = root; 
		for (auto it : s) {
			rt = insert(rt, it - 'a');
		}
		return rt; 
	}
	int que[N], ql, qr;
	void build() {
		for (int i = 1; i <= tot; ++i)
			for (int j = 0; j < ALP; ++j)
				t[i].nx2[j] = t[i].nx[j];
		ql = 1, qr = 0;
		t[root].fail = root;
		for (int i = 0; i < ALP; ++i) {
			if (t[root].nx[i] == -1) {
				t[root].nx[i] = root;
			} else {
				t[t[root].nx[i]].fail = root;
				que[++qr] = t[root].nx[i];
			}
		}
		while (ql <= qr) {
			int now = que[ql++];
			for (int i = 0; i < ALP; ++i) {
				if (t[now].nx[i] == -1) {
					t[now].nx[i] = t[t[now].fail].nx[i];
				}
				else {
					t[t[now].nx[i]].fail = t[t[now].fail].nx[i];
					que[++qr] = t[now].nx[i];
				}
			}
		}
	}
	void pre(int u) {
		in[u] = ++cnt;
		for (auto v : G[u]) pre(v);
		out[u] = cnt;
	}
	void DFS(int u) {
		bit.update(in[u], 1);
		for (auto it : qvec[u]) {
			res[it.se] = bit.query(in[it.fi], out[it.fi]);
		}
		for (int i = 0; i < ALP; ++i)
			if (t[u].nx2[i] != -1)
				DFS(t[u].nx2[i]);
		bit.update(in[u], -1);
	}
	void solve() {
		G.clear(); G.resize(tot + 1);
		for (int i = 2; i <= tot; ++i)
			G[t[i].fail].push_back(i);
		cnt = 0; pre(1);
		bit.init(); DFS(1);
	}
}acam;

void run() {
	acam.init();
	int op, x; char ch[10];
	for (int i = 1; i <= n; ++i) {
		cin >> op;
		if (op == 1) {
			cin >> ch;
			nd[i] = acam.insert(1, ch[0] - 'a');
		} else {
			cin >> x >> ch;
			nd[i] = acam.insert(nd[x], ch[0] - 'a');
		}
	}
//	for (int i = 1; i <= n; ++i) cout << nd[i] << endl;
	cin >> q;
	qvec.clear(); qvec.resize(N);  
	string s;
	for (int i = 1, x; i <= q; ++i) {
		cin >> x >> s;
		qvec[nd[x]].emplace_back(acam.insert(s), i);
	}
	acam.build(); acam.solve();
	for (int i = 1; i <= q; ++i) cout << res[i] << "\n";	
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n) run();
	return 0;
}
