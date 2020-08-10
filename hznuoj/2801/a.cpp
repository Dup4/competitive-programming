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
constexpr int N = 2e5 + 10; 
int n, k; 
char s[N];

pII get() {
	int now = 0, res = 0, tot = 0;;
	for (int i = 1; i <= n; ++i) {
		if (i == n || s[i] == '>') {
			chmax(res, now);
			now = 0;
		} else {
			++now;
			++tot; 
		}
	}
	return pII(tot, res);
}

int back(vector<int> &vec) {
	int t = vec.back();
	vec.pop_back();
	return t;
}

void run() {
	rd(n, k);
	cin >> (s + 1);
	int all, Max;
	tie(all, Max) = get();
	if (all + 1 < k || Max + 1 > k) return pt("NO");
	int di = 0;
	for (int i = 1; i < n; ++i) {
		if (s[i] == '>' && (i == n - 1 || s[i + 1] == '<')) {
			++di;
		}
	}
	vector <int> hvec;
	for (int i = n; i > n - k; --i) hvec.push_back(i);
	int fini = 0;
	vector <int> res;
	res.push_back(back(hvec));
	int _i = 0, _u = n - k;
   //	_d = 1;
	while (1) {
		int up = 0, down = 0;
		while (_i + 1 < n && s[_i + 1] == '<') ++up, ++_i;
		while (_i + 1 < n && s[_i + 1] == '>') ++down, ++_i;
		if (up <= SZ(hvec)) {
			for (int i = 1; i <= up; ++i) res.push_back(back(hvec));
		} else {
			if (fini) {
				for (int i = _u - up + 1; i <= _u; ++i)
					res.push_back(i);
				_u = _u - up;
			} else {
				for (int i = _u - up + 1 + SZ(hvec); i <= _u; ++i) res.push_back(i);
				_u = _u - up + SZ(hvec);
				while (!hvec.empty()) res.push_back(back(hvec));
				fini = 1;
			}
		}
		if (down) {
			for (int i = _u; i > _u - down + 1; --i) res.push_back(i);
			res.push_back(di); --di;
			_u = _u - down + 1;	
		}
		if (_i + 1 == n) break;
	}
	pt("YES");
	pt(res);
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
