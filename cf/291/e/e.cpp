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
constexpr int N = 3e5 + 10; 
int n, fa[N], Next[N], nx[N][27]; string s[N], t;
ll res;

vector <vector<int>> G;

void get_Next(string s) {
	int len = SZ(s);
	int i, j;
	j = Next[0] = -1;
	i = 0;
	while (i < len) {
		while (-1 != j && s[i] != s[j]) j = Next[j];
		Next[++i] = ++j;
	}
	for (int i = 0; i < len; ++i) {
		for (int j = 0; j < 26; ++j) {
			nx[i][j] = i;
			if (nx[i][j] != -1 && s[nx[i][j]] != 'a' + j) {
				nx[i][j] = Next[nx[i][j]];
				if (nx[i][j] != -1 && s[nx[i][j]] != 'a' + j) 
					nx[i][j] = nx[nx[i][j]][j];
			}
		}
	}
}

void dfs(int u, int kmpPos) {
	for (auto &v : G[u]) {
		int j = kmpPos, i = 0;
		while (i < SZ(s[v])) {
			if (j != -1) j = nx[j][s[v][i] - 'a'];
		   	++i, ++j;
			if (j >= SZ(t)) {
				++res; 
				j = Next[j];
			}
		}
		dfs(v, j);
	}
}

void run() {
	G.clear(); G.resize(n + 1);
	for (int i = 2; i <= n; ++i) {
		rd(fa[i], s[i]);
		G[fa[i]].push_back(i);
	}	
	rd(t);
	get_Next(t);
	res = 0;
	dfs(1, 0);
	pt(res);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n) run();
	return 0;
}
