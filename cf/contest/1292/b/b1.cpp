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
int n, res;
ll xz, yz, ax, ay, bx, by, xs, ys, t;
ll dis(pLL a, pLL b) {
	return abs(a.fi - b.fi) + abs(a.se - b.se);
}
vector <pLL> vec;
int up(pLL it, ll cost) {
	int res = 0;
	while (cost <= t) {
		++res;
		pLL nx = pLL(ax * it.fi + bx, ay * it.se + by);
		cost += dis(it, nx);
		it = nx;
	}
	return res;
}
int down(pLL it, ll cost) {
	int res = 0;
	while (cost <= t && !(it.fi == xz && it.se == yz)) {
		++res;
		pLL nx = pLL((it.fi - bx) / ax, (it.se - by) / ay);
		dbg(cost, nx.fi, nx.se);
		cost += dis(it, nx);
		it = nx;
	}
	return res;
}
void run() {
	cin >> xs >> ys >> t;
	vec.clear();
	ll xn = xz, yn = yz; 
	while (1) {
		if (xn > xs + t || yn > ys + t)
			break;
		if (xn >= xs - t && yn >= ys - t) {
			vec.push_back(pLL(xn, yn));
		}
		xn = ax * xn + bx;
		yn = ay * yn + by; 
	}
	res = 0;
	n = vec.size(); 
	for (int i = 0; i < n; ++i) {
		int now = 0;
		pLL pre = pLL(xs, ys); 
		ll cost = 0;
		for (int j = i; j < n; ++j) {
			cost += dis(pre, vec[j]);
			if (cost <= t) ++now;
			else break;
			pre = vec[j];
		}
		chmax(res, now);
	}
	for (int i = n - 1; i >= 0; --i) {
		int now = 0;
		pLL pre = pLL(xs, ys);
		ll cost = 0;
		for (int j = i; j >= 0; --j) {
			cost += dis(pre, vec[j]);
			if (cost <= t) ++now;
			else break;
			pre = vec[j];
		}
		chmax(res, now);
	}
	pt(res);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> xz >> yz >> ax >> ay >> bx >> by) run();
	return 0;
}
