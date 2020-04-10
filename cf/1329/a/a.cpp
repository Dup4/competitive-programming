#include <bits/stdc++.h>
#define fi first
#define se second
#define SZ(x) int((x).size())
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
constexpr int N = 1e5 + 10; 
int n, m, a[N], b[N], cnt[N]; 

void run() {
	for (int i = 1; i <= n; ++i) cnt[i] = 0;
	cnt[n + 1] = 1; cnt[0] = 0;
	for (int i = 1; i <= m; ++i) rd(a[i]);
	int Max = n + 1;
	for (int i = m; i >= 1; --i) {
		int r = n - a[i] + 1;
		if (r < Max) { 
			b[i] = r;
		} else {
			while (cnt[Max]) --Max;
			if (Max <= 0) return pt(-1);
			b[i] = Max;
		}
		for (int j = b[i]; j <= b[i] + a[i] + 1; ++j) {
			if (cnt[j]) break;
			cnt[j] = 1;
		}
		chmin(Max, b[i]);
	}
	int pre = 0;
	for (int i = 1; i <= m; ++i) {
		if (b[i] > pre) {
			b[i] = pre + 1;
			pre = b[i] + a[i] - 1;
		} else {
			break;
		}
	}
	for (int i = 1; i <= n; ++i) cnt[i] = 0;
	cnt[n + 1] = 1; cnt[0] = 0;
	for (int i = m; i >= 1; --i) {
		for (int j = b[i]; j <= b[i] + a[i] - 1; ++j) {
			if (cnt[j]) break;
			cnt[j] = 1;
		}
	}
	for (int i = 1; i <= n; ++i) if (!cnt[i])
		return pt(-1);
	for (int i = 1; i <= m; ++i)
		cout << b[i] << " \n"[i == m];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n >> m) run();
//    for (int kase = 1; kase <= _T; ++kase) {
//        cout << "Case #" << kase << ":\n";
//        run();
//    }
	return 0;
}
