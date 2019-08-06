#include <bits/stdc++.h>
using namespace std;
#define N 1000010
#define ALP 26
char s[N]; 
char t[200][220];
int n;

struct ACAM {
	struct node {
		int nx[ALP], fail;
		int cnt, v; 
		bool vis; 
		node() {
			memset(nx, -1, sizeof nx);
			cnt = 0; vis = 0; v = 0;
		}
	}t[N];
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
	void insert(char *s) {
		int len = strlen(s); 
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
	int gao(char *s) {
		int len = strlen(s);
		int now = root;
		int res = 0;
		for (int i = 0; i < len; ++i) {
			now = t[now].nx[s[i] - 'a'];
			int tmp = now;
			while (tmp != root) {
			    if (t[tmp].cnt) {
					++t[tmp].v;
					res = max(res, t[tmp].v);
				}	
				tmp = t[tmp].fail;
			}
		}
		return res;
	}
	int query(char *s) {
		int len = strlen(s);
		int now = root;
		for (int i = 0; i < len; ++i) {
			now = t[now].nx[s[i] - 'a'];
		}
		int res = t[now].v;
		t[now].v = 0;
		return res;
	}
}ac;

int main() {
	while (scanf("%d", &n), n) {
		ac.init();
		for (int i = 1; i <= n; ++i) {
			scanf("%s", t[i]);
			ac.insert(t[i]);
		}
		ac.build(); 
		scanf("%s", s);
		int Max = ac.gao(s);
		printf("%d\n", Max);
		for (int i = 1; i <= n; ++i) {
			if (ac.query(t[i]) == Max) {
				printf("%s\n", t[i]);
			}
		}
	}
	return 0;
}
