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
int n, d, L, R, son[N][2], dep[N], fa[N]; 

void dfs(int u, int dep) {
	if (u > n) return;
	L += dep;
	dfs(u << 1, dep + 1);
	dfs(u << 1 | 1, dep + 1);
}

void run() {
	rd(n, d);
	L = 0; R = n * (n - 1) / 2; 
	dfs(1, 0);
	if (d < L || d > R) return pt("NO");
	for (int i = 1; i <= n; ++i) {
		son[i][0] = son[i][1] = 0;
		dep[i] = i - 1;
		if (i < n) son[i][0] = i + 1;
	}
	int now = n;
	int need = R - d;
	while (need > 0) {
		int ok = 0;
		for (int i = 1; i <= n; ++i) {
		//	dbg(i, dep[i], dep[now], son[i][0], son[i][1]); 
			if (dep[i] + 2 == dep[now] && (bool)son[i][0] + (bool)son[i][1] < 2) {
				--dep[now];
				if (son[i][0]) son[i][1] = now;
				else son[i][0] = now;
				ok = 1;
				break;
			}
		}
		if (ok) {
			--need;
			for (int i = 1; i <= n; ++i) {
				if (dep[i] == dep[now]) {
					if (son[i][0] == now) son[i][0] = 0;
					else if (son[i][1] == now) son[i][1] = 0;
				}
			}
		}
		else --now;
		if (!need) break;
	}
	pt("YES");
	for (int i = 1; i <= n; ++i) {
		if (son[i][0]) fa[son[i][0]] = i;
		if (son[i][1]) fa[son[i][1]] = i;
	}
	for (int i = 2; i <= n; ++i) 
		cout << fa[i] << " \n"[i == n];
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
