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
constexpr int N = 5e2 + 10, INF = 0x3f3f3f3f; 
int n, x, y, res, a[N][N]; 

bool ok(int x, int y) {
	if (x < 1 || x > n || y < 1 || y > n) return false;
	return true;
}

int dis(int x, int y, int nx, int ny) {
	return abs(x - nx) + abs(y - ny);
}

vector <pII> Move[4];

int gao(int x, int y, int round) {
	vector <int> vec;
	for (auto ix : {1, 2, 3}) {
		for (auto &it : Move[ix]) {
			int nx = x + it.fi;
			int ny = y + it.se;
			if (ok(nx, ny)) vec.push_back(a[nx][ny]);
		}
	}
	sort(all(vec));
	int base = a[x][y];
	int food = 0;
	int people = 1;
	while (people < 9 && round <= res) {
		++round;
		food += base;
		if (food >= 8 * people * people) {
			++people;
			if (!vec.empty()) {
				base += vec.back();
				vec.pop_back();	
			}
		}
	}
//	dbg(x, y, round);	
	return round;
}

int ceil(int x, int y) {
	return (x + y - 1) / y;
}

void run() {
	rd(n, x, y);
	for (int i = 1; i <= n; ++i) 
		for (int j = 1; j <= n; ++j)
			rd(a[i][j]);
	res = INF;
	res = gao(x, y, 0);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			chmin(res, gao(i, j, ceil(dis(x, y, i, j), 2)));
		}
	}
//	for (auto ix: {1, 2}) {
//		for (auto &it : Move[ix]) {
//			int nx = x + it.fi, ny = y + it.se;
//			if (ok(nx, ny)) chmin(res, gao(nx, ny, 1));
//		}
//	}
	pt(res);
}

int main() {
	Move[0] = vector <pII>({mkp(0, 0)});
	Move[1] = vector <pII>({mkp(1, 0), mkp(0, 1), mkp(-1, 0), mkp(0, -1)});
	Move[2] = vector <pII>({mkp(2, 0), mkp(0, 2), mkp(-2, 0), mkp(0, -2), mkp(1, 1), mkp(1, -1), mkp(-1, 1), mkp(-1, -1)});
	Move[3] = vector <pII>({mkp(3, 0), mkp(0, 3), mkp(-3, 0), mkp(0, -3), mkp(1, 2), mkp(1, -2), mkp(-1, 2), mkp(-1, -2), mkp(2, 1), mkp(-2, 1), mkp(2, -1), mkp(-2, -1)});
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
