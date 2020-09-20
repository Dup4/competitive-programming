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
constexpr int N = 1e2 + 10; 
constexpr int INF = 0x3f3f3f3f;
int n, m, f[N], g[2][1 << 13]; 

class Solution {
public:
    int connectTwoGroups(vector<vector<int>>& cost) {
		n = SZ(cost);
		m = SZ(cost[0]);
		int res = INF;
		memset(f, 0x3f, sizeof f);
		memset(g, 0x3f, sizeof g);
		g[1][0] = 0;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				chmin(f[j], cost[i][j]);
			}
		}
		for (int i = 0; i < n; ++i) {
			int p = i & 1;
			memset(g[p], 0x3f, sizeof g[p]);
			for (int j = 0; j < m; ++j) {
				for (int S = 0; S < 1 << m; ++S) {
					chmin(g[p][S | (1 << j)], g[p ^ 1][S] + cost[i][j]);
				}
			}
		}
		int p = (n - 1) & 1;
		for (int S = 0; S < 1 << m; ++S) {
			int add = 0;
			for (int i = 0; i < m; ++i) {
				if (!((S >> i) & 1)) {
					add += f[i];
				}
			}
			chmin(res, g[p][S] + add);
		}
		return res;
    }
};

void run() {

}

int main() {
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
