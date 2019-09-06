#include <bits/stdc++.h>
using namespace std;
#define debug(...) { printf("#  "); printf(__VA_ARGS__); puts(""); }
#define fi first
#define se second
#define endl "\n" 
using ll = long long;
using pII = pair <int, int>;
using pLL = pair <ll, ll>;
using pLI = pair <ll, int>;
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
ll n;
mt19937 rnd(time(0));
ll ex_gcd(ll a, ll b, ll &x, ll &y) {
	if (!a && !b) return -1;
	if (!b) {x = 1, y = 0; return a; }
	ll d = ex_gcd(b, a % b, y, x);
	y -= a / b * x;
	return d;
}
inline ll mul(ll a, ll b, ll p) {
	return (a * b - (ll)(a / (long double)p * b + 1e-3) * p + p) % p;
}
inline ll qmod(ll base, ll n, ll p) {
	ll res = 1;
	base %= p;
	while (n) {
		if (n & 1) {
			res = mul(res, base, p);
		}
		base = mul(base, base, p);
		n >>= 1;
	}
	return res;
}
struct Mill {
	ll n, fac[220]; int tot; 
	const int C = 2307;
	const int S = 10;
	inline bool check(ll a, ll n) {
		ll m = n - 1, x, y;
		int j = 0;
		while (!(m & 1)) {
			m >>= 1;
			++j;
		}
		x = qmod(a, m, n);
		for (int i = 1; i <= j; x = y, ++i) {
			y = mul(x, x, n);
			if (y == 1 && x != 1 && x != n - 1) {
				return 1;
			}
		}
		return y != 1;
	}
	inline bool miller_rabin(ll n) {
		if (n < 2) {
			return 0;
		} else if (n == 2) {
			return 1;
		
		} else if (! (n & 1)) {
			return 0;
		}
		for (int i = 0; i < S; ++i) {
			if (check(rnd() % (n - 1) + 1, n)) {
				return 0;
			}
		}
		return 1;
	}
	inline ll pollard_rho(ll n, int c) {
		ll i = 1, k = 2, x = rnd() % n, y = x, d;
		while (1) {
			++i; x = (mul(x, x, n) + c) % n;
			d = gcd(y - x, n);
			if (d > 1 && d < n) {
				return d;
			}
			if (y == x) {
				return n;
			}
			if (i == k) {
				y = x;
				k <<= 1;
			}
		}
	}
	inline void findfac(ll n, int c) {
		if (n == 1) {
			return;
		}
		if (miller_rabin(n)) {
			fac[++tot] = n;
			return;
		}
		ll m = n;
		while (m == n) {
			m = pollard_rho(n, c--);
		}
		findfac(m, c);
		findfac(n / m, c);
	}
	inline void gao(ll _n, vector <ll> &vec) {
		vec.clear();
		n = _n;
		tot = 0;
		findfac(n, C);
		sort(fac + 1, fac + 1 + tot); 
		vec.push_back(fac[1]);	
		for (int i = 2; i <= tot; ++i) {
			if (fac[i] == fac[i - 1])
				vec.back() *= fac[i];
			else
				vec.push_back(fac[i]);
		}
	//	vec.push_back(1); 
	//	int sze;
	//	for (int i = 1; i <= tot; ++i) {
	//		if (i == 1 || fac[i - 1] % fac[i]) {
	//			sze = vec.size();
	//		} else {
	//			fac[i] *= fac[i - 1];
	//		}
	//		for (int j = 0; j < sze; ++j) {
	//			vec.push_back(fac[i] * vec[j]);
	//		}
	//	}
	}
}mill;
vector <ll> fac;
void run() {
	cin >> n; n *= 2;
	mill.gao(n, fac);
	int sze = fac.size();
	int S = 1 << sze;
	ll res = 1e18;
	for (int i = 0; i < S; ++i) {
		ll a = 1, b = 1, x, y;
		for (int j = 0; j < sze; ++j) {
			if ((i >> j) & 1)
				a = a * fac[j];
			else 
				b = b * fac[j];
		}
		ex_gcd(a, b, x, y);
		if (!x || !y) {
			
		}
		cout << a << " " << b << " " << x << " " << y << endl;
		res = min(res, y * b);
	}
	cout << res << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	int _T; cin >> _T;
	while (_T--) run();
	return 0;
}
