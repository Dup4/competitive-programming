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
constexpr int N = 2e5 + 10;
int n, m, x[N]; ll S[N]; 
inline void add(int l, int r, int v) {
	if (l > r) return;
	S[l] += v;
	S[r + 1] -= v;
}
void run() {
	memset(S, 0, sizeof S); 
	for (int i = 1; i <= m; ++i) cin >> x[i];
	for (int i = 1; i < m; ++i) {
		int a = x[i], b = x[i + 1];
		if (a == b) continue;
		if (a > b) swap(a, b);
		add(1, a - 1, b - a);
		add(b + 1, n, b - a);
		add(a + 1, b - 1, b - a - 1);
		add(a, a, b - 1);
		add(b, b, a);
	}
	for (int i = 1; i <= n; ++i) S[i] += S[i - 1];
	for (int i = 1; i <= n; ++i)
		cout << S[i] << " \n"[i == n];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n >> m) run();
	return 0;
}
