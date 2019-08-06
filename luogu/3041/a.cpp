#include <bits/stdc++.h>
using namespace std;
#define N 1010
#define ALP 3
char s[N];
int n, k;
int f[N][N]; 

struct ACAM {
	struct node {
		int nx[ALP], fail;
		int cnt; 
		node() {
			memset(nx, -1, sizeof nx);
			cnt = 0;  
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
			if (t[now].nx[s[i] - 'A'] == -1)
				t[now].nx[s[i] - 'A'] = newnode();
			now = t[now].nx[s[i] - 'A'];
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
			t[now].cnt += t[t[now].fail].cnt;
		}
	}
	int gao(int n) {
		memset(f, -0x3f, sizeof f);
		f[0][1] = 0;
		for (int i = 0; i < n; ++i) {
			for (int j = 1; j <= tot; ++j) {
				for (int k = 0; k < 3; ++k) {
					f[i + 1][t[j].nx[k]] = max(f[i + 1][t[j].nx[k]], f[i][j] + t[t[j].nx[k]].cnt);
				}
			}	
		}
		int res = 0;
		for (int i = 1; i <= tot; ++i)
			res = max(res, f[n][i]);
		return res;
	}
}ac;

int main() {
	while (scanf("%d%d", &n, &k) != EOF) {
		ac.init();
		for (int i = 1; i <= n; ++i) {
			scanf("%s", s);
			ac.insert(s);
		}	
		ac.build();
		printf("%d\n", ac.gao(k));
	}
	return 0;
}
