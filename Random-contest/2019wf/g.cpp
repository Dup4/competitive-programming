#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e6 + 10;
const int ALP = 26;
int n, q, trie_pos[N]; char s[N];
struct SAM {
	//空间开两倍，节点个数是两倍字符串长度
	//maxlen 表示节点i表示的最大后缀长度, nx[j]表示节点i加一个字符j所表示的字符串对应的节点
	//minlen 表示节点i表示的最小后缀长度，其等于t[t[i].fa].maxlen + 1 
	//fa 表示节点i的后缀链接 cnt 表示节点i的enspos集合大小 
	//c[]表示拓扑排序辅助数组,　rk[]表示拓扑序，rk[i],i小的节点所表示的后缀长度也小
	struct node {
		int maxlen, cnt, fa, nx[ALP];
		void init() { maxlen = cnt = fa = 0; memset(nx, 0, sizeof nx); } 
	}t[N << 1];
	int tot, c[N << 1], rk[N << 1];  
	inline int newnode() { 
		++tot;
		t[tot].init();
		return tot;
	}
	inline void init() {
		tot = 0;
		newnode();
	}
	inline int extend(int id, int lst, int cnt) { 
		int cur = newnode(), p; 
		t[cur].cnt = cnt;
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
		return cur;
	}
	//字符串从0开始 
	void build() {  
		memset(c, 0, sizeof c);  
		for (int i = 1; i <= tot; ++i) c[t[i].maxlen]++;
		for (int i = 1; i <= tot; ++i) c[i] += c[i - 1];
		for (int i = 1; i <= tot; ++i) rk[c[t[i].maxlen]--] = i;
		for (int i = tot; i; --i) t[t[rk[i]].fa].cnt += t[rk[i]].cnt;
	}
	void query(char *s) {
		int p = 1;
		for (int i = 1; s[i]; ++i) {
			int ch = s[i] - 'A';
			if (!t[p].nx[ch]) {
				puts("0"); 
				return;
			}
			p = t[p].nx[ch];
		}	
		printf("%d\n", t[p].cnt);
	}
}sam;

struct Trie {
	struct node {
		int nx[ALP], cnt, sam_pos;
	    void init() { memset(nx, 0, sizeof nx);  cnt = 0; sam_pos = 0; }	
	}t[N];
	int rt, tot;
	int newnode() {
		++tot;
		t[tot].init();
		return tot;
	}
	void init() { tot = 0; rt = newnode(); }
	int add(int p, int ch) {
		if (!t[p].nx[ch]) {
			t[p].nx[ch] = newnode();
		}
		int now = t[p].nx[ch];
		++t[now].cnt;
		return now;
	}
	void bfs() {
		queue <int> q;
		q.push(1);
		t[1].sam_pos = 1;
		while (!q.empty()) {
			int u = q.front(); q.pop();
			for (int i = 0; i < ALP; ++i) {
				if (!t[u].nx[i]) continue;
				int now = t[u].nx[i];
				t[now].sam_pos = sam.extend(i, t[u].sam_pos, t[now].cnt);
				q.push(now); 
			}
		}
	}
}trie;

int main() {
	while (scanf("%d%d", &n, &q) != EOF) {
		trie_pos[0] = 1; trie.init();		
		for (int i = 1, p; i <= n; ++i) {
			scanf("%s%d", s, &p);
			trie_pos[i] = trie.add(trie_pos[p], s[0] - 'A');	
		}
		sam.init(); trie.bfs(); sam.build();
		for (int i = 1; i <= q; ++i) {
			scanf("%s", s + 1);
			int len = strlen(s + 1);			
			reverse(s + 1, s + 1 + len);
			sam.query(s);
		}
	}
	return 0;
}
