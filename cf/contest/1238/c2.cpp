#include <bits/stdc++.h>
#define debug(...) { printf("#  "); printf(__VA_ARGS__); puts(""); }
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
inline void pt() { cout << endl; }
template <class T, class... Ts> void pt(const T& arg, const Ts&... args) { cout << arg << " "; pt(args...); }
template <class T> inline void pt(const T &s) { cout << s << "\n"; }
template <class T> inline void pt(const vector <T> &vec) { for (auto &it : vec) cout << it << " "; cout << endl; } 
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
inline ll qpow(ll base, ll n) { ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
constexpr int N = 2e5 + 10;
int h, n, a[N]; 
set <int> se;
void run() {
	cin >> h >> n;
	if (n == 1) return pt(0);
	vector <int> vec; se.clear();
	for (int i = 1; i <= n; ++i) {
		cin >> a[i]; se.insert(a[i]);
		if (i > 1) vec.push_back(a[i] + 1);
		vec.push_back(a[i]);
		vec.push_back(a[i] - 1);
	}
	vec.push_back(0);
	sort(vec.begin(), vec.end());
	erase(unique(vec.begin(), vec.end()), vec.end());
	int lazy = 0, Min = 0; 
	for (int i = 1, sze = vec.size(); i < sze; ++i) {
		if (se.find(i) != se.end()) ++lazy;
		int f = Min + lazy; 
			
		
	}
	int res = 0, lst = a[2] + 1; 
	for (int i = 2; i <= n; ++i) {
		if (lst <= a[i]) continue;
		lst = a[i] + 1;
		if (i == n) {
			if (lst >= 3) ++res; 
			break;
		}
		if (lst - a[i + 1] >= 3) {
			++res;
			lst = a[i + 1] + 1;
		} else {
			lst = a[i + 1];
		}
	}
	pt(res);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	int _T; cin >> _T;
	while (_T--) run();
	return 0;
}
