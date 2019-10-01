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
constexpr int N = 1e5 + 10;
mt19937 rnd(time(0));
int m; ll t[N], St[N], n, k, D; 
inline ll f(ll x) {
	ll tot = (k + m) * x;
	ll _D = D - x * St[m];
	int l = 0, r = m, pos = 0;
	while (r - l >= 0) {
		int mid = (l + r) >> 1;
		if (St[mid] * (n - x) <= _D) {
			pos = mid;
			l = mid + 1;
		} else {
			r = mid - 1;
		}
	}
	tot += 1ll * pos * (n - x);
	if (pos < m) tot += (_D - St[pos] * (n - x)) / t[pos + 1];
	else tot += k * (n - x);
	return tot;
}
ll gao(ll l, ll r) {
	ll res = 0;
	while (r - l >= 0) {
		ll mid = (l + r) >> 1;
		ll mmid = (l + mid) >> 1; 
		chmax(res, f(mid));
		chmax(res, f(mmid));
		if (f(mid) >= f(mmid)) {  
			l = mmid + 1;
		} else {
			r = mid - 1;
		}
	}
	return res;
}
inline ll random(ll l, ll r) {
	return rnd() % (r - l + 1) + l;
}
void run() {
	cin >> n >> m >> k >> D;
	for (int i = 1; i <= m; ++i) cin >> t[i];
	sort(t + 1, t + 1 + m); 
	St[0] = 0;
	for (int i = 1; i <= m; ++i) St[i] = St[i - 1] + t[i];  
	ll res = gao(0, D / St[m]);
	for (int i = 1; i <= 10; ++i) { 
		chmax(res, gao(random(0, D / St[m]), D / St[m]));
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
