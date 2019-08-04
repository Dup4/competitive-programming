#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e6 + 10;
const int ALP = 26;
char s[N];

struct SAM {
	//空间开两倍
	int maxlen[N << 1], trans[N << 1][ALP], link[N << 1], sze, lst;
	int in[N << 1], endpos[N << 1]; 
	vector <vector<int>> G;
	int que[N << 1], ql, qr;
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
				//蓝点
				int clone = ++sze;
				endpos[clone] = 0; 
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
			extend(s[i] - 'a');
		}
	}
	void solve(int n) {
		G.clear(); G.resize(sze + 1);
		for (int i = 1; i <= sze; ++i) in[i] = 0;
		for (int i = 1; i <= sze; ++i) {
			G[i].push_back(link[i]);
			++in[link[i]];
		}
		ql = 1, qr = 0;
		for (int i = 1; i <= sze; ++i)
			if (in[i] == 0)
				que[++qr] = i;
		while (ql <= qr) {
			int u = que[ql++]; 
			for (auto v : G[u]) {
				endpos[v] += endpos[u];
				if (--in[v] == 0)
					que[++qr] = v;
			}
		}
		ll res = 0;
		for (int i = 1; i <= sze; ++i)
			f[maxlen[i]] = max(f[maxlen[i]], endpos[i]);
		for (int i = n - 1; i >= 1; --i) {
			f[i] = max(f[i], f[i + 1]);
		}
		for (int i = 1; i <= n; ++i) {
			printf("%d\n", f[i]);
		}
	}
}sam;

int main() {
	scanf("%s", s);
	sam.build(s); sam.solve(strlen(s));
	return 0;
}
