#include <bits/stdc++.h>
using namespace std;
#define debug(...) { printf("#  "); printf(__VA_ARGS__); puts(""); }
#define ll long long
#define pII pair <int, int>
#define fi first
#define se second
#define endl "\n" 
constexpr int N = 2e6 + 10;
constexpr int mod = 1e9 + 7;
template <class T1, class T2> inline void chadd(T1 &x, T2 y) { x += y; if (x >= mod) x -= mod; else if (x < 0) x += mod; } 
template <class T1, class T2> inline void chmax(T1 &x, T2 y) { if (x < y) x = y; }
template <class T1, class T2> inline void chmin(T1 &x, T2 y) { if (x > y) x = y; }
inline int rd() { int x; cin >> x; return x; }
template <class T> inline void rd(T &x) { cin >> x; }
template <class T > inline void out(T s) { cout << s << "\n"; }
inline ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
inline ll qpow(ll base, ll n) { ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
int n, a[N]; pII id[1 << 22];  
void DFS(int mask, int x) {
	if (id[mask].fi != -1) return;
	if (id[mask].se == -1) id[mask].se = x;
	else if (id[mask].se != x) id[mask].fi = x;
	else return;
	for (int i = 21; i >= 0; --i) if ((mask >> i) & 1)
		DFS(mask ^ (1 << i), x);
}
void run() {
	memset(id, -1, sizeof id); 
	for (int i = 1; i <= n; ++i) cin >> a[i];
	for (int i = n; i >= 1; --i) DFS(a[i], i);
	int res = 0;
	for (int i = 1; i <= n; ++i) {
		int now = 0;
		for (int j = 21; j >= 0; --j) if (((a[i] >> j) & 1) == 0) {
			if (id[now ^ (1 << j)].fi > i) { 
				now = now ^ (1 << j); 
			}
		}
		if (id[now].fi > i) res = max(res, a[i] | now);
	}
	cout << res << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n) run();
	return 0;
}
