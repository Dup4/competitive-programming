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
constexpr int N = 2e5 + 10;
int n, a[26], b[26]; char s[N], t[N]; 
bool same() {
	memset(a, 0, sizeof a);
	memset(b, 0, sizeof b);
	for (int i = 1; i <= n; ++i) {
		++a[s[i] - 'a'];
		++b[t[i] - 'a'];	
	}
	for (int i = 0; i < 26; ++i)
		if (a[i] != b[i])
			return false;
	return true;
}
int cnt(char *s, char *t) {
	int res = 0;
	for (int i = 1; i <= n; ++i) {
		if (s[i] != t[i]) {
			for (int j = i + 1; j <= n; ++j) {
				if (s[j] == t[i]) {
					for (int k = j - 1; k >= i; --k) {
						swap(s[k], s[k + 1]);
						++res;
					}
					break;
				}
			}
		}
	}
	return res;
}
void run() {
	n = rd(); cin >> (s + 1) >> (t + 1);
	if (!same()) return pt("NO");  
	for (int i = 0; i < 26; ++i) {
		if (a[i] > 1) {
			return pt("YES");
		}
	}
    if (cnt(s, t) % 2) pt("NO");
	else pt("YES");	
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	int _T = rd();
	while (_T--) run();
	return 0;
}
