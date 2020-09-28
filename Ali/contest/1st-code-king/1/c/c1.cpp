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
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
int n, a[N]; 
ll f[N];

class Solution {
public:
    /**
     * @param heights: the heights of buildings.
     * @param k: the vision.
     * @param x: the energy to spend of the first action.
     * @param y: the energy to spend of the second action.
     * @return: the minimal energy to spend.
     */
    long long shuttleInBuildings(vector<int> &heights, int k, int x, int y) {
        // write your code here.
		n = SZ(heights);
		int que[N]; int head = 1, tail = 0;
		for (int i = 1; i <= n; ++i) a[i] = heights[i - 1], f[i] = INFLL;
		f[n] = 0;
		que[++tail] = n;
		for (int i = n - 1; i >= 1; --i) {
			f[i] = f[i + 1] + y;
			if (i < n - 1) chmin(f[i], f[i + 2] + y);
			while (head <= tail && que[head] - k > i) ++head;
			while (head <= tail && a[que[tail]] < a[i]) --tail;
			if (head <= tail) chmin(f[i], f[que[tail]] + x);
			que[++tail] = i;
		}
		return f[1];
    }
};

void run() {
	int n, k, x, y;
	rd(n, k, x, y);
	vector <int> vec(n);
	for (auto &it : vec) rd(it);
	pt((new Solution)->shuttleInBuildings(vec, k, x, y));
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	int _T = 1;
//	nextInt();
	while (_T--) run(); 
//	while (cin >> n) run();
//	run();
	return 0;
}
