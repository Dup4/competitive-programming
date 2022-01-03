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
constexpr int N = 2e5 + 10, INF = 0x3f3f3f3f;
int n, sze[3], pre[3][N]; 
void run() {
	n = sze[0] + sze[1] + sze[2];
	vector <int> vec[3];
	for (int i = 0; i < 3; ++i) {
		vec[i].clear(); vec[i].resize(sze[i]);
		for (auto &it : vec[i]) it = rd();
		sort(vec[i].begin(), vec[i].end());
		memset(pre[i], 0, sizeof pre[i]);
		for (auto &it : vec[i]) pre[i][it] = 1;
		for (int j = 1; j <= n; ++j) pre[i][j] += pre[i][j - 1];
		pre[i][n + 1] = 0;
	}
	int res = 0, Max = -INF; 
	for (int i = 0; i < 3; ++i) {
		for (int j = i; j < 3; ++j) {
			for (int k = 0; k <= n; ++k) {
				chmax(res, pre[i][k] + pre[j][n] - pre[j][k]);
			}
		}
	}
	for (int i = n; i >= 0; --i) {
		chmax(Max, pre[2][n] - pre[2][i] + pre[1][i]);
	    chmax(res, Max - pre[1][i] + pre[0][i]); 	
	}
	pt(n - res);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> sze[0] >> sze[1] >> sze[2]) run();
	return 0;
}
