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
constexpr int mod = 998244353;
template <class T1, class T2> inline void chadd(T1 &x, T2 y) { x += y; while (x >= mod) x -= mod; while (x < 0) x += mod; } 
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
ll n; 
struct node {
	ll a[4][4];
	node() { memset(a, 0, sizeof a); }
	node operator * (const node &other) const {
		node res = node();
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				for (int k = 0; k < 4; ++k)
					chadd(res.a[i][j], a[i][k] * other.a[k][j] % mod);
		return res;
	}
}res, base;
void qpow(ll n) {
	while (n) {
		if (n & 1) res = res * base;
		base = base * base;
		n >>= 1;
	}
}
void run() {
	res = node(); base = node();
	res.a[0][2] = 1;
	base.a[0][0] = base.a[0][1] = 1;
	base.a[1][0] = 1;
	base.a[2][2] = base.a[2][3] = 1;
	base.a[3][0] = base.a[3][2] = 1;
	qpow(n);
	cout << res.a[0][0] << endl;	
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n) run();
	return 0;
}
