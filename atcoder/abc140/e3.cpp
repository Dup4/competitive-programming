#include <bits/stdc++.h>
using namespace std;
#define debug(...) { printf("#  "); printf(__VA_ARGS__); puts(""); }
#define fi first
#define se second
#define endl "\n" 
using ll = long long;
using pII = pair <int, int>;
using pLL = pair <ll, ll>;
using VI = vector <int>;
using VL = vector <ll>;
constexpr int mod = 1e9 + 7;
template <class T1, class T2> inline void chadd(T1 &x, T2 y) { x += y; if (x >= mod) x -= mod; else if (x < 0) x += mod; } 
template <class T1, class T2> inline void chmax(T1 &x, T2 y) { if (x < y) x = y; }
template <class T1, class T2> inline void chmin(T1 &x, T2 y) { if (x > y) x = y; }
inline int rd() { int x; cin >> x; return x; }
template <class T> inline void rd(T &x) { cin >> x; }
template <class T> inline void rd(vector <T> &vec) { for (auto &it : vec) cin >> it; }
template <class T> inline void out(T s) { cout << s << "\n"; }
template <class T> inline void out(vector <T> &vec) { for (auto &it : vec) cout << it << " "; cout << endl; } 
inline ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
inline ll qpow(ll base, ll n) { ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
constexpr int N = 1e5 + 10;
int n, a[N]; 
pII pre[N], nx[N];
struct SEG {
	int M[N << 2];
	void build(int id, int l, int r) {
		if (l == r) {
			M[id] = a[l];
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
		M[id] = max(M[id << 1], M[id << 1 | 1]);
	}
	int ask(int id, int l, int r, int ql, int qr) {
		if (l >= ql && r <= qr) return M[id];
		int mid = (l + r) >> 1;
		int res = 0;
		if (ql <= mid) chmax(res, ask(id << 1, l, mid, ql, qr));
		if (qr > mid) chmax(res, ask(id << 1 | 1, mid + 1, r, ql, qr));
		return res;
	}
}seg;
int getl(int x, int y, int a) {
	if (x > y) return -1;
	int l = x, r = y, res = -1;
	while (r - l >= 0) {
		int mid = (l + r) >> 1;
		if (seg.ask(1, 1, n, mid, y) > a) {
			l = mid + 1;
			res = mid;	
		} else 
			r = mid - 1;
	}
	return res;
}
int getr(int x, int y, int a) {
	if (x > y) return -1;
	int l = x, r = y, res = -1;
	while (r - l >= 0) {
		int mid = (l + r) >> 1;
		if (seg.ask(1, 1, n, x, mid) > a) {
			r = mid - 1;
			res = mid;	
		} else 
			l = mid + 1;
	}
	return res;
}
void run() {
	for (int i = 1; i <= n; ++i) cin >> a[i];
	seg.build(1, 1, n);
	memset(pre, -1, sizeof pre);
	memset(nx, -1, sizeof nx);
	ll res = 0;
	for (int i = 1; i <= n; ++i) {
		int p = getl(1, i - 1, a[i]);
		if (p != -1) {
			pre[i].fi = p;
			p = getl(1, p - 1, a[i]);
			if (p != -1) pre[i].se = p;
		}
		p = getr(i + 1, n, a[i]);
		if (p != -1) {
			nx[i].fi = p;
			p = getr(p + 1, n, a[i]);
			if (p != -1) nx[i].se = p;
		}
	//	printf("%d %d %d %d %d\n", i, pre[i].fi, pre[i].se, nx[i].fi, nx[i].se);
		if (pre[i].fi != -1) {
			if (pre[i].se == -1) pre[i].se = 0;
			int Nx = nx[i].fi; if (Nx == -1) Nx = n + 1;
			res += 1ll * a[i] * (pre[i].fi - pre[i].se) * (Nx - i);
		}
		if (nx[i].fi != -1) {
			if (nx[i].se == -1) nx[i].se = n + 1;
			int Pre = pre[i].fi; if (Pre == -1) Pre = 0;
			res += 1ll * a[i] * (nx[i].se - nx[i].fi) * (i - Pre);
		}
	}
	cout << res << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n) run();
	return 0;
}
