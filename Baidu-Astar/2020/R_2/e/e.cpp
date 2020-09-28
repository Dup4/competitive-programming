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
constexpr int N = 1e5 + 10; 
constexpr int INF = 0x3f3f3f3f;
int n; 

struct Min_Cost_Max_Flow {
	static const int N = 5e3 + 10;
	static const int M = 5e4 + 10;
	static const int INF = 0x3f3f3f3f;
	struct E { int to, nx, cap, flow, cost; }edge[M << 1]; int head[N], tot;
	int pre[N], dis[N]; 
	bool vis[N];
	int n;
	void init(int _n) {
		n = _n;
		tot = 0;
		memset(head, -1, sizeof head);
	}
	void addedge(int u, int v, int cap, int cost) {
		edge[tot] = { v, head[u], cap, 0, cost}; head[u] = tot++;
		edge[tot] = { u, head[v], 0, 0, -cost}; head[v] = tot++;
	}
	bool spfa(int s, int t) {
		queue <int> q;
		for (int i = 1; i <= n; ++i) {
			dis[i] = INF;
			vis[i] = false;
			pre[i] = -1;
		}
		dis[s] = 0;
		vis[s] = true;
		q.push(s);
		while (!q.empty()) {
			int u = q.front(); q.pop();
			vis[u] = false;
			for (int i = head[u]; i != -1; i = edge[i].nx) {
				int v = edge[i].to;
				if (edge[i].cap > edge[i].flow && dis[v] > dis[u] + edge[i].cost) {
					dis[v] = dis[u] + edge[i].cost;
					pre[v] = i;
					if (!vis[v]) {
						vis[v] = true;
						q.push(v);
					}
				}
			}
		}
		if (pre[t] == -1) return false;
		return true;
	}
	//返回flow cost引用传递
	//点的编号从1开始
	int gao(int s, int t, int &cost) {
		int flow = 0;
		cost = 0;
		while (spfa(s, t)) {
			int Min = INF;
			for (int i = pre[t]; i != -1; i = pre[edge[i ^ 1].to]) {
				if (Min > edge[i].cap - edge[i].flow) {
					Min = edge[i].cap - edge[i].flow;
				}
			}
			for (int i = pre[t]; i != -1; i = pre[edge[i ^ 1].to]) {
				edge[i].flow += Min;
				edge[i ^ 1].flow -= Min;
				cost += edge[i].cost * Min;
			}
			flow += Min;
		}
		return flow;
	}
}MCMF;

map <string, int> mp;
int cnt[10];

void run() {
	int a, b, c;
	rd(n, a, b, c);
	memset(cnt, 0, sizeof cnt);
	MCMF.init(11); 
	int S = 10, T = 11;
	for (int i = 1; i <= n; ++i) {
		static string s;
		rd(s);
		++cnt[mp[s]];
	}
	MCMF.addedge(S, 1, a, 0);
	MCMF.addedge(S, 2, b, 0);
	MCMF.addedge(S, 3, c, 0);
	for (auto &it : mp) {
		int fee = -3;
		for (auto &ch : it.fi) {
			int x = ch - '0' + 1;
			MCMF.addedge(x, it.se, INF, fee);
			++fee;
		}
		MCMF.addedge(it.se, T, cnt[it.se], 0);
	}
	int cost = 0;
	MCMF.gao(S, T, cost);
	pt(-cost);
}

int main() {
	mp["012"] = 4;
	mp["021"] = 5;
	mp["102"] = 6;
	mp["120"] = 7;
	mp["201"] = 8;
	mp["210"] = 9;
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
