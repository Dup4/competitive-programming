#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 2e6 + 10;
const int ALP = 26;
char s[N];

struct SAM {
	int maxlen[N], trans[N][ALP], link[N], sze, lst;
	SAM() { sze = 0; lst = ++sze; }
	inline void init() {
		for (int i = 0; i <= sze; ++i) 
			for (int j = 0; j < ALP; ++j)
				trans[i][j] = 0; 
		sze = 0; lst = ++sze;
	}
	inline void extend(int id) {
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
	void build(char *s) {
		init();
		for (int i = 0, len = strlen(s); i < len; ++i) {
			extend(s[i] - 'a');
		}
	}
	void solve() {
		ll res = 0;
		for (int i = 1; i <= sze; ++i) {
			res += maxlen[i] - maxlen[link[i]];
		}
		printf("%lld\n", res);
	}
}sam;

int main() {
	scanf("%s", s);
	sam.build(s); sam.solve();
	return 0;
}
