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
constexpr int N = 1e5 + 10; 
int n, m;  
vector <vector<int>> a;

bool ok(int x, int y) {
	if (x < 0 || x >= n || y < 0 || y >= m) return 0;
//	if (a[x][y] == 0) return 0;
	return 1;
}

ll ceil(ll x, ll y) { return (x + y - 1) / y; }

int Move[][2] = {
	-1, 0,
	1, 0,
	0, 1,
	0, -1
};

void run() {
	rd(n, m);
	a = vector <vector<int>> (n, vector<int>(m));
	for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) rd(a[i][j]);
	ll res = 0;
	while (1) {
		vector <pII> vec;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) if (a[i][j]) {
				res += a[i][j];
				ll tot = 0;
				int num = 0;
				for (int k = 0; k < 4; ++k) { 
					for (int o = 1; ; ++o) {
						int nx = i + Move[k][0] * o;
						int ny = j + Move[k][1] * o;
						if (!ok(nx, ny)) break;
						if (a[nx][ny]) {
							++num;
							tot += a[nx][ny];
							break;
						}
					}
				}
				//dbg(i, j, a[i][j], num, tot);
				if (num == 0 || a[i][j] >= ceil(tot, num)) {
				
				} else {
					vec.push_back(pII(i, j));
				}
			}
		}
		if (vec.empty()) break;
		for (auto &it : vec) a[it.fi][it.se] = 0;
	}
	pt(res);
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
