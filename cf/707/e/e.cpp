#include <bits/stdc++.h>
#define fi first
#define se second
#define SZ(x) ((int)x.size())
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
template <class T1, class T2> T1 gcd(T1 a, T2 b) { return b ? gcd(b, a % b) : a; }
inline ll qpow(ll base, ll n) { assert(n >= 0); ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
//head
constexpr int N = 2e3 + 10;
int n, m, q, K, a[N][N], sta[N], x[N][2], y[N][2], cntAsk;
ll ans[N]; 
vector <vector<int>> qvec;
vector <vector<pII>> vec; 

struct BIT {
	ll a[N][N]; 
	void init() { memset(a, 0, sizeof a); }
	int lowbit(int x) { return x & -x; }
	void update(int x, int y, int v) {
		for (int i = x; i < N; i += lowbit(i)) {
			for (int j = y; j < N; j += lowbit(j)) {
				a[i][j] += v;
			}
		}
	}
	ll query(int x, int y) {
		ll res = 0;
		for (int i = x; i; i -= lowbit(i)) {
			for (int j = y; j; j -= lowbit(j)) {
				res += a[i][j];
			}
		}
		return res;
	}
	ll query(int x1, int y1, int x2, int y2) {
		return query(x2, y2) - query(x1 - 1, y2) - query(x2, y1 - 1) + query(x1 - 1, y1 - 1);
	}
}bit;

void run() {
	vec.clear(); vec.resize(K + 1);
	qvec.clear(); qvec.resize(K + 1);
	for (int i = 1, sze; i <= K; ++i) {
		sta[i] = 1;
		cin >> sze;
		for (int j = 1, x, y, w; j <= sze; ++j) {
			cin >> x >> y >> w;
			a[x][y] = w;
			vec[i].push_back(pII(x, y));
		}
	}
	cin >> q;
	cntAsk = 0;
	char op[10];
	for (int i = 1; i <= q; ++i) {
		cin >> op;
		if (op[0] == 'S') sta[rd()] ^= 1;
		else {
			++cntAsk;
			ans[cntAsk] = 0; 
			cin >> x[cntAsk][0] >> y[cntAsk][0] >> x[cntAsk][1] >> y[cntAsk][1];
			for (int j = 1; j <= K; ++j) {
				if (sta[j]) {
					qvec[j].push_back(cntAsk);
				}
			}
		}
	}
	bit.init();
	for (int i = 1; i <= K; ++i) {
		for (auto &it : vec[i]) bit.update(it.fi, it.se, a[it.fi][it.se]);
		for (auto &it : qvec[i]) ans[it] += bit.query(x[it][0], y[it][0], x[it][1], y[it][1]);
		for (auto &it : vec[i]) bit.update(it.fi, it.se, -a[it.fi][it.se]);
	}
	for (int i = 1; i <= cntAsk; ++i)
		pt(ans[i]);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n >> m >> K) run();
	return 0;
}
