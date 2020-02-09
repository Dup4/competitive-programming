#include <bits/stdc++.h>
#define fi first
#define se second
#define SZ(x) ((int)x.size())
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
template <class T1, class T2> T1 gcd(T1 a, T2 b) { return b ? gcd(b, a % b) : a; }
inline ll qpow(ll base, ll n) { assert(n >= 0); ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
//head
constexpr int N = 1e3 + 100;
int n, K, dead[N], g[N][N], need[N], pos[N], posl[N], posr[N];

inline bool ask(int x) {
	pt("?", x);
	cout.flush();
	string s; cin >> s;
	return s[0] == 'Y';
}

inline void reset() {
	pt('R');
	cout.flush();
}

void run() {
	memset(dead, 0, sizeof dead);
    memset(g, 0, sizeof g);
	memset(need, 0, sizeof need);
	K /= 2; if (!K) K = 1;
	int unit = n / K;
	for (int i = 1; i <= n; ++i) {
		pos[i] = (i - 1) / K + 1; 
		if (i == 1 || pos[i] != pos[i - 1]) posl[pos[i]] = i;
		posr[pos[i]] = i;
	}
	for (int i = 1; i <= pos[n]; ++i) {
		need[i] = pos[n] - i;		
	}
	if (need[1] == 0) need[1] = 1; 
	while (1) {
		int st = -1;
		for (int i = 1; i <= pos[n]; ++i) {
			if (need[i] > 0) {
				st = i;
				break;
			}
		}
		if (st == -1) break;
		--need[st]; 
		for (int i = posl[st]; i <= posr[st]; ++i) {
			if (ask(i)) dead[i] = 1;
		}	
		for (int i = st + 1; i <= pos[n]; ++i) {
			if (g[st][i] == 0) {
				g[st][i] = 1;
				for (int j = posl[i]; j <= posr[i]; ++j) {
					if (ask(j)) dead[j] = 1; 
				}
				st = i;
				--need[st];
			}
		}
		reset();
	}
	int res = 0;
	for (int i = 1; i <= n; ++i)
		res += (!dead[i]);
	pt("!", res);
	cout.flush();
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n >> K) run();
	return 0;
}
