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
constexpr int N = 1e3 + 10; 
int n, vis[N][N]; pII a[N][N]; char s[N][N]; 
int Move[][2] = {
	-1, 0,
	1, 0,
	0, -1,
	0, 1
};

bool ok(int x, int y) { return x >= 1 && x <= n && y >= 1 && y <= n; } 

void run() {
	memset(s, 0, sizeof s);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) { 
			rd(a[i][j].fi, a[i][j].se);
		}
	}	
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			int cnt = 0;
			for (int k = 0; k < 4; ++k) {
				pII nx = pII(i, j);
				nx.fi += Move[k][0];
				nx.se += Move[k][1];
				if (ok(nx.fi, nx.se) && a[nx.fi][nx.se] == a[i][j])
					++cnt;
			}
			if (a[i][j] == pII(-1, -1) && cnt == 0) return pt("INVALID");
		//	if (a[i][j] != pII(i, j) && a[i][j] != pII(-1, -1) && cnt > 2) return pt("INVALID");	
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (a[i][j] == pII(-1, -1)) {
				int _ok[4] = {0};
				for (int k = 0; k < 4; ++k) {
					pII nx = pII(i, j);
					nx.fi += Move[k][0];
					nx.se += Move[k][1];
					if (ok(nx.fi, nx.se)) {
						if (a[nx.fi][nx.se] == pII(-1, -1)) 
							_ok[k] = 1;
					}
				}
				if (_ok[2] && _ok[3]) s[i][j] = 'R';
				else if (_ok[2]) s[i][j] = 'L';
				else if (_ok[3]) s[i][j] = 'R';
			    else if (_ok[0] && _ok[1]) s[i][j] = 'D';
				else if (_ok[0]) s[i][j] = 'U';
				else if (_ok[1]) s[i][j] = 'D';
				else return pt("INVALID");
			}
		}
	}
	memset(vis, 0, sizeof vis);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (a[i][j] == pII(i, j)) {
				s[i][j] = 'X';
				queue <pII> que;
				que.push(pII(i, j));
				vis[i][j] = 1;
				while (!que.empty()) {
					pII now = que.front(); que.pop();
					for (int k = 0; k < 4; ++k) {
						pII tmp = now;
						tmp.fi += Move[k][0];
						tmp.se += Move[k][1];
						if (ok(tmp.fi, tmp.se) && !vis[tmp.fi][tmp.se] && a[tmp.fi][tmp.se] == a[i][j]) {
							pII nx = tmp;
							char *S = "DURL";
							s[nx.fi][nx.se] = S[k];
							que.push(nx);
							vis[nx.fi][nx.se] = 1;
							//break;
						}
					}
				}
			}
		}
	}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			if (s[i][j] == 0)
				return pt("INVALID");
	pt("VALID");
	for (int i = 1; i <= n; ++i)
		cout << (s[i] + 1) << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n) run();
//    for (int kase = 1; kase <= _T; ++kase) {
//        cout << "Case #" << kase << ":\n";
//        run();
//    }
	return 0;
}
