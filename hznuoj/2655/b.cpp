#include <bits/stdc++.h>
using namespace std;

#define N 2100
const int p = 2019;
int n, q, a[N];
int f[N][N];

void add(int &x, int y) {
	x += y;
	if (x >= p) x -= p;
}
int qmod(int base, int n) {
	int res = 1;
	while (n) {
		if (n & 1) {
			res = res * base % p;
		}
		base = base * base % p;
		n >>= 1;
	} 
	return res;
}

struct BIT {
	int a[N];
	void init() {
		memset(a, 0, sizeof a);
	}
	void update(int x, int v) {
		for (; x < N; x += x & -x) {
			a[x] += v;
		}
	}
	int query(int x) {
		int res = 0;
		for (; x > 0; x -= x & -x) {
			res += a[x];  
		}
		return res;
	}
	int query(int l, int r) {
		return query(r) - query(l - 1);
	}
}bit;

struct BIT2 {
	int a[N];
	void init() {
		memset(a, 0, sizeof a);
	}
	void update(int x, int v) {
		for (; x < N; x += x & -x) {
			a[x] = max(a[x], v);
		}
	}
	int query(int x) {
		int res = 0;
		for (; x > 0; x -= x & -x) {
			res = max(res, a[x]);
		}
		return res;
	}
}bit2;


int main() {
	memset(f, 0, sizeof f);
	f[0][0] = 1;
	for (int i = 1; i <= 2018; ++i) {
		f[i][0] = 1;
		for (int j = 1; j <= 2018; ++j) {
			f[i][j] = f[i][j - 1] * i % p;
		}
	}
	while (scanf("%d%d", &n, &q) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i); 
		} 
		int op, l, r, x, res, tmp;
		while (q--) {
			scanf("%d%d%d", &op, &l, &r);
			switch(op) {
				case 1 :
					scanf("%d", &x);
					for (int i = l; i <= r; ++i) {
						add(a[i], x);
					}
					break;
				case 2 :
					scanf("%d", &x);
					for (int i = l; i <= r; ++i) {
						a[i] = x;
					}
					break;
				case 3 :
					scanf("%d", &x);
					for (int i = l; i <= r; ++i) {
						a[i] = f[a[i]][x];
					}
					break;
				case 4 :
					sort(a + l, a + r + 1);
					break;
				case 5 :
					reverse(a + l, a + r + 1);
					break;
				case 6 :
					res = 0;
					for (int i = l; i <= r; ++i) {
						add(res, a[i]);
					}
					printf("%d\n", res);
					break;
				case 7 :
					scanf("%d", &x);
					res = 0;
					for (int i = l; i <= r; ++i) {
						add(res, f[a[i]][x]);
					}
					printf("%d\n", res);
					break;
				case 8 :
					res = 0;
					for (int i = l; i <= r; ++i) {
						for (int j = l; j < i; ++j) {
							if (a[i] < a[j] && a[j] <= 2018) ++res;
						}
					}
					printf("%d\n", res);
					break;
				case 9 :
					bit2.init(); res = 0;
					for (int i = l; i <= r; ++i) {
						++a[i];
						tmp = bit2.query(a[i] - 1) + 1;
						res = max(res, tmp);
						bit2.update(a[i], tmp);
						--a[i];
					}
					printf("%d\n", res);
					break;
				case 10 :
					scanf("%d", &x);
					res = 0;
					for (int i = l; i <= r; ++i) {
						res += (a[i] > x);
					}
					printf("%d\n", res);
					break;
				default : 
					assert(0);
			}
		}	
	}
	return 0;
}
