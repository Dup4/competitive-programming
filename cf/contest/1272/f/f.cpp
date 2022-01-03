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
constexpr int N = 2e2 + 5, INF = 0x3f3f3f3f;
struct E {
	int i, j, k;
	E() {}
	E(int i, int j, int k) : i(i), j(j), k(k) {} 
	bool operator == (const E &other) const {
		return i == other.i && 
			   j == other.j &&
			   k == other.k;
	}
}pre[N][N][N * 2]; 
int n, m, limit, f[N][N][N * 2];
char s[N], t[N];
void update(E ePre, E eNow) {
	if (ePre.k >= 0 && ePre.k <= limit && ePre.i >= 0 && ePre.j >= 0) {
		int &iPre = f[ePre.i][ePre.j][ePre.k];
		int &iNow = f[eNow.i][eNow.j][eNow.k];
		if (iPre + 1 < iNow) {
			iNow = iPre + 1;
			pre[eNow.i][eNow.j][eNow.k] = ePre;
		}	
	}	
}
void run() {
	n = strlen(s + 1);
	m = strlen(t + 1); 
	limit = n + m; 
	memset(f, 0x3f, sizeof f);
	memset(pre, -1, sizeof pre);
	f[0][0][0] = 0; 
	for (int i = 1; i <= n + m; ++i) {
		f[0][0][i] = i;
		pre[0][0][i] = E(0, 0, i - 1); 
	}
	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= m; ++j) {
			for (int k = 0; k <= limit; ++k) { 
				vector <E> o{
					E(i - 1, j, s[i] == '(' ? k - 1 : k + 1),
					E(i, j - 1, t[j] == '(' ? k - 1 : k + 1),
					E(i, j, k - 1),
				};
				if (s[i] == t[j]) {
					o.emplace_back(i - 1, j - 1, s[i] == '(' ? k - 1 : k + 1); 
				}
				for (auto &it : o) {
					update(it, E(i, j, k));
				}
			}
			for (int k = limit; k >= 0; --k) {
				update(E(i, j, k + 1), E(i, j, k));
			}
		}
	}
	string s = "";
	E now = E(n, m, 0);
	assert(f[n][m][0] != INF);
	while (!(now == E(0, 0, 0))) {
		E tmp = pre[now.i][now.j][now.k];
		if (tmp.k < now.k) s += '(';
		else s += ')';
		now = tmp;
	}
	reverse(s.begin(), s.end());
	cout << s << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> (s + 1) >> (t + 1)) run();
	return 0;
}
