#include <bits/stdc++.h>
using namespace std;

/*
	假设一共有m个0，和n - m个1
 	f[i][j] 表示到第i个操作，前m个数字当中有j个1的方案数
	1. 前m个数字随便取两个交换，或者后(n - m)个数字随便取两个交换，不会改变j
	f[i][j] += f[i - 1][j] * (C[m][2] + C[n - m][2])  
	2. 前m个数字中的1和后(n - m)个数字中的1进行交换
	f[i][j] += f[i - 1][j] * j * (n - m - j)
	3. 前m个数字中的0和后(n - m)个数字中的0进行交换
	f[i][j] += f[i - 1][j] * (m - j) * j

	4. 前m个数字中取一个0和后(n - m)个数字中的1进行交换
	f[i][j] += f[i - 1][j - 1] * (m - j + 1) * (n - m - j + 1)
	5. 前m个数字中取一个1和后(n - m)个数字中的0进行交换
	f[i][j] += f[i - 1][j + 1] * (j + 1) * (j + 1)
*/

#define ll long long
#define N 110
const ll p = (ll)1e9 + 7;
int n, m, k, a[N];
ll f[N][N], C[N][N];
ll qmod(ll base, ll n) {
	ll res = 1;
	while (n) {
		if (n & 1) {
			res = res * base % p;
		}
		base = base * base % p;
		n >>= 1;
	}
	return res;
}
struct node {
	int len;
	ll a[N][N];
	node () {
		memset(a, 0, sizeof a);
	}
	node (int len) {
		this->len = len;
		memset(a, 0, sizeof a);
	}
	node operator * (const node &other) const {
		node res = node(len);
		for (int i = 0; i <= len; ++i) {
			for (int j = 0; j <= len; ++j) {
				for (int k = 0; k <= len; ++k) {
					(res.a[i][j] += a[i][k] * other.a[k][j] % p) %= p;
				}
			}
		}
		return res; 
	}
}base, res;

void qmod(node &res, node &base, ll n) {
	while (n) {
		if (n & 1) {
			res = res * base;
		}
		base = base * base;
		n >>= 1;
	}
}

int main() {
	memset(C, 0, sizeof C); 
	C[1][0] = C[1][1] = 1;
	for (int i = 1; i <= 100; ++i) {
		for (int j = 0; j <= i; ++j) {
			(C[i + 1][j + 1] += C[i][j]) %= p;
			(C[i + 1][j] += C[i][j]) %= p;
		}
	}
	while (scanf("%d%d", &n, &k) != EOF) {
		m = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			m += (a[i] == 0);
		}
		base = node(m); res = node(m);
		for (int i = 1, j = 0; i <= m; ++i) {
			j += (a[i] == 1);
			if (i == m) {
				res.a[0][j] = 1;
			}
		}
		for (int i = 0; i <= m; ++i) {
			(base.a[i][i] += C[m][2] + C[n - m][2]) %= p;
			(base.a[i][i] += i * (n - m - i) % p) %= p;
			(base.a[i][i] += (m - i) * i % p) %= p;
			if (i != 0) {
				(base.a[i][i - 1] += (m - i + 1) * (n - m - i + 1) % p) %= p;
			}
			if (i != m) {
				(base.a[i][i + 1] += (i + 1) * (i + 1) % p) %= p;
			}
		}
		
		qmod(res, base, k);
		ll a = res.a[0][0], b = 0;
		for (int i = 0; i <= m; ++i) {
			(b += res.a[0][i]) %= p;
		}
		printf("%lld\n", a * qmod(b, p - 2) % p);

		/*
		memset(f, 0, sizeof f);
		for (int i = 1, j = 0; i <= m; ++i) {
			j += (a[i] == 1);
			if (i == m) {
				f[0][j] = 1;
			}
		}
		for (int i = 1; i <= k; ++i) {
			for (int j = 0; j <= m; ++j) {
				(f[i][j] += f[i - 1][j] * (C[m][2] + C[n - m][2]) % p) %= p;
				(f[i][j] += f[i - 1][j] * j % p * (n - m - j) % p) %= p;
				(f[i][j] += f[i - 1][j] * (m - j) % p * j % p) %= p;
				if (j != 0) {
					(f[i][j] += f[i - 1][j - 1] * (m - j + 1) % p * (n - m - j + 1) % p) %= p;
				}
				if (j != m) {
					(f[i][j] += f[i - 1][j + 1] * (j + 1) % p * (j + 1) % p) %= p;
				}
			}
		}
		ll a = 0, b = f[k][0];
		for (int i = 0; i <= m; ++i) {
			(a += f[k][i]) %= p;
		}


		printf("%lld\n", b * qmod(a, p - 2) % p);
		*/
	}
	return 0;
}
