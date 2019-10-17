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
int n, m, k;
set <int> se[N];
bool del(int up, int down, int left, int right) {
	for (int i = up; i <= down; ++i) {
		for (int j = left; j <= right; ++j) {
			if (se[i].find(j) == se[i].end()) {
				return false;
			} else {
				se[i].erase(j);
				--k; 
			}
		}
	}
	return true;
}
int get(int y) {
	int l = 1, r = n, pos = -1;
	while (r - l >= 0) {
		int mid = (l + r) >> 1;
		if (se[mid].find(y) != se[mid].end()) {
			pos = mid;
			r = mid - 1;
		} else 
			l = mid + 1;
	}
	return pos;
}
int get2(int y) {
	int l = 1, r = n, pos = -1;
	while (r - l >= 0) {
		int mid = (l + r) >> 1;
		if (se[mid].find(y) != se[mid].end()) {
			pos = mid;
			l = mid + 1;
		} else 
			r = mid - 1; 
	}
}
//dir
//0 right
//1 down
//2 left
//3 up
void run() {
	for (int i = 1; i <= n; ++i) se[i].clear();
	for (int i = 1, x, y; i <= k; ++i) {
		cin >> x >> y;
		se[x].insert(y);
	}
	if (!k) return pt("Yes");
	int up = 1, down = n, left = 1, right = m; 
	int x = 1, y = 1, dir = 0;
	while (k) {
		if (dir == 0) {
			auto nx = se[x].begin();
			if (nx == se[x].end()) {
				y = right; 
			} else {
				if (!del(up, down, *nx, right)) {
					return pt("NO");
				}
				right = *nx - 1; 
				y = *nx - 1; 
			}
		} else if (dir == 1) {
			int pos = get(y);
			if (pos == -1) {
				x = down;
			} else {
				if (!del(pos, down, left, right)) {
					return pt("NO");
				}
				down = pos - 1;
				x = pos - 1;
			}
		} else if (dir == 2) {
			auto pre = se[x].end();
			if (pre != se[x].begin()) {
				--pre;
				if (!del(up, down, left, *pre)) {
					return pt("NO");
				}
				left = *pre + 1;
				y = *pre + 1;
			} else {
				y = left;
			}
		} else {
			auto pre = get2(y);

		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n >> m >> k) run();
	return 0;
}
