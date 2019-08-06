#include <bits/stdc++.h>
using namespace std;
#define N 200010
#define M 2000010  
#define ALP 26
string t[200010];
char s[M];
int n;

struct ACAM { 
	struct node {
		int nx[ALP], fail;
		int cnt, num; 
		node() {
			memset(nx, -1, sizeof nx);
			cnt = 0; 
		    num = 0;
		}
	}t[N];
	vector <vector<int>> G; 
	int root, tot; 
	int que[N], ql, qr;
	//节点从1开始
	int newnode() {
		++tot;
		t[tot] = node();
		return tot;
	}
	void init() { 
		tot = 0;
		root = newnode();
	}
	void insert(string s) {
		int len = s.size(); 
		int now = root;
		for (int i = 0; i < len; ++i) {
			if (t[now].nx[s[i] - 'a'] == -1)
				t[now].nx[s[i] - 'a'] = newnode();
			now = t[now].nx[s[i] - 'a'];
		}
		//表示以该结点结尾的模式串数量
		++t[now].cnt;
	}
	void build() {
		ql = 1, qr = 0;
		t[root].fail = root;
		//将第二层出现过的字母扔进队列，并将fail指向根
		//对于没出现过的字母，直接将该字母的下一个节点指向根
		for (int i = 0; i < ALP; ++i) {
			if (t[root].nx[i] == -1) {
				t[root].nx[i] = root;
			} else {
				t[t[root].nx[i]].fail = root;
				que[++qr] = t[root].nx[i];
			}
		}
		while (ql <= qr) {
			int now = que[ql++];
			for (int i = 0; i < ALP; ++i) {
				//如果当前节点没有子节点i + 'a'
				//则让这个子节点指向当前节点fail指针对应的子节点
				if (t[now].nx[i] == -1) {
					t[now].nx[i] = t[t[now].fail].nx[i];
				}
				else {
					//如果当前节点有子节点i + 'a'
					//则让这个子节点的fail指针指向(((它父亲节点)的fail指针指向的那个节点)的对应的子节点)
					t[t[now].nx[i]].fail = t[t[now].fail].nx[i];
					que[++qr] = t[now].nx[i];
				}
			}
		}
	}
	void DFS(int u) {
		for (auto v : G[u]) {
			DFS(v);
			t[u].num += t[v].num;
		}
	}
	void gao(char *s) {
		int len = strlen(s);
		int now = root;
		for (int i = 0; i < len; ++i) {
			//查找以s[i]结尾的模式串数量
			now = t[now].nx[s[i] - 'a'];
			++t[now].num;
		}
		G.clear(); G.resize(tot + 10);
		for (int i = 2; i <= tot; ++i) {
			G[t[i].fail].push_back(i);
		}	
		DFS(1);
	}
	int query(string s) {
		int len = s.size();
		int now = root;
		for (int i = 0; i < len; ++i) {
			now = t[now].nx[s[i] - 'a'];
		}
		return t[now].num;
	}
}ac;

//给定n个模式串和1一个文本串
//求有多少个模式串在文本串中出现过
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0); 
	while (cin >> n) {
		ac.init();
		for (int i = 1; i <= n; ++i) {
			cin >> t[i];
			ac.insert(t[i]);
		}
		ac.build();
		cin >> s;
		ac.gao(s);
		for (int i = 1; i <= n; ++i) {
			cout << ac.query(t[i]) << "\n";
		}
	}
	return 0;
}
