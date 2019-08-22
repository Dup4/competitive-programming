#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 2e5 + 10;
const int ALP = 26;
char s[N], t[N];

struct SAM {
	//空间开两倍
	int maxlen[N << 1], trans[N << 1][ALP], link[N << 1], sze, lst; 
	int endpos[N << 1], c[N << 1], rk[N << 1], f[N << 1], g[N << 1]; 
	SAM() { sze = 0; lst = ++sze; }
	inline void init() {
		for (int i = 0; i <= sze; ++i) 
			for (int j = 0; j < ALP; ++j)
				trans[i][j] = 0; 
		sze = 0; lst = ++sze;
	}
	inline void extend(int id) {
		int cur = ++sze, p;
		endpos[cur] = 1;
		maxlen[cur] = maxlen[lst] + 1;
		for (p = lst; p && !trans[p][id]; p = link[p]) trans[p][id] = cur;
		if (!p) {
			link[cur] = 1;
		} else {
			int q = trans[p][id];
			if (maxlen[q] == maxlen[p] + 1) {
				link[cur] = q;
			} else {
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
		memset(endpos, 0, sizeof endpos);
		for (int i = 0; s[i]; ++i) {
			extend(s[i] - 'a');
		}
		memset(c, 0, sizeof c);
		for (int i = 1; i <= sze; ++i) ++c[maxlen[i]];
		for (int i = 1; i <= sze; ++i) c[i] += c[i - 1];
		for (int i = 1; i <= sze; ++i) rk[c[maxlen[i]]--] = i; 
		for (int i = sze; i >= 1; --i) endpos[link[rk[i]]] += endpos[rk[i]]; 
	} 
	void gao(char *s) {
		ll res = 0;
		memset(f, 0, sizeof f);
		memset(g, 0, sizeof g);
		for (int i = 0, p = 1, len = 0; s[i]; ++i) {
			int c = s[i] - 'a';
			while(p && !trans[p][c]) {
				p = link[p];
				len = maxlen[p];
			}
			if (p) {
				++len; p = trans[p][c];
			} else {
				len = 0; p = 1;
			}
			res += 1ll * endpos[p] * (len - maxlen[link[p]]);
		   	++g[p];	
		}
		for (int i = sze; i >= 1; --i) f[link[rk[i]]] += f[rk[i]] + g[rk[i]];
		for (int i = 1; i <= sze; ++i) res += 1ll * endpos[i] * f[i] * (maxlen[i] - maxlen[link[i]]);
		printf("%lld\n", res);
	}
}sam;

int main() {
	scanf("%s%s", s, t);
	sam.build(s); 
	sam.gao(t);
	return 0;
}
