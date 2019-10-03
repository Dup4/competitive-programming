#include <bits/stdc++.h>
using namespace std;
#define debug(...) { printf("#  "); printf(__VA_ARGS__); puts(""); }
#define fi first
#define se second
#define endl "\n" 
using ll = long long;
using ull = unsigned long long; 
using pII = pair <int, int>;
using pLL = pair <ll, ll>;
using VI = vector <int>;
using VL = vector <ll>;
constexpr int mod = 1e9 + 7;
template <class T1, class T2> inline void chadd(T1 &x, T2 y) { x += y; while (x >= mod) x -= mod; while (x < 0) x += mod; } 
template <class T1, class T2> inline void chmax(T1 &x, T2 y) { if (x < y) x = y; }
template <class T1, class T2> inline void chmin(T1 &x, T2 y) { if (x > y) x = y; }
inline int rd() { int x; cin >> x; return x; }
template <class T> inline void rd(T &x) { cin >> x; }
template <class T> inline void rd(vector <T> &vec) { for (auto &it : vec) cin >> it; }
template <class T> inline void pt(T s) { cout << s << "\n"; }
template <class T> inline void pt(vector <T> &vec) { for (auto &it : vec) cout << it << " "; cout << endl; } 
inline ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
inline ll qpow(ll base, ll n) { ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
const int N = 1e5 + 10, M = 28;
int n, m, q; 
struct node {
	int ls, rs, sum; 
	node() {
		ls = rs = sum = 0;
	}
}t[N * M];  
int tot, rt[2];  
inline int newnode() {
	++tot;
	assert(tot < N * M);
	t[tot] = node();
	return tot;
}
inline void init() { tot = 0; rt[0] = newnode(); rt[1] = newnode(); }
void up(int id) {
	int ls = t[id].ls, rs = t[id].rs;
	t[id].sum = 0;
	if (ls) t[id].sum += t[ls].sum;
	if (rs) t[id].sum += t[rs].sum;
}
void update(int &id, int l, int r, int ql, int qr) {
	if (!id) id = newnode();
	if (l >= ql && r <= qr) {
		t[id].sum = r - l + 1;
		return;
	}
	int mid = (l + r) >> 1;
	if (ql <= mid) update(t[id].ls, l, mid, ql, qr);
	if (qr > mid) update(t[id].rs, mid + 1, r, ql, qr);
	up(id);
}
void run() {
	init(); 
	ll a = 0, b = 0;
	for (int i = 1, op, l, r; i <= q; ++i) {
		cin >> op >> l >> r;
		update(rt[op - 1], 1, 1000000000, l, r);
		a = t[rt[0]].sum;
		b = t[rt[1]].sum;
		ll res = 1ll * n * m;
		if (a == 0) {
			res -= b * (n - 1);
		} else if (b == 0) {
			res -= a * (m - 1);
		} else {
			res -= a * m + b * n - a * b;
			++res;
		}
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
