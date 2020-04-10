#include <bits/stdc++.h>
using namespace std;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
typedef double db;
const int N = 2e5 + 10;
const int K = 2;
const db INF = 0x3f3f3f3f3f3f3f3f;
int n; db ans;
inline db sqr(db x) { return x * x; }

struct Point {
	db x[K]; int id;
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
		db Min[K], Max[K]; 
		Node *ls, *rs;
		int div;
	}pool[N], *tail, *root;
	void init() { tail = pool; }
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
	Node* build(int l, int r) {
		if (l > r) return nullptr;
		int mid = (l + r) >> 1;
		Node *p = tail++;
		p->div = 0;
		if (l == r) {
			p->e = s[mid];
			pushup(p);
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
		p->e = s[mid];
		p->ls = build(l, mid - 1);
		p->rs = build(mid + 1, r);
		pushup(p);
		return p;	
	}
	db calc(Node *a, Point &e) {
		if (a == nullptr) return INF; 
	    db res = 0;
		for (int i = 0; i < K; ++i) {
			if (a->Min[i] > e.x[i])
				res += sqr(a->Min[i] - e.x[i]);
			if (a->Max[i] < e.x[i])
				res += sqr(a->Max[i] - e.x[i]);
		}
		return res;
	}
	void query(Node *t, int l, int r, Point &e) {
	    if (l > r) return;
	    int mid = (l + r) >> 1;
	    if (t->e.id != e.id) ans = min(ans, e.dis(t->e));  
	    if (l == r) return;
	    db distl = calc(t->ls, e), distr = calc(t->rs, e);
	    if (distl < ans && distr < ans) {
	        if (distl < distr) {
	            query(t->ls, l, mid - 1, e);
	            if (distr < ans) query(t->rs, mid + 1, r, e);
	        } else {
	            query(t->rs, mid + 1, r, e);
	            if (distl < ans) query(t->ls, l, mid - 1, e); 
	        }
	    } else {
	        if (distl < ans) query(t->ls, l, mid - 1, e);
	        if (distr < ans) query(t->rs, mid + 1, r, e);
	    }
	}
}kdTree;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
		scanf("%lf%lf", &s[i].x[0], &s[i].x[1]); 
		s[i].id = i;	
	}
	kdTree.init();
	kdTree.root = kdTree.build(1, n);
	ans = 2e18;
    for (int i = 1; i <= n; i++) kdTree.query(kdTree.root, 1, n, s[i]); 
    printf("%.4f\n", sqrt(ans));
    return 0;
}
