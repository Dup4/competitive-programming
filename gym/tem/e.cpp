#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int n, rt;

struct node {
	//tp 2 3 4
	int tp, fa;
	// v 0 1 2
	// son 0 1 2 3
	int v[5], son[5];  
	node() {}
	node(int tp, int fa) : tp(tp), fa(fa) {
		memset(v, 0, sizeof v);
		memset(son, -1, sizeof son); 
	}
	bool isleaf() {
		for (int i = 0; i < tp - 1; ++i) 
			if (son[i] != -1)
				return 0;
		return 1; 
	}
}t[N]; int cnt;

void insert(int u, int x, int fa) {
	if (t[u].tp == 4) {
		if (rt == u) {
			int tmp = ++cnt;
			t[tmp] = node(2, -1);
			t[tmp].v[0] = t[u].v[1]; 
			int ls = ++cnt, rs = ++cnt;
			t[tmp].son[0] = ls, t[tmp].son[1] = rs;  
			t[ls] = node(2, tmp); t[rs] = node(2, tmp);
			t[ls].v[0] = t[u].v[0]; t[rs].v[0] = t[u].v[2];
			int son;
			son = t[u].son[0]; t[ls].son[0] = son; t[son].fa = ls;
			son = t[u].son[1]; t[ls].son[1] = son; t[son].fa = ls;
			son = t[u].son[2]; t[rs].son[0] = son; t[son].fa = rs;
			son = t[u].son[3]; t[rs].son[1] = son; t[son].fa = rs;
			rt = tmp;
			u = rt;
		} else {
			int ls = ++cnt, rs = ++cnt;
			t[ls] = node(2, fa); t[rs] = node(2, fa);
			t[ls].v[0] = t[u].v[0]; t[rs].v[0] = t[u].v[2];
			int son; 
			son = t[u].son[0]; t[ls].son[0] = son; t[son].fa = ls;
			son = t[u].son[1]; t[ls].son[1] = son; t[son].fa = ls;
			son = t[u].son[2]; t[rs].son[0] = son; t[son].fa = rs;
			son = t[u].son[3]; t[rs].son[1] = son; t[son].fa = rs; 
			int id = -1;
			for (int i = 0; i < t[fa].tp; ++i) { 
				if (t[fa].son[i] == u) {
					id = i;
					break;
				}
			}
			for (int i = t[fa].tp - 2; i >= id; --i) {
				t[fa].v[i + 1] = t[fa].v[i]; 
				t[fa].son[i + 1] = t[fa].son[i];
			}
			t[fa].v[id] = t[u].v[1]; 
			++t[fa].tp;
			t[fa].son[id] = ls; t[fa].son[id + 1] = rs;
			u = fa;
		}
	}
    if (t[u].isleaf()) {
		++t[u].tp;
		t[u].v[t[u].tp - 2] = x;
		sort(t[u].v, t[u].v + t[u].tp - 1);
		return;
	}
	for (int i = 0; i < t[u].tp - 1; ++i) {
		if (x < t[u].v[i]) {
			insert(t[u].son[i], x, u);
			return;
		}
	}
	insert(t[u].son[t[u].tp - 1], x, u);
}

void out(int u) { 
	if (u == -1) return;
//	cout << "bug\n" << u << endl;
	for (int i = 0; i < t[u].tp - 1; ++i)
		printf("%d%c", t[u].v[i], " \n"[i == t[u].tp - 2]); 
	for (int i = 0; i < t[u].tp; ++i)
		out(t[u].son[i]); 
}

int main() {
	int T; scanf("%d", &T);
	for (int kase = 1; kase <= T; ++kase) {
		printf("Case #%d:\n", kase);
		scanf("%d", &n);
		rt = -1; cnt = 0;
		for (int i = 1, x; i <= n; ++i) {
			scanf("%d", &x);
			if (i == 1) {
				rt = ++cnt;
				t[rt] = node(2, -1);
				t[rt].v[0] = x;
			} else {
				insert(rt, x, -1);
			}
		//	cout << rt << endl;
		}
		out(rt);
	}
	return 0;
}
