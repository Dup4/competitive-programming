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

class Solution {
public:
	bool gao(string &res, int &a, int &b, int &c, char _a, char _b, char _c) {
	//	pt(res, res[-2], res[-3], _a);
		if (SZ(res) > 1 && *(res.end() - 1) == _a && *(res.end() - 2) == _a) {
			if (b + c == 0) return false;
			if (b > c) {
				res += _b;
				--b;
			} else {
				res += _c;
				--c;
			}
		} else {
			res += _a;
			--a;
		}
		return true;
	}
	string longestDiverseString(int a, int b, int c) {
		string res = "";
		while (a + b + c > 0) {
			int t = max({a, b, c});
			if (a == t) {
				if (!gao(res, a, b, c, 'a', 'b', 'c')) break;
			} else if (b == t) {
				if (!gao(res, b, a, c, 'b', 'a', 'c')) break;
			} else {
				if (!gao(res, c, a, b, 'c', 'a', 'b')) break;
			}
		}
		return res;
    }
};

void run() {
	int a, b, c;
	rd(a, b, c);
	pt((new Solution())->longestDiverseString(a, b, c));
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	run();
//	while (cin >> n) run();
//    for (int kase = 1; kase <= _T; ++kase) {
//        cout << "Case #" << kase << ":\n";
//        run();
//    }
	return 0;
}
