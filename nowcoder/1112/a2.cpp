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
ll n, m, f[10], g[10], bit[10]; 
inline ll gao(ll n, ll m) {
	n /= 7;
	for (int i = 5; i >= 0; --i) {
		f[i] = n / bit[i];
		g[i] = m / bit[i];
		for (int j = i + 1; j <= 5; ++j) f[i] -= f[j];
	}
	ll res = 0;
	for (int i = 0; i <= 5; ++i) {
		res += f[i] * g[5 - i];
	}
	return res;
}
inline ll gao2(ll n, ll m) {
	m /= 7;
	for (int i = 5; i >= 0; --i) {
		f[i] = n / bit[i];
		g[i] = m / bit[i];
		for (int j = i + 1; j <= 5; ++j) f[i] -= f[j];
	}
	ll res = 0;
	for (int i = 0; i <= 5; ++i) {
		res += f[i] * g[5 - i];
	}
	return res;
}
inline ll gao3(ll n, ll m) {
	n /= 7; m /= 7;
	for (int i = 5; i >= 0; --i) {
		f[i] = n / bit[i];
		g[i] = m / bit[i];
		for (int j = i + 1; j <= 5; ++j) f[i] -= f[j];
	}
	ll res = 0;
	for (int i = 0; i <= 5; ++i) {
		res += f[i] * g[5 - i];
	}
	return res;
}
void run() {
	ll res = gao(n / 9, m) + gao(n / 3 - (n / 9), m / 3) + gao(n - n / 3, m / 9);
	res = gao2(n / 9, m) + gao2(n / 3 - (n / 9), m / 3) + gao2(n - n / 3, m / 9);
//	res -= gao3(n / 9, m) + gao3(n / 3 - (n / 9), m / 3) + gao3(n - n / 3, m / 9);
	pt(res);
}

int main() {
	bit[0] = 1; bit[1] = 2; bit[2] = 4; bit[3] = 8; bit[4] = 16; bit[5] = 32;
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n >> m) run();
	return 0;
}
