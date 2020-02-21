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
template <class T1, class T2> inline void chadd(T1 &x, T2 y, int Mod = mod) { x += y; while (x >= Mod) x -= Mod; while (x < 0) x += Mod; } 
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
inline ll qpow(ll base, ll n) { assert(n >= 0); ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
//head
constexpr int N = 2e4 + 10;
constexpr ll INF = 0x3f3f3f3f3f3f3f3f;
int n, m, a[N]; ll f[2][N];  

struct Hash {
	vector <int> a;
	int& operator[](int x) { return a[x - 1]; }
	void init() { a.clear(); }
	void add(int x) { a.push_back(x); }
	void gao() { sort(a.begin(), a.end()); a.erase(unique(a.begin(), a.end()), a.end()); }
	int query(int x) { return lower_bound(a.begin(), a.end(), x) - a.begin() + 1; }	
}hs;

void run() {
	hs.init();
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		hs.add(a[i] - 1);
		hs.add(a[i]);
		hs.add(a[i] + 1);
		hs.add(a[i] - 2);
		hs.add(a[i] + 2);
	}
	hs.gao();
	m = hs.a.size();
//	for (int i = 1; i <= m; ++i)
//		dbg(i, hs[i]);
	memset(f, 0, sizeof f);
	for (int i = 1; i <= n; ++i) {
		int p = i & 1; 
		for (int j = 1; j <= m; ++j) {
			f[p][j] = f[p ^ 1][j - 1] + abs(a[i] - hs[j]);
		}
		f[p][0] = INF;
		for (int j = 2; j <= m; ++j) {
			chmin(f[p][j], f[p][j - 1]);
		}
	//	for (int j = 1; j <= m; ++j)
	//		dbg(i, j, f[p][j]);
	}
	pt(f[n & 1][m]); 
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n) run();
	return 0;
}
