#include <bits/stdc++.h>
using namespace std;
#define endl "\n" 
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
#define mkp make_pair
#define all(x) (x).begin(), (x).end()
using db = double;
using ll = long long;
using ull = unsigned long long; 
using pII = pair <int, int>;
using pLL = pair <ll, ll>;
constexpr int mod = 1e9 + 7;
template <class T1, class T2> inline void chadd(T1 &x, T2 y, int Mod = mod) { x += y; while (x >= Mod) x -= Mod; while (x < 0) x += Mod; } 
template <class T1, class T2> inline void chmax(T1 &x, T2 y) { if (x < y) x = y; }
template <class T1, class T2> inline void chmin(T1 &x, T2 y) { if (x > y) x = y; }
inline int nextInt() { int x; cin >> x; return x; }
void rd() {}
template <class T, class... Ts> void rd(T& arg, Ts&... args) { cin >> arg; rd(args...); }
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
template <template<typename...> class T, typename t, typename... A> 
void err(const T <t> &arg, const A&... args) { for (auto &v : arg) cout << v << ' '; err(args...); }
void ptt() { cout << endl; }
template <class T, class... Ts> void ptt(const T& arg, const Ts&... args) { cout << ' ' << arg; ptt(args...); }
template <class T, class... Ts> void pt(const T& arg, const Ts&... args) { cout << arg; ptt(args...); }
void pt() {}
template <template<typename...> class T, typename t, typename... A>
void pt(const T <t> &arg, const A&... args) { for (int i = 0, sze = arg.size(); i < sze; ++i) cout << arg[i] << " \n"[i == sze - 1]; pt(args...); }
inline ll qpow(ll base, ll n) { assert(n >= 0); ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
//head
constexpr int N = 1e5 + 10; 
int n, m; ll k; 

ll POW(int x, int y) {
	ll res = 1;
	for (int i = 1; i <= y; ++i) {
		res *= x;
		if (res >= 1e17) break;
	}
	return res;
}

ll C(int n, int m) {
//	if (n < m) return 0;
	if (n == m || !m) return 1;
	ll res = 1;
	m = min(m, n - m);
	vector <int> vec;
	for (int i = 2; i <= m; ++i) vec.push_back(i);
	for (int i = n; i > n - m; --i) {
		res = res * i;
		vector <int> _vec;
		for (auto &it : vec) {
			if (res % it == 0) {
				res /= it;
			} else {
				_vec.push_back(it);
			}
		}
		vec = _vec;
	}
//	for (int i = 1; i <= m; ++i) res = res / i;
	return res;
}

ll get(int n, int m) {
//	if (!m) return n;
	ll res = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j <= m; ++j) {
			res += C(i + j, i);
			if (res >= 1e18) break;
		}
		if (res >= 1e18) break;
	}
//	pt(n, m, res);
//	for (int i = 1; i <= m; ++i) {
//		res += POW(n + 1, m);
//		if (res >= 1e16) break;
//	}
	return res;
}

void run() {
//	pt(C(5, 2));
	string res = "";
	int _n = n, _m = m;
	while (k && _n && _m) {
		ll cnt = get(_n, _m);
		if (cnt >= k) {
			res += 'a';
			--_n;
		} else {
			res += 'b';
			--_m;
			k -= cnt;
		}
		--k;
	}
//	pt(k);
	while (k && (_n || _m)) {
		--k;
		if (_n) {
			--_n;
			res += 'a';
		} else if (_m) {
			--_m;
			res += 'b';
		} else {
			assert(0);
		}
	}
	cout << res << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n >> m >> k) run();
//    for (int kase = 1; kase <= _T; ++kase) {
//        cout << "Case #" << kase << ": ";
//        run();
//    }
//	while (cin >> n) run();
//	run();
	return 0;
}
