#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
#define mkp make_pair
#define all(x) (x).begin(), (x).end()
#define endl "\n" 
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
constexpr int N = 1e3 + 10; 
int n, m, a[N], f[N], fee[N];  

vector <vector<pII>> G; 

void run() {
	rd(n, m);
	for (int i = 2; i <= n; ++i) rd(a[i]), a[i] *= -1;
	G.clear(); G.resize(n + 1);
	for (int i = 1, u, v; i <= m; ++i) {
		rd(u, v);
		G[u].push_back(pII(v, i));
		G[v].push_back(pII(u, i));
		fee[i] = 1e6; 
	}
	vector <int> vec;
	for (int i = 2; i <= n; ++i) vec.push_back(i);
	sort(all(vec), [&](int x, int y) { return a[x] < a[y]; });
//	pt(vec);
	memset(f, -1, sizeof f); 
	f[1] = 0;
	int pre = 0, preOrd = 0;
	for (auto &u : vec) {
		int Min = 1e6, fa = -1, id = -1;
		for (auto &it : G[u]) {
			int v = it.fi;
			if (f[v] != -1 && a[v] < a[u]) { 
				if (preOrd == a[u] && f[v] >= pre) continue;
				int now;
				if (preOrd == a[u]) now = max(1, pre - f[v]);
				else now = max(1, pre + 1 - f[v]);
				if (now < Min) {
					fa = v;
					Min = now;
					id = it.se;
				}
			}
		}
//		dbg(u, fa);
	//	if (fa == -1) continue;
		assert(fa != -1);
		fee[id] = Min;
		f[u] = f[fa] + fee[id];
		pre = f[u]; 
		preOrd = a[u];
	}
	for (int i = 1; i <= m; ++i) {
		assert(fee[i] <= 1e6);
		cout << fee[i] << " \n"[i == m];
	}
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
