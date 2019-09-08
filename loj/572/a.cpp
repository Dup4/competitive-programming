#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned uint; 
const int N = 1e6 + 10;
uint n, k, tot, blk, pri[N], prik[N], check[N], m, id1[N], id2[N], f[N];
bool vis[N];
inline uint id(uint x) {
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
		if (!check[i]) pri[++tot] = i, prik[tot] = qpow(pri[tot], k);
		for (int j = 1; j <= tot; ++j) {
			if (1ll * i * pri[j] >= N) break;
			check[i * pri[j]] = 1;
			if (i % pri[j] == 0) break; 
		}
	}
}
struct Min25 {
	uint w[N], g[N];
	inline void init() {
		blk = sqrt(n); m = 0;
		for (uint i = 1, j; i <= n; i = j + 1) {
			j = n / (n / i);
			w[++m] = n / i; g[m] = w[m] - 1;
			if (w[m] <= blk) id1[w[m]] = m;
			else id2[n / w[m]] = m;  
		}
		for (int j = 1; j <= tot && 1ll * pri[j] * pri[j] <= n; ++j) {
			for (int i = 1; 1ll * pri[j] * pri[j] <= w[i] && i <= m; ++i) {
				int k = id(w[i] / pri[j]);
				g[i] -= g[k] - j + 1;
			}
		}
	}
	uint S(uint x, int y) { 
		if (x <= 1 || pri[y] > x) return 0; 
		int k = id(x);
		//y - 1 可能会用到pri[0], 所以不要用*pri来存个数
		//这里是[1, x]中>=y的质数的贡献，他们上一轮选择的是pri[y - 1]，那么他们的次大质因子就是pri[y - 1], 这就是他们的贡献
		uint res = prik[y - 1] * (g[k] - y + 1);
		for (int i = y; i <= tot && 1ll * pri[i] * pri[i] <= x; ++i) {
			ll t1 = pri[i], t2 = 1ll * pri[i] * pri[i];
			for (int e = 1; t2 <= x; ++e, t1 = t2, t2 *= pri[i]) {
				res += S(x / t1, i + 1) + prik[i];
			}
		}
		return res;
	}
	inline uint gao(uint n) {
		//因为此处是把质数的贡献置为0，但是题目要求质数的贡献为1，所以特别加上即可。
		return S(n, 1) + g[id(n)]; 
	}
}min25;

uint S(uint x) {
	int t = id(x);
	if (vis[t]) return f[t]; vis[t] = 1;
	f[t] = min25.gao(x);
	for (uint i, j = 1; j < x; ) {
		i = j + 1; j = x / (x / i);
		f[t] -= (j - i + 1) * S(x / i);
	}
	return f[t];
}

int main() {
	while (scanf("%u%u", &n, &k) != EOF) {
		sieve(); min25.init();
		memset(vis, 0, sizeof vis); 
	 	uint res = 0, lt = 0, nw;
		for (uint i = 1, j; i <= n; i = j + 1) {
			j = n / (n / i);
			nw = S(j);
			res += (uint)1 * (n / i) * (n / i) * (nw - lt);
			lt = nw;
		}	
		printf("%u\n", res);
	}
	return 0;
}

