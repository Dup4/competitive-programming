#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e5 + 10;
const int ALP = 10;
int n, c, a[N], d[N];

struct SAM {
	//空间开两倍，节点个数是两倍字符串长度
	//maxlen 表示节点i表示的最大后缀长度, nx[j]表示节点i加一个字符j所表示的字符串对应的节点
	//minlen 表示节点i表示的最小后缀长度，其等于t[t[i].fa].maxlen + 1 
	//fa 表示节点i的后缀链接 cnt 表示节点i的enspos集合大小 
	//c[]表示拓扑排序辅助数组,　rk[]表示拓扑序，rk[i],i小的节点所表示的后缀长度也小
	struct node {
		int maxlen, fa, nx[ALP];
		node() { maxlen = fa = 0; }
	}t[N * 20];
	int tot, lst; 
	inline int newnode() { 
		++tot;
		t[tot] = node(); 
		return tot;
	}
	inline void init() {
		tot = 0;
		lst = newnode();
	}
	inline int extend(int id, int p) { 
		int cur = newnode(); 
		t[cur].maxlen = t[p].maxlen + 1; 
		for (; p && !t[p].nx[id]; p = t[p].fa) t[p].nx[id] = cur;
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
		return cur;
	}
	ll calc() {
		ll res = 0;
		for (int i = 1; i <= tot; ++i) res += t[i].maxlen - t[t[i].fa].maxlen;
		return res;
	}
}sam;
struct Edge { int v, nx; }e[N << 1]; int h[N]; 
inline void add(int u, int v) {
	e[++*h] = {v, h[u]};
	h[u] = *h;
    ++d[u];	
}
void DFS(int u, int fa, int p) {
	p = sam.extend(a[u], p);
	for (int i = h[u]; i; i = e[i].nx) {
		int v = e[i].v;
		if (v == fa) continue;
		DFS(v, u, p);
	}
}

int main() {
	while (scanf("%d%d", &n, &c) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		sam.init();
		memset(h, 0, sizeof h); 
		memset(d, 0, sizeof d);
		for (int i = 1, u, v; i < n; ++i) {
			scanf("%d%d", &u, &v);
			add(u, v);
			add(v, u);
		}
		for (int i = 1; i <= n; ++i) if (d[i] == 1) DFS(i, i, 1);
		printf("%lld\n", sam.calc());	
	}
	return 0;
}
