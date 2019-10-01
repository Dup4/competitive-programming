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
constexpr int N = 2e6 + 10, D = (1 << 20) - 1; 
int n, h[N]; char s[N];  
inline int calc(int x) {
	int res = 0;
	while (x) {
		res += x % 2;
		x /= 2;
	}
	return res;
}
void run() {
	n = strlen(s + 1);
	memset(h, 0, sizeof h);	
	int res = 0;
	for (int i = n; i >= 1; --i) {
		int mask = 0, num = 0;
		for (int j = i; j >= 1; --j) {
			int c = s[j] - 'a';
			if (((mask >> c) & 1) == 0) {
				mask |= 1 << c; 
				++num;
				chmax(res, num + h[D ^ mask]);
			} else break;
		}
		num = 0, mask = 0;
		for (int j = i; j <= n; ++j) {
			int c = s[j] - 'a';
			if (((mask >> c) & 1) == 0) {
				mask |= 1 << c;
				++num;
				for (int k = mask; k <= D; k = (k + 1) | mask) {
					if (h[k] >= num) break;
					h[k] = num;
				}
			} else break;
		}
	}	
	pt(res);
}

int main() {
	int mask = 1, d = (1 << 5) - 1;
	for (int k = mask; k <= d; k = (k + 1) | mask) {
		cout << k << endl;
	}
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> (s + 1)) run();
	return 0;
}
