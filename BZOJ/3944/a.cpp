#include <bits/stdc++.h>
using namespace std;

#define ll long long
//#define N 1000010
const int N = 1000010;
int prime[N + 10];
ll phi[N + 10], mu[N + 10];
bool check[N + 10];
void init()
{
	memset(check, 0, sizeof check);
	prime[0] = 0;
	phi[1] = 1;
	mu[1] = 1;
	for (int i = 2; i <= N; ++i)
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
	for (int i = 1; i <= N; ++i)
	{
		phi[i] += phi[i - 1];
		mu[i] += mu[i - 1]; 	
	}
}

map <ll, ll> mp_phi, mp_mu;
ll get_phi(ll x)
{
	if (x <= N) return phi[x];
	if (mp_phi[x])
		return mp_phi[x];
	ll tot = (1ll * x * (x + 1)) / 2;
	for (int i = 2, j; i <= x; i = j + 1)
	{
		j = x / (x / i);     
		tot -= 1ll * (j - i + 1) * get_phi(x / i);
	}
	return mp_phi[x] = tot;
}

ll get_mu(ll x)
{
	if (x <= N) return mu[x];
	if (mp_mu[x])
		return mp_mu[x]; 
	ll tot = 1;
	for (int i = 2, j; i <= x; i = j + 1)
	{
		j = x / (x / i);
		tot -= 1ll * (j - i + 1) * get_mu(x / i);
	}
	return mp_mu[x] = tot;
}

int main()
{
	init();
	int T; cin >> T;
	while (T--)
	{
		ll n; scanf("%lld", &n);
		printf("%lld %lld\n", get_phi(n), get_mu(n));
	}
	return 0;
}
