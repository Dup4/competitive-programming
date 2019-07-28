#include <bits/stdc++.h>
using namespace std;

#define ll long long
const ll p = 1e9 + 7;
ll d; int m;

#define N 30
struct Gauss {
	//增广矩阵
	ll a[N][N];
	//最后得到的解集  最终结果在x[0] - x[n - 1]
	ll x[N];
	inline ll gcd(ll a, ll b) {
		return b ? gcd(b, a % b) : a;
	}
	inline ll lcm(ll a, ll b) {
		return a / gcd(a, b) * b;
	}
	inline ll inv(ll a, ll m) {
		if (a == 1) return 1;
		return inv(m % a, m) * (m - m / a) % m;
	}
	inline void add(ll &x, ll y) {
		x += y;
		if (x >= p) x -= p;
	}
	//设置增广矩阵
	//k为变元数量　
	void init(int k) {
		memset(a, 0, sizeof a);
		ll tmp = inv(k, p);
		for (int i = 1; i <= k; ++i) { 
			for (int j = 1; j <= k; ++j) { 
				if (j < i) {
					add(a[i - 1][i - j - 1], tmp);
				} else if (j > i) {
					add(a[i - 1][j - i - 1], tmp);	
				}
			}
			add(a[i - 1][i - 1], p - 1);  
			a[i - 1][k] = (p - 1) % p;
		}
	}
	//equ为方程数量　var为变元数量
	//右equ行　equ + 1列，最后一列为常量
	int work(int equ, int var) {
		int max_r, col, k;
		for (k = 0, col = 0; k < equ && col < var; ++k, ++col) {
			max_r = k;
			for (int i = k + 1; i < equ; ++i) {
				if (abs(a[i][col]) > abs(a[max_r][col])) 
					max_r = i;
			}
			if (a[max_r][col] == 0) {
				k--;
				continue;
			}
			if (max_r != k) {
				for (int j = col; j < var + 1; ++j) {
					swap(a[k][j], a[max_r][j]);
				}
			} 
			for (int i = k + 1; i < equ; ++i) {
				if (a[i][col] != 0) {
					ll LCM = lcm(abs(a[i][col]), abs(a[k][col]));
					ll ta = LCM / abs(a[i][col]);
					ll tb = LCM / abs(a[k][col]);
					if (a[i][col] * a[k][col] < 0) tb = -tb;
					for (int j = col; j < var + 1; ++j) {
						a[i][j] = ((a[i][j] * ta - a[k][j] * tb) % p + p) % p;
					}
				}
			}
		}
		for (int i = k; i < equ; ++i) {
			if (a[i][col] != 0) 
				return -1; //无解
		}
		if (k < var) return var - k; //多解
		for (int i = var - 1; i >= 0; --i) {
			ll tmp = a[i][var];
			for (int j = i + 1; j < var; ++j) {
				if (a[i][j] != 0) {
					tmp -= a[i][j] * x[j] % p;
					tmp = (tmp + p) % p;
				}
			}
			x[i] = tmp * inv(a[i][i], p) % p;
		}
		return 0;
	}
}gauss;
ll f[30];
struct node {
	ll a[25][25];
	node () {
		memset(a, 0, sizeof a);
	}
	node operator * (const node &other) const {
		node res = node();
		for (int i = 0; i <= m; ++i)
			for (int j = 0; j <= m; ++j)
				for (int k = 0; k <= m; ++k)
					res.a[i][j] = (res.a[i][j] + a[i][k] * other.a[k][j] % p) % p;
		return res;
	}
}base, res;

void qmod(node base, ll n) {
	while (n) {
		if (n & 1) res = res * base;
		base = base * base;
		n >>= 1;
	}
}

int main() {
	while (scanf("%lld%d", &d, &m) != EOF) {
		gauss.init(m);
	    assert(gauss.work(m, m) == 0);	
		for (int i = 1; i <= m; ++i) f[i] = gauss.x[i - 1];
		if (d == m) {
			printf("%lld\n", f[m]);
			continue;
		}
		base = node();
		ll tmp = gauss.inv(m, p);
		for (int i = 0; i < m; ++i) base.a[i][0] = tmp;
		base.a[m][0] = 1;
		for (int i = 0; i < m - 1; ++i) base.a[i][i + 1] = 1;
		base.a[m][m] = 1;
		res = node();
		for (int i = 0; i < m; ++i) res.a[0][i] = f[m - i];
		res.a[0][m] = 1;
		qmod(base, d - m);
		printf("%lld\n", res.a[0][0]);
	}
	return 0;
}
