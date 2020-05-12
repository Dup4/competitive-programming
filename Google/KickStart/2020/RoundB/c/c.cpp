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
constexpr int mod = 1e9;
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
int n, id[N]; char s[N];

map <char, pLL> mp;

pLL gao(int l, int r) {
//	dbg(l, r);
	pLL now = pLL(0, 0);
	for (int i = l; i <= r; ++i) {
		if (s[i] < '2' || s[i] > '9') {
			now.fi += mp[s[i]].fi;
			now.se += mp[s[i]].se;
		} else {
			pII it = gao(i + 2, id[i + 1] - 1);
			now.fi += 1ll * (s[i] - '0') * it.fi % mod;
			now.se += 1ll * (s[i] - '0') * it.se % mod;
			now.fi %= mod;
			now.se %= mod;
			i = id[i + 1];
		}
	}
	now.fi = (now.fi % mod + mod) % mod;
	now.se = (now.se % mod + mod) % mod;
	return now;
}

void run() {
	cin >> (s + 1);
	n = strlen(s + 1);
	stack <int> sta;
	for (int i = 1; i <= n; ++i) {
		if (s[i] == '(') {
			sta.push(i);
		} else if (s[i] == ')') {
			int it = sta.top(); sta.pop();
			id[it] = i;
			id[i] = it;	
		}
	}
//	for (int i = 1; i <= n; ++i) {
//		if (s[i] == '(')
//			dbg(i, id[i], id[id[i]]);
//	}
	pLL add = gao(1, n);
	pt(add.fi + 1, add.se + 1);
}

int main() {
	mp['N'] = pII(0, -1);
	mp['S'] = pII(0, 1);
	mp['E'] = pII(1, 0);
	mp['W'] = pII(-1, 0);
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
