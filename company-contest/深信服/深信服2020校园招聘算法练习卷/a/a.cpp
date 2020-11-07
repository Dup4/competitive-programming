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
int n; 
char s[N];

struct Hash {
	int mod = 998244353;
	int seed = 233;
	int base[N], a[N];
	void init() {
		base[0] = 1;
		for (int i = 1; i < N; ++i) {
			base[i] = 1ll * base[i - 1] * seed % mod;
		}
	}
	void work(char *s) {
		int len = strlen(s + 1);
		a[0] = 1;
		for (int i = 1; i <= len; ++i) {
			a[i] = (1ll * a[i - 1] * seed % mod + s[i]) % mod;
		}
	}
	int get(int l, int r) {
		return (a[r] - 1ll * a[l - 1] * base[r - l + 1] % mod + mod) % mod;
	}
}hs;

void run() {
	cin >> (s + 1);
	n = strlen(s + 1);
	hs.work(s);
	int res = 0;
	for (int len = n / 2; len >= 1; --len) {
		for (int i = 1; i + len * 2 - 1 <= n; ++i) {
			int l1 = i, r1 = l1 + len - 1;
			int l2 = i + len, r2 = l2 + len - 1;
			if (hs.get(l1, r1) == hs.get(l2, r2)) {
				res = len;
				break;
			}
		}
		if (res) break;
	}
	pt(res * 2);
}

int main() {
	hs.init();
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	int _T = 1;
	//nextInt();
	while (_T--) run(); 
//    for (int kase = 1; kase <= _T; ++kase) {
//        cout << "Case #" << kase << ": ";
//        run();
//    }
//	while (cin >> n) run();
//	run();
	return 0;
}
