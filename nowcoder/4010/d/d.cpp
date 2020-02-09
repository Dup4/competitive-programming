#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 10;
const int ALP = 26; 
char s[N]; int n, vis[N], res; 

struct SAM {
	struct node {
		int maxlen, cnt, fa, nx[ALP];
		void init() { maxlen = cnt = fa = 0; memset(nx, 0, sizeof nx); }
	}t[N << 1];
	int tot, lst;
	inline int newnode() { 
		++tot;
		t[tot].init();
		return tot;
	}
	inline void init() {
		tot = 0;
		lst = newnode(); 
	}
	inline void extend(int id) { 
		int cur = newnode(), p; 
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
			  	t[clone] = t[q]; 
				t[clone].maxlen = t[p].maxlen + 1; 
				for (; p && t[p].nx[id] == q; p = t[p].fa) t[p].nx[id] = clone;
				t[cur].fa = t[q].fa = clone;
			}
		}
		lst = cur; 	
		++t[t[cur].fa].cnt; 
		if (t[cur].fa > 1 && t[t[cur].fa].cnt > 0) {
			vis[t[t[cur].fa].maxlen] = 1;
		}
		if (t[cur].fa == 1 && t[t[cur].fa].cnt > 1) {
			vis[0] = 1;
		}
	}
	void build(char *s) { 
		init();
		res = 0;
		for (int i = 1; i <= n; ++i) {
			extend(s[i] - 'a');
			while (vis[res]) ++res;
			printf("%d%c", res, " \n"[i == n]);
		}
	}
}sam;

int main() {
	int _T; scanf("%d", &_T);
	while (_T--) {
		scanf("%s", s + 1);
		n = strlen(s + 1);
		for (int i = 0; i <= n + 1; ++i) vis[i] = 0;
		sam.build(s);
	}
	return 0;
}
