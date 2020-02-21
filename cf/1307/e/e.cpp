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
constexpr int N = 5e3 + 10; 
int n, m, a[N], b[2][N], bit[N];
void run() {
	vector <vector<int>> vec(n + 1);
	for (int i = 1; i <= n; ++i) rd(a[i]);
	for (int i = 1, x, y; i <= m; ++i) {
		rd(x, y);
		vec[x].push_back(y);
	}
	for (int i = 1; i <= n; ++i) if (!vec[i].empty()) {
		sort(vec[i].begin(), vec[i].end());
	}
	pII res = pII(0, 0);
	memset(b, 0, sizeof b);
	for (int i = 1; i <= n; ++i) ++b[1][a[i]];
	for (int i = 1; i <= n + 1; ++i) {
		pII now = pII(0, 1);
		for (int j = 1; j <= n; ++j) if (!vec[j].empty()) {
			if (SZ(vec[j]) == 1) {
				int num = (vec[j][0] <= b[0][j]) +
						  (vec[j][0] <= b[1][j]);
				if (num) ++now.fi;
				if (num != 1) chadd(now.se, now.se); 
			} else {
				int A = b[0][j], B = b[1][j];
				int _A = vec[j][0], _B = vec[j][1];
				if (A > B) swap(A, B);
				now.se = (1ll * now.se * bit[SZ(vec[j]) - 2] % mod);
				if (_A <= A && _B <= B) now.fi += 2;
				else if (_A <= B) {
					now.fi += 1;
					chadd(now.se, now.se);
					if (_A <= A) chadd(now.se, now.se);
				}	
			}
		}
		if (now.fi > res.fi) res = now;
		else if (now.fi == res.fi) chadd(res.se, now.se);
		--b[1][a[i]];
		++b[0][a[i]];
	}
	pt(res.fi, res.se);
}

int main() {
	bit[0] = 1;
	for (int i = 1; i < N; ++i)
		bit[i] = (bit[i - 1] * 2) % mod;
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n >> m) run(); 
//	while (cin >> n) run();
//    for (int kase = 1; kase <= _T; ++kase) {
//        cout << "Case #" << kase << ":\n";
//        run();
//    }
	return 0;
}
