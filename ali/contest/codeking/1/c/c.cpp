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

struct BIT {
	int n;
	ll a[N];
	void init() { n = 0; memset(a, 0x3f, sizeof a); }
	void update(int x, ll v) {
		for (; x > 0; x -= x & -x)
			chmin(a[x], v);
	}
	ll query(int x) {
		ll res = INFLL;
		for (; x <= n; x += x & -x) {
			chmin(res, a[x]);
		}
		return res;
	}
}bit;

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
		bit.init();
		f[0] = 0;
		int que[N]; int head = 1, tail = 0;
		for (int i = 1; i <= n; ++i) a[i] = heights[i - 1], f[i] = INFLL;
		for (int i = 1; i <= n; ++i) {
			if (i >= 1) chmin(f[i], f[i - 1] + y);
			if (i >= 2) chmin(f[i], f[i - 2] + y);
			for (int j = i - 1; j >= 1; --j) {
				if (a[j] <= a[i]) {
					chmin(f[i], f[j] + x);
				}
				if (a[j] >= a[i]) break;
			}
			if (i == 1) f[1] = 0;
//			while (head <= tail && que[head] + k < i) ++head;
//			if (head <= tail) {
//				int l = head, r = tail, pos = l;
//				while (l <= r) {
//					int mid = (l + r) >> 1;
//					if (a[que[mid]] >= a[i]) {
//						pos = mid;
//						l = mid + 1;
//					} else {
//						r = mid - 1;
//					}
//				}
//				//dbg(i, que[pos] + 1, f[4]);
//				//dbg(bit.query(que[pos] + 1));
//				chmin(f[i], bit.query(que[pos] + 1) + x);
//				if (a[que[pos]] <= a[i]) chmin(f[i], f[que[pos]] + x);
//				//f[que[pos]] + x);
//			}
//		//	dbg(i, f[i]);
//			while (head <= tail && a[que[tail]] <= a[i]) --tail;
//			que[++tail] = i;
//			if (i == 1) f[1] = 0;
//			bit.update(i, f[i]);
//			bit.n = i;
		}
		return f[n];
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
