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
inline ll qpow(ll base, ll n) { assert(n >= 0); ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
//head
constexpr int N = 1e5 + 10;
int n, a[N]; 
vector <int> vec;

pII cross(pII a, pII b) {
	return pII(max(a.fi, b.fi), min(a.se, b.se));
}

pII gao(int x) {
	pII it = pII(0, 1e9);
	for (int i = 2; i <= n; ++i) {
		if (vec[i - 1] == -1 && vec[i] != -1) {
			it = cross(it, pII(vec[i] - x, vec[i] + x));
		} 
		if (vec[i - 1] != -1 && vec[i] == -1) {
			it = cross(it, pII(vec[i - 1] - x, vec[i - 1] + x));
		}
	}
	return it;
}

void run() {
    vec.clear();
	vec.push_back(0);
	cin >> n;
	int Max = 0;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		if (i > 1 && a[i] != -1 && a[i - 1] != -1)
			Max = max(Max, abs(a[i] - a[i - 1]));
		if (a[i] == -1 && vec.back() == -1) continue;
		vec.push_back(a[i]);
	}	
	n = vec.size() - 1;
	int l = Max, r = 1e9, res = 2e9;
	while (r - l >= 0) {
		int mid = (l + r) >> 1;
		pII tmp = gao(mid);
		if (tmp.se >= tmp.fi) {
			res = mid;
			r = mid - 1;
		} else {
			l = mid + 1;
		}
	}
	pII tmp = gao(res); 
	pt(res, tmp.fi); 
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	int _T = rd();
	while (_T--) run();
	return 0;
}
