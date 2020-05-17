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
constexpr int N = 1e2 + 10; 
int n, e[N], vis[N]; ll x[N], y[N]; 

ll gcd(ll a, ll b) { return __gcd(a, b); }

struct frac{
    ll x,y; 
	void sim() {
		return;
		if (x * y == 0) {
			if (x) x = 1;
			else if (y) y = 1;
			return;
		}
		ll g = gcd(abs(x), abs(y));
		x /= g;
		y /= g;
		if (x * y < 0) {
			x = -abs(x);
			y = abs(y);
		} else {
			x = abs(x);
			y = abs(y);
		}
	}
	frac() {}
	frac(ll x, ll y) : x(x), y(y) {sim();}
    frac operator+(const frac &u){
        ll p, q; 
        p = x * u.y + y * u.x;
        q = u.y * y;
        ll d = gcd(p, q);
        p /= d; q /= d;
        return (frac){p, q};
    }
    frac operator-(const frac &u){
        ll p, q;
        p = x * u.y - y * u.x;
        q = u.y * y;
        ll d = gcd(p, q);
        p /= d; q /= d;
        return (frac){p, q};
    }
    frac operator*(const frac &u){
        ll p, q;
        p = u.x * x;
        q = u.y * y;
        ll d = gcd(p, q); 
        p /= d; q /= d;
        return (frac){p, q};
    }
    frac operator/(const frac &u){
        ll p, q;
        p = u.y * x;
        q = u.x * y;
        ll d = gcd(p,q);
        p /= d; q /= d;
        return (frac){p,q};
    }
	bool operator < (const frac &other) const { return x * other.y < y * other.x; }
	bool operator > (const frac &other) const { return x * other.y > y * other.x; }
	bool operator != (const frac &other) const { return x * other.y != y * other.x; }
	bool operator <= (const frac &other) const { return x * other.y <= y * other.x; }
	bool operator >= (const frac &other) const { return x * other.y >= y * other.x; }
	bool operator == (const frac &other) const { return x * other.y == y * other.x; }
	void sqr() { *this = (*this) * (*this); }
    void print(){
		sim();
		if (x * y < 0) putchar('-');
		printf("%lld/%lld", abs(x), abs(y));
    }
};

vector <frac> vec;

inline ll sqr(ll x) { return x * x; }

inline ll dis(int i, int j) {
	return sqr(x[i] - x[j]) + sqr(y[i] - y[j]);
}

inline frac slop(int i, int j) {
	frac it = frac(y[j] - y[i], x[j] - x[i]);
//	dbg(it.x, it.y);
	return it;
}

int gao(vector <int> &id) {
	memset(e, -1, sizeof (e[0]) * (n + 5));
	for (int i = 0; i + 1 < SZ(id); i += 2) {
		e[id[i]] = id[i + 1];
		e[id[i + 1]] = id[i];
	}
	int res = 1;
	for (auto &it : vec) {
		for (int i = 1; i <= n; ++i) {
			memset(vis, 0, sizeof (vis[0]) * (n + 5));
			int st = i;
			vis[st] = 1;
			int now = 1;
			while (1) {
			//	assert(st >= 1 && st <= n);
				if (e[st] == -1) break;
				st = e[st];
				now += (vis[st] == 0);
				vis[st]++;
		//		if (vis[st] > n) break;
				int nx = -1;
				for (int j = 1; j <= n; ++j) if (j != st) {
					frac _it = slop(st, j);
					if (_it.x * it.y == _it.y * it.x) {
						if (nx == -1) nx = j;
						else if (dis(st, j) < dis(st, nx)) nx = j;
					}
				}
				if (nx == -1) break;
			//	dbg(nx);
				st = nx;
				now += (vis[st] == 0);
				vis[st]++;
				if (vis[st] > n * 2) break;
			}	
		//	if (i == 1 && it == frac(1, 0)) dbg(now);
			chmax(res, now);
		}
	}
	return res;
}

void run() {
	rd(n);
	vector <int> id;
	for (int i = 1; i <= n; ++i) {
		rd(x[i], y[i]);
		id.push_back(i);
	}
	vec.clear();
	for (int i = 1; i <= n; ++i) {
		for (int j = i + 1; j <= n; ++j) {
			vec.push_back(frac(y[j] - y[i], x[j] - x[i]));
			//dbg(vec.back().x, vec.back().y);
		}
	}
	sort(vec.begin(), vec.end());
	vec.erase(unique(all(vec)), vec.end());
//	dbg(n);
//	return;
	int res = 1;
	do {
		chmax(res, gao(id));
	} while (next_permutation(all(id)));
	pt(res);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	int _T = nextInt();
//	while (_T--) run(); 
    for (int kase = 1; kase <= _T; ++kase) {
        cout << "Case #" << kase << ": ";
        run();
    }
//	while (cin >> n) run();
//	run();
	return 0;
}
