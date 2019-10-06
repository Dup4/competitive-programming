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
constexpr int N = 1e5 + 10;
int n, q; char s[N], t[N];
bitset <N> b[30], res;
void run() {
	n = strlen(s + 1);
	for (int i = 0; i < 26; ++i) b[i].reset();
	for (int i = 1; i <= n; ++i) b[s[i] - 'a'][i] = 1;
	cin >> q;
	int op, l, r, x, y; char ch[10];
	while (q--) {
		cin >> op;
		if (op == 1) {
			cin >> x >> ch;
			b[s[x] - 'a'][x] = 0;
			s[x] = ch[0];
			b[s[x] - 'a'][x] = 1;
		} else {
			cin >> l >> r >> t;
			res.set();
			for (int i = 0; t[i]; ++i) {
				res = (res << 1);
				res = res >> l << l;
				res = res << (N - r - 1) >> (N - r - 1);
				res = res & (b[t[i] - 'a']);
			}
			pt(res.count());
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> (s + 1)) run();
	return 0;
}
