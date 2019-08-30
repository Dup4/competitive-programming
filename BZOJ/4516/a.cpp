#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e5 + 10;
const int ALP = 26;
int n, a[N]; 
ll res = 0;

struct SAM {
	//空间开两倍，节点个数是两倍字符串长度
	//maxlen 表示节点i表示的最大后缀长度, nx[j]表示节点i加一个字符j所表示的字符串对应的节点
	//minlen 表示节点i表示的最小后缀长度，其等于t[t[i].fa].maxlen + 1 
	//fa 表示节点i的后缀链接 cnt 表示节点i的enspos集合大小 
	//c[]表示拓扑排序辅助数组,　rk[]表示拓扑序，rk[i],i小的节点所表示的后缀长度也小
	struct node {
		int maxlen, cnt, fa;
		map <int, int> nx; 
		node() { maxlen = cnt = fa = 0; nx.clear(); }
	}t[N << 1];
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
	inline void extend(int id) { 
		int cur = newnode(), p; 
		t[cur].cnt = 1;
		t[cur].maxlen = t[lst].maxlen + 1; 
		for (p = lst; p && !t[p].nx.count(id); p = t[p].fa) t[p].nx[id] = cur;
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
				for (; p && t[p].nx.count(id) && t[p].nx[id] == q; p = t[p].fa) t[p].nx[id] = clone;
				t[cur].fa = t[q].fa = clone;
			//	res += t[clone].maxlen - t[t[clone].fa].maxlen;
			}
		}
		lst = cur; 	
		res += t[cur].maxlen - t[t[cur].fa].maxlen;
	}
}sam;

int main() {
	scanf("%d", &n); 
	sam.init();
	res = 0; 
	for (int i = 1; i <= n; ++i) {
		scanf("%1d", a + i); 
		sam.extend(a[i]);
	//	printf("%lld\n", res); 
	}
	printf("%lld\n", res); 
	return 0;
}
