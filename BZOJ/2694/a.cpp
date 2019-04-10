#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 4000010
const ll p = 1 << 30;
int mu[N], prime[N];
ll f[N];
bool check[N];
void init()
{
	memset(check, 0, sizeof check);
	prime[0] = 0; mu[1] = 1;
	for (int i = 2; i < N; ++i)
	{
		if (!check[i])
		{
			prime[++prime[0]] = i;
			mu[i] = -1;
		}
		for (int j = 1; j <= prime[0]; ++j)
		{
			if (1ll * i * prime[j] >= N) break;
			check[i * prime[j]] = 1;
			if (i % prime[j] == 0)
			{
				mu[i * prime[j]] = 0;
				break;
			}
			else
				mu[i * prime[j]] = -mu[i];
		}
	}
	memset(f, 0, sizeof f);
	for (int i = 1; i < N; ++i)
		for (int j = i; j < N; j += i) if (mu[i])
			f[j] += i * mu[j / i];
	for (int i = 2; i < N; ++i)
		f[i] = (f[i] + f[i - 1]); 
	
}

ll get(int x) { return (1ll * x * (x + 1) / 2) % p; }

ll work(int a, int b)
{
	if (a > b) swap(a, b);
	ll res = 0;
	for (int i = 1, j; i <= a; i = j + 1)  
	{
		j = min(a / (a / i), b / (b / i)); 
		res = (res + get(a / i)* get(b / i) % p * (f[j] - f[i - 1] + p) % p + p) % p;
	}
	return res; 
}

int main()
{
	init();
	int T; scanf("%d", &T);
	while (T--)
	{
		int n, m; scanf("%d%d", &n, &m);
		printf("%lld\n", work(n, m));
	}
	return 0;
}
