#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#define fi first
#define se second
#define endl "\n" 
using namespace std;
using db = double;
using ll = long long;
using ull = unsigned long long; 
using pII = pair <int, int>;
using pLL = pair <ll, ll>;
constexpr int mod = 1e9 + 7;
template <class T1, class T2> inline void chadd(T1 &x, T2 y) { x += y; while (x >= mod) x -= mod; while (x < 0) x += mod; } 
template <class T1, class T2> inline void chmax(T1 &x, T2 y) { if (x < y) x = y; }
template <class T1, class T2> inline void chmin(T1 &x, T2 y) { if (x > y) x = y; }
inline int rd() { int x; cin >> x; return x; }
template <class T> inline void rd(T &x) { cin >> x; }
template <class T> inline void rd(vector <T> &vec) { for (auto &it : vec) cin >> it; }  
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
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
inline ll qpow(ll base, ll n) { ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
//head
constexpr int N = 2e5 + 10, M = 5e5 + 10;
int n, m, A, B; 
struct Edge { int v, nx, cut; }e[M]; int h[N], tot; 
inline void addedge(int u, int v) { e[tot] = {v, h[u], 0}; h[u] = tot++; } 
struct Tarjan {
	//DFN[i] 点i第一次访问的时间戳
	//Low[i] 点i能访问到的点中的Low的最小值
	//cut[i] 点i是否是割点
	int Low[N], DFN[N], add_block[N], cut[N], bridge; bool Insta[N]; 
	void dfs(int u, int pre) {
		Low[u] = DFN[u] = ++*Low;
		Insta[u] = 1;
		int son = 0; 
	    int pre_cnt = 0;	
		for (int i = h[u]; ~i; i = e[i].nx) {
			int v = e[i].v;
			//处理重边
			if (v == pre && pre_cnt == 0) { pre_cnt++; continue; }
			if (!DFN[v]) {
				++son;
				dfs(v, u);
				Low[u] = min(Low[u], Low[v]);
				//桥
				//一条(u, v)是桥，当且仅当(u, v)为树枝边，且满足DFN[u] < Low[v]
				if (Low[v] > DFN[u]) {
					++bridge;
					e[i].cut = 1;
					e[i ^ 1].cut = 1; 
				}
				//割点
				//一个顶点u是割点，当且仅当
				//1. u 为树根，且u有多余一个子树
				//2. u 不为树根，满足存在(u, v)为树枝边，即u为v在搜索树中的父亲，使得DFN[u] <= Low[v]
				if (u != pre && Low[v] >= DFN[u]) {
					cut[u] = 1;
					++add_block[u];
				}
			} else Low[u] = min(Low[u], DFN[v]); 
		}
		if (u == pre && son > 1) cut[u] = 1;
		if (u == pre) add_block[u] = son - 1;
		Insta[u] = 0;
	}
	void gao(int n) {
		memset(DFN, 0, sizeof (DFN[0]) * (n + 10));
		memset(Insta, 0, sizeof (Insta[0]) * (n + 10));
		*Low = 0;
		for (int i = 1; i <= n; ++i) if (!DFN[i]) dfs(i, i); 
	}
	void gogogo() {
		vector <int> vec;
		for (int i = 1; i <= n; ++i) if (cut[i]) vec.push_back(i);
		int sze = vec.size();
		printf("%d\n", sze);
		for (int i = 0; i < sze; ++i)
			printf("%d%c", vec[i], " \n"[i == sze - 1]);
	}
}tarjan;
void run() {
	cin >> n >> m >> A >> B;
	tot = 0;
	for (int i = 1; i <= n; ++i) h[i] = -1; 
	for (int i = 1, u, v; i <= m; ++i) {
		cin >> u >> v;
		addedge(u, v);
		addedge(v, u);
	}
	if (tarjan.cut[A] == 0 || tarjan.cut[B] == 0) return pt(0);
	

}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	int _T = rd();
	while (_T--) run();
	return 0;
}
