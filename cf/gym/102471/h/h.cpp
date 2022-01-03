#include <bits/stdc++.h>
#define fi first
#define se second
#define SZ(x) int((x).size())
#define endl "\n" 
using namespace std;
using db = double;
using ll = long long;
using ull = unsigned long long; 
using pII = pair <int, int>;
using pLL = pair <ll, ll>;
#include <bits/extc++.h>
using namespace __gnu_pbds;
int mod = 1e9 + 7;
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
constexpr int N = 2e5 + 10; 
int n, a[N]; 

ll inv(ll x) { return qpow(x, mod - 2); }

gp_hash_table<int, int> h;

unordered_map <int, int> mp;

void run() {
	rd(n, mod);
	for (int i = 1; i <= n; ++i) rd(a[i]);
	mp.clear();
	for (int i = 2; i <= n; ++i) {
		++mp[1ll * a[i] * inv(a[i - 1]) % mod];
		if (i > 2) ++mp[1ll * a[i] * inv(a[i - 2]) % mod];
	}
	vector <pII> vec;
	for (auto &it : mp) vec.emplace_back(it.fi, it.se);
	sort(vec.begin(), vec.end(), [&](pII a, pII b) { return a.se > b.se; });
	vec.resize(min(SZ(vec), 30));
	int res = 0;
	for (auto &it : vec) {
		h.clear();
		int invQ = inv(it.fi);
		for (int i = 1; i <= n; ++i) {
			int now = h[1ll * a[i] * invQ % mod];
			chmax(res, now + 1);
			chmax(h[a[i]], now + 1);
		}		
	}
	if (res < (n + 1) / 2) res = -1;
	pt(res);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	int _T = nextInt();
	while (_T--) run(); 
//	while (cin >> n) run();
//    for (int kase = 1; kase <= _T; ++kase) {
//        cout << "Case #" << kase << ":\n";
//        run();
//    }
	return 0;
}
