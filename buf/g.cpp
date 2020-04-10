#include <bits/stdc++.h>
using namespace std;
const int N = 1e2 + 10;

template <typename T>
struct BIT {
	int n, _n, __n;
	T a[N][N][N];
	BIT() {}
	BIT(int n, int _n, int __n) : n(n), _n(_n), __n(__n) { memset(a, 0, sizeof a); }
	int lowbit(int x) { return x & -x; }
	void update(int x, int y, int z, T v) {
	    for (int i = x; i <= n; i += lowbit(i))
	        for (int j = y; j <= _n; j += lowbit(j))
	            for (int k = z; k <= __n; k += lowbit(k))
	                a[i][j][k] += v;
	}
	T query(int x, int y, int z) {
	    T ret = 0;
	    for (int i = x; i > 0; i -= lowbit(i))
	        for (int j = y; j > 0; j -= lowbit(j))
	            for (int k = z; k > 0; k -= lowbit(k))
	                ret += a[i][j][k];
	    return ret;
	}
	T query(int x, int y, int z, int xx, int yy, int zz) {
	    return    query(xx, yy, zz)
	            - query(xx, yy, z - 1)
	            - query(xx, y - 1, zz)
	            - query(x - 1, yy, zz)
	            + query(xx, y - 1, z - 1)
	            + query(x - 1, yy, z - 1)
	            + query(x - 1, y - 1, zz)
	            - query(x - 1, y - 1, z - 1);
	}
};

int main() {

}
