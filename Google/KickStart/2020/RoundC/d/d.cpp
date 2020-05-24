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
constexpr int N = 2e5 + 10, S = 400; 
int n, q, a[N], b[N]; 

struct SEG {
	struct node {
		//0 + 开头 1 - 开头
		ll sum[2], base[2];
		int len;
		node() { sum[0] = sum[1] = 0; base[0] = base[1] = 0; len = 0; }
		node operator + (const node &other) const {
			node res = node();
			res.len = len + other.len;
			if (len % 2 == 0) {
				res.base[0] = base[0] + other.base[0];
				res.sum[0] = sum[0] + other.sum[0] + 1ll * len * other.base[0];
				res.base[1] = base[1] + other.base[1];
				res.sum[1] = sum[1] + other.sum[1] + 1ll * len * other.base[1];
			} else {
				res.base[0] = base[0] + other.base[1];
				res.sum[0] = sum[0] + other.sum[1] + 1ll * len * other.base[1];
				res.base[1] = base[1] + other.base[0];
				res.sum[1] = sum[1] + other.sum[0] + 1ll * len * other.base[0];
			}
			return res;
		}
	}t[N << 2], res;
	void build(int id, int l, int r) {
		if (l == r) {
			t[id].sum[0] = t[id].base[0] = a[l]; 
			t[id].sum[1] = t[id].base[1] = -a[l];
			t[id].len = 1;
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	void query(int id, int l, int r, int ql, int qr) {
		if (l >= ql && r <= qr) {
			res = res + t[id];
			return;
		}
		int mid = (l + r) >> 1;
		if (ql <= mid) query(id << 1, l, mid, ql, qr);
		if (qr > mid) query(id << 1 | 1, mid + 1, r, ql, qr);
	}
}seg;

void run() {
	rd(n, q);
	for (int i = 1; i <= n; ++i) rd(a[i]), b[i] = a[i];
	seg.build(1, 1, n);
	vector <pII> vec;
	char op[10]; int x, y;
	ll ans = 0;
	for (int i = 1; i <= q; ++i) {
		cin >> (op + 1) >> x >> y;
		if (op[1] == 'U') { 
			vec.push_back(pII(x, y));
			continue;
		}
		if (SZ(vec) > S) {
			for (auto &it : vec) {
				a[it.fi] = it.se;
				b[it.fi] = it.se;
			}
			seg.build(1, 1, n);
			vec.clear();
		}
		int l = x, r = y;
		seg.res = SEG::node();
		seg.query(1, 1, n, l, r);
		ll res = seg.res.sum[0];
		//dbg(i, res);
		for (auto &it : vec) {
			int x = it.fi, y = it.se;
			if (x >= l && x <= r) {
				int pre = b[x] * (x - l + 1);
				b[x] = y;
				int now = b[x] * (x - l + 1);
				if ((x - l) & 1) pre *= -1, now *= -1;
				res -= pre;
		 		res += now;		
			}
		}
		for (auto &it : vec) {
			b[it.fi] = a[it.fi];
		}
		ans += res;
	}
	pt(ans);
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
