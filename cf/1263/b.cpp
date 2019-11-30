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
constexpr int N = 1e2 + 10;
int n, id[N], num[N], vis[N]; 
void run() {
	n = rd();
	vector <string> s;
	map <string, int> mp;
	s.resize(n);
	memset(id, 0, sizeof id);
	memset(num, 0, sizeof num);  
	for (auto &it : s) cin >> it; 
	memset(vis, 0, sizeof vis);
	memset(id, 0, sizeof id);
	memset(num, 0, sizeof num);
	*id = 0; 
	int res = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = i - 1; j >= -1; --j) {
			if (j == -1) {
				id[i] = ++*id;
				num[id[i]] = 1;
				mp[s[i]] = 1; 
				vis[i] = 1;
			} 
			if (s[i] == s[j]) {
				id[i] = id[j];
				++num[id[i]]; 
				if (num[id[i]] > 1) {
					++res;
				}
				break;
			}
		}
	}
	for (int i = 0; i < n; ++i) {
		if (vis[i] == 0) {
			for (int j = 0; j < 4; ++j) {
				char ori = s[i][j];
				bool ok = false;
				for (int k = 0; k <= 9; ++k) {
					s[i][j] = k + '0';
					if (mp.count(s[i]) == 0) {
						mp[s[i]] = 1;
						ok = true;
						break;
					}
				}
				if (!ok) {
					s[i][j] = ori;
				} else {
					break;
				}
			}
		}	
	}
	pt(res);
	for (auto &it : s) 
		cout << it << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	int _T = rd();
	while (_T--) run();
	return 0;
}
