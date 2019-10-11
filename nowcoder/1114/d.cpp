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
inline void pt() { cout << endl; } 
template <class T, class... Ts> void pt(const T& arg, const Ts&... args) { cout << arg << ' '; pt(args...); }
template <template<typename...> class T, typename t, typename... A> 
void pt(const T <t> &arg, const A&... args) { for (auto &v : arg) cout << v << ' '; pt(args...); }
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
inline ll qpow(ll base, ll n) { ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
//head
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr int INF = 0x3f3f3f3f;
struct Dicnic { 
	static const int M = 2e3 + 10;
	static const int N = 2e3 + 10;
    struct Edge {
        int to, nxt;
        ll flow;
        Edge() {}
        Edge(int to, int nxt, ll flow) : to(to), nxt(nxt), flow(flow) {}
    } edge[M];
	int S, T;
    int head[N], tot;
    int dep[N];
    void init() {
        memset(head, -1, sizeof head);
        tot = 0;
    }
	void set(int S, int T) {
		this->S = S;
		this->T = T;
	}
    void addedge(int u, int v, int w, int rw = 0) {
        edge[tot] = Edge(v, head[u], w);
        head[u] = tot++;
        edge[tot] = Edge(u, head[v], rw);
        head[v] = tot++;
    }
    bool BFS() {
        memset(dep, -1, sizeof dep);
        queue<int> q;
        q.push(S);
        dep[S] = 1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = head[u]; ~i; i = edge[i].nxt) {
                if (edge[i].flow && dep[edge[i].to] == -1) {
                    dep[edge[i].to] = dep[u] + 1;
                    q.push(edge[i].to);
                }
            }
        }
        return dep[T] >= 0;
    }
    ll DFS(int u, ll f) {
        if (u == T || f == 0) return f;
        ll w, used = 0;
        for (int i = head[u]; ~i; i = edge[i].nxt) {
            if (edge[i].flow && dep[edge[i].to] == dep[u] + 1) {
                w = DFS(edge[i].to, min(f - used, edge[i].flow));
                edge[i].flow -= w;
                edge[i ^ 1].flow += w;
                used += w;
                if (used == f) return f;
            }
        }
        if (!used) dep[u] = -1;
        return used;
    }
    ll solve() {
        ll ans = 0;
        while (BFS()) {
            ans += DFS(S, INFLL);
        }
        return ans;
    }
}dicnic;
constexpr int N = 1e5 + 10;
int n, q, a[110], b[13]; string s; 
unordered_map <string, int> mp; int id; 
inline int get(string &s) {
	sort(s.begin(), s.end());
	if (mp.count(s) == 0) mp[s] = ++id;
	return mp[s];
}
void run() {
	mp.clear(); id = 0;
	memset(a, 0, sizeof a);
	for (int i = 1; i <= n; ++i) {
		cin >> s;
		++a[get(s)];
	}
	while (q--) {
		cin >> s;
		int len = s.size();
		memset(b, 0, sizeof b);
		for (auto &c : s) ++b[c - '0'];
		dicnic.init(); 
		int S = 120, T = 121;
		dicnic.set(S, T);
		for (int i = 1; i <= 9; ++i)
			dicnic.addedge(S, i + 85, b[i]);
		for (int i = 1; i <= id; ++i)
			dicnic.addedge(i, T, a[i]);
		for (auto &it : mp) {
			for (auto &c : it.fi) {
				dicnic.addedge(c - '0' + 85, it.se, INF);
			}
		}
		if (dicnic.solve() == len) pt("dyf");
		else pt("zzk");
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n >> q) run();
	return 0;
}
