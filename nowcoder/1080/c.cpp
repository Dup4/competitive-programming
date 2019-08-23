#include <bits/stdc++.h>
using namespace std;
#define debug(...) { printf("#  "); printf(__VA_ARGS__); puts(""); }
#define ll long long
#define pii pair <int, int>
#define fi first
#define se second
#define endl "\n" 
constexpr int N = 1e5 + 10;
constexpr int mod = 1e9 + 7;
template <class T1, class T2> inline void chadd(T1 &x, T2 y) { x += y; if (x >= mod) x -= mod; else if (x < mod) x += mod; } 
template <class T1, class T2> inline void chmax(T1 &x, T2 y) { if (x < y) x = y; }
template <class T1, class T2> inline void chmin(T1 &x, T2 y) { if (x > y) x = y; }
inline int rd() { int x; cin >> x; return x; }
template <class T> inline void rd(T &x) { cin >> x; }
template <class T > inline void out(T s) { cout << s << "\n"; }
inline ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
inline ll qpow(ll base, ll n) { ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
int n; pii a[N]; 
void run() {
	for (int i = 1; i <= n; ++i)
		cin >> a[i].fi >> a[i].se;
	sort(a + 1, a + 1 + n, [](pii x, pii y){
		return x.se > y.se; 	
	});
	ll sum = 0, res = 0;
	multiset <int> se;
	for (int i = 1; i <= n; ++i) {
		se.insert(a[i].fi);
		sum += a[i].fi;
		while ((int)se.size() > a[i].se) {
			sum -= *se.begin();
			se.erase(se.begin());
		}
		res = max(res, sum);
	}
	cout << res << "\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n) run();
	return 0;
}
