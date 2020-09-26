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
constexpr int N = 1e5 + 10; 
int n; 
vector <string> obj;
string s, t;
int f[N][10];

bool isYEAP(int year) {
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) return true;
	return false;
}

int Mon[2][13] = {
	0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31,
	0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31,
};

int ok(string t) {
	string _t = t;
	reverse(all(_t));
	if (t != _t) return false;
	int year = atoi(t.substr(0, 4).c_str());
	int month = atoi(t.substr(4, 2).c_str());
	int day = atoi(t.substr(6, 2).c_str());
	if (year < 1 || month < 1 || day < 1) return false;
	if (month > 12) return false;
	if (day > Mon[isYEAP(year)][month]) return false;
	return true;
}

inline int calc(string s, string t) {
	int lens = SZ(s), lent = SZ(t);
	for (int i = 0; i <= lens; ++i) f[i][0] = 1;
	for (int i = 1; i <= lens; ++i) {
		for (int j = 1; j <= lent; ++j) {
			f[i][j] = f[i - 1][j];
			if (s[i - 1] == t[j - 1]) {
				chadd(f[i][j], f[i - 1][j - 1]);
			}
		}
	}
	return f[lens][lent];
}

void run() {
	if (s == "#") return;
	string _s = "";
	for (auto &ch : s) if (ch != ' ') _s += ch;
	int res = 0;
	for (auto &it : obj) 
		chadd(res, calc(_s, it));
	pt(res);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	for (int i = 2000; i <= 2099; ++i) {
		for (int j = 1; j <= 12; ++j) {
			for (int k = 1; k <= 31; ++k) {
				char t[10];
				sprintf(t, "%04d%02d%02d", i, j, k);
			//	string _t = string(t);
			//	cout << _t << endl;
				if (ok(string(t))) {
					obj.push_back(string(t));
				}	
			}
		}
	}
	while (getline(cin, s)) run(); 
	return 0;
}
