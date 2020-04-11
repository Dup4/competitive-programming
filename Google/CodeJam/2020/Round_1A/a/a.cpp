#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define SZ(x) int((x).size())
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
int n; 

void run() {
	rd(n);
	vector<string> A, B;
	string res = "";
	for (int i = 0; i < n; ++i) {
		string s; rd(s);
		string pre = "", suf = "";
		int l = -1, r = -1;
		for (int j = 0; j < SZ(s); ++j) {
			if (s[j] == '*') {
				l = j;
				break;
			}
			pre += s[j];
		}
		for (int j = SZ(s) - 1; j >= 0; --j) {
			if (s[j] == '*') {
				r = j;
				break;
			}
			suf += s[j];
		}
		for (int j = l + 1; j < r; ++j) {
			if (s[j] == '*') continue;
			res += s[j];
		}
		if (!pre.empty()) A.push_back(pre);
		if (!suf.empty()) {
			reverse(suf.begin(), suf.end());
			B.push_back(suf); 
		}
	}
	sort(A.begin(), A.end(), [&](string x, string y) { return SZ(x) > SZ(y); });
	sort(B.begin(), B.end(), [&](string x, string y) { return SZ(x) > SZ(y); });
	for (int i = 1; i < SZ(A); ++i) { 
		for (int j = 0; j < SZ(A[i]); ++j) {
			if (A[0][j] != A[i][j]) {
				return pt("*");
			}
		}
	}
	for (int i = 1; i < SZ(B); ++i) {
		for (int j = SZ(B[i]) - 1, k = SZ(B[0]) - 1; j >= 0; --j, --k) { 
			if (B[0][k] != B[i][j]) {
				return pt("*");
			}
		}
	}
	if (!A.empty()) {
		A[0] += res;
		res = A[0];
	}
	if (!B.empty()) res += B[0];
	cout << res << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	int _T = nextInt();
//	while (_T--) run(); 
//	while (cin >> n) run();
    for (int kase = 1; kase <= _T; ++kase) {
        cout << "Case #" << kase << ": ";
        run();
    }
	return 0;
}
