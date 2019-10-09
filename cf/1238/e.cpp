#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
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
int n, m, w[30][30], f[1 << 21], g[1 << 21][22], num[1 << 21], lg[1 << 21]; char s[N]; 
void run() {
    cin >> (s + 1);	
	memset(w, 0, sizeof w);
	for (int i = 1; i < n; ++i) {
		int c = s[i] - 'a', c2 = s[i + 1] - 'a';
		if (c == c2) continue;
		++w[c][c2];
		++w[c2][c];
	}
	int lim = 1 << m;
	memset(g, 0, sizeof g);
	for (int i = 1; i < lim; ++i) {
		for (int j = 0; j < m; ++j) {
			int lb = i & -i;
			g[i][j] = g[i ^ lb][j] + w[j][lg[lb]]; 
		}
	}
	memset(f, 0x3f, sizeof f); f[0] = 0; 
	for (int i = 0; i < lim; ++i) {
		for (int j = 0; j < m; ++j) {
			if (!((i >> j) & 1)) {
				int pos = num[i] + 1;
				chmin(f[i ^ (1 << j)], f[i] + g[i][j] * pos - g[(lim - 1) ^ i ^ (1 << j)][j] * pos);
			}
		}
	}
	pt(f[lim - 1]);
}

int main() {
	memset(num, 0, sizeof num);
	for (int i = 1; i < 1 << 20; ++i) 
		num[i] = num[i ^ (i & -i)] + 1;
	memset(lg, 0, sizeof lg);
	lg[0] = -1; lg[1] = 0; 
	for (int i = 2; i < 1 << 20; i <<= 1) lg[i] = lg[i >> 1] + 1;
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n >> m) run();
	return 0;
}
