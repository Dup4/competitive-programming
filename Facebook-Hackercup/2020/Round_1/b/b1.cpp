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
constexpr int N = 1e6 + 10; 
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
int n, m, k, s, h[N], vis[N];  
ll P[N], Q[N], f[N][2], g[N];
pII pos[N];

inline ll dis(ll x, ll y) { return abs(x - y); }

void input(ll *arr, int n) {
	for (int i = 1; i <= k; ++i) rd(arr[i]);
	ll A, B, C, D;
	rd(A, B, C, D);
	for (int i = k + 1; i <= n; ++i) {
		arr[i] = ((A * arr[i - 2] % D + B * arr[i - 1] % D + C) % D) + 1;
	}
}

bool ok(ll x) {
	int pre = 1;
	for (int i = 1; i <= n; ++i) {
		int j = pre;
		for ( ; j <= m; ++j) {
			ll need = min(dis(P[i], Q[pre]), dis(P[i], Q[j])) + dis(Q[pre], Q[j]);
			if (need > x) {
				break;
			}
		}
		pre = j;
	}
	return pre > m;
}

void run() {
	rd(n, m, k, s);
	input(P, n);
	input(Q, m);
	sort(P + 1, P + 1 + n);
	sort(Q + 1, Q + 1 + m);
	ll l = 0, r = 2e9, res = r;
	while (r - l >= 0) {
		ll mid = (l + r) >> 1;
		if (ok(mid)) {
			r = mid - 1;
			res = mid;
		} else {
			l = mid + 1;
		}
	}
	pt(res);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	int _T = nextInt();
//	while (_T--) run(); 
    for (int kase = 1; kase <= _T; ++kase) {
        cout << "Case #" << kase << ": ";
        run();
    }
//	while (cin >> n) run();
//	run();
	return 0;
}