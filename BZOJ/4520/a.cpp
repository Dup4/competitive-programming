#include <bits/stdc++.h>
#define SZ(x) (int(x.size()))
using namespace std;
typedef long long db;
const int N = 1e5 + 10;
const int DIM = 2;
const int K = 2;
const db INF = 0x3f3f3f3f3f3f3f3f;
int n, k; 
inline db sqr(db x) { return x * x; }

struct Point {
	db x[DIM]; int id;
	void scan() { for (int i = 0; i < K; ++i) scanf("%lld", x + i); }
	void print() { for (int i = 0; i < K; ++i) printf("%lld%c", x[i], " \n"[i == K - 1]); }
	db dis(const Point &b) const {
		db res = 0;
		for (int i = 0; i < K; ++i)
			res += sqr(x[i] - b.x[i]); 
		return res;
	}
}s[N];

struct KDTree {
	struct cmpx {
		int div;
		cmpx(int div = 0) : div(div) {}
		bool operator () (const Point &a, const Point &b) {
			for (int i = 0; i < K; ++i)
				if (a.x[(i + div) % K] != b.x[(i + div) % K])
					return a.x[(i + div) % K] < b.x[(i + div) % K];
			return true;
		}
	};
	bool cmp(const Point &a, const Point &b, int div) { return cmpx(div)(a, b); }
	struct Node {
		Point e;
		db Min[DIM], Max[DIM];
		Node *ls, *rs;
		int div;
		void init() { ls = rs = NULL; div = 0;}
	}pool[N], *tail, *root;
	void init() { tail = pool; }
 	Node* newnode() { tail->init(); return tail++; }
	void pushup(Node *a) { 
		for (int i = 0; i < K; ++i) {
			a->Min[i] = a->Max[i] = a->e.x[i]; 
		} 
	    if (a->ls) {
			for (int i = 0; i < K; ++i) {
				a->Min[i] = min(a->Min[i], a->ls->Min[i]);
				a->Max[i] = max(a->Max[i], a->ls->Max[i]);
			}
		}
		if (a->rs) {
			for (int i = 0; i < K; ++i) {
				a->Min[i] = min(a->Min[i], a->rs->Min[i]);
				a->Max[i] = max(a->Max[i], a->rs->Max[i]);
			}
		}
	}
	Node* build(int l, int r, int div) {
		if (l > r) return NULL;
		int mid = (l + r) >> 1;
		Node *p = newnode();
		p->div = div;
		nth_element(s + l, s + mid, s + r + 1, cmpx(div));
		p->e = s[mid];
		p->ls = build(l, mid - 1, (div + 1) % K);
		p->rs = build(mid + 1, r, (div + 1) % K);
		pushup(p);
		return p;
	}	
	struct qnode {
		Point p;
		db dis;
		qnode() {}
		qnode(Point p, db dis) : p(p), dis(dis) {}
		bool operator < (const qnode &other) const { return dis > other.dis; }
	};
	priority_queue <qnode> pq;
	db calc(Node *t, Point e) {
		if (t == NULL) return 0;
		db res = 0;
		for (int i = 0; i < K; ++i) {
			res += max(sqr(e.x[i] - t->Max[i]), sqr(e.x[i] - t->Min[i]));
		}
		return res;
	}
	void search(Node *t, int k, Point p) {
		if (!t) return;
		if (!cmp(p, t->e, t->div)) {
			search(t->ls, k, p);	
			if (SZ(pq) < k) {
				if (p.id > t->e.id) pq.push(qnode(t->e, p.dis(t->e)));
				search(t->rs, k, p);
			} else {
				if (p.id > t->e.id && p.dis(t->e) > pq.top().dis) {
					pq.pop();
					pq.push(qnode(t->e, p.dis(t->e))); 
				} 
				if (calc(t->rs, p) > pq.top().dis)
					search(t->rs, k, p);
			}
		} else {
			search(t->rs, k, p);
			if (SZ(pq) < k) {
				if (p.id > t->e.id) pq.push(qnode(t->e, p.dis(t->e)));
				search(t->ls, k, p);
			} else {
				if (p.id > t->e.id && p.dis(t->e) > pq.top().dis) {
					pq.pop();
					pq.push(qnode(t->e, p.dis(t->e)));
				}
				if (calc(t->ls, p) > pq.top().dis)
					search(t->ls, k, p);
			}
		}
	}
}kdTree;

int main() {
	while (scanf("%d%d", &n, &k) != EOF) { 
		for (int i = 1; i <= n; ++i) {
			s[i].scan();
			s[i].id = i;
		}	
		kdTree.init();
		kdTree.root = kdTree.build(1, n, 0);
		for (int i = 1; i <= n; ++i) kdTree.search(kdTree.root, k, s[i]);
		printf("%lld\n", kdTree.pq.top().dis);
	}
    return 0;
}

