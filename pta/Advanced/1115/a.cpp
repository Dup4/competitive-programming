#include <bits/stdc++.h>
using namespace std;
const int N = 1e4 + 10;
int n, a[N], Max, ans[N];

struct BST {
	struct node {
		int v, son[2];
		node() { v = 0, son[0] = son[1] = 0; }
	}t[N];
	int rt, tot;
	void init() {
		rt = 0; 
		tot = 0;
	}
	int newnode() {
		++tot;
		t[tot] = node(); 
		return tot; 
	}
	void insert(int &rt, int v, int dep) {
		Max = max(Max, dep);
		if (rt == 0) {
			rt = newnode();
			++ans[dep];
			t[rt].v = v;
			return;
		}
		if (v <= t[rt].v) insert(t[rt].son[0], v, dep + 1);
		else insert(t[rt].son[1], v, dep + 1); 
	}
}bst;

int main() {
	while (scanf("%d", &n) != EOF) {
		Max = 0; 
		memset(ans, 0, sizeof ans);
		bst.init();
		for (int i = 1, x; i <= n; ++i) {
			scanf("%d", &x);
			bst.insert(bst.rt, x, 0);
		}	
		assert(Max >= 0);
		if (Max == 0) {
			printf("%d + %d = %d\n", ans[Max], 0, ans[Max]);
		} else {
			printf("%d + %d = %d\n", ans[Max], ans[Max - 1], ans[Max] + ans[Max - 1]);
		}
	}
	return 0;
}
