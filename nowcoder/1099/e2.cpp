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
constexpr int N = 110 + 10;
using B = bitset<100>; 
using pBI = pair<B, int>;
char s[N]; int n; 
unordered_map <B, int> f[52];
inline int ord(char c) { return c - '0'; }
B b;
void run() {
	n = strlen(s + 1);
	b.reset(); 
	f[0][b] = 1;
	for (int i = 1; i <= n; ++i) f[i].clear();
	for (int i = 1; i <= n; ++i) {
		int p = ord(s[i]);
		int v1 = p, v2 = p;
		if (i < n) v1 = ord(s[i + 1]);
	   	if (s[i + 1] != '0' && i < n - 1) v2 = ord(s[i + 1]) * 10 + ord(s[i + 2]);
		for (auto &it : f[i - 1]) {
			if (it.fi[p] == 0 && (it.fi[v1] == 0 || it.fi[v2] == 0)) {
				b[p] = 1;
				f[i][it.fi | b] += it.se;
				b[p] = 0;
			}
		}	
		if (i > 1 && s[i - 1] != '0') {
			p = ord(s[i - 1]) * 10 + ord(s[i]);
			if (v2 == v1) v2 = p;
			for (auto &it : f[i - 2]) {
				if (it.fi[p] == 0 && (it.fi[v1] == 0 || it.fi[v2] == 0)) {
					b[p] = 1;
					f[i][it.fi | b] += it.se;
					b[p] = 0;
				}
			}
		}
	//	for (auto &it : f[i])
	//		cout << it.fi << " "  << it.se << endl;
	//	if (i > 2) f[i - 2].clear();
	}
	int res = 0;
	for (auto &it : f[n]) {
		res += it.se;
	}
	pt(res);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> (s + 1)) run();
	return 0;
}
