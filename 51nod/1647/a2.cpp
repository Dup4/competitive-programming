#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5, ALP = 26, M = 21;
int n, q;
char s[N]; 
vector <vector<int>> trie_pos;  
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
	int tot, c[N << 1], rk[N << 1], bz[N << 1][M]; 
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
		for (int i = 1; i <= tot; ++i) {
			int p = rk[i]; bz[p][0] = t[p].fa;
			for (int j = 1; j < M; ++j)
				bz[p][j] = bz[bz[p][j - 1]][j - 1];
		}
	}
	void query(int p, int len) {
		for (int i = M - 1; i >= 0; --i) {
			int nx = bz[p][i];
			if (t[nx].maxlen >= len) {
				p = nx;
			}
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
	void insert(char *s, vector<int> &vec) {
		int p = 1;
		for (int i = 1; s[i]; ++i) {
			int ch = s[i] - 'a';
			if (!t[p].nx[ch]) {
				int tmp = newnode();
				t[p].nx[ch] = tmp;
			}
			p = t[p].nx[ch];
			t[p].cnt = 1;
			vec[i] = p;
		}
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
	while (scanf("%d", &n) != EOF) {
		trie.init();
		trie_pos.clear(); trie_pos.resize(n + 1);
		for (int i = 1, len; i <= n; ++i) {
			scanf("%s", s + 1); 
			len = strlen(s + 1);
			trie_pos[i].resize(len + 1);
			trie.insert(s, trie_pos[i]);
		}
		sam.init(); trie.bfs(); sam.build();
		scanf("%d", &q);
		for (int i = 1, p, x, y; i <= q; ++i) {
			scanf("%d%d%d", &p, &x, &y);
			sam.query(trie.t[trie_pos[p][y]].sam_pos, y - x + 1); 
		}	
	}
	return 0;
}