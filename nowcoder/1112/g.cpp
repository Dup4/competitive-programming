#include <bits/stdc++.h>
#define debug(...) { printf("#  "); printf(__VA_ARGS__); puts(""); }
#define fi first
#define se second
#define endl "\n" 
using namespace std;
using db = double;
using ll = long long;
using ull = unsigned long long; 
using pII = pair <int, int>;
using pLL = pair <ll, ll>;
constexpr int mod = 1e9 + 7;
template <class T1, class T2> inline void chadd(T1 &x, T2 y) { x += y; while (x >= mod) x -= mod; while (x < 0) x += mod; } 
template <class T1, class T2> inline void chmax(T1 &x, T2 y) { if (x < y) x = y; }
template <class T1, class T2> inline void chmin(T1 &x, T2 y) { if (x > y) x = y; }
inline int rd() { int x; cin >> x; return x; }
template <class T> inline void rd(T &x) { cin >> x; }
template <class T> inline void rd(vector <T> &vec) { for (auto &it : vec) cin >> it; }
inline void pt() { cout << endl; }
template <class T, class... Ts> void pt(const T& arg, const Ts&... args) { cout << arg << " "; pt(args...); }
template <class T> inline void pt(const T &s) { cout << s << "\n"; }
template <class T> inline void pt(const vector <T> &vec) { for (auto &it : vec) cout << it << " "; cout << endl; } 
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
inline ll qpow(ll base, ll n) { ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
constexpr int N = 1e5 + 10;
int n, q, S[N]; char s[N]; 
struct SEG {
	struct node {
		int Min, lazy;
		node() { Min = -1e9, lazy = 0; }
		void up(int x) {
			Min += x;
			lazy += x;
		}
		node operator + (const node &other) const {
			node res = node();
			res.Min = min(Min, other.Min);
			return res;
		}
	}t[N << 2];
	void build(int id, int l, int r) {
		if (l == r) {
			t[id] = node();
			t[id].Min = S[l];
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	void down(int id) {
		if (!t[id].lazy) return;
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
		down(id);
		if (ql <= mid) update(id << 1, l, mid, ql, qr, v);
		if (qr > mid) update(id << 1 | 1, mid + 1, r, ql, qr, v);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
}seg;
void run() {
	cin >> (s + 1);
	S[0] = 0;
	for (int i = 1; i <= n; ++i) {
		S[i] = S[i - 1] + (s[i] == '(' ? 1 : -1);
	}
	bool F = 1;
	if (S[n] != 0) F = 0;
	seg.build(1, 1, n);
	int x, y;
	while (q--) {
		cin >> x >> y;
		if (x > y) swap(x, y);
		if (!F) {
			pt("No");
			continue;
		}
		if (s[x] != s[y]) {
			seg.update(1, 1, n, x, y - 1, 2 * (s[x] == '(' ? -1 : 1));
		} 
		if (seg.t[1].Min >= 0) pt("Yes");
		else pt("No");
		if (s[x] != s[y]) {
			seg.update(1, 1, n, x, y - 1, 2 * (s[x] == '(' ? 1 : -1));
		} 
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n >> q) run();
	return 0;
}
