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
constexpr int N = 1e5 + 10, INF = 0x3f3f3f3f; 
int n, f[N]; ull x[N], y[N], z[N];

ull k1, k2;
ull CoronavirusBeats() {
	unsigned long long k3 = k1, k4 = k2;
	k1 = k4;
	k3 ^= k3 << 23;
	k2 = k3 ^ k4 ^ (k3 >> 17) ^ (k4 >> 26);
	return k2 + k4;
}

struct Hash {
	vector <ull> a;
	ull& operator[](int x) { return a[x - 1]; }
	int size() { return a.size(); }
	void init() { a.clear(); }
	void add(ull x) { a.push_back(x); }
	void gao() { sort(a.begin(), a.end()); a.erase(unique(a.begin(), a.end()), a.end()); }
	int get(ull x) { return lower_bound(a.begin(), a.end(), x) - a.begin() + 1; }	
}hx, hy, hz;

struct E {
	int x, y, z, id, isLeft;
	bool operator < (const E &other) const {
		if (x == other.x) {
			if (y == other.y)
				return z > other.z;
			return y > other.y;
		}
		return x < other.x;
	}
}e[N], e1[N];

struct BIT {
	int a[N];
	void init() { memset(a, 0, sizeof a); }
	void update(int x, int v) {
		for (; x < N; x += x & -x)
			chmax(a[x], v);
	}
	int query(int x) {
		int res = 0;
		for (; x; x -= x & -x)
			chmax(res, a[x]);
		return res;
	}
	void clear(int x) {
		for (; x < N; x += x & -x)
			a[x] = 0;
	}
}bit;

bool cmp(E a, E b) {
	if (a.y == b.y)
		return a.z > b.z;
	return a.y < b.y;
}

void gao(int l, int r) {
	if (l == r) { 
		return;
	}
	int mid = (l + r) >> 1;
	gao(l, mid);
	for (int i = l; i <= r; ++i) {
		e1[i] = e[i];
		if (i <= mid) e1[i].isLeft = 1;
		else e1[i].isLeft = 0;
	}
	sort(e1 + l, e1 + r + 1, cmp);
	for (int i = l; i <= r; ++i) {
		if (e1[i].isLeft) {
			bit.update(e1[i].z, f[e1[i].id]);
		} else {
			chmax(f[e1[i].id], bit.query(e1[i].z - 1) + 1);	
		}
	}	
	for (int i = l; i <= r; ++i) {
		if (e1[i].isLeft) {
			bit.clear(e1[i].z);
		}
	}
	gao(mid + 1, r);
}

void run() {
	rd(n, k1, k2);
	hx.init(); hy.init(); hz.init();
	for (int i = 1; i <= n; ++i) {
		x[i] = CoronavirusBeats();
		hx.add(x[i]);
		y[i] = CoronavirusBeats();
		hy.add(y[i]);
		z[i] = CoronavirusBeats();
		hz.add(z[i]);
	}
	hx.gao(); hy.gao(); hz.gao();
	for (int i = 1; i <= n; ++i) {
		f[i] = 1;
		e[i] = {hx.get(x[i]), hy.get(y[i]), hz.get(z[i]), i, 0};
	}
	sort(e + 1, e + 1 + n);
	gao(1, n);
	pt(*max_element(f + 1, f + 1 + n));
	for (int i = 1; i <= n; ++i)
		cout << f[i] - 1 << " \n"[i == n];
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
