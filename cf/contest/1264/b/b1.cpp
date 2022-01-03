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
constexpr int N = 1e5 + 10;
int a[4]; 
void run() {
	int cnt = 0;
	for (int i = 0; i <= 3; ++i) {
		cnt += (a[i] > 0);
	}
	if (cnt == 1) {
		for (int i = 0; i <= 3; ++i) {
			if (a[i] && a[i] == 1) {
				pt("YES");
				pt(i);
				return;
			}
		}
		return pt("NO");
	} else if (cnt == 2) {
		for (int i = 1; i <= 3; ++i) {
			if (a[i] && a[i - 1]) {
				if (abs(a[i] - a[i - 1]) <= 1) {
					pt("YES");
					int x = i - 1, y = i;
					if (a[x] < a[y]) swap(x, y);
					if (a[x] > a[y]) {
						cout << x << " ";
						--a[x];
					}
					for (int j = 1; j <= a[x]; ++j) {
						cout << y << " " << x << " "; 
					}
					cout << endl;
					return;
				}
			}
		}	
		return pt("NO");
	} 
	if (a[1] < a[0] || a[2] < a[3]) return pt("NO");
	vector <int> l, r;
	for (int i = 1; i <= a[0]; ++i) {
		l.push_back(0);
		l.push_back(1);
	}
	a[1] -= a[0]; a[0] = 0;	
	for (int i = 1; i <= a[3]; ++i) {
		r.push_back(3);
		r.push_back(2);
	}
	a[2] -= a[3]; a[3] = 0;
	reverse(r.begin(), r.end());
	if (abs(a[1] - a[2]) > 1) return pt("NO");
	if (a[1] > a[2]) l.insert(l.begin(), 1), --a[1];
	if (a[2] > a[1]) r.push_back(2), --a[2];
	pt("YES");
	for (auto &it : l) cout << it << " ";
	for (int i = 1; i <= a[1]; ++i) cout << " 2 1 ";
	for (auto &it : r) cout << it << " ";
	cout << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> a[0] >> a[1] >> a[2] >> a[3]) run();
	return 0;
}
