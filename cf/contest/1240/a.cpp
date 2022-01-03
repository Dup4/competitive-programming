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
constexpr int N = 2e5 + 10;
int n, p[N], x, y, a, b; ll k; 
bool check(ll mid) {
	ll lcm = 1ll * a * b / gcd(a, b);
	ll cnt[3] = {mid / a - mid / lcm, mid / b - mid / lcm, mid / lcm};
	ll tot = 0;
	for (int i = 1; i <= mid; ++i) {
		if (cnt[2]) {
			tot += 1ll * p[i] / 100 * (x + y);
			--cnt[2];
		} else if (cnt[1]) {
			tot += 1ll * p[i] / 100 * y;
			--cnt[1];
		} else if (cnt[0]) {
			tot += 1ll * p[i] / 100 * x;
			--cnt[0];
		} else break;
	}
	return tot >= k;
}
void run() {
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> p[i];
	sort(p + 1, p + 1 + n, [&](int x, int y) { return x > y; }); 
	cin >> x >> a >> y >> b >> k;
	if (x > y) swap(x, y), swap(a, b);
	int l = 1, r = n, res = -1;
	while (r - l >= 0) {
		int mid = (l + r) >> 1;
		if (check(mid)) {
			res = mid;
			r = mid - 1;
		} else 
			l = mid + 1;
	}
	pt(res);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	int _T; cin >> _T;
	while (_T--) run();
	return 0;
}
