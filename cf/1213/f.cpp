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
constexpr int N = 2e5 + 10;
int n, k, p[N], q[N], f[N], g[N];   
void run() {
	for (int i = 1; i <= n; ++i) cin >> p[i];
	for (int i = 1; i <= n; ++i) cin >> q[i];
	for (int i = 1; i <= n; ++i) f[i] = i;
	int Min = 1e9;
	for (int i = n; i >= 1; --i) {
		f[p[i]] = min(Min, f[p[i]]);
		Min = min(Min, p[i]);
	}
	Min = 1e9;
	for (int i = n; i >= 1; --i) {
		f[q[i]] = min(Min, f[q[i]]);
		Min = min(Min, q[i]);
	}
	for (int i = n - 1; i >= 1; --i) f[i] = min(f[i + 1], f[i]); 
	int cnt = 1;
	for (int i = 2; i <= n; ++i) if (f[i] == i) ++cnt;
	if (cnt < k) return out("NO");
	out("YES");
	string res = "a"; 
	for (int i = 2; i <= n; ++i) { 
		if (f[i] == i && res.end()[-1] < 'z') {
			res += res.end()[-1] + 1; 
		} else {
			res += res.end()[-1];
		}
	}	
	cout << res << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n >> k) run();
	return 0;
}
