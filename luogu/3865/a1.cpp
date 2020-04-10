#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
int n, m;

template <typename RMQItem, RMQItem base> 
struct RMQ {
	vector <RMQItem> v;
	vector <vector<RMQItem>> tl, tr;
	//确立两数运算规则
	RMQItem op(const RMQItem &a, const RMQItem &b) { return max(a, b); }
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
	while(scanf("%d%d", &n, &m) != EOF) {
		vector <int> a(n);
		for (int i = 0, x; i < n; ++i) {
			scanf("%d", &x);
			a[i] = x;
		}
		RMQ <int, -INF> rmq(a);
		int l, r;
		while (m--) {
			scanf("%d%d", &l, &r);
			printf("%d\n", rmq.query(l - 1, r - 1));
		}
	}
	return 0;
}
