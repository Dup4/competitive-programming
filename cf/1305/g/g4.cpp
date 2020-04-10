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
using pLI = pair<ll, int>;
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
constexpr int N = 3e5 + 10, INF = 0x3f3f3f3f; 
int n, m, a[N]; ll res;

struct UFS {
	int fa[N], rk[N];
	void init(int n) {
		memset(fa, -1, sizeof (fa[0]) * (n + 5));
		memset(rk, 0, sizeof (rk[0]) * (n + 5)); 
	}
	int find(int x) { return fa[x] == -1 ? x : fa[x] = find(fa[x]); }
	int merge(int x, int y) {
		int fx = find(x), fy = find(y);
		if (fx != fy) {
			if (rk[fx] > rk[fy]) swap(fx, fy);	    
			fa[fx] = fy;
			if (rk[fx] == rk[fy]) ++rk[fy]; 
			int cnt = a[fx] + a[fy] - 1;
			a[fx] = 1; a[fy] = 1;
			return cnt;
		}
		return 0;
	}
}ufs;

void run() {
	m = 200000; 
	memset(a, 0, sizeof a);
	res = 0;
	for (int i = 1, x; i <= n; ++i) {
		rd(x);
		++a[x];
		res -= x;
	}
	++a[0];
	int all = (1 << 18) - 1; 
	ufs.init(m);
	for (int sum = all; sum >= 0; --sum) {
		for (int u = sum; u; u = (u - 1) & sum) {
			int v = u ^ sum;
			if (a[u] && a[v]) {
				res += 1ll * sum * ufs.merge(u, v);
			}
		}	
	}
	pt(res);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n) run();
//    for (int kase = 1; kase <= _T; ++kase) {
//        cout << "Case #" << kase << ":\n";
//        run();
//    }
	return 0;
}
