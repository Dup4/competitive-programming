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
int n, m, a[N];
ll F[110];

struct BIT {
	ll a[N];
	void init() { memset(a, 0, sizeof a); }
	void update(int x, ll v) { for (; x < N; a[x] += v, x += x & -x); }
	ll query(int x) { ll res = 0; for (; x > 0; res += a[x], x -= x & -x); return res; }
	ll query(int l, int r) { return query(r) - query(l - 1); }
}bit;

void run() {
	rd(n, m);
	set <int> se;
	bit.init();
	for (int i = 1; i <= n; ++i) se.insert(i), a[i] = 1, bit.update(i, 1);
	for (int i = 1, op, l, r; i <= m; ++i) {
		rd(op, l, r);
		if (op == 1) {
			auto pos = se.lower_bound(l);
			for (; pos != se.end() && (*pos) <= r; ) {
				auto nx = next(pos);
				bit.update(*pos, F[a[(*pos)] - 1]);
				++a[*pos];
				if (a[*pos] == 50) se.erase(pos);
				pos = nx;
			}
		} else {
			ll k; rd(k);
		//	pt(k, bit.query(l, r));
			pt((bit.query(l, r) >= k) ? "YES" : "NO");
		}
	}
}

int main() {
	F[0] = 0, F[1] = 1; F[2] = 1; 
	for (int i = 3; i <= 50; ++i) F[i] = F[i - 1] + F[i - 2];
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	int _T = 1;
	while (_T--) run(); 
//    for (int kase = 1; kase <= _T; ++kase) {
//        cout << "Case #" << kase << ": ";
//        run();
//    }
//	while (cin >> n) run();
//	run();
	return 0;
}
