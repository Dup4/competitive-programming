#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 2e5 + 10;
const int mod = 1e9 + 7;
ll n, w[N];
int blk, tot, check[N], pri[N], spri[N], g[N], h[N], id1[N], id2[N], m; 
inline int id(ll x) {
	if (x <= blk) return id1[x];
	return id2[n / x];
}
void add(int &x, int y) {
	x += y;
	while (x >= mod) x -= mod;
	while (x < 0) x += mod;
}
void init(int n) {
	memset(check, 0, sizeof check);
	tot = 0; spri[0] = 0;
	for (int i = 2; i <= n; ++i) {
		if (!check[i]) {
			pri[++tot] = i;
			spri[tot] = (spri[tot - 1] + i) % mod;
		}
		for (int j = 1; j <= tot; ++j) {  
			if (1ll * i * pri[j] > n) break;
			check[i * pri[j]] = 1;  
			if (i % pri[j] == 0) break;
		}
	}
}

int S(ll x, int y) {
	if (x <= 1 || pri[y] > x) {
		return 0;
	}
	int k = id(x);
	int ret = ((g[k] - h[k] - spri[y - 1] + y - 1) % mod + mod) % mod;
	//把2的少加的贡献加上
	if (y == 1) add(ret, 2);
	for (int i = y; i <= tot && 1ll * pri[i] * pri[i] <= x; ++i) {
		ll t1 = pri[i], t2 = 1ll * pri[i] * pri[i];
		for (int e = 1; t2 <= x; ++e, t1 = t2, t2 *= pri[i]) {
			add(ret, (1ll * (pri[i] ^ e) * S(x / t1, i + 1) % mod + (pri[i] ^ (e + 1))) % mod);
		}
	}
	return ret;
}

int main() {
	while (scanf("%lld", &n) != EOF) {
		m = 0;
		init(blk = sqrt(n));
		//数论分块和预处理h(n, 0)以及g(n, 0)，但是要注意不要把1的贡献算上
		for (ll i = 1, j; i <= n; i = j + 1) {
			j = n / (n / i);
			w[++m] = n / i;
			h[m] = (w[m] + mod - 1) % mod;
			g[m] = ((w[m] % mod) * ((w[m] + 1) % mod) / 2 - 1 + mod) % mod;
			//记录位置
			if (w[m] <= blk) id1[w[m]] = m;
			else id2[n / w[m]] = m;
		}
		//递推，第一维枚举j，就是为了数组只开一维，j那一维直接滚掉就好了
		for (int j = 1; j <= tot; ++j) {
			for (int i = 1; i <= m && 1ll * pri[j] * pri[j] <= w[i]; ++i) {
				int k = id(w[i] / pri[j]);
				add(g[i], mod - 1ll * pri[j] * (g[k] - spri[j - 1] + mod) % mod);
				add(h[i], mod - (h[k] - (j - 1) + mod) % mod);
			}
		}
		//注意把特殊的1的贡献加上
		printf("%d\n", (S(n, 1) + 1) % mod); 
	}
	return 0;
}
