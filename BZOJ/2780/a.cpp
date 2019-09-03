#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e5 + 10;
const int ALP = 26;
int n, q; 
string s[N], t;

struct SAM {
	//空间开两倍，节点个数是两倍字符串长度
	//maxlen 表示节点i表示的最大后缀长度, nx[j]表示节点i加一个字符j所表示的字符串对应的节点
	//minlen 表示节点i表示的最小后缀长度，其等于t[t[i].fa].maxlen + 1 
	//fa 表示节点i的后缀链接 cnt 表示节点i的enspos集合大小 
	//c[]表示拓扑排序辅助数组,　rk[]表示拓扑序，rk[i],i小的节点所表示的后缀长度也小
	struct node {
		int maxlen, cnt, fa, vis, nx[ALP];
		node() { maxlen = cnt = fa = vis = 0; memset(nx, 0, sizeof nx); }
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
			  	t[clone] = t[q]; t[clone].cnt = 0;
				t[clone].maxlen = t[p].maxlen + 1; 
				for (; p && t[p].nx[id] == q; p = t[p].fa) t[p].nx[id] = clone;
				t[cur].fa = t[q].fa = clone;
			}
		}
		lst = cur; 	
	}
	//字符串从0开始 
	void add(string s) { 
		for (int i = 0, len = s.size(); i < len; ++i) {
			extend(s[i] - 'a'); 
		}
	}
	void work() {
		for (int i = 1; i <= n; ++i) {
			int u = 1;
			for (int j = 0, len =s[i].size(); j < len; ++j) {
				u = t[u].nx[s[i][j] - 'a'];
				int tmp = u;
				while (tmp && t[tmp].vis != i) {
					t[tmp].vis = i;
					++t[tmp].cnt;
					tmp = t[tmp].fa;
				}
			}
		}
	}
}sam;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	while (cin >> n >> q) {
		sam.init();
		for (int i = 1; i <= n; ++i) {
			cin >> s[i];
			sam.lst = 1;
			sam.add(s[i]);
		}
		sam.work();
		for (int i = 1; i <= q; ++i) {
			cin >> t;
			int u = 1;
			for (int j = 0, len = t.size(); j < len; ++j) {
				u = sam.t[u].nx[t[j] - 'a'];
			}
			cout << sam.t[u].cnt << "\n";
		}
	}
	return 0;
}
