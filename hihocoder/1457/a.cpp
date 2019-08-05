#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll p = 1e9 + 7;  
const int N = 2e6 + 10;
const int ALP = 11;
char s[N], t[N];

struct SAM {
	//空间开两倍
	int maxlen[N << 1], trans[N << 1][ALP], link[N << 1], sze, lst;
	int in[N << 1]; 
	int que[N << 1], ql, qr; 
	ll f[N << 1], g[N << 1]; 
	//minlen[i] = maxlen[link[i]] + 1
	SAM() { sze = 0; lst = ++sze; }
	inline void init() {
		for (int i = 0; i <= sze; ++i) 
			for (int j = 0; j < ALP; ++j)
				trans[i][j] = 0; 
		sze = 0; lst = ++sze;
	}
	inline void extend(int id) {
		//新建绿点
		int cur = ++sze, p;
		maxlen[cur] = maxlen[lst] + 1;
		for (p = lst; p && !trans[p][id]; p = link[p]) trans[p][id] = cur;
		if (!p) {
			link[cur] = 1;
		} else {
			int q = trans[p][id];
			if (maxlen[q] == maxlen[p] + 1) {
				link[cur] = q;
			} else {
				//蓝点
				int clone = ++sze;
				maxlen[clone] = maxlen[p] + 1;
				memcpy(trans[clone], trans[q], sizeof trans[q]);
				link[clone] = link[q];
				for (; p && trans[p][id] == q; p = link[p]) trans[p][id] = clone;
				link[cur] = link[q] = clone;  
			}
		}
		lst = cur; 	
	}
	//字符串从0开始
	void build(char *s) {
		init();
		for (int i = 0, len = strlen(s); i < len; ++i) {
			extend(s[i] - '0'); 
		}
	}
	ll solve() {
		ll res = 0;
		for (int i = 1; i <= sze; ++i) in[i] = 0;
		for (int i = 1; i <= sze; ++i) {
			f[i] = g[i] = 0;
			for (int j = 0; j < ALP - 1; ++j) {
				if (trans[i][j]) {
					++in[trans[i][j]];
				}
			}
		}
		ql = 1, qr = 0; 
		f[1] = 0, g[1] = 1;
		for (int i = 1; i <= sze; ++i)
			if (in[i] == 0)
				que[++qr] = i; 
		while (ql <= qr) {
			int u = que[ql++];
		 	res = (res + f[u]) % p;
		 	for (int i = 0; i < ALP - 1; ++i) {
				int v = trans[u][i];
				if (!v) continue;
				g[v] = (g[v] + g[u]) % p;
				f[v] = (f[v] + f[u] * 10 % p + 1ll * i * g[u] % p) % p;
				if (--in[v] == 0)
					que[++qr] = v;
			}	
		}
		return res;
	}
}sam;

int main() {
	int T; scanf("%d", &T);
	scanf("%s", s); T--;
	while (T--) {  
		scanf("%s", t);
		strcat(s, ":");
		strcat(s, t);
	}
	sam.build(s);
	printf("%lld\n", sam.solve());
	return 0;
}

