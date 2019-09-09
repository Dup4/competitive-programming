#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
#define N 101000
const ull one = 1;
ull n, K, w[N << 1], g[N << 1]; 
int blk, tot, pri[N], check[N], id1[N], id2[N], m; 
inline int id(ull x) {
	if (x <= blk) return id1[x];
	return id2[n / x];
}
void init(int n) {
	memset(check, 0, sizeof check);
	tot = 0;
	for (int i = 2; i <= n; ++i) {
		if (!check[i]) pri[++tot] = i;
		for (int j = 1; j <= tot; ++j) {  
			if (1ll * i * pri[j] > n) break;
			check[i * pri[j]] = 1;  
			if (i % pri[j] == 0) break;
		}
	}
}

ull S(ull x, int y) {
	if (x <= 1 || pri[y] > x) return 0;
	int k = id(x);
	ull res = (K + 1) * (g[k] - y + 1); 
	for (int i = y; i <= tot && one * pri[i] * pri[i] <= x; ++i) {
		ull t1 = pri[i], t2 = one * pri[i] * pri[i];
		for (int e = 1; t2 <= x; ++e, t1 = t2, t2 *= pri[i]) {
			res += (K * e + 1) * S(x / t1, i + 1) + (K * (e + 1) + 1);
		}
	}
	return res;
}

int main() {
	int _T; scanf("%d", &_T);
	while (_T--) {
		scanf("%llu%llu", &n, &K);
		m = 0; init(blk = sqrt(n));
		//数论分块和预处理h(n, 0)以及g(n, 0)，但是要注意不要把1的贡献算上
		for (ull i = 1, j; i <= n; i = j + 1) {
			j = n / (n / i);
			w[++m] = n / i; 
			g[m] = w[m] - 1;
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
			for (int i = 1; i <= m && one * pri[j] * pri[j] <= w[i]; ++i) {
				int k = id(w[i] / pri[j]);
				g[i] -= g[k] - (j - 1);  
			}
		}
		//注意把特殊的1的贡献加上
		printf("%llu\n", S(n, 1) + 1); 
	}
	return 0;
}
