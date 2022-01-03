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
constexpr int N = 2e5 + 10; 
int n, m, res, a[N], vis[N]; 
vector <set<int>> se;

void merge(int a, int b) {
	if (SZ(se[a]) < SZ(se[b])) {
		swap(se[a], se[b]);
	}
	for (auto &it : se[b]) {
		int pNum = it - 1, nNum = it + 1;
		if (pNum >= 1) {
			auto pre = se[a].lower_bound(pNum);
			if (pre != se[a].end() && (*pre) == pNum) {
				if (vis[pNum]) {
					--res;
					vis[pNum] = 0;
				}
			}
		}
		if (vis[it]) {
			auto nx = se[a].lower_bound(nNum);
			if (nx != se[a].end() && (*nx) == nNum) {
				--res;
				vis[it] = 0;
			}
		}
		se[a].insert(it);
	}
}

void run() {
	rd(n, m);
	se.clear(); se.resize(m + 1);
	for (int i = 1; i <= n; ++i) {
		int x; rd(x);
		se[x].insert(i);
		vis[i] = 1;
	}
	vis[n] = 0;
	res = n - 1;
	for (int i = 1; i <= m; ++i) {
		for (auto &it : se[i]) {
			if (it < n) {
				auto pos = se[i].lower_bound(it + 1);
				if (pos != se[i].end() && (*pos) == it + 1) {
					vis[it] = 0;
					--res;
				}
			}
		}
	}
	pt(res);
	for (int i = 1, a, b; i < m; ++i) {
		rd(a, b);
		merge(a, b);
		pt(res);
	}
}

int main() {
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
