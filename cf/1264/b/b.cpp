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
constexpr int N = 20;
int n, a[N], link[N][N], in[N], out[N]; 

bool gao(int st) {
	int inTot = accumulate(in, in + 10, 0);
	int inOut = accumulate(out, out + 10, 0);
	if (inTot != inOut) return false;
	for (int i = 1; i <= inTot; ++i) {
		int pos = 0;
		for (int o = 1; o <= 4; ++o) {
			if (out[o] > out[pos])
				pos = o;
		}
		if (!pos) return false;
		if (pos == 2 || pos == 3) {
			int pre = pos - 1, nx = pos + 1;
			if (in[pre] + in[nx] == 0) return false;
			int now = pre;
			if (in[pre] > in[nx]) now = pre;
			else if (in[pre] < in[nx]) now = nx;
			else if (pos == 2) now = 2;
			else now = 4; 
			++link[pos][now];
			--in[now];
			--out[pos];
		} else if (pos == 1) {
			if (in[2] == 0) return false;
			++link[1][2];
			--in[2];
			--out[1];
		} else {
			if (in[3] == 0) return false;
			++link[4][3];
			--in[3];
			--out[4];
		}
	}
	pt("YES");
	for (int i = 1; i <= 4; ++i)
		for (int j = 1; j <= 4; ++j)
			dbg(i - 1, j - 1, link[i][j]);
	vector <int> vec;
	for (int i = 1; i <= n; ++i) {
		vec.push_back(st - 1);
		if (i < n) for (auto &it : {-1, 1}) {
			if (link[st][st + it]) {
				--link[st][st + it];
				st += it;
				break;
			} 
		}
	}
	pt(vec);
	return true;
}

void run() {
	n = accumulate(a, a + 10, 0); 
	for (int i = 1; i <= 4; ++i) {
		for (int j = 1; j <= 4; ++j) {
			if ((i == j && a[i] >= 2) || (i != j && a[i] && a[j])) {
				memset(in, 0, sizeof in);
				memset(out, 0, sizeof out);
				memset(link, 0, sizeof link); 
				++out[i];
				++in[j];
				--a[i]; --a[j];
				for (int k = 1; k <= 4; ++k) {
					in[k] += a[k];
					out[k] += a[k];
				}
				if (gao(i)) return;
				++a[i]; ++a[j]; 
			} 
		}
	}
	return pt("NO");
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> a[1] >> a[2] >> a[3] >> a[4]) run();
	return 0;
}
