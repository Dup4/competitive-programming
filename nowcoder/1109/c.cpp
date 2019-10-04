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
constexpr ll mod = 1ll << 61;
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
constexpr int N = 1e5 + 10;
int n;  
struct Base {
	static const int L = 61;
	ll a[L];
	Base() {
		memset(a, 0, sizeof a);
	}
	ll& operator [](int x) {
		return a[x];
	}
	ll operator [](int x) const {
		return a[x];
	}
	void insert(ll x) {
		for (int i = L - 1; i >= 0; --i) {
			if ((x >> i) & 1) {
				if (a[i]) x ^= a[i];
				else {
					a[i] = x;
					break;
				}
			}
		}
	}
	friend Base intersection(const Base &a, const Base &b) {
		Base ans = Base(), c = b, d = b;
		for (int i = 0; i <= L - 1; ++i) {
			ll x = a[i];
			if (!x) continue;
			int j = i; ll T = 0;
			for (; j >= 0; --j) {
				if ((x >> j) & 1) {
					if (c[j]) {
						x ^= c[j];
						T ^= d[j];   
					} else {
						break;
					}
				}
			}
			if (!x) ans[i] = T;
			else {
				c[j] = x;
				d[j] = T;
			}
		}
		return ans;
	}
}A, B;
void run() {
	A = Base(); B = Base();
	ll x;
	for (int i = 1; i <= n; ++i) {
		cin >> x;
		A.insert(x);
	}
	for (int i = 1; i <= n; ++i) {
		cin >> x;
		B.insert(x);
	}
	A = intersection(A, B);
	int res = 0;
	for (int i = 60; i >= 0; --i)
		if (A[i])
			++res;
	pt(qpow(2, res)); 
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n) run();
	return 0;
}
