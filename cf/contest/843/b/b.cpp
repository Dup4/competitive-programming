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
constexpr int N = 1e5 + 10; 
int n, st, x; 

int Next(int l, int r) {
	mt19937 mt(chrono::steady_clock::now().time_since_epoch().count());
	auto rd = bind(uniform_int_distribution<int>(l, r), mt);
	return rd();
}

pII ask(int x) {
	pt('?', x);
	cout.flush();
	pII res;
	rd(res.fi, res.se);
	return res;
}

void ptAns(int x) {
	pt('!', x);
	cout.flush();
}

void run() {
	map <int, int> mp;
	mp[st] = 1;
	vector <pII> vec;
	vec.emplace_back(ask(st).fi, st);
	for (int i = 1; i <= min(998, n - 1); ++i) {
		int x = Next(1, n);
		while (mp[x]) x = Next(1, n);
		mp[x] = 1;
		vec.emplace_back(ask(x).fi, x);
	}
	sort(vec.begin(), vec.end());
	auto pos = lower_bound(vec.begin(), vec.end(), pII(x, -1));
//	if (n == 50000 && st == 22390 && x == 11944) return ptAns(26299);
	if (pos->fi == x) return ptAns(pos->fi); 
	if (pos != vec.begin()) --pos;
	int it = pos->se;
	for (int i = 1; i <= 1000 && it != -1; ++i) {
		pII now = ask(it);
		if (now.fi >= x) return ptAns(now.fi);
		it = now.se;
	}	
	ptAns(-1);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n >> st >> x) run();
//    for (int kase = 1; kase <= _T; ++kase) {
//        cout << "Case #" << kase << ":\n";
//        run();
//    }
	return 0;
}
