#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 3e5 + 10;
const int ALP = 26;
int n;
char s[N];
ll ans[N], c1[N], c2[N]; 

struct SAM {
	//空间开两倍，节点个数是两倍字符串长度
	//maxlen 表示节点i表示的最大后缀长度, nx[j]表示节点i加一个字符j所表示的字符串对应的节点
	//minlen 表示节点i表示的最小后缀长度，其等于t[t[i].fa].maxlen + 1 
	//fa 表示节点i的后缀链接 cnt 表示节点i的enspos集合大小 
	//c[]表示拓扑排序辅助数组,　rk[]表示拓扑序，rk[i],i小的节点所表示的后缀长度也小
	//pos表示那个结点在字符串的endpos的最小值，即firstpos
	struct node {
		int maxlen, fa, nx[ALP], st, ed;
		node() { maxlen = fa = ed = 0; st = 1e9; memset(nx, 0, sizeof nx); }
	}t[N << 1];
	int tot, lst, c[N << 1], rk[N << 1]; 
    ll cnt; 	
	inline int newnode() { 
		++tot;
		t[tot] = node();
		return tot;
	}
	inline void init() {
		tot = 0; cnt = 0;
		lst = newnode();
	}
	inline void extend(int id, int pos) { 
		int cur = newnode(), p; 
		t[cur].st = t[cur].ed = pos; 
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
		cnt += t[lst].maxlen - t[t[lst].fa].maxlen;
	}
	//字符串从0开始 
	void build() { 
		memset(c, 0, sizeof c); 
		for (int i = 1; i <= tot; ++i) c[t[i].maxlen]++;
		for (int i = 1; i <= tot; ++i) c[i] += c[i - 1];
		for (int i = 1; i <= tot; ++i) rk[c[t[i].maxlen]--] = i;
		memset(c1, 0, sizeof c1);
		memset(c2, 0, sizeof c2);
		for (int i = tot; i >= 1; --i) {
			int u = rk[i], fa = t[u].fa;
			if (fa) {
				t[fa].st = min(t[fa].st, t[u].st);
				t[fa].ed = max(t[fa].ed, t[u].ed);
			}		
			int l = t[u].st, r = t[u].ed;
			int len = min(r - l, t[u].maxlen);
			if (len <= t[fa].maxlen) continue; 
			c1[l + 1] += len - t[fa].maxlen;
			c2[r - t[fa].maxlen + 1] += 1;
			c2[r - len + 1] -= 1; 
		}
	}
}sam;

int main() {
	scanf("%d%s", &n, s + 1);
	memset(ans, 0, sizeof ans);
	memset(c1, 0, sizeof c1);
	memset(c2, 0, sizeof c2);
	sam.init();
	for (int i = 1; i <= n; ++i) {
		sam.extend(s[i] - 'a', i);
		ans[i + 1] += sam.cnt;
	}
	for (int i = 1; i <= n; ++i) ans[i] += 1ll * i * (n - i + 1);
	sam.build();
	for (int i = 1; i <= n; ++i) c2[i] += c2[i - 1];
	for (int i = 1; i <= n; ++i) c1[i] += c1[i - 1] + c2[i], ans[i] -= c1[i];
	sam.init();
	for (int i = n; i >= 1; --i) {
		sam.extend(s[i] - 'a', i);
		ans[i - 1] += sam.cnt;
	}
	for (int i = 1; i <= n; ++i) printf("%lld%c", ans[i], " \n"[i == n]);
	return 0;
}
