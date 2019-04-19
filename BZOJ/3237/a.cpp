#include <bits/stdc++.h>
using namespace std;

/*
	BZOJ 3237
	每次操作删除k条边 k <= 4
	输出每次操作后整张图是否连通
*/

#define N 1000010
#define pii pair <int, int>
#define fi first
#define se second
pii e[N];
int n, m, q;
int used[N], res[N];
struct qnode {
	int id, c[10];  
	void scan(int id) {
		this->id = id;
		scanf("%d", c);
		for (int i = 1; i <= c[0]; ++i) {
			scanf("%d", c + i);
		}
	} 
}qrr[N];

int pre[N], Top, tim;
pii stk[N];
int find(int x) {
	if (pre[x] == 0) {
		return x; 
	}
	int y = find(pre[x]);
	if (pre[x] != y) {
		//存下路径压缩的状态
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
	//回滚操作	
	while (Top != TOP) {
		int x = stk[Top].fi, y = stk[Top].se;
		pre[x] = y;
		--Top;
	}
}

void CDQ(int l, int r) {
	//存下当前的栈顶状态 
	int TOP = Top;
	if (l > r) {
		return;
	}
	if (l == r) {
		int id = qrr[l].id;
		res[id] = 1;
		for (int i = 1; i <= qrr[l].c[0]; ++i) {
			int now = qrr[l].c[i];
			res[id] &= find(e[now].fi) == find(e[now].se);  
		}
		rollback(TOP);
		return;
	}

	int mid = (l + r) >> 1;  ++tim;
	//标记左区间中都不存在的边
	for (int i = l; i <= mid; ++i) {
		for (int j = 1; j <= qrr[i].c[0]; ++j) {
			used[qrr[i].c[j]] = tim;    
		}
	}

	//从右区间找左区间中所有询问都存在的边 
	for (int i = mid + 1; i <= r; ++i) {
		for (int j = 1; j <= qrr[i].c[0]; ++j) {
			int now = qrr[i].c[j];
			if (used[now] != tim) {
				join(e[now].fi, e[now].se);
			}
		}	
	}
	CDQ(l, mid);
	rollback(TOP);

	++tim;
	for (int i = mid + 1; i <= r; ++i) {
		for (int j = 1; j <= qrr[i].c[0]; ++j) {
			used[qrr[i].c[j]] = tim;
		}
	}

	for (int i = l; i <= mid; ++i) {
		for (int j = 1; j <= qrr[i].c[0]; ++j) {
			int now = qrr[i].c[j];
			if (used[now] != tim) {
				join(e[now].fi, e[now].se);   
			}
		}
	}
	CDQ(mid + 1, r);
	//rollback(TOP);
	//这里不需要回滚操作
}

void init() {
	Top = 0; tim = 1; 
	memset(used, 0, sizeof used);
    memset(pre, 0, sizeof pre);	
}
int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		init();
		for (int i = 1; i <= m; ++i) {
			scanf("%d%d", &e[i].fi, &e[i].se);
		}
		scanf("%d", &q);
		for (int i = 1; i <= q; ++i) {
			qrr[i].scan(i);  
		}
		for (int i = 1; i <= q; ++i) {
			for (int j = 1; j <= qrr[i].c[0]; ++j) {
				used[qrr[i].c[j]] = 1;
			}
		}
		for (int i = 1; i <= m; ++i) if (!used[i]) {
			join(e[i].fi, e[i].se);
		}
		CDQ(1, q);
		for (int i = 1; i <= q; ++i) {
			if (!res[i]) {
				puts("Disconnected");
			} else {
				puts("Connected");
			} 
		}
	}
	return 0;
}
