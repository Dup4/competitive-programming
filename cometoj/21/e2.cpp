#include <bits/stdc++.h>
using namespace std;

#define db long double
#define ll long long
#define N 400010
#define S 10010
const ll mod = 998244353;
int n, m, a[N], b[N], c[N], x1[N], x2[N], goal[N], fn, fl;
vector <int> l[N], r[N];
ll ans[N];

void Hash()
{
	c[0] = 0;
	for (int i = 0; i <= n; ++i) c[++c[0]] = a[i];
	for (int i = 0; i <= m; ++i) c[++c[0]] = b[i];
	sort(c + 1, c + 1 + c[0]);
	c[0] = unique(c + 1, c + 1 + c[0]) - c - 1;
	for (int i = 0; i <= n; ++i) a[i] = lower_bound(c + 1, c + 1 + c[0], a[i]) - c;
	for (int i = 0; i <= m; ++i) b[i] = lower_bound(c + 1, c + 1 + c[0], b[i]) - c;   
}

ll mul(ll a, ll b, ll p) {
	a %= p, b %= p;
	return (a * b - (ll)(a / (long double)p * b + 1e-3) * p + p) % p;
}

int qpow(int base, int n, int mod) {
	int res = 1;
	while (n) {
		if (n & 1) res = 1ll * res * base % mod;
		base = 1ll * base * base % mod;
		n >>= 1;
	}
	return res;
}

struct NTT {
	static const int m1 = 469762049, m2 = 998244353, m3 = 1004535809, g = 3;
	static const ll M = 1ll * m1 * m2;
	int r[N], c[N], d[N], ans[3][N]; 
	void init(int fn, int fl) {
		for (int i = 0; i < fn; ++i) {
			r[i] = (r[i >> 1] >> 1) | ((i & 1) << (fl - 1));
		}
	}
	void work(int n, int *a, int opt, int mod) {
   		for (int i = 0; i < n; ++i)
   		    if (i < r[i]) swap(a[i], a[r[i]]);
   		for (int k = 1; k < n; k <<= 1)
   		    for (int i = 0, wn = qpow(g, (mod - 1) / (k << 1), mod); i < n; i += (k << 1))
   		        for (int j = 0, w = 1; j < k; ++j, w = 1ll * w * wn % mod) {
   		            int x = a[i + j], y = 1ll * w * a[i + j + k] % mod;
   		            a[i + j]= (x + y) % mod, a[i + j + k] = (x - y + mod) % mod;
   		        }
   		if (opt == -1) {
   		    a[0] = 1ll * a[0] * qpow(n, mod - 2, mod) % mod;
   		    for (int i = 1, inv = qpow(n, mod - 2, mod); i <= n / 2; ++i) {
   		        a[i] = 1ll * a[i] * inv % mod;
   		        if (i != n - i) a[n - i] = 1ll * a[n - i] * inv % mod;
   		        swap(a[i], a[n - i]);
   		    }
   		}
	}
	
	//满足模数可以分解成p = a2^k + 1形式
	void gao(int *a, int *b, int n, int m) {
		copy(a, a + n, c); copy(b, b + m, d); work(fn, c, 1, mod); work(fn, d, 1, mod);
		for (int i = 0; i <= fn; ++i) goal[i] = 1ll * c[i] * d[i] % mod;
		work(fn, goal, -1, mod);
	}
	//任意模数
	void gao2(int *a, int *b, int n, int m) {
		copy(a, a + n + 1, c), copy(b, b + m + 1, d), work(fn, c, 1, m1), work(fn, d, 1, m1);
    	for (int i = 0; i <= fn; ++i) ans[0][i] = 1ll * c[i] * d[i] % m1;
    	memset(c, 0, sizeof c), memset(d, 0, sizeof d);
    	copy(a, a + n + 1, c), copy(b, b + m + 1, d), work(fn, c, 1, m2), work(fn, d, 1, m2);
    	for (int i = 0; i <= fn; ++i) ans[1][i] = 1ll * c[i] * d[i] % m2;
    	memset(c, 0, sizeof c), memset(d, 0, sizeof d);
    	copy(a, a + n + 1, c), copy(b, b + m + 1, d), work(fn, c, 1, m3), work(fn, d, 1, m3);
    	for (int i = 0; i <= fn; ++i) ans[2][i] = 1ll * c[i] * d[i] % m3;
    	work(fn, ans[0], -1, m1), work(fn, ans[1], -1, m2), work(fn, ans[2], -1, m3); 
    	for (int i = 0; i <= n + m; ++i) {
    	    ll A = (mul(1ll * ans[0][i] * m2 % M, qpow(m2 % m1, m1 - 2, m1), M) +
    	                   mul(1ll * ans[1][i] * m1 % M, qpow(m1 % m2, m2 - 2, m2), M)) % M;
    	    ll k = ((ans[2][i] - A) % m3 + m3) % m3 * qpow(M % m3, m3 - 2, m3) % m3;
			goal[i] = ((k % mod) * (M % mod) % mod + A % mod) % mod;
    	}
	}
}ntt;

int main()
{
	while (scanf("%d%d", &n, &m) != EOF)
	{
		for (int i = 0; i <= n; ++i) scanf("%d", a + i);
		for (int i = 0; i <= m; ++i) scanf("%d", b + i); Hash();
		for (int i = 0; i <= n; ++i) l[a[i]].push_back(i);
		for (int i = 0; i <= m; ++i) r[b[i]].push_back(i);
		int len1 = n + 1, len2 = m + 1; fn = 1, fl = 0;
		while (fn < (len1 + len2)) fn <<= 1, ++fl;
		ntt.init(fn, fl);
		memset(ans, 0, sizeof ans);
		for (int i = 1; i <= n + m + 5; ++i) 
		{
			if (l[i].size() + r[i].size() < S)
			{
				for (auto u : l[i]) for (auto v : r[i])
					ans[u + v] = (ans[u + v] + (1ll * u * v) % mod) % mod; 
			}
			else
			{
				for (int j = 0; j < fn; ++j) x1[j] = 0;
				for (int j = 0; j < fn; ++j) x2[j] = 0;
				for (auto x : l[i]) x1[x] = x;
				for (auto x : r[i]) x2[x] = x;
			    ntt.gao(x1, x2, fn, fn);	
				for (int j = 0; j <= n + m; ++j) 
					ans[j] = (ans[j] + goal[j]) % mod;
			}
		}
		for (int i = 0; i <= n + m; ++i) 
			printf("%lld%c", ans[i] % mod, " \n"[i == n + m]);
	}
	return 0;
}
