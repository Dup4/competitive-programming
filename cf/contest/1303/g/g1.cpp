#include <bits/stdc++.h>
#define fi first
#define se second
#define SZ(x) ((int)x.size())
#define endl "\n" 
using namespace std;
using db = long long;
using ll = long long;
using ull = unsigned long long; 
using pII = pair <int, int>;
using pLL = pair <ll, ll>;
constexpr int mod = 1e9 + 7;
template <class T1, class T2> inline void chadd(T1 &x, T2 y, int Mod = mod) { x += y; while (x >= Mod) x -= Mod; while (x < 0) x += Mod; } 
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
inline ll qpow(ll base, ll n) { assert(n >= 0); ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
//head
constexpr int N = 2e5 + 10;
constexpr ll INF = 1e18;
int n; ll a[N];

int sgn(db x) { if (x == 0) return 0; return x < 0 ? -1 : 1; }
// upHull enables you to do the following two operations in amortized O(log n) time:
// 1. Insert a pair (a_i, b_i) into the structure
// 2. For any value of x, query the maximum value of a_i * x + b_i
// All values a_i, b_i, and x can be positive or negative.
struct UpHull {
	struct Point {
	    db x, y; 
	    Point(db _x = 0, db _y = 0) : x(_x), y(_y) {}
	};
    struct segment {
        Point p;
        mutable Point next_p;
        segment(Point _p = {0, 0}, Point _next_p = {0, 0}) : p(_p), next_p(_next_p) {}
        bool operator < (const segment &other) const {
            // Sentinel value indicating we should binary search the set for a single x-value.
            if (sgn(p.y - INF) == 0)
            	return sgn(p.x * (other.next_p.x - other.p.x) - (other.p.y - other.next_p.y)) <= 0;
            return sgn(p.x - other.p.x) == 0 ? sgn(p.y - other.p.y) < 0 : p.x < other.p.x;
        }
    };
    set<segment> segments;
	void clear() { segments.clear(); }
    int size() const { return segments.size(); }
    set<segment>::iterator prev(set<segment>::iterator it) const { return it == segments.begin() ? it : --it; }
    set<segment>::iterator next(set<segment>::iterator it) const { return it == segments.end() ? it : ++it; }
    //double类型使用
	//static db floor_div(db a, db b) { return a / b; }
	static db floor_div(db a, db b) { return a / b - ((a ^ b) < 0 && a % b != 0); }
	static bool bad_middle(const Point &a, const Point &b, const Point &c) {
        // This checks whether the x-value where b beats a comes after the x-value where c beats b. It's fine to round
        // down here if we will only query integer x-values. (Note: plain C++ division rounds toward zero)
        return sgn(floor_div(a.y - b.y, b.x - a.x) - floor_div(b.y - c.y, c.x - b.x)) >= 0;
    }
    bool bad(set<segment>::iterator it) const {
        return it != segments.begin() && next(it) != segments.end() && bad_middle(prev(it)->p, it->p, next(it)->p);
    }
    void insert(const Point &p) {
        set<segment>::iterator next_it = segments.lower_bound(segment(p));
        if (next_it != segments.end() && p.x == next_it->p.x)
            return;
        if (next_it != segments.begin()) {
            set<segment>::iterator prev_it = prev(next_it);
            if (p.x == prev_it->p.x)
                segments.erase(prev_it);
            else if (next_it != segments.end() && bad_middle(prev_it->p, p, next_it->p))
                return;
        }
        // Note we need the segment(p, p) here for the single x-value binary search.
        set<segment>::iterator it = segments.insert(next_it, segment(p, p));
        while (bad(prev(it)))
            segments.erase(prev(it));
        while (bad(next(it)))
            segments.erase(next(it));
        if (it != segments.begin())
            prev(it)->next_p = it->p;
        if (next(it) != segments.end())
            it->next_p = next(it)->p;
    }
    void insert(db a, db b) { insert(Point(a, b)); }
    // Queries the maximum value of ax + b.
    db query(db x) {
		if (size() == 0) return -INF;
        set<segment>::iterator it = segments.upper_bound(segment(Point(x, INF)));
      	return it->p.x * x + it->p.y;
    }
};

vector <vector<int>> G;
namespace DCTree {
	int all, rt, vis[N];
	int sze[N], f[N];
	ll deep[N], sum[N], tot[N], res;
	UpHull uphull;
	void getrt(int u, int fa) {
		f[u] = 0, sze[u] = 1;
		for (auto &v : G[u]) {
		 	if (v == fa || vis[v]) continue;	
			getrt(v, u);
			sze[u] += sze[v];
			f[u] = max(f[u], sze[v]);
		}
		f[u] = max(f[u], all - sze[u]);
		if (f[u] < f[rt]) rt = u;
	}
	void getdeep(int u, int fa) {
		chmax(res, uphull.query(deep[u]) + tot[u]);
		for (auto &v : G[u]) {
			if (v == fa || vis[v]) continue;
			deep[v] = deep[u] + 1;
			sum[v] = sum[u] + a[v];
			tot[v] = tot[u] + sum[v];
			getdeep(v, u);  
		}
	}
	void add(int u, int fa) {
		chmax(res, tot[u]);
		uphull.insert(sum[u], tot[u]);
		for (auto &v : G[u]) {
		 	if (v == fa || vis[v]) continue;
			deep[v] = deep[u] + 1;
			sum[v] = sum[u] + a[v];
			tot[v] = tot[u] + a[v] * deep[v];	
			add(v, u); 
		} 
	}
	void calc(int u) {
		deep[u] = 0;
		tot[u] = sum[u] = a[u];
		uphull.clear(); uphull.insert(a[u], a[u]);
		for (auto &v : G[u]) {
			if (vis[v]) continue; 
			deep[v] = 1;
			sum[v] = a[v]; 
			tot[v] = a[v];
			getdeep(v, u); 
			deep[v] = 2;
			sum[v] = sum[u] + a[v];
			tot[v] = tot[u] + a[v] * deep[v]; 
			add(v, u);
		}
	} 
	void solve(int u) {
		vis[u] = 1;
	    calc(u);	
		reverse(G[u].begin(), G[u].end());
		calc(u);
		for (auto &v : G[u]) {
		 	if (vis[v]) continue;	
			all = f[0] = sze[v]; rt = 0;
			getrt(v, 0);
			solve(rt);
		}
	}
	void gao() {
		res = *max_element(a + 1, a + 1 + n);
		memset(vis, 0, sizeof vis);
		all = f[0] = n; rt = 0;
		getrt(1, 0);
		solve(rt);
		pt(res);
	}
};

void run() {
	G.clear(); G.resize(n + 1);
	for (int i = 1, u, v; i < n; ++i) {
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for (int i = 1; i <= n; ++i) rd(a[i]);
	DCTree::gao(); 
}	

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n) run();
	return 0;
}
