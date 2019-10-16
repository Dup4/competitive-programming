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
constexpr int N = 1e5 + 10;
int n, vis[N];
struct E {
	int x, y, z, id;
	E() {}
	E(int x, int y, int z) : x(x), y(y), z(z) {}
};
vector <E> e;
vector <pII> res;
void gao1() {
	vector <E> sta;
	sta.push_back(e[0]);
	int sze = e.size();
	for (int i = 1; i < sze; ++i) {
		if (sta.empty()) sta.push_back(e[i]);
		else {
			if (e[i].x != sta.back().x) {
				res.push_back(pII(e[i].id, sta.back().id));
				sta.pop_back();
			} else {
				sta.push_back(e[i]);
			}
		}
	}
	e = sta;
}
void gao2() {
	vector <E> sta;
	sta.push_back(e[0]);
	int sze = e.size();
	for (int i = 1; i < sze; ++i) {
		if (sta.empty()) sta.push_back(e[i]);
		else {
			if (e[i].y != sta.back().y) {
				res.push_back(pII(e[i].id, sta.back().id));
				sta.pop_back();
			} else {
				sta.push_back(e[i]);
			}
		}
	}
	e = sta;
}

void gao3() {
	vector <E> sta;
	sta.push_back(e[0]);
	int sze = e.size();
	for (int i = 1; i < sze; ++i) {
		if (sta.empty()) sta.push_back(e[i]);
		else {
			if (e[i].z != sta.back().z) {
				res.push_back(pII(e[i].id, sta.back().id));
				sta.pop_back();
			} else {
				sta.push_back(e[i]);
			}
		}
	}
	e = sta;
}

void run() {
	e.clear(); e.resize(n);
	res.clear();
	for (int i = 0; i < n; ++i) {
		cin >> e[i].x >> e[i].y >> e[i].z;
		e[i].id = i + 1;
	}
	if (!e.empty()) {
		sort(e.begin(), e.end(), [&](E x, E y) { return x.x < y.x; });
		gao1();
	}
	if (!e.empty()) {
		sort(e.begin(), e.end(), [&](E x, E y) { return x.y < y.y; });
		gao2();
	}
	if (!e.empty()) {
		sort(e.begin(), e.end(), [&](E x, E y) { return x.z < y.z; });
		gao3();
	}
	assert(e.empty());
	for (auto &it : res)
		pt(it.fi, it.se);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n) run();
	return 0;
}
