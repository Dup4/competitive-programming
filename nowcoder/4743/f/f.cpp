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
constexpr int N = 1e5 + 10; 
int n, m, vLimit; ll a[N], b[N];

struct E {
	ll t, p, c;
	bool operator == (const E &other) const { return t == other.t && p == other.p; }
}e[N];

struct Hash {
	vector <ll> a;
	ll& operator[](int x) { return a[x - 1]; }
	int size() { return a.size(); }
	void init() { a.clear(); }
	void add(ll x) { a.push_back(x); }
	void gao() { sort(a.begin(), a.end()); a.erase(unique(a.begin(), a.end()), a.end()); }
	int get(ll x) { return lower_bound(a.begin(), a.end(), x) - a.begin() + 1; }	
}hp, htp1, htp2;

struct VSEG {
	struct node {
		int ls, rs;
		ll Max;
		void init() { ls = rs = Max = 0; }
	}t[N * 320];
	int tot;
	void init() { tot = 0; }
	int newnode() { assert(tot < N * 320 - 1); int now = ++tot; t[now].init(); return now; } 
	void pushup(int id) {
		t[id].Max = 0;
		int ls = t[id].ls, rs = t[id].rs;
		if (ls) chmax(t[id].Max, t[ls].Max);
		if (rs) chmax(t[id].Max, t[rs].Max);
	}
	void update(int &id, int l, int r, int pos, ll v) {
		if (!id) id = newnode();
		chmax(t[id].Max, v);
		if (l == r) {
			chmax(t[id].Max, v);
			return;
		}
		int mid = (l + r) >> 1;
		if (pos <= mid) update(t[id].ls, l, mid, pos, v);
		else update(t[id].rs, mid + 1, r, pos, v);
		pushup(id); 
	}
	ll query(int id, int l, int r, int ql, int qr) {
		if (ql > qr) return 0;
		if (!id) return 0;
		if (l >= ql && r <= qr) return t[id].Max;
		int mid = (l + r) >> 1;
		ll res = 0;
		if (ql <= mid) chmax(res, query(t[id].ls, l, mid, ql, qr));
		if (qr > mid) chmax(res, query(t[id].rs, mid + 1, r, ql, qr));
		return res;
	}
}vseg;

struct SEG {
	int t[N << 2];
	void build(int id, int l, int r) {
		t[id] = 0;
		if (l == r) return;
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
	}
	void update(int id, int l, int r, int x, int y, ll v) {
		vseg.update(t[id], 1, vLimit, y, v);
		if (l == r) return;
		int mid = (l + r) >> 1;
		if (x <= mid) update(id << 1, l, mid, x, y, v);
		else update(id << 1 | 1, mid + 1, r, x, y, v);
	}
	ll query(int id, int l, int r, int ql, int qr, int _ql, int _qr) {
		if (ql > qr) return 0;
		if (l >= ql && r <= qr) return vseg.query(t[id], 1, vLimit, _ql, _qr);
		int mid = (l + r) >> 1;
		ll res = 0;
		if (ql <= mid) chmax(res, query(id << 1, l, mid, ql, qr, _ql, _qr));
		if (qr > mid) chmax(res, query(id << 1 | 1, mid + 1, r, ql, qr, _ql, _qr));
		return res;
	}
}seg[2]; 

void run() {
	hp.init(); htp1.init(); htp2.init();
	for (int i = 1; i <= m; ++i) rd(a[i]);
	for (int i = 1; i <= m; ++i) rd(b[i]);	
	for (int i = 1; i <= n; ++i) {
		rd(e[i].t, e[i].p, e[i].c);
		e[i].t += b[e[i].p];
		e[i].p = a[e[i].p];
		hp.add(e[i].p);
	}
	sort(e + 1, e + 1 + n, [&](E a, E b) {
		if (a.t != b.t)
			return a.t < b.t;
		return a.p < b.p;
	});
	int _n = 1;
	for (int i = 2; i <= n; ++i) { 
		if (e[i] == e[_n])
			e[_n].c += e[i].c;
		else 
			e[++_n] = e[i];
	}
	n = _n;
	vLimit = n; 
	for (int i = 1; i <= n; ++i) {
		htp1.add(e[i].t - e[i].p);
		htp2.add(e[i].t + e[i].p); 
	}
	hp.gao(); htp1.gao(); htp2.gao();
	ll res = 0;
	vseg.init();
	seg[0].build(1, 1, vLimit);
	seg[1].build(1, 1, vLimit);
	for (int i = 1; i <= n; ++i) {
		int _p = hp.get(e[i].p);
		int _htp1 = htp1.get(e[i].t - e[i].p);
		int _htp2 = htp2.get(e[i].t + e[i].p);
		ll pre1 = seg[0].query(1, 1, vLimit, 1, _p, 1, _htp1);
		ll pre2 = seg[1].query(1, 1, vLimit, _p, vLimit, 1, _htp2);
		ll now = max(pre1, pre2) + e[i].c;
		seg[0].update(1, 1, vLimit, _p, _htp1, now);
		seg[1].update(1, 1, vLimit, _p, _htp2, now);
		chmax(res, now);
	}
	pt(res);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	cin >> n >> m; run();
//	while (cin >> n) run();
//    for (int kase = 1; kase <= _T; ++kase) {
//        cout << "Case #" << kase << ":\n";
//        run();
//    }
	return 0;
}
