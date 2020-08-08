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
constexpr int Mod = 666;
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
constexpr int N = 1e2 + 10; 
char s[N];
int a[N], bit[N];
int f[51][668][2][2], n;

int dfs(int pos, int S, int limit, int flag) {
	int &res = f[pos][S][limit][flag];
	if (res != -1 && limit == 0) return res;
	res = 0;
	if (pos == 0) {
		if (S == 0 && flag == 0 && limit == 1) res = 1;
		return res;
	}
	if (limit) {
		int _S = (a[pos] * bit[n - pos] % Mod - a[pos] + S + Mod) % Mod;
		chadd(res, dfs(pos - 1, _S, limit, flag ^ (a[pos] == 6)));
	} else {
		int up = pos == 1 ? a[1] - 1 : 9;
		for (int i = 0; i <= up; ++i) {
			int _S = (S + i * bit[n - pos] % Mod - i + Mod) % Mod;
			if (i < a[pos]) {
				chadd(res, dfs(pos - 1, _S, 1, flag ^ (i == 6)));
			}
			chadd(res, dfs(pos - 1, _S, 0, flag ^ (i == 6)));
		}
	}
	return res;
}

void run() {
	cin >> (s + 1);
	n = strlen(s + 1);
	for (int i = 1; i <= n; ++i) a[i] = s[i] - '0';
	if (n == 1) {
		return pt(a[1] >= 6);
	}
	int res = 0;
	for (int i = 0; i <= 9; ++i) {
		int now = 0;
		chadd(now, dfs(n - 1, 0, 0, 1 ^ (i == 6)));
		if (i <= a[n]) {
			chadd(now, dfs(n - 1, 0, 1, 1 ^ (i == 6)));
		}
		chadd(res, now);
	}
	pt(res);
}

int main() {
	bit[0] = 1;
	for (int i = 1; i < 60; ++i) bit[i] = 1ll * bit[i - 1] * 10 % Mod;
	memset(f, -1, sizeof f);
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	int _T = nextInt();
	while (_T--) run(); 
//    for (int kase = 1; kase <= _T; ++kase) {
//        cout << "Case #" << kase << ": ";
//        run();
//    }
//	while (cin >> n) run();
//	run();
	return 0;
}
