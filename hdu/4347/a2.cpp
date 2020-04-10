#include <bits/stdc++.h>
#define SZ(x) (int(x.size()))
#ifdef ONLINE_JUDGE
#define assert(condition) do if (!condition) exit(*(int*)0); while (0)
#endif
using namespace std;
typedef long long db;
const int N = 5e4 + 10;
const int DIM = 5;
const db INF = 0x3f3f3f3f3f3f3f3f;
int n, K, q; 
inline db sqr(db x) { return x * x; }

struct Point {
	db x[DIM]; 
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
		Node *ls, *rs;
		int div;
		void init() { ls = rs = nullptr; div = 0;}
	}pool[N], *tail, *root;
	void init() { tail = pool; }
 	Node* newnode() { tail->init(); return tail++; }
	Node* build(int l, int r, int div) {
		if (l > r) return nullptr;
		int mid = (l + r) >> 1;
		Node *p = newnode();
		p->div = div;
		nth_element(s + l, s + mid, s + r + 1, cmpx(div));
		p->e = s[mid];
		p->ls = build(l, mid - 1, (div + 1) % K);
		p->rs = build(mid + 1, r, (div + 1) % K);
		return p;
	}	
	struct qnode {
		Point p;
		db dis;
		qnode() {}
		qnode(Point p, db dis) : p(p), dis(dis) {}
		bool operator < (const qnode &other) const { return dis < other.dis; }
	};
	priority_queue <qnode> pq;
	void search(Node *t, int k, Point p) {
		if (!t) return;
		if (cmp(p, t->e, t->div)) {
			search(t->ls, k, p);	
			if (SZ(pq) < k) {
				pq.push(qnode(t->e, p.dis(t->e)));
				search(t->rs, k, p);
			} else {
				if (p.dis(t->e) < pq.top().dis) {
					pq.pop();
					pq.push(qnode(t->e, p.dis(t->e))); 
				}
				if (sqr(t->e.x[t->div] - p.x[t->div]) < pq.top().dis)
					search(t->rs, k, p);
			}
		} else {
			search(t->rs, k, p);
			if (SZ(pq) < k) {
				pq.push(qnode(t->e, p.dis(t->e)));
				search(t->ls, k, p);
			} else {
				if (p.dis(t->e) < pq.top().dis) {
					pq.pop();
					pq.push(qnode(t->e, p.dis(t->e)));
				}
				if (sqr(t->e.x[t->div] - p.x[t->div]) < pq.top().dis)
					search(t->ls, k, p);
			}
		}
	}
	void search(Point p, int k) {
		while (!pq.empty()) pq.pop();
		search(root, k, p);
		printf("the closest %d points are:\n", k);
		vector <Point> vec;
		while (!pq.empty()) {
			vec.push_back(pq.top().p);
			pq.pop();
		}
		reverse(vec.begin(), vec.end());
		for (int i = 0; i < SZ(vec); ++i) vec[i].print();
	}
}kdTree;

int main() {
	while (scanf("%d%d", &n, &K) != EOF) {
		for (int i = 1; i <= n; ++i) s[i].scan();
		kdTree.init();
		kdTree.root = kdTree.build(1, n, 0);
		scanf("%d", &q);
		while (q--) {
			Point p; p.scan();
			int k; scanf("%d", &k);
			kdTree.search(p, k);	
		}
	}
    return 0;
}
