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
int a[N], bit[70];
int f[60][680][680][2][2], n;

int ok(int x) {
	int cnt = 0;
	int res = 0;
	int _x = x;
	while (x) {
		int y = x % 10;
		cnt += (y == 6);
		res += y;
		x /= 10;
	}
	return (_x % 666) == res && (cnt & 1); 
}

int dfs(int pos, int S, int _S, int limit, int flag) {
	//dbg(pos, S, limit, flag);
	if (pos < 0) return 0;
	if (pos == 0) {
		if (S == 0 && _S == 0 && flag == 0 && limit == 1) return 1;
		else return 0;
	}
	if (f[pos][S][_S][limit][flag] != -1) return f[pos][S][_S][limit][flag]; 
	int &res = f[pos][S][_S][limit][flag];
//	if (pos == 1) {
//		
//		if (S > a[pos] || (S == 6 && flag == 0) || (S != 6 && flag == 1) || (S != a[pos] && limit)) res = 0;
//		else res = 1;
//		return res;
//	}
	res = 0;
	if (limit) {
		int SS = (1ll * S - 1ll * a[pos] * bit[n - pos] % Mod + Mod) % Mod;
		int _SS = _S - a[pos];
	//	dbg(_S);
		chadd(res, dfs(pos - 1, SS, _SS, limit, flag ^ (a[pos] == 6)));
	} else {
		int up = pos == 1 ? a[1] - 1 : 9;
		for (int i = 0; i <= up; ++i) {
			int SS = (1ll * S - 1ll * i * bit[n - pos] % Mod + Mod) % Mod;
			int _SS = _S - i;
	//		dbg(_S);
			if (i < a[pos]) {
				chadd(res, dfs(pos - 1, SS, _SS, 1, flag ^ (i == 6)));
			}
			chadd(res, dfs(pos - 1, SS, _SS, 0, flag ^ (i == 6)));
		}
	}
	return res;
}

void run() {
	cin >> (s + 1);
	n = strlen(s + 1);
	for (int i = 1; i <= n; ++i) a[i] = s[i] - '0';
	memset(f, -1, sizeof f);
	int res = 0;
	for (int i = 0; i <= 9; ++i) {
		for (int S = 0; S < 666; ++S) {
			int SS = (1ll * S - 1ll * i % Mod + Mod) % Mod;
			int _SS = S - i;
			int now = 0;
			chadd(now, dfs(n - 1, SS, _SS, 0, 1 ^ (i == 6)));
			if (i <= a[n]) {
				chadd(now, dfs(n - 1, SS, _SS, 1, 1 ^ (i == 6)));
			}
	//		if (now) dbg(i, S, now);
			chadd(res, now);
		}
	}
	//for (int i = 0; i < 666; ++i) chadd(res, dfs(n, i, 1, 1));
	//for (int i = 0; i < 666; ++i) chadd(res, dfs(n, i, 0, 1));
	pt(res);

//	int res = 0; 
//	for (int i = 1; i <= n; ++i) {
//		if (ok(i)) {
//			++res;
//		//	pt(i);
//		}
//	}
//	pt(res);
}

int main() {
	bit[0] = 1;
	for (int i = 1; i < 60; ++i) bit[i] = 1ll * bit[i - 1] * 10 % Mod;
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
