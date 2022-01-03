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

void change(ll &_x, ll x, ll i) {
//	dbg(_x, x, i);
	if (x >= _x) {
		_x += i;
	} else {
		_x -= i;
	}
}

void run() {
	ll x, y;
	rd(x, y);
	if (x == 0 && y == 0) {
		pt(0);
	//	pt(0, 0);
		return;
	}
	ll need = abs(x) + abs(y);
	int st = 0; ll now = 0;
	while (1) {
		++st;
		now += st;
		if (now >= need && (now - need) % 2 == 0) break;
	}
	pt(st);
	ll _x = 0, _y = 0;
	for (int i = 1; i <= st; ++i) {
		if (abs(x - _x) >= i) {
			change(_x, x, i);
		} else if (abs(y - _y) >= i) {
			change(_y, y, i);
		} else {
			int _i = i;
			_i -= abs(x - _x);
			_x = x; 
			int gap = abs(y - _y); 
			if (_i >= gap) {
				if ((_i - gap) % 2 == 0) {
					change(_y, y, gap);
					assert(_y == y);
				} else {
					change(_y, y, gap - 1);
					assert(abs(y - _y) == 1);
				}
			} else {
				change(_y, y, _i);
			}
		}
		pt(_x, _y);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	int _T = nextInt();
//	while (_T--) run(); 
    for (int kase = 1; kase <= _T; ++kase) {
        cout << "Case #" << kase << ":\n";
        run();
    }
//	while (cin >> n) run();
//	run();
	return 0;
}
