#include <bits/stdc++.h>
using namespace std;
using pII = pair<int, int>;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
#define fi first
#define se second
const int N = 1e6 + 10;
int n, q, rt[N];  

struct SEG {
	struct node {
		int ls, rs;
		int fa, sze, id, del;
	    void init() {
			ls = rs = fa = id = del = 0; 
			sze = 1; 
		}	
	}t[N * 11];
	int tot;
	int newnode() {
		++tot;
		assert(tot < N * 11);
		t[tot].init();
		return tot;
	}	
	void init() {
		tot = 0;
		t[0].init();
	}
	void build(int &id, int l, int r) {
	    id = newnode();	
		if (l == r) {
			t[id].fa = l;
			t[id].id = l;
			return;
		}
		int mid = (l + r) >> 1;
		build(t[id].ls, l, mid);
		build(t[id].rs, mid + 1, r);  
	}
	//更改父亲
	void update(int &now, int pre, int l, int r, int pos, int fa) {  
		int tmp = newnode();
		if (l == r) {
			t[tmp].fa = fa; 
			t[tmp].sze = t[pre].sze;  
			t[tmp].id = t[pre].id;
			t[tmp].del = t[pre].del;
			now = tmp; 
			return;	
		}
		t[tmp].ls = t[pre].ls; 
		t[tmp].rs = t[pre].rs;
		int mid = (l + r) >> 1;
		if (pos <= mid) {
			update(t[tmp].ls, t[pre].ls, l, mid, pos, fa);
		} else {
			update(t[tmp].rs, t[pre].rs, mid + 1, r, pos, fa); 
		}
		now = tmp;
	}
	//更改子树大小
	void add(int &now, int pre, int l, int r, int pos, int sze) {
		int tmp = newnode(); 
		if (l == r) {
			t[tmp].fa = t[pre].fa;
			t[tmp].sze = t[pre].sze + sze; 
			t[tmp].id = t[pre].id; 
			t[tmp].del = t[pre].del;
			now = tmp;
			return;
		}
		t[tmp].ls = t[pre].ls;
		t[tmp].rs = t[pre].rs;
		int mid = (l + r) >> 1;
		if (pos <= mid) {
			add(t[tmp].ls, t[pre].ls, l, mid, pos, sze);
		} else {
			add(t[tmp].rs, t[pre].rs, mid + 1, r, pos, sze);
		}
		now = tmp;
	}
	pII query(int now, int l, int r, int pos) { 
		if (l == r) {
			return pII(t[now].fa, t[now].sze);
		}
		int mid = (l + r) >> 1;
		if (pos <= mid) {
			return query(t[now].ls, l, mid, pos);
		} else {
			return query(t[now].rs, mid + 1, r, pos);
		}
	} 
	void modifyId(int &now, int pre, int l, int r, int pos, int newId) { 
		int tmp = newnode();
		if (l == r) {
			t[tmp].fa = t[pre].fa;
			t[tmp].sze = t[pre].sze;
			t[tmp].id = newId;
			t[tmp].del = t[pre].del; 
			now = tmp;
			return;
		}
		t[tmp].ls = t[pre].ls;
		t[tmp].rs = t[pre].rs;
		int mid = (l + r) >> 1;
		if (pos <= mid) {
			modifyId(t[tmp].ls, t[pre].ls, l, mid, pos, newId);
		} else {
			modifyId(t[tmp].rs, t[pre].rs, mid + 1, r, pos, newId); 
		}
		now = tmp;
	}
	void modifyDel(int &now, int pre, int l, int r, int pos, int newDel) {
		int tmp = newnode();
		if (l == r) {
			t[tmp].fa = t[pre].fa;
			t[tmp].sze = t[pre].sze;
			t[tmp].id = t[pre].id;
			t[tmp].del = newDel;
			now = tmp;
			return;
		}
		t[tmp].ls = t[pre].ls;
		t[tmp].rs = t[pre].rs;
		int mid = (l + r) >> 1;
		if (pos <= mid) {
			modifyDel(t[tmp].ls, t[pre].ls, l, mid, pos, newDel);
		} else {
			modifyDel(t[tmp].rs, t[pre].rs, mid + 1, r, pos, newDel);
		}
		now = tmp;
	}
	int queryId(int now, int l, int r, int pos) {
		//dbg(now, l, r, pos, t[now].id);
		if (l == r) return t[now].id;
		int mid = (l + r) >> 1;
		if (pos <= mid) {
			return queryId(t[now].ls, l, mid, pos);
		} else {
			return queryId(t[now].rs, mid + 1, r, pos);
		}
	}
	int queryDel(int now, int l, int r, int pos) {
		if (l == r) return t[now].del;
		int mid = (l + r) >> 1;
		if (pos <= mid) {
			return queryDel(t[now].ls, l, mid, pos);
		} else {
			return queryDel(t[now].rs, mid + 1, r, pos);  
		}
	}
}seg; 

pII find(int k, int x) {
	pII pre = seg.query(rt[k], 1, n, x); 
	if (pre.fi == x) {
		return pre;  
	} else {
		return find(k, pre.fi); 
	}
}
void join(int k, int x, int y) {
	pII fx = find(k, x), fy = find(k, y);
	if (fx.fi != fy.fi) {  
		//启发式合并
		if (fx.se > fy.se) { 
			swap(fx, fy);
		}
		seg.update(rt[k], rt[k], 1, n, fx.fi, fy.fi);
		seg.add(rt[k], rt[k], 1, n, fy.fi, fx.se);
	}
}
bool same(int k, int x, int y) {
	if (x == y) return 1;
	pII fx = find(k, x), fy = find(k, y);
	return fx.fi == fy.fi;
}

int id(int k, int u) {
	return seg.queryId(rt[k], 1, n, u);
}

int del(int k, int u) {
	return seg.queryDel(rt[k], 1, n, u);
}

int main() {
	while (scanf("%d%d", &n, &q) != EOF) {
		seg.init();
		for (int i = 0; i <= n; ++i) {
			rt[i] = 0;
		}
		seg.build(rt[0], 1, n);
		int op, k, a, b;
		for (int i = 1; i <= q; ++i) {
			scanf("%d%d%d", &op, &k, &a);
			rt[i] = rt[k];
			if (op == 1 || op == 3 || op == 4) 
				scanf("%d", &b);
			if (op == 1) {
				if (del(i, a) + del(i, b) == 0) { 
					join(i, id(i, a), id(i, b)); 
				}
			} else if (op == 2) {
				if (del(i, a) == 0) {
					pII fa = find(i, id(i, a)); 
					seg.add(rt[i], rt[i], 1, n, fa.fi, -1); 
				}
				seg.modifyDel(rt[i], rt[i], 1, n, a, 1);
			} else if (op == 3) {
				if (del(i, a) + del(i, b) == 0) {
					pII fa = find(i, id(i, a));
					seg.add(rt[i], rt[i], 1, n, fa.fi, -1);
					int newId = id(i, b);
					seg.modifyId(rt[i], rt[i], 1, n, a, newId); 
					fa = find(i, newId);
					seg.add(rt[i], rt[i], 1, n, fa.fi, 1);
				}
			} else if (op == 4) {
				if (del(i, a) + del(i, b) == 0) {
					puts(same(i, id(i, a), id(i, b)) ? "Yes" : "No");
				} else {
					puts("No");
				}
			} else if (op == 5) {
				if (del(i, a) == 0) {
					pII fa = find(i, id(i, a));
					printf("%d\n", fa.se);
				} else {
					puts("0"); 
				}
			}
			
		}
	}
	return 0;
}
