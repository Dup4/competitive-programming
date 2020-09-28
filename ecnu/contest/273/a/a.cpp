#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
#define mkp make_pair
#define all(x) (x).begin(), (x).end()
#define endl "\n" 
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
int n, m; 

bool ok(vector <string> &vec, int mask) {
	if (__builtin_popcount(mask) <= 2) return 1;
	vector <string> A;
	for (int i = 0; i < SZ(vec); ++i) if ((mask >> i) & 1) 
		A.push_back(vec[i]);
	for (int i = 2; i < SZ(A); ++i) {
		int x0 = A[0][0] - 'A', y0 = A[0][1] - '0';
		int x1 = A[1][0] - 'A', y1 = A[1][1] - '0';
		int x2 = A[i][0] - 'A', y2 = A[i][1] - '0';
		if ((y2 - y0) * (x1 - x0) != (y1 - y0) * (x2 - x0))
			return 0;
	}	
	return 1;
}

int gao(vector <string> vec) {
	int n = SZ(vec), all = (1 << n) - 1;
	vector <int> f((1 << n) + 5, 8);
	vector <bool> valid((1 << n) + 5, 0);
	for (int i = 0; i < 1 << n; ++i) {
		valid[i] = ok(vec, i);
	}
	f[0] = 0;
	for (int i = 0; i < 1 << n; ++i) {
		int mask = all ^ i;
		for (int j = mask; j; j = (j - 1) & mask) {
			if (valid[j]) {
				chmin(f[i ^ j], f[i] + 1);
			}
		}
	}
	return f[all];
}

void run() {
	rd(n);
	vector <string> A(n);
	for (auto &it : A) rd(it);
	rd(m);
	vector <string> B(m);
	for (auto &it : B) rd(it);
//	dbg(gao(A), gao(B));
	if (SZ(A) > SZ(B)) pt("Cuber QQ");
	else pt("Quber CC");
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	int _T = 1;
	while (_T--) run(); 
//    for (int kase = 1; kase <= _T; ++kase) {
//        cout << "Case #" << kase << ": ";
//        run();
//    }
//	while (cin >> n) run();
//	run();
	return 0;
}
