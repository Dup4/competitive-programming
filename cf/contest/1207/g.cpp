#include <bits/stdc++.h>
using namespace std;
#define debug(...) { printf("#  "); printf(__VA_ARGS__); puts(""); }
#define ll long long
const int N = 4e5 + 10;
const int mod = 1e9 + 7;
template <class T1, class T2> inline void chadd(T1 &x, T2 y) { x += y; if (x >= mod) x -= mod; } 
template <class T1, class T2> inline void chmax(T1 &x, T2 y) { if (x < y) x = y; }
template <class T1, class T2> inline void chmin(T1 &x, T2 y) { if (x > y) x = y; }
inline int rd() { int x; cin >> x; return x; }
template <class T > inline void out(T s) { cout << s << "\n"; }
inline ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
inline ll qpow(ll base, ll n) { ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
int n, m, id[N], stop[N], cnt; string s[N], t;
struct KMP {
	int Next[N];
	//下标从0开始
	void get_Next(string s) {
		int len = s.size();
		int i, j;
		j = Next[0] = -1;
		i = 0;
		while (i < len) {
			while (-1 != j && s[i] != s[j]) j = Next[j];
			Next[++i] = ++j;
		}
	}
	//s是主串 t是模式串
	int work(string s, int lens, string t) {
		int lent = t.size();
		int i, j, ans = 0;
		get_Next(t);
		i = j = 0;
		while (i < lens) {
			while (-1 != j && s[i] != t[j]) j = Next[j];
			++i, ++j;
			if (j >= lent) {
				++ans;
				j = Next[j];
			}
		}
		//返回出现次数
		return ans;
	}
}kmp;
void run() {
	cnt = 0; int op, x; char ch[10];
	for (int i = 1; i <= n; ++i) {
		cin >> op;
		if (op == 1) {
			cin >> ch;
			++cnt;
			id[i] = cnt;
			s[cnt] = "";
			s[cnt] += ch[0];
			stop[i] = 1;
		} else {
			cin >> x >> ch;
			id[i] = id[x];
			s[id[i]] += ch[0];
			stop[i] = s[id[i]].size(); 
		}
	}
	cin >> m;
	for (int i = 1, x; i <= m; ++i) {
		cin >> x >> t;
		cout << kmp.work(s[id[x]], stop[x], t) << "\n";
	}
	
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n) run();
	return 0;
}
