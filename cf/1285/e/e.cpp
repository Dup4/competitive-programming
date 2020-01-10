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
constexpr int N = 2e5 + 10, M = 20;
int n, g[N]; pII a[N]; 

struct RMQ {
	pII Max[N][M];
	int mm[N];
	void init(int n, pII *b) {
		mm[0] = -1;
		for (int i = 1; i <= n; ++i) {
			mm[i] = ((i & (i - 1)) == 0) ? mm[i - 1] + 1 : mm[i - 1];
			Max[i][0] = pII(b[i].se, i); 
		}
		for (int j = 1; j <= mm[n]; ++j) {
			for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
				Max[i][j] = max(Max[i][j - 1], Max[i + (1 << (j - 1))][j - 1]);
			}
		}
	}
	pII queryMax(int x, int y) {
		int k = mm[y - x + 1];
		return max(Max[x][k], Max[y - (1 << k) + 1][k]);
	}
}rmq;

void gaof() {
	g[n] = 1; 
	vector <pII> vec;
	vec.push_back(a[n]);
	g[n + 1] = 0;
	for (int i = n - 1; i >= 1; --i) {
		pII tmp = a[i];
		while (!vec.empty() && tmp.se >= vec.end()[-1].fi) {
			chmax(tmp.se, vec.end()[-1].se);
			vec.pop_back();
		}
		vec.push_back(tmp);
		g[i] = vec.size(); 
	}
}

void run() {
	n = rd();
	for (int i = 1; i <= n; ++i) cin >> a[i].fi >> a[i].se;
	sort(a + 1, a + 1 + n, [&](pII x, pII y) {
		if (x.fi != y.fi)
			return x.fi < y.fi;
		else 
			return x.se < y.se;		
	});
	rmq.init(n, a);
	gaof();
	int res = g[2];
	vector <pII> vec; 
	for (int i = 1; i < n; ++i) {
		if (vec.empty()) vec.push_back(a[i]);
		else if (vec.back().se >= a[i].fi) chmax(vec.back().se, a[i].se);
		else vec.push_back(a[i]);
		if (i == n - 1) {
			chmax(res, (int)vec.size());
			break;
		}
		int l = i + 2, r = n, pos = i + 1;
		while (r - l >= 0) {
			int mid = (l + r) >> 1;
			if (a[mid].fi <= vec.back().se) {
				pos = mid;
				l = mid + 1;
			} else {
				r = mid - 1;
			}
		}
		if (pos == i + 1) {
			chmax(res, (int)vec.size() + g[i + 2]); 
		} else {
			pII tmp = rmq.queryMax(i + 2, pos);
			if (tmp.fi <= a[i].se) {
				chmax(res, (int)vec.size() + g[pos + 1]); 
			} else {
				chmax(res, (int)vec.size() + g[tmp.se] - 1);
			}
		}
	}
	pt(res);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	int _T = rd();
	while (_T--) run();
	return 0;
}
