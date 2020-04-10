#include <bits/stdc++.h>
#define SZ(x) (int(x.size()))
using namespace std;
typedef long long db;
const int N = 5e4 + 10;
const int DIM = 5;
const db INF = 0x3f3f3f3f3f3f3f3f;
int n, K, q; 
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
//		db Min[DIM], Max[DIM]; 
		Node *ls, *rs;
		int div;
		void init() { ls = rs = nullptr; div = 0;}
	}pool[N], *tail, *root;
	void init() { tail = pool; }
   	Node* newnode() { tail->init(); return tail++; }	
//	void pushup(Node *a) {
//		for (int i = 0; i < K; ++i) {
//			a->Min[i] = a->Max[i] = a->e.x[i];
//		}
//	    if (a->ls) {
//			for (int i = 0; i < K; ++i) {
//				a->Min[i] = min(a->Min[i], a->ls->Min[i]);
//				a->Max[i] = max(a->Max[i], a->ls->Max[i]);
//			}
//		}
//		if (a->rs) {
//			for (int i = 0; i < K; ++i) {
//				a->Min[i] = min(a->Min[i], a->rs->Min[i]);
//				a->Max[i] = max(a->Max[i], a->rs->Max[i]);
//			}
//		}
//	}
	Node* build(int l, int r) {
		if (l > r) return nullptr;
		int mid = (l + r) >> 1;
		Node *p = newnode();
		p->e = s[mid];
		if (l == r) {
			//pushup(p);
			return p;
		}
		//average variance
		db avx[K] = {0}, vax[K] = {0};
		for (int i = l; i <= r; ++i) 
			for (int j = 0; j < K; ++j) 
				avx[j] += s[i].x[j];
		for (int i = 0; i < K; ++i) avx[i] /= (db)(r - l + 1);
		for (int i = l; i <= r; ++i) 
			for (int j = 0; j < K; ++j) 
				vax[j] += sqr(s[i].x[j] - avx[j]);
		for (int i = 1; i < K; ++i) {
			if (vax[i] > vax[p->div])
				p->div = i;
		}
		nth_element(s + l, s + mid, s + r + 1, cmpx(p->div));
		p->ls = build(l, mid - 1);
		p->rs = build(mid + 1, r);
	//	pushup(p);
		return p;	
	}
//	db calc(Node *a, Point &e) {
//		if (a == nullptr) return INF; 
//	    db res = 0;
//		for (int i = 0; i < K; ++i) {
//			if (a->Min[i] > e.x[i])
//				res += sqr(a->Min[i] - e.x[i]);
//			if (a->Max[i] < e.x[i])
//				res += sqr(a->Max[i] - e.x[i]); 
//		}
//		return res;
//	}
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
//	void query(Node *t, int l, int r, Point &e) {
//	    if (l > r) return;
//	    int mid = (l + r) >> 1;
//	    if (t->e.id != e.id) ans = min(ans, e.dis(t->e));  
//	    if (l == r) return;
//	    db distl = calc(t->ls, e), distr = calc(t->rs, e);
//	    if (distl < ans && distr < ans) {
//	        if (distl < distr) {
//	            query(t->ls, l, mid - 1, e);
//	            if (distr < ans) query(t->rs, mid + 1, r, e);
//	        } else {
//	            query(t->rs, mid + 1, r, e);
//	            if (distl < ans) query(t->ls, l, mid - 1, e); 
//	        }
//	    } else {
//	        if (distl < ans) query(t->ls, l, mid - 1, e);
//	        if (distr < ans) query(t->rs, mid + 1, r, e);
//	    }
//	}
}kdTree;

int main() {
	while (scanf("%d%d", &n, &K) != EOF) {
		for (int i = 1; i <= n; ++i) s[i].scan();
		kdTree.init();
		kdTree.root = kdTree.build(1, n);
		scanf("%d", &q);
		while (q--) {
			Point p; p.scan();
			int k; scanf("%d", &k);
			kdTree.search(p, k);	
		}
	}
    return 0;
}
