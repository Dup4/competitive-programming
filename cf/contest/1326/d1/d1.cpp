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
constexpr int N = 1e6 + 10; 
int n, ok[N], cnt; char s[N], t[N]; 

void up(int i, int n, int opt) {
	int j = n - i + 1;
	//dbg(i, j, n);
	if (t[i] != t[j]) cnt += opt;
}

bool check(int x) {
	memset(ok, 0, sizeof ok);
	cnt = 0;
	int del = n - x;
	t[x + 1] = 0;
	for (int i = del + 1, j = 1; i <= n; ++i, ++j) {
		t[j] = s[i];
	}
	for (int i = 1; i <= x / 2; ++i) up(i, x, 1);
//	dbg(x, cnt);
	if (!cnt) return 1;
	if (!del) return 0;
	for (int i = del, j = 1; i < n; ++i, ++j) {
		up(j, x, -1);
		t[j] = s[j];
		up(j, x, 1);
		if (!cnt) return 1;
	}
	return 0;
}

void print(int x) {
	memset(ok, 0, sizeof ok);
	cnt = 0;
	int del = n - x;
	t[x + 1] = 0;
	for (int i = del + 1, j = 1; i <= n; ++i, ++j) {
		t[j] = s[i];
	}
	for (int i = 1; i <= x / 2; ++i) up(i, x, 1);
	if (!cnt) {
		cout << t + 1 << endl;
		return;
	}
	if (!del) return;
	for (int i = del, j = 1; i < n; ++i, ++j) {
		up(j, x, -1);
		t[j] = s[j];
		up(j, x, 1);
		if (!cnt) {
			cout << t + 1 << endl;
			return;
		}
	}
	assert(0);
}

void run() {
	cin >> (s + 1);
	n = strlen(s + 1);
	vector <int> vec[2];
	for (int i = 1; i <= n; i += 2) vec[0].push_back(i);
	for (int i = 2; i <= n; i += 2) vec[1].push_back(i);
	int res = 1;
	for (int i = 1; i < 2; ++i) if (!vec[i].empty()) {
		int l = 0, r = SZ(vec[i]) - 1, pos = -1;
		while (r - l >= 0) {
			int mid = (l + r) >> 1;
			if (check(vec[i][mid])) {
				pos = mid;
				l = mid + 1;
			} else {
				r = mid - 1;
			}
		}
		if (pos > -1) chmax(res, vec[i][pos]);
	}	
	//pt(res);
	if (res % 2 == 0 && res < n && check(res + 1)) ++res;
	print(res);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	int _T = nextInt();
	while (_T--) run(); 
//	while (cin >> n) run();
//    for (int kase = 1; kase <= _T; ++kase) {
//        cout << "Case #" << kase << ":\n";
//        run();
//    }
	return 0;
}
