#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
struct BIT {
    ll a[N];
	inline void init() { memset(a, 0, sizeof a); }
    inline int lowbit(int x) { return x & -x; }
    void add(int x, ll v) {
        for (int i = x; i < N; i += lowbit(i))
            a[i] += v;
    }
    ll query(int x) {
        ll ret = 0;
        for (int i = x; i > 0; i -= lowbit(i))
            ret += a[i];
        return ret;
    }
	//a[i]表示i这个数有a[i]个，相当于权值BIT，查询第k大。
    int kth(ll k) {
        int p = 0;
        for (int lim = 1 << 20; lim; lim /= 2)
            if (p + lim < N && a[p + lim] < k) {
                p += lim;
                k -= a[p];
            }
        return p + 1;
    }
    ll query(int l, int r) { if (l > r) return 0; return query(r) - query(l - 1); }
    void add(int l, int r, ll v) { if (l > r) return; add(l, v); add(r + 1, -v); }
}bit;

int main() {
	int n, q; cin >> n >> q;
	bit.init();
	int op, l, r, v, k, x;
	while (q--) {
		cin >> op;
		if (op == 1) {
			cin >> x >> v;
			bit.add(x, v);
		} else {
			cin >> k;
			cout << bit.kth(k) << endl;
		}
	}
	return 0;
}
