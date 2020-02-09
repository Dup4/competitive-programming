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
constexpr int N = 1e2 + 10;
int n, m, W, cnt[15];

struct E {
	vector <vector<int>> vec; 
	int cnt[15], score, submit, ac;
	void init(int n) {
		vec.clear();
		vec.resize(n + 1);
		memset(cnt, 0, sizeof cnt);
		score = 0;
		submit = 0;
		ac = 0;
	}
}e[N];

int f(vector <int> vec) {
	int res = 0, now = 0;
	for (auto &it : vec) {
		if (it == 0) ++now;
		else now = 0;
		chmax(res, now);
	}
	return res;
}

void run() {
	for (int i = 1; i <= n; ++i) {
		e[i].init(m);
	}
	memset(cnt, 0, sizeof cnt);
	for (int i = 1, x, y, c; i <= W; ++i) {
		cin >> x >> y >> c;
		e[x].vec[y].push_back(c);
		++e[x].submit;
		if (c) {
			if (e[x].cnt[y] == 0) {
				e[x].cnt[y] = 1;
				++e[x].ac;	
			}
		}
	}	
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			cnt[j] += e[i].cnt[j];
		}
	}
	for (int i = 1; i <= n; ++i) {
		e[i].score = 0;
		for (int j = 1; j <= m; ++j) {
			if (e[i].cnt[j] == 0) {
				if (cnt[j]) e[i].score += 20;
				if (cnt[j] >= n / 2) e[i].score += 10;
			}
			int K = f(e[i].vec[j]);
			e[i].score += K * K;
			if (e[i].cnt[j] == 0) e[i].score += K * K;
		}
		if (e[i].submit == 0) {
			e[i].score = 998244353;
		} else if (e[i].ac == 0) {
			e[i].score = 1000000;
		} else if (e[i].ac == m) {
			e[i].score = 0;
		}
		pt(e[i].score);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n >> m >> W) run();
	return 0;
}
