#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#define fi first
#define se second
#define endl "\n" 
using namespace std;
using db = double;
using ll = long long;
using ull = unsigned long long; 
using pII = pair <int, int>;
using pLL = pair <ll, ll>;
constexpr int mod = 1e9 + 7;
template <class T1, class T2> inline void chadd(T1 &x, T2 y) { x += y; while (x >= mod) x -= mod; while (x < 0) x += mod; } 
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
inline void pt() { cout << endl; } 
template <class T, class... Ts> void pt(const T& arg, const Ts&... args) { cout << arg << ' '; pt(args...); }
template <template<typename...> class T, typename t, typename... A> 
void pt(const T <t> &arg, const A&... args) { for (auto &v : arg) cout << v << ' '; pt(args...); }
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
inline ll qpow(ll base, ll n) { ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
//head
constexpr int N = 1e5 + 10;
int n, q, a[N];
struct FHQ { 
	#define ls t[x].son[0]
	#define rs t[x].son[1]
	struct node {
		int son[2], key, rnd, sze; 
		ll sum, lazy; 
	}t[N];
	int tot, rt;
	inline void init() { tot = rt = 0; }
	inline void pushup(int x) { 
		t[x].sze = t[ls].sze + t[rs].sze + 1;
		t[x].sum = t[ls].sum + t[rs].sum + t[x].key;   
	}
	inline void pushdown(int x) {
		if (x && t[x].lazy) {
			ll &lazy = t[x].lazy;
			t[ls].lazy += lazy;
			t[ls].sum += lazy * t[ls].sze;
			t[rs].lazy += lazy;
			t[rs].sum += lazy * t[rs].sze;
		}
	}
	inline int random() {
		static int seed = 703;
		return seed = int(seed * 482147ll % 2147483647);
	}
	inline int newnode(int key) {
		++tot;
		t[tot].sze = 1;
		t[tot].key = key;
		t[tot].rnd = random(); 
		t[tot].rev = t[tot].son[0] = t[tot].son[1] = 0;
		return tot;
	}
	int build(int l, int r) {
		if (l > r) return 0;
		int mid = (l + r) >> 1, v = mid; 
		int x = newnode(v);
		ls = build(l, mid - 1);
		rs = build(mid + 1, r);
		pushup(x);
		return x;
	}
	int merge(int x, int y) {
		if (!x || !y) return x + y;
		if (t[x].rnd < t[y].rnd) {
			pushdown(x);
			t[x].son[1] = merge(t[x].son[1], y);
			pushup(x);
			return x;
		} else {
			pushdown(y);
			t[y].son[0] = merge(x, t[y].son[0]);
			pushup(y);
			return y;
		}
	}
	//根据sze分
	void split(int now, int k, int &x, int &y) {
		if (!now) x = y = 0;
		else {
			pushdown(now);
			//将所有排名小于等于k的保留在左边
			if (k <= t[t[now].son[0]].sze) {
				y = now;
				split(t[now].son[0], k, x, t[now].son[0]);
			//将排名大于k的保留在右边
			} else {
				x = now;
				split(t[now].son[1], k - t[t[now].son[0]].sze - 1, t[now].son[1], y);
			}
			pushup(now);
		}
	}
	void insert(ll key) {
		
	}
	//先将整棵树以l - 1，分成两棵树a, b
	//那么b树中的排名为[l, n]，再将b树按r - l + 1，分成两棵树c, d
	//那么c树中的排名为[l, r]，将c树打上标记，再合并回去即可
	inline void rev(int l, int r) {
		int a, b, c;
		split(rt, l - 1, a, b);
		split(b, r - l + 1, b, c);
		t[b].rev ^= 1;
		rt = merge(a, merge(b, c));
	}
	inline void print(int x) {
		if (!x) return;
		pushdown(x); 
		print(ls);
		printf("%d ", t[x].key);
		print(rs);
	}
}fhq;
void run() {
	for (int i = 1; i <= n; ++i) a[i] = rd();
		
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n) run();
	return 0;
}
