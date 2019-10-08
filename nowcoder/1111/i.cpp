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
constexpr int N = 5e4 + 10;
using B = bitset<N>;
int n, q; char s[N], t[N];
B mask[26], res;
void run() {
	cin >> (s + 1);
	for (int i = 0; i < 26; ++i) mask[i].reset();
	for (int i = 1; i <= n; ++i) mask[s[i] - 'a'][i] = 1;
	int op, k;
	while (q--) {
		cin >> op;
		if (!op) {
			cin >> t;
			res.set();
			for (int i = 0; t[i]; ++i) {
				res = (res << 1) & (mask[t[i] - 'a']);
			}
			pt(res.count());
		} else {
			cin >> t;;
			mask[s[op] - 'a'][op] = 0;
			s[op] = t[0];
			mask[s[op] - 'a'][op] = 1;
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n >> q) run();
	return 0;
}