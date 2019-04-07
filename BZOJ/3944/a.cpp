#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 3000010
#define M 100010
int prime[N + 10];
ll phi[N + 10], mu[N + 10];
bool check[N + 10];
void init()
{
	memset(check, 0, sizeof check);
	prime[0] = 0;
	phi[1] = 1;
	mu[1] = 1;
	for (int i = 2; i < N; ++i)
	{
		if (!check[i])
		{
			prime[++prime[0]] = i;
			phi[i] = i - 1;
			mu[i] = -1;
		}
		for (int j = 1; j <= prime[0]; ++j)
		{
			if (1ll * i * prime[j] >= N) break;
			check[i * prime[j]] = 1;
			if (i % prime[j] == 0)
			{
				phi[i * prime[j]] = phi[i] * prime[j];
				mu[i * prime[j]] = 0;
				break;
			}
			else
			{
				phi[i * prime[j]] = phi[i] * (prime[j] - 1);
				mu[i * prime[j]] = -mu[i];	
			}
		}
	} 
	for (int i = 1; i < N; ++i)
	{
		phi[i] += phi[i - 1];
		mu[i] += mu[i - 1]; 	
	}
}

ll mp_phi[M], mp_mu[M]; int n; 
bool vis_phi[M], vis_mu[M];
ll get_phi(int x)
{
	if (x < N) return phi[x]; 
	int t = n / x;
	if (vis_phi[t])
		return mp_phi[t];
	vis_phi[t] = 1;
	ll tot = (1ll * x * (x + 1)) / 2;
	for (int i, j = 1; j < x; )
	{
		i = j + 1;
		j = x / (x / i);     
		tot -= 1ll * (j - i + 1) * get_phi(x / i);
	}
	return mp_phi[t] = tot;
}

ll get_mu(int x)
{
	if (x < N) return mu[x]; 
	int t = n / x; 
	if (vis_mu[t])
		return mp_mu[t]; 
	vis_mu[t] = 1;
	ll tot = 1;
	for (int i, j = 1; j < x; )
	{
		i = j + 1;
		j = x / (x / i);
		tot -= 1ll * (j - i + 1) * get_mu(x / i);
	}
	return mp_mu[t] = tot;
}

int main()
{
	init();
	int T; scanf("%d", &T);
	while (T--)
	{
		memset(vis_phi, 0, sizeof vis_phi);
		memset(vis_mu, 0, sizeof vis_mu);
		scanf("%d", &n);
		printf("%lld %lld\n", get_phi(n), get_mu(n));
	}
	return 0;
}
