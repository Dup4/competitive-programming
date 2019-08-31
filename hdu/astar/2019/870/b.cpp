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
ll a, b, c, d, p, q, bit[110];  
bool ok(ll x) {
	for (int i = 0; i <= 62; ++i) 
		if (x == bit[i])
			return 1;
	return 0;
}
void run() {
	cin >> a >> b >> c >> d;
	if (a == b) {
		if (c == a && d == b) {
			out("Yes");
			out("");
			return;
		} else return out("No"); 
	}
	if ((c - a) % (a - b) || (d - b) % (b - a)) return out("No");
	p = (c - a) / (a - b);
	q = (d - b) / (b - a);
	if (p < 0 || q < 0 || !ok(p + q)) return out("No");
	string res = "";
	while (p + q) {
		if (p == q) break;
		if (p > q) {
			p -= q + 1;
			if (p % 2) break;
			p /= 2;
			res += "B";
		} else {
			q -= p + 1;
			if (q % 2) break;
			q /= 2;
			res += "A";
		}
	}
	if (p + q) return out("No");
	out("Yes");
	reverse(res.begin(), res.end());
	cout << res << endl;
}

int main() {
	bit[0] = 1;
	for (int i = 1; i <= 62; ++i) bit[i] = bit[i - 1] * 2;
	for (int i = 0; i <= 62; ++i) bit[i] -= 1;
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	int _T; cin >> _T;
	while (_T--) run();
	return 0;
}
