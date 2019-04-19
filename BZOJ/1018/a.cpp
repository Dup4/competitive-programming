#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 500010
#define pii pair <int, int>
#define fi first
#define se second
pii e[N];
int n, m, q; 
int used[N], tmp[N], res[N]; 
map <int, int> mp; int mp_cnt;
int getid(int u, int v) {
	if (u > v) {
		swap(u, v);
	}
	ll t = 1ll * u * 2 * n + v;
	if (mp.find(t) == mp.end()) {
		mp[t] = ++mp_cnt;
	}
	return mp[t]; 
}
struct qnode {
	int op, id, x;
	qnode () {}
	qnode (int op, int id, int x) : op(op), id(id), x(x) {}
}qrr[N]; 

int pre[N], Top;
pii stk[N];
int find(int x) {
	if (pre[x] == 0) {
		return x; 
	}
	int y = find(pre[x]);
	if (pre[x] != y) {
		stk[++Top] = pii(x, pre[x]); 
	} 
	return pre[x] = y; 
}
void join(int x, int y) {
	int fx = find(x), fy = find(y);
	if (fx != fy) {
		stk[++Top] = pii(fx, pre[fx]);
		pre[fx] = fy;
	}
}
void rollback(int TOP) {
	while (Top != TOP) {
		int x = stk[Top].fi, y = stk[Top].se;
		pre[x] = y;
		--Top;
	}
}

void CDQ(int l, int r) {
	int TOP = Top;
	if (l > r) {
		return;
	}
	if (l == r) {
		int op = qrr[l].op;
		int id = qrr[l].id;
		int x = qrr[l].x;
		if (op == 0) {
			if (used[x] == 1) {
				used[x] = 0;
			}
		} else if (op == 1) {
			if (used[x] == 0) {
				used[x] = 1;
			}
		} else {
			res[id] = find(e[x].fi) == find(e[x].se);
			rollback(TOP);  
		}
	}
	int mid = (l + r) >> 1;
	CDQ(l, mid);  
	rollback(TOP);
	
	for (int i = l; i <= mid; ++i) if (qrr[i].op != 2) { 
		int x = qrr[i].x;
		int op = qrr[i].op;
		switch(op) {
			case 0 :
				if (used[x] == 1) { 
					used[x] = 0;
				}
				break;
			case 1 :
				if (used[x] == 0) { 
					used[x] = 1;	
				}
				break;
			default : 
				assert(0);
		}
	}
	for (int i = l; i <= mid; ++i) if (qrr[i].op != 2) {
		int x = qrr[i].x;
		if (used[x]) {
			join(e[x].fi, e[x].se);
		}
	}
	CDQ(mid + 1, r);
	rollback(TOP);
}

void init() {
	Top = 0; mp_cnt = 0; m = 0; q = 0;
	mp.clear();
	memset(used, 0, sizeof used); 
    memset(pre, 0, sizeof pre);	
}
int main() {
	while (scanf("%d", &n) != EOF) {
		init();
		for (int i = 2; i <= n; ++i) {
			e[++m] = pii(i - 1, i);
			getid(i - 1, i); 
			e[++m] = pii(n + i - 1, n + i);
			getid(n + i - 1, n + i);
		} 
		for (int i = 1; i <= n; ++i) {
			e[++m] = pii(i, n + i);
			getid(i, n + i);
		}
		char op[10]; int u, v, r1, c1, r2, c2;
		while (scanf("%s", op) != EOF) {
			if (op[0] == 'E') {
				break;
			}
			scanf("%d%d%d%d", &r1, &c1, &r2, &c2);
			u = (r1 - 1) * n + c1, v = (r2 - 1) * n + c2;
			++q;
			switch (op[0]) {
				case 'C' :
					qrr[q] = qnode(0, q, getid(u, v)); 
					break;
				case 'O' :
					qrr[q] = qnode(1, q, getid(u, v));
					break;
				case 'A' :
					qrr[q] = qnode(2, q, getid(u, v)); 
					break;
				default : 
					assert(0); 
			}
		}
		CDQ(1, q);
		for (int i = 1; i <= q; ++i) if (qrr[i].op == 2) {
			puts(res[i] ? "Y" : "N");
		}
	}
	return 0;
}

