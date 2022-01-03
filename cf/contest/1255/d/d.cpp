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
constexpr int N = 1e2 + 10;
int n, m, k, pos, vis[N][N]; char S[N][N];
vector <char> alpha;
pII gao(pII it, int x, int y) { 
	while (y--) {
		int need = x;
		while (1) {
			if (S[it.fi][it.se] == 'R') --need;
			vis[it.fi][it.se] = 1; 
			S[it.fi][it.se] = alpha[pos];
			if (it.fi % 2 == 1) ++it.se;
			else --it.se;
			if (it.se == m + 1) {
				++it.fi;
				it.se = m;
			} else if (it.se == 0) {
				++it.fi;
				it.se = 1; 
			}
			if (need == 0) {
				++pos;
				break;
			}
		}
	}
	return it;
}
void run() {
	pos = 0; 
	cin >> n >> m >> k;
	int tot = 0;
	for (int i = 1; i <= n; ++i) {
		cin >> (S[i] + 1);
		for (int j = 1; j <= m; ++j) {
			vis[i][j] = 0;
			tot += (S[i][j] == 'R');
		}
	}
	gao(gao(pII(1, 1), tot / k + 1, tot % k), tot / k, k - tot % k);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (vis[i][j] == 0) {
				S[i][j] = alpha[k - 1];
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		cout << (S[i] + 1) << endl;
	}
}

int main() {
	alpha.clear();
	for (char i = 'a'; i <= 'z'; ++i) alpha.push_back(i);
	for (char i = 'A'; i <= 'Z'; ++i) alpha.push_back(i);
	for (char i = '0'; i <= '9'; ++i) alpha.push_back(i);
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	int _T = rd();
	while (_T--) run();
	return 0;
}
