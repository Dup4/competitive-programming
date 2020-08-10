#include <bits/stdc++.h>
using namespace std;
#define endl "\n" 
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
#define mkp make_pair
#define all(x) (x).begin(), (x).end()
using db = double;
using ll = long long;
using ull = unsigned long long; 
using pII = pair <int, int>;
using pLL = pair <ll, ll>;
constexpr int mod = 1e9 + 7;
template <class T1, class T2> inline void chadd(T1 &x, T2 y, int Mod = mod) { x += y; while (x >= Mod) x -= Mod; while (x < 0) x += Mod; } 
template <class T1, class T2> inline void chmax(T1 &x, T2 y) { if (x < y) x = y; }
template <class T1, class T2> inline void chmin(T1 &x, T2 y) { if (x > y) x = y; }
inline int nextInt() { int x; cin >> x; return x; }
void rd() {}
template <class T, class... Ts> void rd(T& arg, Ts&... args) { cin >> arg; rd(args...); }
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
constexpr int N = 3e3 + 10; 
int n, a[N], f[N][N]; 

struct Hash {
	vector <int> a;
	int& operator[](int x) { return a[x - 1]; }
	int size() { return a.size(); }
	void init() { a.clear(); }
	void add(int x) { a.push_back(x); }
	void gao() { sort(a.begin(), a.end()); a.erase(unique(a.begin(), a.end()), a.end()); }
	int get(int x) { return lower_bound(a.begin(), a.end(), x) - a.begin() + 1; }	
}hs;

void run() {
	rd(n);
	hs.init();
	for (int i = 1; i <= n; ++i) rd(a[i]), hs.add(a[i]);
	hs.gao();
	for (int i = 1; i <= n; ++i) a[i] = hs.get(a[i]);
	memset(f, 0, sizeof f);
	for (int i = 1; i <= a[1]; ++i) f[1][i] = 1; 
	int m = SZ(hs.a);
	f[1][m + 1] = hs[a[1]] - a[1]; 
   	for (int i = 2; i <= n; ++i) {
		int up = min(a[i], a[i - 1]);
		for (int j = 1; j <= up; ++j) {
			if (j != a[i]) chadd(f[i][j], f[i - 1][a[i]]); 
			else {
				int _up = i == 2 ? a[i - 1] : min(a[i - 2], a[i - 1]);
				for (int k = 1; k <= _up; ++k) chadd(f[i][j], f[i - 1][k]); 
				chadd(f[i][j], f[i - 1][m + 1]);
			}
		}
		chadd(f[i][m + 1], f[i - 1][m + 1]);
		int _up = i == 2 ? a[i - 1] : min(a[i - 2], a[i - 1]);
		for (int j = 1; j <= _up; ++j) if (j != a[i - 1]) {
			chadd(f[i][m + 1], f[i - 1][j]);
		}
	}	
	int res = 0;
	for (int i = 1; i < N; ++i) chadd(res, f[n][i]);
	pt(res);
	
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	int _T = nextInt();
	while (_T--) run(); 
//    for (int kase = 1; kase <= _T; ++kase) {
//        cout << "Case #" << kase << ": ";
//        run();
//    }
//	while (cin >> n) run();
//	run();
	return 0;
}
