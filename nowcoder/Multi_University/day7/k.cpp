#include <bits/stdc++.h>
using namespace std;

#define N 101000
#define ll long long
ll n, w[N << 1];
int blk; 
int pri[N], tot, check[N];
ll sum[N], h[N << 1]; 
int id1[N], id2[N], m; 
void add(ll &x, ll y) {
	x += y;
}

ll f(int p, int e) {
	if (p % 4 == 1) return 3 * e + 1;
	else return 1;
}

void init(int n) {
	memset(check, 0, sizeof check);
	tot = 0;
	for (int i = 2; i <= n; ++i) {
		if (!check[i]) {
			pri[++tot] = i;
			sum[tot] = sum[tot - 1] + f(i, 1);
		}
		for (int j = 1; j <= tot; ++j) {    
			if (1ll * i * pri[j] > n) {     
				break;
			}
			check[i * pri[j]] = 1;  
			if (i % pri[j] == 0) {
				break;
			}
		}
	}
}

ll S(ll x, int y) {
	if (x <= 1 || pri[y] > x) {
		return 0;
	}
	int k = (x <= blk) ? id1[x] : id2[n / x];
	ll ret = h[k] - sum[y - 1];
	for (int i = y; i <= tot && 1ll * pri[i] * pri[i] <= x; ++i) {
		ll t1 = pri[i], t2 = 1ll * pri[i] * pri[i];
		for (int e = 1; t2 <= x; ++e, t1 = t2, t2 *= pri[i]) {
			add(ret, 1ll * f(pri[i], e) * S(x / t1, i + 1) + f(pri[i], e + 1));
		}
	}
	return ret;
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%lld", &n);
		m = 0;
		init(blk = sqrt(n));
		//数论分块和预处理h(n, 0)以及g(n, 0)，但是要注意不要把1的贡献算上
		for (ll i = 1, j; i <= n; i = j + 1) {
			j = n / (n / i);
			w[++m] = n / i;
			h[m] = ((w[m] - 1) / 4 * 3 + w[m] - 1);    
			//记录位置
			if (w[m] <= blk) {
				id1[w[m]] = m;
			} else {
				id2[n / w[m]] = m;   
			}
		}
		//递推，第一维枚举j，就是为了数组只开一维，j那一维直接滚掉就好了
		//g[i][j]表示的是小于等于i的本身就是质数或者最小质因子大于p_j的所有贡献，省掉的是j那一维
		for (int j = 1; j <= tot; ++j) {
			for (int i = 1; i <= m && 1ll * pri[j] * pri[j] <= w[i]; ++i) {
				int k = (w[i] / pri[j] <= blk) ? id1[w[i] / pri[j]] : id2[n / (w[i] / pri[j])];
				add(h[i], 1ll * -f(pri[j], 1) * (h[k] - sum[j - 1]));  
			}
		}
		//注意把特殊的1的贡献加上
		printf("%lld\n", S(n, 1) + 1); 
	}
	return 0;
}
