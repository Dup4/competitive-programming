#include <bits/stdc++.h>
using namespace std;
#define debug(...) { printf("#  "); printf(__VA_ARGS__); puts(""); }
#define fi first
#define se second
#define endl "\n" 
using ll = long long;
using pII = pair <int, int>;
using pLL = pair <ll, ll>;
using VI = vector <int>;
using VL = vector <ll>;
constexpr int mod = 1e9 + 7;
template <class T1, class T2> inline void chadd(T1 &x, T2 y) { x += y; if (x >= mod) x -= mod; else if (x < 0) x += mod; } 
template <class T1, class T2> inline void chmax(T1 &x, T2 y) { if (x < y) x = y; }
template <class T1, class T2> inline void chmin(T1 &x, T2 y) { if (x > y) x = y; }
inline int rd() { int x; cin >> x; return x; }
template <class T> inline void rd(T &x) { cin >> x; }
template <class T> inline void rd(vector <T> &vec) { for (auto &it : vec) cin >> it; }
template <class T> inline void out(T s) { cout << s << "\n"; }
template <class T> inline void out(vector <T> &vec) { for (auto &it : vec) cout << it << " "; cout << endl; } 
inline ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
inline ll qpow(ll base, ll n) { ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
constexpr int N = 1e5 + 10;
constexpr int INF = 0x3f3f3f3f;
int n, a[N], l[N], r[N];
struct Cartesian_Tree {
	struct node {
		int id, val, fa;
		int son[2];
		node() {}
		node (int id, int val, int fa) : id(id), val(val), fa(fa) {
			son[0] = son[1] = 0;
		}
		//定义排序规则
		bool operator < (const node &other) const {
			//小根堆<
			//大根堆>
			return val > other.val;
		}
	}t[N];
	int root;
	//初始化笛卡尔树，以0作为根，防止下面算法中A循环异常
	void init() {
		//小根堆设为-INF
		//大根堆设为INF
		t[0] = node(0, INF, 0);
	}
	//这里建的是小根堆
	void build(int n, int *a) {
		for (int i = 1; i <= n; ++i) {
			t[i] = node(i, a[i], 0);
		}
		for (int i = 1; i <= n; ++i) {
			int k = i - 1;
			//A循环
			//一直找到比i位置小的位置k
			while (t[i] < t[k]) {
				k = t[k].fa;
			}

			//将父节点的右子树放到自己的左子树上，因为不能改变他们映射后的序列位置，因此是将右子树放到左子树
			t[i].son[0] = t[k].son[1];

			//父节点的右子树重新指向
			t[k].son[1] = i;

			//设置i的父节点
			t[i].fa = k;

			//设置原本为右子树，现改为当前节点的左子树的父亲
			t[t[i].son[0]].fa = i;
		}
		//笛卡尔树的根节点设置为根节点的右子树节点（即我们插入的1～n范围里的最值）
		root = t[0].son[1]; 
	}
	int DFS(int u) {
		if (!u) return 0;
		l[u] = r[u] = 0;
		int ls = t[u].son[0], rs = t[u].son[1];
		if (ls) l[u] = DFS(ls);
		if (rs) r[u] = DFS(rs);
		return l[u] + r[u] + 1;
	}
}CT;
void run() {
	for (int i = 1; i <= n; ++i) cin >> a[i];
	CT.init(); CT.build(n, a); CT.DFS(CT.root);  
	ll res = 0;
	for (int i = 1; i <= n; ++i) {
		res += 1ll * a[i] * l[i] * (r[i] + 1);
	}	
	cout << res << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n) run();
	return 0;
}
