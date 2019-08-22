#include <bits/stdc++.h>
using namespace std;
#define debug(...) { printf("#  "); printf(__VA_ARGS__); puts(""); }
#define ll long long
#define pii pair <int, int>
#define fi first
#define se second
const int N = 110 + 10;
const int mod = 1e9 + 7;
template <class T1, class T2> inline void chadd(T1 &x, T2 y) { x += y; if (x >= mod) x -= mod; } 
template <class T1, class T2> inline void chmax(T1 &x, T2 y) { if (x < y) x = y; }
template <class T1, class T2> inline void chmin(T1 &x, T2 y) { if (x > y) x = y; }
inline int rd() { int x; cin >> x; return x; }
template <class T > inline void out(T s) { cout << s << "\n"; }
inline ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
inline ll qpow(ll base, ll n) { ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
int n, m, a[N][N], b[N][N];
bool ok() {
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			if (a[i][j] != b[i][j])
				return 0;
	return 1;
}
void run() {
	memset(b, 0, sizeof b);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			cin >> a[i][j];
	vector <pii> res;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (i >= 2 && j >= 2 && a[i][j] && b[i][j] == 0) {
				if (a[i - 1][j] == 1 && a[i - 1][j - 1] == 1 && a[i][j - 1] == 1) {
					res.push_back(pii(i - 1, j - 1));
					b[i - 1][j] = 1;
					b[i - 1][j - 1]  = 1;
					b[i][j - 1] = 1;
					b[i][j] = 1;
				}
			}
		}
	}
	if (ok()) {
		sort(res.begin(), res.end());
		res.erase(unique(res.begin(), res.end()), res.end());
		cout << res.size() << "\n";
		for (auto &it : res) cout << it.fi << " " << it.se << "\n";
	} else out("-1");
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n >> m) run();
	return 0;
}
