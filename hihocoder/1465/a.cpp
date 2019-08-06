#include <bits/stdc++.h>
using namespace std;

#define pii pair <int, int>
#define fi first
#define se second
typedef long long ll;
const int N = 2e6 + 10;
const int ALP = 26;
char s[N], t[N];
map <int, int> mp;

struct SAM {
	//空间开两倍
	int maxlen[N << 1], trans[N << 1][ALP], link[N << 1], sze, lst;
	int endpos[N << 1], minlen[N << 1];
	vector <vector<int>> G;
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
	void DFS(int u) {
		for (auto v : G[u]) {
			DFS(v);
			endpos[u] += endpos[v];
		}
	}
	void work() {
		G.clear(); G.resize(sze + 1);
		for (int i = 1; i <= sze; ++i) {
			G[link[i]].push_back(i);
		}
		DFS(1);
		for (int i = 1; i <= sze; ++i)
			minlen[i] = maxlen[link[i]];
	}
	void solve(char *t) {
		mp.clear();
		int u = 1, l = 0;
		int len = strlen(t + 1); 
		int n = len / 2;
		ll res = 0;
		for (int i = 1; i <= len; ++i) {
			int ch = t[i] - 'a';
			while (u != 1 && trans[u][ch] == 0) u = link[u], l = maxlen[u];
			if (trans[u][ch] != 0) {
				u = trans[u][ch];
				++l;
			} else {
				u = 1, l = 0;
			}
			if (l > n) {
				while (maxlen[link[u]] >= n)
					u = link[u];
			}
			if (l >= n && !mp[u]) {
				mp[u] = 1;
				res += endpos[u];
			}
		}
		printf("%lld\n", res);
	}
}sam;

int main() {
	scanf("%s", s);
	sam.build(s); sam.work();
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%s", t + 1);
		int len = strlen(t + 1);
		for (int i = len + 1; i <= 2 * len; ++i) {
			t[i] = t[i - len];
		}
		t[2 * len + 1] = 0;
		sam.solve(t);
	}
	return 0;
}
