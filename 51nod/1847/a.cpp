#include <bits/stdc++.h>
using namespace std;

typedef unsigned int uint; 
const int N = 1e5 + 10;
int tot, K, m;
uint n, blk, pri[N], prik[N], sprik[N], check[N], f[N], g[N], h[N], id1[N], id2[N], w[N];
inline int id(uint x) { 
	if (x <= blk) return id1[x];
	return id2[n / x]; 
}
uint qpow(uint base, uint n) {
	uint res = 1;
	while (n) {
		if (n & 1) res = res * base;
		base = base * base;
		n >>= 1;
	}
	return res;
}
void sieve() {
	memset(check, 0, sizeof check);
	tot = 0;
	for (int i = 2; i < N; ++i) {
		if (!check[i]) {
			pri[++tot] = i;
			prik[tot] = qpow(pri[tot], K);
			sprik[tot] = sprik[tot - 1] + prik[tot];
		}
		for (int j = 1; j <= tot; ++j) {  
			if (1ll * i * pri[j] >= N) break;
			check[i * pri[j]] = 1;  
			if (i % pri[j] == 0) break;
		}
	}
}

//伯努利数预处理求幂和
struct Sumk {
	static const int M = 110;
	uint S[M][M];
	void init() {
		S[0][0] = 1;
		for (int i = 1; i < M; ++i) {
			for (int j = 1; j <= i; ++j) {
				S[i][j] = S[i - 1][j - 1] + 1u * j * S[i - 1][j];
			}
		}	
	}
	//计算sum i^k   O(k^2)
	inline uint calc(uint n, int k) {
		uint res = 0;
		for (int i = 1; i <= k; ++i) {
			uint s = 1;
			for (int j = 0; j <= i; ++j) {
				if ((n + 1 - j) % (i + 1)) s *= n + 1 - j;
				else s *= (n + 1 - j) / (i + 1);
			}
			res += S[k][i] * s;
		}
		return res;
	}
}sumk;

bool vis[N];
uint F[N];
uint S(uint x) {
	int t = id(x);
	if (vis[t]) return F[t];
	uint res = f[t];
	for (uint i, j = 1; j < x; ) {
		i = j + 1;
		j = x / (x / i);
		res -= (j - i + 1) * S(x / i);
	}
	vis[t] = 1;
	return F[t] = res;
}

int main() {
	while (scanf("%u%d", &n, &K) != EOF) {
		memset(vis, 0, sizeof vis);
		memset(f, 0, sizeof f);
		sieve(); sumk.init(); m = 0; blk = sqrt(n); 
		//数论分块和预处理h(n, 0)以及g(n, 0)，但是要注意不要把1的贡献算上
		for (uint i = 1, j; i <= n; i = j + 1) {
			j = n / (n / i);
			w[++m] = n / i; 
			g[m] = w[m] - 1;
			h[m] = sumk.calc(w[m], K) - 1;
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
				int k = id(w[i] / pri[j]);
				g[i] -= g[k] - (j - 1);
				h[i] -= prik[j] * (h[k] - sprik[j - 1]);
				f[i] += h[k] - sprik[j - 1];
			}
		}
		for (int i = 1; i <= m; ++i) f[i] += g[i];
		uint res = 0, lt = 0, nw;
		for (uint i = 1, j; i <= n; i = j + 1) {
			j = n / (n / i); nw = S(j);
			res += (n / i) * (n / i) * (nw - lt);
			lt = nw;
		}
		printf("%u\n", res);
		
	}
	return 0;
}
