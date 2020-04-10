#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 10;
int n, m, p, q, b[N];

template <typename RMQItem, RMQItem base> 
struct RMQ {
	vector <RMQItem> v;
	vector <vector<RMQItem>> tl, tr;
	//确立两数运算规则
	RMQItem op(const RMQItem &a, const RMQItem &b) { return 1ll * a * b % p; }
	int log2Up(int n) { 
	    int res = 0;
	    while ((1 << res) < n) {
	        res++;
	    }
	    return res; 
	}
	//下标从0开始
	RMQ(const vector<RMQItem> &a) {
		int n = a.size();
		v = a;
		tl = tr = vector <vector<RMQItem>>(log2Up(n) + 1, vector <RMQItem>(n));
		for (int k = 0; (1 << k) <= n; ++k) {
			int ones = (1 << k) - 1;
			RMQItem tmp = base;
			for (int i = 0; i < n; ++i) {
				tmp = op(tmp, a[i]);
				tl[k][i] = tmp;
				if ((i & ones) == ones) tmp = base;
			}
			tmp = base;
			for (int i = n - 1; i >= 0; --i) {
				tmp = op(tmp, a[i]);
				tr[k][i] = tmp;
				if ((i & ones) == 0) tmp = base;
			}
		}
	}
	RMQItem query(int l, int r) {
		if (l == r) return v[l];
		int num = 31 - __builtin_clz(l ^ r);
		return op(tl[num][r], tr[num][l]);
	}
};

int main() {
	int _T; scanf("%d", &_T);
	while (_T--) {
		scanf("%d%d%d", &n, &p, &q);
		vector <int> a(n);
		for (int i = 0, x; i < n; ++i) {
			scanf("%d", &x);
			a[i] = x;
		}
		RMQ <int, 1> rmq(a);
		m = (q / 64) + 2;
		for (int i = 0; i < m; ++i) scanf("%d", b + i);
		int lst = 0;
		for (int i = 0, l = 0, r = 0; i < q; ++i) {
			if (i % 64 == 0) {
				l = (b[i / 64] + lst) % n;
				r = (b[i / 64 + 1] + lst) % n;
			} else {
				l = (l + lst) % n;
				r = (r + lst) % n;
			}
			if (l > r) swap(l, r);
			lst = (rmq.query(l, r) + 1) % p;
		}
		printf("%d\n", lst);
	}		
	return 0;
}
