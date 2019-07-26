#include <bits/stdc++.h>
using namespace std; 

#define N 100010
#define pii pair <int, int>
#define fi first
#define se second
struct LeftTree {
    #define M 20 * N
    struct node {
        int w, id, lc, rc, h;
        node() {}
        node(int w, int id, int lc, int rc, int h) : w(w), id(id), lc(lc), rc(rc), h(h) {}
    }a[M]; 
	int rt[N], cnt;
	void init() {
		cnt = 0; rt[0] = 0;
	}
	//合并操作
    int merge(int A, int B) {
        if (!A) return B;
        if (!B) return A;
		//排序规则 这里的大于是小根堆，即维护左儿子最小
        if (a[A].w > a[B].w || (a[A].w == a[B].w && a[A].id > a[B].id)) swap(A, B);
        a[A].rc = merge(a[A].rc, B);
        if (a[a[A].lc].h < a[a[A].rc].h) swap(a[A].lc, a[A].rc);
        if (a[A].rc) a[A].h = a[a[A].rc].h + 1;
        else a[A].h = 0;
        return A;
    }
    void insert(int &A, int x, int id) {
        ++cnt;
        a[cnt] = node(x, id, 0, 0, 0);
        if (A) A = merge(A, cnt);  
		else A = cnt;
    } 
    pii del(int &A) {
        pii res = pii(a[A].w, a[A].id);
        A = merge(a[A].lc, a[A].rc); 
        return res;
    }
}lt;

int n, q;
int pre[N], a[N], isdel[N];
int find(int x) {
	return pre[x] == x ? x : pre[x] = find(pre[x]);
}

//合并两个堆
void merge(int x, int y) {
	if (isdel[x] || isdel[y]) return;
	int fx = find(x), fy = find(y);
	if (fx != fy) {
		pre[fx] = fy;
		lt.rt[fy] = lt.merge(lt.rt[fx], lt.rt[fy]); 
	}
}


int main() {
	while (scanf("%d%d", &n, &q) != EOF) {
		for (int i = 1; i <= n; ++i) pre[i] = i, isdel[i] = 0;
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		for (int i = 1; i <= n; ++i) {
			lt.rt[i] = 0; 
			lt.insert(lt.rt[i], a[i], i);
		}
		int op, x, y;
		while (q--) {
			scanf("%d%d", &op, &x);
			if (op == 1) {
				scanf("%d", &y); 
				merge(x, y);
			} else {
				if (isdel[x]) {
					puts("-1");
				} else {
					int top = find(x);
					pii tmp = lt.del(lt.rt[top]);
					printf("%d\n", tmp.fi);
					isdel[tmp.se] = 1;
				}
			}
		}
	}
    return 0;
}
