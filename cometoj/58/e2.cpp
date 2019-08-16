#include <bits/stdc++.h>
using namespace std;

#define N 3501000
#define ll long long
ll n; int blk; 
void add(ll &x, ll y) {
	x += y;
}

//线性筛
int pri[N], check[N], ptot; 
ll f[N];
void sieve_gao(int n) { 
	memset(check, 0, sizeof check);
	ptot = 0;
	for (int i = 2; i <= n; ++i) {
		if (!check[i]) {
			pri[++ptot] = i;
			f[ptot] = f[ptot - 1];
			++f[ptot];
		}
		for (int j = 1; j <= ptot; ++j) {    
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

//Min25筛
struct Min25 {
	int id1[N], id2[N], m;
	ll w[N << 1];
	//预处理所需要的函数
	ll h[N << 1]; 

	//快速计算p^e时的贡献
//	ll f(int p, int e) {
//		if (p % 4 == 1) return 3 * e + 1; 
//		else return 1;
//	}

	//第二部分，计算合数的贡献
	ll S(ll x, int y) {
		if (x <= 1 || pri[y] > x) {
			return 0;
		}
		int k = (x <= blk) ? id1[x] : id2[n / x];
		ll ret = h[k] - f[y - 1];
		//对2特殊考虑，把2少加的贡献加上
	//	if (y == 1) ++ret;  
		for (int i = y; i <= ptot && 1ll * pri[i] * pri[i] <= x; ++i) {
			ll t1 = pri[i], t2 = 1ll * pri[i] * pri[i];
			ll base = 1;
			for (int e = 1; t2 <= x; ++e, t1 = t2, t2 *= pri[i]) {
				add(ret, base * S(x / t1, i + 1) + base * (e % 2 ? pri[i] : 1));
				if (e % 2) 
					base *= pri[i];
			}
		}
		return ret;
	}
	
	ll gao(ll n) {
		m = 0;
		//数论分块和预处理h(n, 0)以及g(n, 0)，但是要注意不要把1的贡献算上
		for (ll i = 1, j; i <= n; i = j + 1) {
			j = n / (n / i);
			w[++m] = n / i;
			h[m] = w[m] - 1;
			//记录位置
			if (w[m] <= blk) {
				id1[w[m]] = m;
			} else {
				id2[n / w[m]] = m;
			}
		}	
		//递推，第一维枚举j，就是为了数组只开一维，j那一维直接滚掉就好了
		//g[i][j]表示的是小于等于i的本身就是质数或者最小质因子大于p_j的所有贡献，省掉的是j那一维
		for (int j = 1; j <= ptot; ++j) {
			for (int i = 1; i <= m && 1ll * pri[j] * pri[j] <= w[i]; ++i) {
				int k = (w[i] / pri[j] <= blk) ? id1[w[i] / pri[j]] : id2[n / (w[i] / pri[j])];
				add(h[i], -(h[k] - (j - 1)));
			}
		}
		//把特殊的1的贡献加上
		return S(n, 1) + 1;
	}
}min25;

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%lld", &n);
		sieve_gao(blk = sqrt(n));
		printf("%lld\n", min25.gao(n));
	}
	return 0;
}