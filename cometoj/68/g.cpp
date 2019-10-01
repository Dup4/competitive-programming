#include <bits/stdc++.h>
using namespace std;
#define debug(...) { printf("#  "); printf(__VA_ARGS__); puts(""); }
#define fi first
#define se second
#define endl "\n" 
using ll = long long;
using ull = unsigned long long; 
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
template <class T> inline void pt(T s) { cout << s << "\n"; }
template <class T> inline void pt(vector <T> &vec) { for (auto &it : vec) cout << it << " "; cout << endl; } 
inline ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
inline ll qpow(ll base, ll n) { ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
constexpr int N = 2e5 + 10, ALP = 26, INF = 0x3f3f3f3f;
int n, q;
char s[N], t[N];
struct SAM {
	struct node {
		int maxlen, cnt, fa, pos, nx[ALP];
		node() { maxlen = cnt = fa = pos = 0; memset(nx, 0, sizeof nx); }
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
		t[cur].cnt = 1; t[cur].pos = _pos;
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
			int p = rk[i], fa = t[p].fa;
			t[fa].pos = min(t[fa].pos, t[p].pos);
		}
	}
	void gao(char *s) {
		int res = INF; 
		int len = strlen(s);
		for (int i = 0, now = 1; s[i]; ++i) {
			for (int j = s[i] + 1; j <= 'z'; ++j) {
				if (t[now].nx[j - 'a']) {
					int nx = t[now].nx[j - 'a']; 
				//	cout << i << " " << j << " " << s[i] << " " << t[nx].pos << endl;
					if (n - t[nx].pos >= len - i) {
						res = min(res, t[nx].pos - i);
					}
				}
			}
			if (t[now].nx[s[i] - 'a']) {
				now = t[now].nx[s[i] - 'a'];
			} else break;
		}
		if (res == INF) res = -1;
		pt(res);
	}
}sam;

void run() {
	cin >> s; n = strlen(s); 
	sam.build(s);
	for (int i = 1; i <= q; ++i) {
		cin >> t;
		sam.gao(t);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20); 
	while (cin >> q) run();
	return 0;
}
