#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
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
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
template <template<typename...> class T, typename t, typename... A> 
void err(const T <t> &arg, const A&... args) { for (auto &v : arg) cout << v << ' '; err(args...); }
inline void pt() { cout << endl; } 
template <class T, class... Ts> void pt(const T& arg, const Ts&... args) { cout << arg << ' '; pt(args...); }
template <template<typename...> class T, typename t, typename... A> 
void pt(const T <t> &arg, const A&... args) { for (auto &v : arg) cout << v << ' '; pt(args...); }
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
inline ll qpow(ll base, ll n) { ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
//head
constexpr int N = 1e3 + 10, INF = 0x3f3f3f3f;
int n, a[N], f[N], g[N], h[N]; char s[N]; 
int calc() {
	f[0] = g[0] = h[n + 1] = 0;
	for (int i = 1; i <= n; ++i) f[i] = f[i - 1] + a[i];
	for (int i = 1; i <= n; ++i) g[i] = max(g[i - 1], f[i]);
	for (int i = n; i >= 1; --i) h[i] = max(h[i + 1], f[i]);
	if (f[n] != 0) return 0; 
	int res = 0; 
	for (int i = n; i >= 1; --i) {
		if (h[i] - f[i - 1] <= 0 && g[i - 1] + (f[n] - f[i - 1]) <= 0)
			++res;	
	}
	return res;
}
void run() {
	cin >> (s + 1);
	for (int i = 1; i <= n; ++i) {
		if (s[i] == '(') a[i] = -1;
		else a[i] = 1;
	}
	int num = calc(), x = 1, y = 1;
	for (int i = 1; i <= n; ++i) {
		for (int j = i + 1; j <= n; ++j) {
			swap(a[i], a[j]);
			int now = calc();
			if (now > num) {
				num = now;
				x = i, y = j;
			}
			swap(a[i], a[j]);
		}
	}
	pt(num);
	pt(x, y);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n) run();
	return 0;
}