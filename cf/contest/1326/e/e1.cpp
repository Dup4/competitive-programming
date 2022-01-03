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
constexpr int N = 3e5 + 10; 
int n, p[N], fp[N], q[N]; 

struct SEG {
	struct node {
		int Max;
		node() { Max = 0; }
		node operator + (const node &other) const {
			node res = node();
			res.Max = max(Max, other.Max);
			return res;
		}		
	}t[N << 2];
	void init() { memset(t, 0, sizeof t); }
	void update(int id, int l, int r, int pos, int v) {
		if (l == r) {
			t[id].Max = v;
			return;
		}
		int mid = (l + r) >> 1;
		if (pos <= mid) update(id << 1, l, mid, pos, v);
		else update(id << 1 | 1, mid + 1, r, pos, v);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	int query(int id, int l, int r, int ql, int qr) {
		if (l >= ql && r <= qr) return t[id].Max;
		int mid = (l + r) >> 1;
		int res = 0;
		if (ql <= mid) chmax(res, query(id << 1, l, mid, ql, qr));
		if (qr > mid) chmax(res, query(id << 1 | 1, mid + 1, r, ql, qr));
		return res;
	}
}seg;

struct TSEG {
	struct node {
		int Max, pos, lazy;
		node(int Max = 0, int pos = 0, int lazy = 0) : Max(Max), pos(pos), lazy(lazy) {}
		void up(int _lazy) {
			Max += _lazy;
			lazy += _lazy;
		}
		node operator + (const node &other) const {
			node res = node();
			if (Max >= other.Max) { 
				res = *this;
	//			res.Max = Max;
	//			res.pos = pos;
			} else {
				res = other;
	//			res.Max = other.Max;
	//			res.pos = other.pos;
			}
			res.lazy = 0;
			return res;
		}
	}t[N << 2];
	void build(int id, int l, int r) {
		if (l == r) {
			t[id].pos = l;
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r); 
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	void pushdown(int id) {
		int &lazy = t[id].lazy;
		t[id << 1].up(lazy);
		t[id << 1 | 1].up(lazy);
		lazy = 0;
	}
	void update(int id, int l, int r, int ql, int qr, int v) {
		if (l >= ql && r <= qr) {
			t[id].up(v);
			return;
		}
		int mid = (l + r) >> 1;
		pushdown(id);
		if (ql <= mid) update(id << 1, l, mid, ql, qr, v);
		if (qr > mid) update(id << 1 | 1, mid + 1, r, ql, qr, v);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	int query(int id, int l, int r, int pos) {
		if (l == r) return t[id].Max;
		int mid = (l + r) >> 1;
		if (pos <= mid) return query(id << 1, l, mid, pos);
		else return query(id << 1 | 1, mid + 1, r, pos);
	}
}tseg;

void run() {
	for (int i = 1; i <= n; ++i) rd(p[i]), fp[p[i]] = i;
	for (int i = 1; i <= n; ++i) rd(q[i]);
	seg.init();
	tseg.build(1, 1, n);
	for (int i = 1; i <= n; ++i) seg.update(1, 1, n, i, p[i]);
	vector <int> vec;
	vec.push_back(n);
	for (int i = 1; i < n; ++i) {
		//dbg(i, q[i], n);
		tseg.update(1, 1, n, q[i], n, 1);
		int pos = tseg.t[1].pos;
	//	dbg(i, tseg.t[1].pos, tseg.t[1].Max);
		int Max = seg.query(1, 1, n, 1, pos);
	//	dbg(i, pos, Max);
		//dbg(i, tseg.query(1, 1, n, 5));
		//dbg(i, fp[Max], n);
		tseg.update(1, 1, n, fp[Max], n, -1);
		seg.update(1, 1, n, fp[Max], 0);
		vec.push_back(seg.t[1].Max);
	}
	for (int i = 0; i < n; ++i)
		cout << vec[i] << " \n"[i == n - 1];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n) run();
//    for (int kase = 1; kase <= _T; ++kase) {
//        cout << "Case #" << kase << ":\n";
//        run();
//    }
	return 0;
}
