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
template <class T1, class T2> inline void chadd(T1 &x, T2 y) { x += y; while (x >= mod) x -= mod; while (x < 0) x += mod; } 
template <class T1, class T2> inline void chmax(T1 &x, T2 y) { if (x < y) x = y; }
template <class T1, class T2> inline void chmin(T1 &x, T2 y) { if (x > y) x = y; }
inline int rd() { int x; cin >> x; return x; }
template <class T> inline void rd(T &x) { cin >> x; }
template <class T> inline void rd(vector <T> &vec) { for (auto &it : vec) cin >> it; }
template <class T> inline void out(T s) { cout << s << "\n"; }
template <class T> inline void out(vector <T> &vec) { for (auto &it : vec) cout << it << " "; cout << endl; } 
inline ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
inline ll qpow(ll base, ll n) { ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
constexpr int N = 5e3 + 10;
const int ALP = 26;

struct SAM {
	//空间开两倍，节点个数是两倍字符串长度
	//maxlen 表示节点i表示的最大后缀长度, nx[j]表示节点i加一个字符j所表示的字符串对应的节点
	//minlen 表示节点i表示的最小后缀长度，其等于t[t[i].fa].maxlen + 1 
	//fa 表示节点i的后缀链接 cnt 表示节点i的enspos集合大小 
	//c[]表示拓扑排序辅助数组,　rk[]表示拓扑序，rk[i],i小的节点所表示的后缀长度也小
	//pos表示那个结点在字符串的endpos的最小值，即firstpos
	struct node {
		int maxlen, cnt, fa, nx[ALP], pos[2]; 
		node() { maxlen = cnt = fa = 0; memset(nx, 0, sizeof nx); pos[0] = 1e9, pos[1] = 0; } 
	}t[N << 1];
	int tot, lst, c[N << 1], rk[N << 1];  
	inline int newnode() { 
		++tot;
		t[tot] = node();
		return tot;
	}
	inline void init() {
		tot = 0;
		lst = newnode();
	}
	inline void extend(int id, int _pos) {  
		int cur = newnode(), p; 
		t[cur].cnt = 1;
		t[cur].pos[0] = t[cur].pos[1] = _pos; 
		t[cur].maxlen = t[lst].maxlen + 1; 
		for (p = lst; p && !t[p].nx[id]; p = t[p].fa) t[p].nx[id] = cur;
		if (!p) {
			t[cur].fa = 1;
		} else {
			int q = t[p].nx[id];
			if (t[q].maxlen == t[p].maxlen + 1) {
				t[cur].fa = q;
			} else {
				int clone = newnode();
			  	t[clone] = t[q]; t[clone].cnt = 0;
				t[clone].maxlen = t[p].maxlen + 1; 
				for (; p && t[p].nx[id] == q; p = t[p].fa) t[p].nx[id] = clone;
				t[cur].fa = t[q].fa = clone;
			}
		}
		lst = cur; 	
	}
	//字符串从0开始 
	void build(char *s) { 
		init();
		for (int i = 0; s[i]; ++i) {
			extend(s[i] - 'a', i);
		}
		memset(c, 0, sizeof c); 
		for (int i = 1; i <= tot; ++i) c[t[i].maxlen]++;
		for (int i = 1; i <= tot; ++i) c[i] += c[i - 1];
		for (int i = 1; i <= tot; ++i) rk[c[t[i].maxlen]--] = i;
		for (int i = tot; i; --i) {
			int now = rk[i], fa = t[now].fa;
			t[fa].cnt += t[now].cnt;
			chmin(t[fa].pos[0], t[now].pos[0]);
			chmax(t[fa].pos[1], t[now].pos[1]);
		}
	}
	void gao() {
		int res = 0;
		for (int i = 1; i <= tot; ++i) if (t[i].cnt > 1) { 
			int gap = t[i].pos[1] - t[i].pos[0]; 
			res = max(res, min(gap, t[i].maxlen));
		}
		cout << res << endl;
	}
}sam;
int n; char s[N];
void run() {
	cin >> (s + 1);
	sam.build(s + 1); 
	sam.gao();
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n) run();
	return 0;
}
